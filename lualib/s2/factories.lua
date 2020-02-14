-- Basic room 

function scumm.func.toggle_pause () 
	scumm.state.game_paused = not scumm.state.game_paused;
	print ("toggling pause, now " .. tostring(scumm.state.game_paused))
	-- local p = monkey.getEntity("main")
	-- local ui = monkey.getEntity("ui")
	-- monkey.enablescriptengine(not engine.state.scumm.game_paused)

	-- p:enableupdate(not engine.state.scumm.game_paused)
	-- ui:enableupdate(not engine.state.scumm.game_paused)
 --   	--p:setactive(not engine.state.scumm.game_paused)
 --   	--ui:setactive(not engine.state.scumm.game_paused)
 --   	engine.state.scumm.game_paused = not engine.state.scumm.game_paused
end

-- this func gets the id of the template


function scumm.factory.object (args)
	
	glib.assert(args.id, 'required item <id>')
	print (args.id)
	local item = engine.items[args.id]

	if not item then error("Hey! Don't know item: " .. args.id, 1) end

	local f = scumm.ifac.fmap[item.type]
	if not f then error("Unknown factory func for item: " .. args.id,1) end

	--local tag = nil
	--i-f item.tag then 
	--	tag = args.id
	--end

	-- 1. if args.params.tag is specified nothing to do
	-- 2. if not specified, and item 
	local params = args.params or {}
	if not params.tag and item.tag then params.tag = args.id end

	params._id = args.id
	return f { item = item, args = params }


end

function scumm.factory.basic_room (args) 
	-- validation phase
	glib.assert(args.width, "width")
	glib.assert(args.height, "width")
	glib.assert(args.defaultroom, "Room requires <defaultroom>")
	
	local font_size = args.font_size or 8

	scumm.state.walk_enabled = true

	local room_width = args.width
	local room_height = args.height

	local camWidth = engine.device_size[1]
	local camHeight = engine.device_size[2] - engine.config.ui.height

	-- the initial position of the player depends on the previous room.
	-- a start location might be used
	local start_pos = nil
	if args.startTable then
		print ("CICICICI")
		local proom = (engine.state.previousRoom == '') and args.defaultroom or engine.state.previousRoom
		start_pos = args.startTable[proom]
		if not start_pos then error ("Unable to find start position for " .. proom, 1) end
	end

	local enableScroll = args.enableScroll
	if (enableScroll == nil) then enableScroll = true end
	
	local p =  {
		afterstartup = function()
			for k, v in ipairs(room.initstuff) do
				v()
			end
			--if (variables.troll_fed==false) then troll() end
		end,
		items = {},
		dialogues = {},
		scripts = {},
		startPos = startPos,
		initstuff = {
			[1] = function() 
				scumm.state.actionInfo.verb = engine.config.default_verb
				--scumm.ui.updateVerb() 
				--scumm.ui.refresh_inventory()
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
			 			-- 	{
							-- 	pos = {0,0,0},
							-- 	children =  {
			 			-- 			{
					 	-- 				type = "textview", 
					 	-- 				tag="inventory",
					 	-- 				pos = {150, 0, 0},
					 	-- 				size = {170, 48},
					 	-- 				font_size = 8,
					 	-- 				lines = 6,
					 	-- 				deltax = 26,
					 	-- 				factory = scumm.factory.inventorybutton
					  --  				},
							-- 	}
							-- }
			 			}
			 		},
			 		-- {
						-- pos  = {0,0,0},
						-- children = {
						-- 	{
						-- 		tag = "dialogueui",
						-- 		type = "textview", 
						-- 		pos = {0, 0},
						-- 		size = {320, 56},
						-- 		font_size = 8,
						-- 		lines = 6,
						-- 		deltax = 26,
						-- 		factory = scumm.factory.dialoguebutton
						-- 	}
						-- }
			 		-- }			 		
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

	if start_pos then
		print ("ADDDD")
		table.insert (refs[start_pos.walkarea], scumm.factory.object {
			id = args.playerid,
			params = {
				tag = 'player',
				pos = start_pos.pos,
				dir = start_pos.dir
			}
		})
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

	-- -- add the walkarea(s)
	-- if (args.walkareas) then
	-- 	for _, wa in ipairs(args.walkareas) do
	-- 		local tmp = scumm.factory.object { id = wa }
	-- 		table.insert (refs.main, tmp)
	-- 		refs[wa] =  tmp.children
	-- 	end

	-- 	-- adding player
	-- 	if (startPos) then
	-- 		local w1 = refs[startPos.walkarea]
	-- 		table.insert(w1,  
	-- 			scumm.factory.object { 
	-- 				id=args.playerid,
	-- 				pos={startPos.pos[1], startPos.pos[2], 0}, 
	-- 				tag="player", 
	-- 				dir = startPos.dir,
	-- 				follow = (room_width > 320 and enableScroll),
	-- 				collide = args.collide
	-- 			}
	-- 		)
	-- 	end
	-- end

	-- --table.insert (refs.ui,scumm.factory.verbbutton {pos={2, 40}, verb = "open"} )

	-- if (p.startPos and p.startPos.func ~= nil) then

	--  	table.insert(p.initstuff, p.startPos.func)
	-- end
	

	function p:add(to, items) 
		for k,v in ipairs(items) do
			--print (refs[to].tag)
			table.insert(refs[to], v)
		end
	end

	scumm.state.actionInfo.verb = engine.config.default_verb
	return p
end

require ('s2/factories/buttons')