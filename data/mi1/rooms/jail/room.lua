local items = engine.items

roomDefinition = {
	width = 320,
	height = 144,
	startTable = {
		village3 = { walkarea="jail.walkarea", pos = items["jail.door"].hotspot.walk_to, dir = "west"},
	},
	font_size = 8,
	playerid="guybrush",
	walkareas = { "jail.walkarea", "jail.walkarea2"},
	defaultroom = "village3",
	depth = { type="linear_y", values= {0, 1, 144, 0} },
	collide = true
}


room = scumm.factory.basic_room  (roomDefinition)

room:add( "main", {
	{ pos = {0, 0,-3}, components = { { type="gfx", image="jail.png" }}},
	{ pos = {0, 15, 0}, components = { { type="gfx", image="jail2.png" }}},
	scumm.factory.object { id = "jail.door"},
})

room:add( "jail.walkarea", {
	--scumm.factory.object { id = "otis"},
})

room:add( "jail.walkarea2", {
 	scumm.factory.object { id = "otis"},
})


table.insert(room.initstuff, function()
	local act = {
		{ ref=1, type = scumm.action.walkto, args = {tag="otis", pos = {60, 25}}},
		{ type = scumm.action.walkto, args = {tag="otis", pos = {30, 25}}},
	}
	local s = script.make(act,1)
	s.name = "_otis"
	monkey.play(s)
end)