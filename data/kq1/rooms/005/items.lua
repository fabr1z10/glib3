engine.items["005.walkarea"] = scumm.factory.walkarea {
	shape = { type = "poly", outline = {5, 0, 17, 17, 17, 24, 25, 29, 25, 36, 30, 41, 30, 47, 54, 63,  110, 63, 122, 80, 79, 80, 92, 94, 172, 94, 185, 71, 316, 71, 316, 30, 194, 30, 204, 0}},
	priority = 0,
	depth = { type="linear_y", values= {0, 1, 144, 0} },
}

engine.items["005.king"] = makeItem { x=55, y=74, width =42, height=33, msg = strings.room005[6],
	talk = function() 
		if (variables.talked_to_king == 0) then
			variables.talked_to_king = 1
			return {
				{ type = scumm.action.walkto, args = { tag="player", pos = {145, 71}}},
				{ type = scumm.action.turn, args = {tag="player", dir="w"}},
				{ type = action.animate, args = { tag="player", anim = "bow", sync=true }},
				{ type = scumm.action.turn, args = {tag="player", dir="w"}},
				{ type = action.kq.showmessage, args = { msg = strings.room005[5] }},
				{ type = action.kq.showmessage, args = { msg = strings.room005[1] }},
				{ type = action.kq.showmessage, args = { msg = strings.room005[2] }},
				{ type = action.kq.showmessage, args = { msg = strings.room005[3] }},
				{ type = action.kq.showmessage, args = { msg = strings.room005[4] }},
			}
		else
			return {
				{ type = action.kq.showmessage, args = { msg = strings.room005[7] }},
			}
		end
end
} 
