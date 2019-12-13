scumm.factory.mapitem = function(args) 
	local pos = args.pos
	return {
		pos = {pos[1], pos[2], 0},
		components = {	
			{ 
				type ="hotspot",
				priority = 1,
				shape = { type = "rect", width=10, height=10, offset={-5,-5} },
				onenter = function() 
					local a = monkey.getEntity("cursor")
					a:setactive(true)
					a:settext(args.name)
				end,
				onleave = function()
					local a = monkey.getEntity("cursor")
					a:setactive(false)					
				end,
				onclick = function() 
					local actions = {
						{ type = scumm.action.walkto, args = { tag="player", pos = pos }},
						{ type = action.change_room, args = {room = args.room }}
					}
					local s = script.make(actions)
					s.name = "_walk"
					monkey.play(s)
				end
			}
		}
	}
end