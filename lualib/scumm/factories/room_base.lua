function scumm.factory.room_base (args) 

	-- validation phase
	glib.assert(args.width, "width")
	glib.assert(args.height, "width")
	--glib.assert(args.defaultroom, "Room requires <defaultroom>")
	
	local font_size = args.font_size or 8

	scumm.state.walk_enabled = true

	local room_width = args.width
	local room_height = args.height

	local camWidth = engine.device_size[1]
	local camHeight = engine.device_size[2] - engine.config.ui.height

	local p =  {
		afterstartup = function()
			for k, v in ipairs(room.initstuff) do
				v()
			end
		end,
		items = {},
		dialogues = {},
		scripts = {},
		startPos = startPos,
		initstuff = {
			[1] = function() 
				scumm.state.actionInfo.verb = engine.config.default_verb
				scumm.script.reset_verb()
				scumm.script.refresh_inventory()
			end
		},
		engines = {
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
						scumm.script.walk(x, y) 
					end
				end,	 
			},
			{ 
				type = "scheduler" 
			}
		},
		scene = {
			{
				tag = "main",
				camera = {
					tag = "maincam",
					type="ortho",
					size = {camWidth, camHeight},
					bounds = {0, 0, room_width, room_height},
					viewport = {0, engine.config.ui.height, camWidth, camHeight}
				},
				children = {}
			},
			{
			 	tag = "ui",
			 	-- camera = {
			 	-- 	tag = "uicam",
			 	-- 	type="ortho",
			 	-- 	size = {camWidth, engine.config.ui.height},
			 	-- 	bounds = {0, 0, camWidth, engine.config.ui.height},
			 	-- 	viewport = {0, 0, camWidth, engine.config.ui.height}
			 	-- },
			 	children = {
			 		{
			 			tag = "mainui",
			 			pos = {0,0,0},
			 			children = {
			 				{
			 					tag = "verbs",
							 	camera = {
							 		tag = "uicam",
							 		type="ortho",
							 		size = {camWidth, engine.config.ui.height},
							 		bounds = {0, 0, camWidth, engine.config.ui.height},
							 		viewport = {0, 0, camWidth, engine.config.ui.height}
							 	},
							 	children = {
							 		{
							 			type = "text",
					 			    	tag = "currentaction",
					 			    	font = engine.config.ui.font,
					 			    	text = engine.config.verbs[engine.config.default_verb].text,
					 			    	align = "bottom",
					 			    	color = engine.config.ui.currentaction_color,
					 			    	pos={160,48,0}
					 				}							 		
							 	}
			 				},
			 			 	{
							 	pos = {0,0,0},
							 	children =  {
			 			 			{
					 	 				type = 'textview', 
					 	 				tag = 'inventory',
					 	 				pos = {150, 0, 0},
					 	 				size = {170, 48},
					 	 				font_size = 8,
					 	 				lines = 6,
					 	 				deltax = 26,
					 	 				factory = scumm.factory.inventorybutton
					  				}
					 			}
							}
			 			}
			 		},
					{
						pos  = {0,0,0},
						children =  {
			 				{
					 			type = 'textview', 
					 			tag = 'dialogueui',
					 	 		pos = {0, 0, 0},
					 	 		size = {320, 56},
					 	 		font_size = 8,
					 	 		lines = 6,
					 	 		deltax = 26,
					 	 		factory = scumm.factory.dialoguebutton
					  		}
					 	}						
					}			 		
		 		
				}
			},
			{
				tag ="other",
				camera = {
					tag = "othercam",
					type="ortho",
					size = engine.device_size,
					bounds = {0, 0, engine.device_size[1], engine.device_size[2]},
					viewport = {0, 0, engine.device_size[1], engine.device_size[2]}
				},
				children = {}
			
			}
		}
	}

	if (args.collide == true) then
		table.insert (p.engines, 
			{ 
				type = "collision", 
				size = {128, 128}, 
				response = {
					{ tag = {1, 2}, onenter=function(e,f) 

							local info = f:getinfo()
							if (info.onenter ~= nil) then
								info.onenter()
							end
					 end}
				}
			}
		)
	end

	local refs = {
		main = p.scene[1].children,
		ui = p.scene[2].children[1].children[1].children
	}

	if args.walkareas then
		for _, w in ipairs(args.walkareas) do
			tmp = scumm.factory.object { id = w}
			table.insert (refs.main, tmp)
			tmp.children = {}
			refs[w] = tmp.children
		end
	end

	-- add the verbs
	local row = 2
	local count = 0
	
	for _, verb in ipairs(engine.config.verbset[1]) do
	 	local col = 1+ count // 4
	 	local x = 2 + (col-1)*46
	 	local y = engine.config.ui.height - row*font_size
	 	row = row + 1
	 	if (row > 5) then row = 2 end
	 	count = count +1
	 	table.insert (refs.ui,scumm.factory.verbbutton {pos={x, y}, verb = verb} )
	end

	function p:add(to, items) 
		for k,v in ipairs(items) do
			--print (refs[to].tag)
			--print ('addddd ' .. v.model .. " " .. v.type)
			table.insert(refs[to], v)
		end
	end

	scumm.state.actionInfo.verb = engine.config.default_verb

	return p
end