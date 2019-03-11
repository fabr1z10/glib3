-- Basic room 
function scumm.factory.basic_room (args) 
	local room_width = args.width
	local room_height = args.height

	local startPos = nil
	if (args.startTable ~= nil) then
		startPos = args.startTable[variables._previousroom]
		if (startPos == nil) then
			startPos = args.startTable[args.defaultroom]
		end	
	end
	local enableScroll = args.enableScroll
	if (enableScroll == nil) then enableScroll = true end
	

	local p =  {
		items = {},
		dialogues = {},
		scripts = {},
		startPos = startPos,
		initstuff = {
			[1] = function() 
				variables._actionInfo.verb = config.verbs.walk
				updateVerb() 
				refresh_inventory()
			end
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
					size = {320, 144},
					bounds = {0, 0, room_width, room_height},
					viewport = {0, 56, 320, 144}
				},
				children = {
					scumm.factory.object {
						id="guybrush", 
						pos={startPos.pos[1], startPos.pos[2], 0}, 
						--tag="player", 
						dir = startPos.dir,
						follow = (room_width > 320 and enableScroll),
						collide = args.collide
					}
				}
					-- factory.player.create { 
					-- 	pos= startPos.pos, 
					-- 	model="guybrush", 
					-- 	facing = startPos.facing, 
					-- 	scroll = (room_width > 320 and enableScroll),
					-- 	depth = args.depth,
					-- 	scale = args.scale,
					-- 	collide = args.collide
					-- }
				
			},
			{
			 	tag = "ui",
			 	camera = {
			 		tag = "uicam",
			 		type="ortho",
			 		size = {320, 56},
			 		bounds = {0, 0, 320, 56},
			 		viewport = {0, 0, 320, 56}
			 	},
			 	children = {
			 		{
			 			tag = "mainui",
			 			pos = {0,0,0},
			 			children = {
			 				{
			 			    	tag = "currentaction",
			 			    	pos={160,48,0},
			 					components = {
			 			    		{ 
										type="text", 
										id = config.verbs[config.default_verb].text, 
										font = config.ui.font, 
										align = "bottom", 
										color = config.ui.currentaction_color
									}
			 					}
			 			    },
			 			    {
			 					pos = {320,0,0},
			 					components = {
			 						{ type="text", id="ciao", font="ui", align="bottomright"},
			 						{ type="fps" }
			 					}
			 				},
			 				scumm.factory.verbbutton {pos={2, 40}, verb = config.verbs.open},
			 				scumm.factory.verbbutton {pos={2, 32}, verb = config.verbs.close},
			 				scumm.factory.verbbutton {pos={2, 24}, verb = config.verbs.push},
			 				scumm.factory.verbbutton {pos={2, 16}, verb = config.verbs.pull},
			 				scumm.factory.verbbutton {pos={48, 40}, verb = config.verbs.walk},
			 				scumm.factory.verbbutton {pos={48, 32}, verb = config.verbs.pick},
			 				scumm.factory.verbbutton {pos={48, 24}, verb = config.verbs.talk},
			 				scumm.factory.verbbutton {pos={48, 16}, verb = config.verbs.give},
			 				scumm.factory.verbbutton {pos={100, 40}, verb = config.verbs.use},
			 				scumm.factory.verbbutton {pos={100, 32}, verb = config.verbs.look},
			 				scumm.factory.verbbutton {pos={100, 24}, verb = config.verbs.turnon},
			 				scumm.factory.verbbutton {pos={100, 16}, verb = config.verbs.turnoff},
			 				{
			 					type = "textview", 
			 					tag="inventory",
			 					pos = {150, 0},
			 					size = {170, 48},
			 					font_size = 8,
			 					lines = 6,
			 					deltax = 26,
			 					factory = scumm.factory.inventorybutton
			 				}
			-- 			}
			-- 		},
			-- 		{
			-- 			pos  = {0,0,0},
			-- 			children = {
			-- 				{
			-- 					tag = "dialogueui",
			-- 					type = "textview", 
			-- 					pos = {0, 0},
			-- 					size = {320, 56},
			-- 					font_size = 8,
			-- 					lines = 6,
			-- 					deltax = 26,
			-- 					factory = factory.scumm.dialoguebutton
			-- 				}
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

	variables._actionInfo.verb = config.verbs[config.default_verb]
	p.depth = args.depth
	p.scale = args.scale
	return p
end