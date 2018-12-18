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
		}
	}

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
