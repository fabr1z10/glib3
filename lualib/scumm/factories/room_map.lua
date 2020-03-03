function scumm.factory.room_map (args) 
	
	glib.assert(args.width, 'required width')
	glib.assert(args.height, 'required height')

	local room_width = args.width
	local room_height = args.height
	local camWidth = engine.device_size[1]
	local camHeight = engine.device_size[2]
	local font_size = args.font_size or 8

	local p = Room:new(args)


	print ("NOW SCENE HAS SIZE:"..tostring(#p.scene))
	-- add the main scene
	table.insert (p.scene, {
		tag = "main",
		camera = {
			tag = "maincam",
			type="ortho",
			size = {camWidth, camHeight},
			bounds = {0, 0, room_width, room_height},
			viewport = {0, 0, camWidth, camHeight}
		},
		children = {}
	})
	
	p.refs['main'] = p.scene[1].children

	p:add_walkareas(args)
	p:load_dynamic_items()

	return p
end

-- function scumm.factory.map_room (args) 
-- 	-- validation phase
-- 	glib.assert(args.width, "width")
-- 	glib.assert(args.height, "width")
-- 	--glib.assert(args.font_size, "font_size")

-- 	local room_width = args.width
-- 	local room_height = args.height
-- 	local camWidth = engine.device_size[1]
-- 	local camHeight = engine.device_size[2]

-- 	local p =  {
-- 		afterstartup = function()
-- 			for k, v in ipairs(room.initstuff) do
-- 				v()
-- 			end
-- 			--if (variables.troll_fed==false) then troll() end
-- 		end,
-- 		initstuff = {
-- 		},
-- 		engines = {
-- 			-- keyboard listener for pause
-- 			{
-- 			 	type = "keylistener",
-- 			 	keys = {
-- 			 		{ key = 32, func = scumm.func.toggle_pause }
-- 			 	}
-- 			},
-- 			{ 
--                 type = "hotspotmanager", 
-- 			    keys = {
-- 				    { key = 299, func = function() print("restart!") end },
-- 			    },
-- 				lmbclick = function(x, y)
-- 					if (scumm.state.lmboverride ~= nil) then
-- 						engine.state.scumm.lmboverride()
-- 						return
-- 					end
-- 					if (scumm.state.walk_enabled == true and scumm.state.actionInfo.verb == "walk") then
-- 						scumm.func.walk(x, y) 
-- 					end
-- 				end,	 
-- 			},
-- 			{ 
-- 				type = "scheduler" 
-- 			}
-- 		},
-- 		scene = {
-- 			{
-- 				tag = "main",
-- 				camera = {
-- 					tag = "maincam",
-- 					type="ortho",
-- 					size = {camWidth, camHeight},
-- 					bounds = {0, 0, room_width, room_height},
-- 					viewport = {0, 0, camWidth, camHeight}
-- 				},
-- 				children = {}
-- 			},
-- 			{
-- 					tag = "diag",
-- 					camera = {
-- 						tag = "maincam",
-- 						type="ortho",
-- 						size = {320, 200},
-- 						bounds = {0, 0, 320, 200},
-- 						viewport = {0, 0, 320, 200}
-- 					},
-- 					children = {
-- 						-- { 
-- 					 --    	tag = "cursor",
-- 					 --    	pos={0,0,0},
-- 						-- 	components = {
-- 					 --    		{ type="text", id = "prova", font="monkey", align = "bottom", color = engine.config.ui_currentaction_color},
-- 						-- 		{ type="cursor"}
-- 						-- 	}
-- 						-- }
-- 					}
-- 			}

-- 		}
-- 	}

-- 	if (args.collide == true) then
-- 		table.insert (p.engines, 
-- 			{ 
-- 				type = "collision", 
-- 				size = {128, 128}, 
-- 				response = {
-- 					{ tag = {1, 2}, onenter=function(e,f) 

-- 							local info = f:getinfo()
-- 							if (info.onenter ~= nil) then
-- 								info.onenter()
-- 							end
-- 					 end}
-- 				}
-- 			}
-- 		)
-- 	end

-- 	local refs = {
-- 		main = p.scene[1].children,
-- 	}

-- 	if args.walkareas then
-- 		for _, w in ipairs(args.walkareas) do
-- 			tmp = scumm.factory.object { id = w}
-- 			table.insert (refs.main, tmp)
-- 			tmp.children = {}
-- 			refs[w] = tmp.children
-- 		end
-- 	end

-- 	function p:add(to, items) 
-- 		for k,v in ipairs(items) do
-- 			table.insert(refs[to], v)
-- 		end
-- 	end

-- 	return p
-- end