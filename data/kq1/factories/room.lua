-- Basic room 
function scumm.factory.sci_room (args) 
	local room_width = args.width
	local room_height = args.height
    -- init verb
    engine.state.scumm.actionInfo.verb = engine.config.default_verb
	engine.state.scumm.play = true
	-- determine start position
	local startPos = nil
	if (args.startTable ~= nil) then
		startPos = args.startTable[engine.state.previousRoom]
		if (startPos == nil) then
			startPos = args.startTable[args.defaultroom]
		end	
	else

	end


	local p =  {
		afterstartup = function()
			for k, v in ipairs(room.initstuff) do
				v()
			end
		end,
		initstuff = {},
		engines = {
			{ type = "scheduler" },
	 		{ 
	 			type = "collision", 
 				size = {80, 80}, 
	 			response = args.collision_response,
	 			coll25 = args.coll25,
				response = {
					{ tag = {1, 10}, onenter = factory.response.basic },
				}
	 			--{
	 			--		{ tag = {1, 10}, onenter = function() print ("CIAO") end }
	 			--}
	 		},			
			{ 
				type = "hotspotmanager",
				tag ="_hotspotmanager", 
				keys = {
					{ key = 299, func = function() monkey.endroom() end },
					{ key = 257, func = function() if (engine.config.pause == true) then exitpause() end end},
					{ key = 258, func = function() if (engine.config.pause == false) then displayInventory() end end }
				},
				-- lmbclick is the func called when you click on no hotspot
				lmbclick = function(x, y) 
					if (engine.state.scumm.actionInfo.verb == "walk" and engine.state.scumm.play == true) then
						--print ("CUIAO")
						local actions = scumm.ui.walk { pos = {x,y} }
						local s = script.make(actions)
						s.name="_walk"
						monkey.play(s)
					end
				end,	
				rmbclick = function() 
 					local current = glib.get(engine.config.verb)
 					local v = glib.get (engine.config.verbs[current].next)
 					print ("NEXT IS " .. v)
 					engine.config.verb = v
 					engine.state.scumm.actionInfo.verb = engine.config.verbs[v].code
 					--print ("current verb = " .. variables._actionInfo.verb.code)
 					local cursor = monkey.getEntity("cursor")
 					local a=engine.config.verbs[v].anim
 					cursor.anim = a
				end
			},
		},
		scene = {
			{
				tag = "main",
	 			camera = {
 					tag = "maincam",
 					type="ortho",
 					size = {room_width, room_height},
 					bounds = {0, 0, room_width, room_height},
 					viewport = {0, 0, room_width, room_height}
 				},
				children = {
				}
				
			},
			{
				tag = "diag",
				camera = {
					tag = "maincam",
 					type="ortho",
 					size = {320, 200},
					bounds = {0, 0, 320, 200},
 					viewport = {0, 0, 320, 200}
 				},
 				children = {
 					{ 
 						type = "sprite",
 					 	model="cursor",
 				     	tag = "cursor",
 		 		    	pos={0,0,5},
 					 	components = {
 							{ type="cursor"}
 					 	}
 					}
 				}
 			}	
		}
	}

	local refs = {
		main = p.scene[1].children,
		diag = p.scene[2].children
	}
	-- add the walkarea(s)
	if (args.walkareas) then
		for _, wa in ipairs(args.walkareas) do
			print (wa)
			local tmp = scumm.factory.object { id = wa, pos ={0,0,-3}}
			table.insert (refs.main, tmp)
			refs[wa] =  tmp.children
		end

		-- adding player
		print("ciao = "..tostring(startPos.pos[1]))
		print("ciao = "..tostring(startPos.pos[2]))
		print(startPos.walkarea)
		local w1 = refs[startPos.walkarea]
		if (args.playerid) then
			table.insert(w1,  
				scumm.factory.object { 
					id=args.playerid,
					pos={startPos.pos[1], startPos.pos[2], 0}, 
					tag="player", 
					dir = startPos.dir,
					follow = (room_width > 320 and enableScroll),
					collide = args.collide
				}
			)
		end
	end


	-- if (p.startPos.func ~= nil) then
	--  	table.insert(p.initstuff, p.startPos.func)
	--  end
	


	function p:add(to, items) 
		for k,v in ipairs(items) do
			print ("ciaociao")
			print (refs[to].tag)
			table.insert(refs[to], v)
		end
	end

	return p
end
