factory.mapitem = {}

factory.mapitem.create = function(args) 
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
					local s = script:new("_walk")
					s.actions = {
						action.walkto{id=1, actor="guybrush", pos=pos},
						action.change_room {id=2, room=args.room }
					}
					monkey.play(s)
				end
			}
		}
	}
end
