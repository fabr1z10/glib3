-- Basic room 
function generateMapRoom (args) 
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
		initstuff = {},
		engines = {
			{ type = "hotspotmanager" },
			{ type = "scheduler" }
		},
		assets = {
			sprites.guybrush
		},
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
					factory.player.create { 
						pos= startPos.pos, 
						model="guybrush", 
						facing = startPos.facing, 
						scroll = (room_width > 320 and enableScroll),
						depth = args.depth,
						scale = args.scale,
						collide = args.collide
					}
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
					-- {
					--     pos = {0, 0, 0},
					--     hotspot = {
					--         priority = 1,
					--         shape = { type = "rect", width=320, height=200 },
					--         onmove = function(x,y) print(x .. " " .. y) end
					--     }
					-- },
					{ 
				    	tag = "cursor",
				    	pos={0,0,0},
						components = {
				    		{ type="text", id = "prova", font="monkey", align = "bottom", color = config.ui_currentaction_color},
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

	if (p.startPos.func ~= nil) then
	
	 	table.insert(p.initstuff, p.startPos.func)
	 end
	

	function p:add(items) 
		for k,v in ipairs(items) do
			table.insert(self.scene[1].children, v)
		end
	end

	function p:add_asset(item) 
		table.insert(self.assets, item)
	end

	p.depth = args.depth
	p.scale = args.scale
	return p
end
