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
			{ type = "hotspotmanager", keys = {
				{ key = 299, func = function() monkey.endroom() end }
			} },
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
					{
                	    pos = {0, 0, 0},
                		components = {
	      					{ 
								type ="hotspot",
								priority = 0,
								shape = {type="rect", width=320, height=200},
								-- on click
								-- LMB: run action
								-- RMB: switch action
								onclick = function() print ("ciao") end,

								onrmbclick = function() print ("rmb") end
           					}
           				}
           			}
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
