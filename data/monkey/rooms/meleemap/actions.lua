function mapLocationEnter(name)
	a = monkey.getEntity("cursor")
	a:setactive(true)
	a:settext(name)
end

function mapLocationExit()
	a = monkey.getEntity("cursor")
	a:setactive(false)
end

function mapscript(args)
	local s = script:new("_walk")
	s.actions = {
		[1] = { type = "walkto", walkarea = "walkarea", actor = "player", pos = args.pos },
		[2] = { type = "gotoroom", room = args.room, after={1} }
	}
	monkey.play(s)

end


function createMapItem (x, y, name, priority, walkposition, room)

	return {
		pos = {x, y, 0},
		hotspot = {
			priority = priority,
			shape = { type = "rect", width=10, height=10 },
			onenter = curry (mapLocationEnter, name),
			onleave = curry (mapLocationExit),
			onclick = curry (mapscript, { pos = walkposition, room = room} )
		}
	}
end