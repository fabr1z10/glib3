-- Dialogue room 
function scumm.factory.dialogue_room (args)
	local room_width = 320
	local room_height = 144

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
		-- assets = {
		-- 	sprites.arrowup,
		-- 	sprites.arrowdown,
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
					{ 
						pos= args.player_pos,
						tag = "player"
					}
				}
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
				}
			}
		}
	}


	function p:add(items) 
		for k,v in ipairs(items) do
			table.insert(self.scene[1].children, v)
		end
	end

	return p
end
