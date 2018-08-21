function mapLocationEnter(name)
	a = monkey.getEntity("cursor")
	a:setactive(true)
	a:settext(name)
end

function mapLocationExit()
	a = monkey.getEntity("cursor")
	a:setactive(false)
end

function createMapItem (x, y, name, priority)

	return {
		pos = {x, y, 0},
		hotspot = {
			priority = priority,
			shape = { type = "rect", width=10, height=10 },
			onenter = curry (mapLocationEnter, name),
			onleave = curry (mapLocationExit)
		}
	}
end