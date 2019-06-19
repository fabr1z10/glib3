
-- a script is just a wrapper for an array of actions. Each action has an after field which links it to other actions in a graph-like
-- structure
script = {
	-- empty actions
	name = nil,
	actions = {},
	offset = {}
}


function script:dump() 
	
	print ("Script: " .. ((self.name == nil) and "*** unknown ***" or self.name))
	print (string.format("%-5s%-10s%-20s", "id", "action", "predecessors"))
	for id, a in ipairs(self.actions) do
		local t = { "{" } 
		if (a.after ~= nil) then
			for _, p in pairs(a.after) do
				table.insert(t, p)
				table.insert(t, ", ")
			end
			table.remove(t)
		end
		table.insert(t, "}")
		print (string.format("%-5s%-10s%-20s", a.id, a.type, table.concat(t)))
	end	
end

-- create a new script with a given name
function script:new(name) 
	s = {}
	setmetatable (s, self)
	self.__index = self
	-- at beginning, beginning and end are both at id 0
	-- add a noop. You can overwrite it if you don't need it
	s.name = name
	s.actions = {}
	s.offset ={}
	return s
end

function script:getid(name, id)
	return self.offset[name] + id
end

function shallowcopy(orig)
    local orig_type = type(orig)
    local copy 
    if orig_type == 'table' then
        copy = {}
        for orig_key, orig_value in pairs(orig) do
			if (orig_key=="after") then
				copy.after= {}
				for _,b in ipairs(orig_value) do
					table.insert(copy.after, b)
				end
			else
            	copy[orig_key] = orig_value
			end
        end
    else -- number, string, boolean, etc
        copy = orig
    end
    return copy
end

-- push another script 
-- call ike s:push { script = a, parent = node }
function script:push (args) 
	local at = args.at
	if (at == nil) then at = "end" end
	--print ("** push a script at the end of another...")
	if (args.script == nil) then
		return
	end
	if (self.actions == nil or #self.actions == 0) then
		print ("Start script has no actions!")
		self.actions = args.script.actions
		return
	end
	local idmax = -1
	local leaves = {}
	print (tostring(#self.actions))
	for k, v in ipairs(self.actions) do
		idmax = math.max(idmax, v.id)
		leaves[v.id] = 1
		--table.insert(leaves, v.id)
	end
	-- find leaves
	for k, v in ipairs(self.actions) do
		if (v.after ~= nil) then
			for i, j in ipairs(v.after) do
				leaves[j] = nil
			end
		else
			if (v.id>1) then
				leaves[v.id-1]=nil
			end
		end
	end

	for k, v in ipairs(args.script.actions) do
		-- copy the action
		local vc = shallowcopy(v)
		local lid = vc.id
		vc.id = idmax + vc.id
		if (lid == 1) then
			if (at == "end") then
				vc.after = {}
				for k, _ in pairs(leaves) do
					table.insert(vc.after, k)
				end
			else
				vc.after={1}
			end
		else
			if (vc.after ~= nil) then
				for i,j in ipairs(vc.after) do
					vc.after[i] = vc.after[i] + idmax
				end
			end
		end
		table.insert(self.actions, vc)
	end
	if (args.script.loop ~= nil) then
		self.loop = idmax + args.script.loop
	end
--     -- append an array to another
-- 	local offset = #self.actions
-- 	if (args.id ~= nil) then
-- 		self.offset[args.id] = offset
-- 	end
-- 	print ("Appending script with " .. #args.script.actions .. " actions.")
-- 	print ("Current script has  " .. offset .. " actions.")
-- 	if (args.at ~= nil) then
-- 		if (args.at == "beginning") then
-- 			parent = (offset == 0) and 0 or 1
-- 		elseif (args.at == "end") then
-- 			parent = offset
-- 		end
-- 	end
-- 	print ("Parent node is " .. parent)
-- 	local leaves = {}
--     for k, v in ipairs(args.script.actions) do
-- 		leaves[offset+k] = true
-- 	end

--     for k, v in ipairs(args.script.actions) do
-- 		print (k .. v.type)
-- 		if (v.after == nil) then
-- 			if (parent ~= 0) then
-- 				v.after = {parent}	
-- 			end
-- 		else
-- 			for a,b in ipairs(v.after) do
-- 				v.after[a] = offset+b
-- 				if (leaves[offset+b] == true) then
-- 					print ("removing " .. (offset+b))
-- 					leaves[offset+b] = nil
-- 				end
-- 			end
-- 		end
-- 		self.actions[offset + k] = v
-- 	end
-- print ("CIAO")
-- 	-- add fake action at the end so that the last node always corresponds to the end of the script
-- 	local after = {}
-- 	for k, _ in pairs(leaves) do
-- 		after[#after+1]=k
-- 	end

-- 	self.actions[#self.actions+1] = { type = "noop", after = after }
end

function isarray(t) 
    return (type(t)=="table" and t[1] ~= nil)
end

function flatten_script(a, offset) 
    local out = {}
	local ref_id = {}
	local id = offset
    for _, v in ipairs(a) do
        if (isarray(v)) then
            --print (tostring(v) .. " is an array")
            tmp = flatten_script(v, id)
			-- copy all ref id 
			for k, v in pairs(tmp[2]) do
				ref_id[k] = v
			end
            for _, j in ipairs(tmp[1]) do
               table.insert(out, j)
            end
			id = tmp[1][#tmp[1]].id
        else
            --print (tostring(v) .. " is not an array")
			if (v.type ~= nil) then
				id = id + 1
				local node = { id = id, action = v.type(v.args) }
				if (v.ref ~= nil) then
					ref_id[v.ref] = id
				end
				if (v.after ~= nil) then 
					node.after = {}
					for _, ref in ipairs(v.after) do
						table.insert (node.after, ref_id[ref])
					end
				else
					if (id > 0) then
						node.after = { id-1 } 
					end
				end
	            table.insert(out, node)
			end
        end
    end
    return {out, ref_id}
end

function ms2(args, loop)

    local s = script:new()
	local data = flatten_script (args, 0) 
	s.actions = data[1]
	if (loop ~= nil) then
		s.loop = data[2][loop]
		print ("script has loop at ref = " .. tostring(loop) .. " which corresponds to id = " .. tostring(s.loop))
	end
		
	-- just for debug. print action
	for _,v in pairs(s.actions) do 
		local sa = ""
		if (v.after == nil) then
			sa = (v.id == 1) and "-" or "{" .. tostring(v.id-1) .. "}"
		else
			sa = tostring(#(v.after)) .. "{"
			for _, after in ipairs(v.after) do
				sa = sa .. tostring(after) .. ", "
			end
			sa = sa .. "}"
		end
		--print ("id = " .. tostring(v.id) .. ", after = " .. sa .. ", type = " .. v.action.type)	
	end
    return s
end