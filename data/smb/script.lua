
-- script object
-- a script is a graph of nodes
-- there is a START node with index 0
-- and a FINAL node with index -1
Script = {
	-- empty actions
	name = nil,
	actions = {},	
	edges = {},
	leaves = {}
}


function makeId(name, id) 
	return (name .. "@" .. tostring(id))
end

function Script:dump() 

	print ("Script: " .. self.name)
	print ("-*-*-*-*-*-*")
	print ("Actions:")
	for id,a in pairs(self.actions) do
		print (string.format("%-20s%-10s", id, a.type))
	end
	print ("-*-*-*-*-*-*")
	print ("Edges:")
	for id, e in pairs(self.edges) do
		io.write(string.format("%-20s{",id))
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
	print ("Leaves:")
	for id, l in pairs(self.leaves) do 
		io.write (string.format("%-20s", id))
		for leaf,v in pairs(l) do
			local del = ", "
			if (next(l,_) == nil) then
				del ="}"
			end
			io.write (tostring(leaf) .. del)
		end
		print ""
	end

end

-- create a new script with a given name
function Script:new(name) 
	s = {}
	setmetatable (s, self)
	self.__index = self
	s.name = name
	s.leaves[name] = {}
	-- add a noop. You can overwrite it if you don't need it
	s:push ({ [0] = { type="noop"}})
	
	return s
end

-- push actions
function Script:push (actions) 
	for id, action in pairs(actions) do
		--print (self.name)
		local newNodeId = makeId(self.name, id)
		self.actions[newNodeId] = action
		if (action.desc ~= nil) then
			for _, desc in ipairs(action.desc) do
				self:addEdge { from = {self.name, desc}, to = {self.name, id}}
			end
		end
		-- when a node is inserted, by definition it is a leaf
		self.leaves[self.name][id] = true
	end


end

function Script:addEdge(args) 
	local fromId = makeId(args.from[1], args.from[2])
	local toId = makeId(args.to[1], args.to[2])
	if (self.edges[fromId] == nil) then
		self.edges[fromId] = {}
	end
	table.insert(self.edges[fromId], toId)
	if ((args.from[1] == args.to[1]) and self.leaves[args.from[1]][args.from[2]]) then
		self.leaves[args.from[1]][args.from[2]] = nil
	end
end

-- adds another script after a given node(s)
-- script = the script to add
-- after (optional) = x if this script is supposed to start AFTER the given script

function Script:add (args) 
	
	-- if there are no actions here, update the name
	local script = args.script
	if (next(self.actions) == nil) then
		self.name = script.name
	end
	-- step 1, copy all the activies and edges of the script into this script
	for id, action in pairs(script.actions) do
		self.actions[id] = action
	end
	for tail, heads in pairs(script.edges) do
		self.edges[tail] = heads
	end

	-- add edges connecting the existing graph to the new sub-graph


	
	if (args.after ~= nil) then
		local leaves = self.leaves[args.after]
	
		for leaf,v in pairs(leaves) do
			self:addEdge { from = {args.after, leaf}, to = {script.name, 0} }	
		end
	else
		-- mmmh, problem
	end
	-- for _, node in ipairs(after)  do
	-- 	local id = makeId(node[1], node[2])
	-- 	if (self.edges[id] == nil) then
	-- 		self.edges[id] = {}
	-- 	end
	-- 	table.insert(self.edges[id], makeId(script.name, 0))
	-- end
end

-- a = Script:new("ciao")
-- a:dump()
-- b = Script:new("c1")
-- b:push({
-- 	[0] = { type = "walkto" },
--  	[1] = { type = "ciao", desc={0} },
--  	[2] = { type = "say", desc={1} }
--  })

-- c = Script:new("c2")
-- c:push({
--  	[0] = { type = "go" },
--  	[1] = { type = "hi", desc={0} },
--  	[2] = { type = "tell", desc={1} }
-- })
-- a:add { script = b, after = "ciao"}
-- a:add { script = c, after = "ciao"}
-- a:dump()