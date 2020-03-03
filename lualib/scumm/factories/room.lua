Room = {}

Room.__index = Room

function Room.afterstartup()
	for k, v in ipairs(room.initstuff) do v() end
end

function Room:add(to, items) 
	for k,v in ipairs(items) do
		print ('do i have .. ' .. to)
		if (self.refs[to]) then print ('YES!') end
		table.insert(self.refs[to], v)
		print ('now ' .. to .. ' has ' ..tostring(#self.refs[to]) .. ' children')
	end
end

function Room:load_dynamic_items()
	local di = variables.dynamic_items[self.id]
	if di then
		local it = {}
		for id, item in pairs(di) do
			print ('adding ' .. id)
			local tag = (id == variables.current_player) and 'player' or nil
			local follow = (id == variables.current_player) and true or nil
			local obj = scumm.factory.object { id = id, params = { pos = item.pos, dir = item.dir, tag = tag, follow=follow }}
			table.insert(it, obj)
			local parent = item.wa 
			if not parent then
				parent = (self.walkareas and self.walkareas[1] or 'main')
			end
			print ('to ... '.. parent)
			self:add(parent, { obj })
		end
	end
end

function Room:add_walkareas(args) 
	-- add walkareas if any
	if args.walkareas then
	    for _, w in ipairs(args.walkareas) do
		    tmp = scumm.factory.object { id = w}
		    tmp.children = {}
		    self:add('main', {tmp})
		    self.refs[w] = tmp.children
		end
	end		
end

function Room:new(args)
	glib.assert (args.id, 'You need an id to create a room!')

	local r = setmetatable({}, Room)
	r.initstuff = {}
	r.engines = {
	    -- keyboard listener for pause
		{
		    type = "keylistener",
			keys = {
			    { key = 32, func = scumm.func.toggle_pause }
			}
		},
		{ 
            type = "hotspotmanager", 
		    keys = {
			    { key = 299, func = function() print("restart!") end },
		    },
			lmbclick = function(x, y)
				if (scumm.state.lmboverride ~= nil) then
					print ("Override")
					engine.state.scumm.lmboverride()
					return
				end
				if (scumm.state.walk_enabled == true and scumm.state.actionInfo.verb == "walk") then
					scumm.func.walk(x, y) 
				end
			end,	 
		},
		{ 
			type = "scheduler" 
		}
	}
	r.scene ={}
	r.refs ={}
	--glib.assert(args.defaultroom, "Room requires <defaultroom>")
	
	local font_size = args.font_size or 8

	scumm.state.walk_enabled = true



	--r.refs['main'] = r.scene[1].children
	r.id = args.id
	r.walkareas = args.walkareas

	-- add collision detection if required
	if args.collide then
		table.insert (r.engines, 
		{ 
			type = "collision", 
			size = {128, 128}, 
			response = {
				{ tag = {1, 2}, onenter=function(e,f) 
					local info = f:getinfo()
					if (info.onenter ~= nil) then
						info.onenter()
					end
				end }
			}
		})
	end


	return r

end