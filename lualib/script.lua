print ("Loading <script> lib")
-- a script is just a wrapper for an array of actions. Each action has an after field which links it to other actions in a graph-like
-- structure
script = {
	-- empty actions
	name = nil,
	actions = {},
	offset = {}
}

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

function flatten_script(a, offset) 
    local out = {}
	local ref_id = {}
	local id = offset
    for _, v in ipairs(a) do
        if (glib.isarray(v)) then
            --print (tostring(v) .. " is an array")
            tmp = flatten_script(v, id)
			-- copy all ref id 
			for k, v in pairs(tmp[2]) do
				print (v)
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
				--print ("qui")
				if (v.ref ~= nil) then
					print ("ciao " .. v.ref .. " ciao")
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


script.make = function(args, loop)
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

