-- Basic room 
function scumm.factory.sci_room (args) 
	local room_width = args.width
	local room_height = args.height

	-- local startPos = nil
	-- if (args.startTable ~= nil) then
	-- 	startPos = args.startTable[variables._previousroom]
	-- 	if (startPos == nil) then
	-- 		startPos = args.startTable[args.defaultroom]
	-- 	end	
	-- end
	-- local enableScroll = args.enableScroll
	-- if (enableScroll == nil) then enableScroll = true end
	

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
		startPos = {},
		initstuff = {
			-- [1] = function() 
			-- 	variables._actionInfo.verb = config.verbs.walk
			-- 	scumm.ui.updateVerb() 
			-- 	scumm.ui.refresh_inventory()
			-- end
		},
		engines = {
			{ 
				type = "hotspotmanager", 
				keys = {
					{ key = 299, func = function() monkey.endroom() end }
				},

				rmbclick = function() 
					variables.currentverb = variables.currentverb + 1
					if (variables.currentverb > #variables.verbs) then
						variables.currentverb = 1
					end
					print ("current verb = " .. variables.verbs[variables.currentverb].mnemonic)
					local cursor = monkey.getEntity("cursor")
					cursor.anim = variables.verbs[variables.currentverb].anim

				end
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
					size = {320, 200},
					bounds = {0, 0, room_width, room_height},
					viewport = {0, 0, 320, 200}
				},
				children = {
					-- {
     --            	    pos = {0, 0, 0},
     --            		components = {
	    --   					{ 
					-- 			type ="hotspot",
					-- 			priority = 0,
					-- 			shape = {type="rect", width=320, height=200},
					-- 			-- on click
					-- 			-- LMB: run action
					-- 			-- RMB: switch action
					-- 			onclick = function() print ("ciao") end,

					-- 			onrmbclick = function() 
					-- 				print ("rmb") 
					-- 				variables.currentverb = variables.currentverb + 1
					-- 				if (variables.currentverb > #variables.verbs) then
					-- 					variables.currentverb = 1
										
					-- 				end
					-- 				print ("current verb = " .. variables.verbs[variables.currentverb].mnemonic)
					-- 				local cursor = monkey.getEntity("cursor")
					-- 				cursor.anim = variables.verbs[variables.currentverb].anim

					-- 			end
     --       					},
     --       				}
     --       			},
           			{
                	    pos = {20,50, 0},
                		components = {
	      					{ 
								type ="hotspot",
								priority = 1,
								shape = {type="rect", width=20, height=50},
								-- on click
								-- LMB: run action
								-- RMB: switch action
								onclick = function() print ("ciao 2") end,
           					},
           				}

           			},

					-- scumm.factory.walkarea { 
					-- 	priority = 0, 
					-- 	shape = { 
			  --      			type = "poly", 

	    --     				outline = {4,14,39,9,61,9,84,22,52,29,0,27,0,68,44,70,64,62,82,64,140,84,155,85,171,84,171,80,180,80,189,88,221,85,274,76,249,67,253,60,241,59,248,54,221,44,177,41,184,48,151,44,130,43,122,43,114,38,107,30,108,27,110,12,77,0,0,0},
     --  						holes = {
					-- 			{211,78,185,81,185,62,211,59}
					-- 		}
     --  					}	
					-- },
					-- scumm.factory.object {
					-- 	id="guybrush", 
					-- 	pos={startPos.pos[1], startPos.pos[2], 0}, 
					-- 	--tag="player", 
					-- 	dir = startPos.dir,
					-- 	follow = (room_width > 320 and enableScroll),
					-- 	collide = args.collide
					-- }
					
					-- factory.player.create { 
					-- 	pos= startPos.pos, 
					-- 	model="guybrush", 
					-- 	facing = startPos.facing, 
					-- 	scroll = (room_width > 320 and enableScroll),
					-- 	depth = args.depth,
					-- 	scale = args.scale,
					-- 	collide = args.collide
					-- }
				
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
				    	pos={0,0,0},
						components = {
				    		--{ type="text", id = "prova", font="monkey", align = "bottom", color = config.ui_currentaction_color},
				    		--{ type = "gfx", model="cujrsor" },
							{ type="cursor"}
						}
					}
				}
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

	if (p.startPos.func ~= nil) then

	 	table.insert(p.initstuff, p.startPos.func)
	 end
	

	function p:add(items) 
		for k,v in ipairs(items) do
			table.insert(self.scene[1].children, v)
		end
	end

	--variables._actionInfo.verb = config.verbs[config.default_verb]
	p.depth = args.depth
	p.scale = args.scale
	return p
end
