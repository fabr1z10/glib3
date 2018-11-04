
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
			for _, p in ipairs(a.after) do
				table.insert(t, p)
				table.insert(t, ", ")
			end
			table.remove(t)
		end
		table.insert(t, "}")
		print (string.format("%-5s%-10s%-20s", id, a.type, table.concat(t)))
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

-- push another script 
-- call ike s:push { script = a, parent = node }
function script:push (args) 
	if (args.script == nil) then
		return
	end
    -- append an array to another
	local offset = #self.actions
	if (args.id ~= nil) then
		self.offset[args.id] = offset
	end
	print ("Appending script with " .. #args.script.actions .. " actions.")
	print ("Current script has  " .. offset .. " actions.")
	if (args.at ~= nil) then
		if (args.at == "beginning") then
			parent = (offset == 0) and 0 or 1
		elseif (args.at == "end") then
			parent = offset
		end
	end
	print ("Parent node is " .. parent)
	local leaves = {}
    for k, v in ipairs(args.script.actions) do
		leaves[offset+k] = true
	end

    for k, v in ipairs(args.script.actions) do
		print (k .. v.type)
		if (v.after == nil) then
			if (parent ~= 0) then
				v.after = {parent}	
			end
		else
			for a,b in ipairs(v.after) do
				v.after[a] = offset+b
				if (leaves[offset+b] == true) then
					print ("removing " .. (offset+b))
					leaves[offset+b] = nil
				end
			end
		end
		self.actions[offset + k] = v
	end
print ("CIAO")
	-- add fake action at the end so that the last node always corresponds to the end of the script
	local after = {}
	for k, _ in pairs(leaves) do
		after[#after+1]=k
	end

	self.actions[#self.actions+1] = { type = "noop", after = after }
end