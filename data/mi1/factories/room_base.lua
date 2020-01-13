-- Basic room 
function scumm.toggle_pause () 
	local p = monkey.getEntity("main")
	local ui = monkey.getEntity("ui")
	monkey.enablescriptengine(not engine.state.scumm.game_paused)

   	p:setactive(not engine.state.scumm.game_paused)
   	ui:setactive(not engine.state.scumm.game_paused)
   	engine.state.scumm.game_paused = not engine.state.scumm.game_paused
end

function scumm.factory.basic_room (args) 
	-- validation phase
	glib.assert(args.width, "width")
	glib.assert(args.height, "width")
	glib.assert(args.font_size, "font_size")
	
	local room_width = args.width
	local room_height = args.height
	local camWidth = engine.device_size[1]
	local camHeight = engine.device_size[2] - engine.config.ui.height

	-- start y
	local font_size = args.font_size

	local startPos = nil
	if (args.startTable ~= nil) then
		startPos = args.startTable[engine.state.previousRoom]
		if (startPos == nil) then
			startPos = args.startTable[args.defaultroom]
		end	
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
				engine.state.scumm.actionInfo.verb = engine.config.default_verb
				--scumm.ui.updateVerb() 
				scumm.ui.refresh_inventory()
			end
		},
		engines = {
			{ 
                type = "hotspotmanager", 
			    keys = {
				    { key = 299, func = function() monkey.endroom() end },
   					{ key = 32, func = function()
   						-- toggle pause
						scumm.toggle_pause()

   					end },

			    },
				lmbclick = function(x, y)
				    --print ("AZONE = " ..tostring(x) .. "," .. tostring(y))
					if (engine.state.scumm.lmboverride ~= nil) then
						engine.state.scumm.lmboverride()
						return
					end
					if (engine.state.scumm.walk_enabled == true and engine.state.scumm.actionInfo.verb == "walk") then
						local actions = scumm.ui.walk { pos = {x,y} }
						local s = script.make(actions)
						s.name="_walk"
						monkey.play(s)
					end
				end,	 
			},
			{ type = "scheduler" }
		},
		-- assets = {
		-- 	"arrow_up",
		-- 	"arrow_down",
		-- 	"guybrush", -- set this as input param
		-- },
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
					 			    	tag = "currentaction",
					 			    	pos={160,48,0},
					 					components = {
					 			    		{ 
												type="text", 
												id = engine.config.verbs[engine.config.default_verb].text, 
												font = engine.config.ui.font, 
												align = "bottom", 
												color = engine.config.ui.currentaction_color
											}
					 					}
					 				}							 		
							 	}
			 				},
			 				{
								pos = {0,0,0},
								children =  {
			 						{
					 					type = "textview", 
					 					tag="inventory",
					 					pos = {150, 0, 0},
					 					size = {170, 48},
					 					font_size = 8,
					 					lines = 6,
					 					deltax = 26,
					 					factory = scumm.factory.inventorybutton
					   				},
								}
							}
			 			}
			 		},
			 		{
						pos  = {0,0,0},
						children = {
							{
								tag = "dialogueui",
								type = "textview", 
								pos = {0, 0},
								size = {320, 56},
								font_size = 8,
								lines = 6,
								deltax = 26,
								factory = scumm.factory.dialoguebutton
							}
						}
			 		}			 		
			 			 --    {
			 				-- 	pos = {320,0,0},
			 				-- 	components = {
			 				-- 		{ type="text", id="ciao", font="ui", align="bottomright"},
			 				-- 		{ type="fps" }
			 				-- 	}
			 				-- },
			 				--scumm.factory.verbbutton {pos={2, 40}, verb = "open"},
			 				--scumm.factory.verbbutton {pos={2, 32}, verb = "close"},
			 				-- scumm.factory.verbbutton {pos={2, 24}, verb = config.verbs.push},
			 				-- scumm.factory.verbbutton {pos={2, 16}, verb = config.verbs.pull},
			 				-- scumm.factory.verbbutton {pos={48, 40}, verb = config.verbs.walk},
			 				-- scumm.factory.verbbutton {pos={48, 32}, verb = config.verbs.pick},
			 				-- scumm.factory.verbbutton {pos={48, 24}, verb = config.verbs.talk},
			 				-- scumm.factory.verbbutton {pos={48, 16}, verb = config.verbs.give},
			 				-- scumm.factory.verbbutton {pos={100, 40}, verb = config.verbs.use},
			 				-- scumm.factory.verbbutton {pos={100, 32}, verb = config.verbs.look},
			 				-- scumm.factory.verbbutton {pos={100, 24}, verb = config.verbs.turnon},
			 				-- scumm.factory.verbbutton {pos={100, 16}, verb = config.verbs.turnoff},


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

	-- get the inventory
	--table.insert(p.initstuff, function()
		--setverb (config.verbs.walk)
		--refresh_inventory()
		-- c:addtext ( { text="ciao" })
		-- c:addtext ( { text="come" })
		-- c:addtext( { text ="stai" })
		-- c:addtext({ text="alleelelel"})
		-- c:addtext({ text="stronzo" })
		-- c:addtext( { text="duro"})
		-- c:addtext( {text="anvedi"})
	--end)
	local refs = {
		main = p.scene[1].children,
		ui = p.scene[2].children[1].children[1].children
	}

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

	-- add the walkarea(s)
	if (args.walkareas) then
		for _, wa in ipairs(args.walkareas) do
			local tmp = scumm.factory.object { id = wa }
			table.insert (refs.main, tmp)
			refs[wa] =  tmp.children
		end

		-- adding player
		if (startPos) then
			local w1 = refs[startPos.walkarea]
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

			--scumm.factory.object { 
		-- 	id="guybrush",
		-- 	
		-- 	tag="player", 
		-- 	dir = startPos.dir,
		-- 	--collide = args.collide


		-- } })

	end

	--table.insert (refs.ui,scumm.factory.verbbutton {pos={2, 40}, verb = "open"} )

	if (p.startPos and p.startPos.func ~= nil) then

	 	table.insert(p.initstuff, p.startPos.func)
	end
	

	function p:add(to, items) 
		for k,v in ipairs(items) do
			--print (refs[to].tag)
			table.insert(refs[to], v)
		end
	end

	engine.state.scumm.actionInfo.verb = engine.config.default_verb
	p.depth = args.depth
	p.scale = args.scale
	return p
end