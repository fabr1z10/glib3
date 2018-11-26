-- Basic room 
function generateBasicRoom (args) 
	local room_width = args.width
	local room_height = args.height

	local p =  {
		items = {},
		dialogues = {},
		scripts = {},
		engines = {
			{ type = "hotspotmanager" },
			{ type = "scheduler" }
		},
		assets = {
			sprites.arrowup,
			sprites.arrowdown,
			sprites.guybrush
		},
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
				children = {}
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
						    		{ type="text", id = "ciao", font="ui", align = "bottom", color = config.ui_currentaction_color}
								}
						    },
							factory.verbbutton.create {pos={2, 40}, verb = config.verbs.open},
							factory.verbbutton.create {pos={2, 32}, verb = config.verbs.close},
							factory.verbbutton.create {pos={2, 24}, verb = config.verbs.push},
							factory.verbbutton.create {pos={2, 16}, verb = config.verbs.pull},
							factory.verbbutton.create {pos={48, 40}, verb = config.verbs.walk},
							factory.verbbutton.create {pos={48, 32}, verb = config.verbs.pick},
							factory.verbbutton.create {pos={48, 24}, verb = config.verbs.talk},
							factory.verbbutton.create {pos={48, 16}, verb = config.verbs.give},
							factory.verbbutton.create {pos={100, 40}, verb = config.verbs.use},
							factory.verbbutton.create {pos={100, 32}, verb = config.verbs.look},
							factory.verbbutton.create {pos={100, 24}, verb = config.verbs.turnon},
							factory.verbbutton.create {pos={100, 16}, verb = config.verbs.turnoff},
							{
								type = "textview", 
								tag="inventory",
								pos = {150, 0},
								size = {170, 48},
								font_size = 8,
								lines = 6,
								deltax = 26,
								factory = factory.inventorybutton.create
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
								factory = factory.dialoguebutton.create
							}
						}
					}
				}
			}
		}
	}
	function p:add(items) 
		for k,v in ipairs(items) do
			table.insert(self.scene[1].children, v)
		end
	end
	function p:add_asset(item) 
		table.insert(self.assets, item)
	end
	return p
end
