-- script object
-- a script is a graph of nodes
-- there is a START node with index 0
-- and a FINAL node with index -1
Script = {
	-- empty actions
	name = nil,
	actions = {},	
	edges = {},
	leaves = {},
	nextid = 0
}


function Script:dump() 

	--print ("Script: " .. self.name)
	print ("-*-*-*-*-*-*")
	print ("Actions:")
	for id,a in pairs(self.actions) do
		print (string.format("%-5s%-10s", id, a.type))
	end
	print ("-*-*-*-*-*-*")
	print ("Edges:")
	for id, e in pairs(self.edges) do
		io.write(string.format("%-5d{",id))
		for _, a in ipairs(e) do
			local del = ", "
			if (next(e,_) == nil) then
				del = "}"
			end
			io.write (a .. del)
		end
		print ()
	end	
	print ("-*-*-*-*-*-*")
	print (string.format("%-20s%-10s%-10s","Subscript","Start","End"))
	for id, l in pairs(self.leaves) do 
		io.write (string.format("%-20s%-10d%-10d", id, l[1], l[2]))
		print("")
	end
	
end

-- create a new script with a given name
function Script:new() 
	s = {}
	setmetatable (s, self)
	self.__index = self
	-- at beginning, beginning and end are both at id 0
	-- add a noop. You can overwrite it if you don't need it
	s.actions = { [0] = {type = "noop"} }
	s.edges = {}
	s.leaves = {}
	s.nextid = 1
	return s
end

-- push actions 
function Script:push (args) 
	-- if no after/before is provided, it adds to 0
	local parent = 0
	if (args.after ~= nil) then
		parent = self.leaves[args.after][2]
	elseif (args.before ~= nil) then
		parent = self.leaves[args.before][1]
	end
	local lv = {}
	local newNext = self.nextid
	for id, action in pairs(args.actions) do
		local newId = self.nextid + id
		self.actions[self.nextid + id] = action
		newNext = math.max(newNext, newId)
		lv[newId] = true
		-- see if it has parents
		if (action.after ~= nil) then
			for _, desc in ipairs(action.after) do
				local tail = self.nextid + desc
				self:addEdge { from = tail, to = newId }
				if (lv[tail] == true) then
					lv[tail] = nil
				end
			end
		else
			self:addEdge {from=parent, to = newId}
		end
	end
	-- add a final node 
	newNext = newNext + 1
	self.actions[newNext] = { type ="noop" }
	for id, desc in pairs(lv) do
		self:addEdge { from = id, to = newNext }
	end
	
	if (args.name ~= nil) then
		self.leaves[args.name] = {parent, newNext}
	end
	self.nextid = newNext+1
end

function Script:addEdge(args) 
	if (self.edges[args.from] == nil) then
		self.edges[args.from] = {}
	end
	table.insert(self.edges[args.from], args.to)
end