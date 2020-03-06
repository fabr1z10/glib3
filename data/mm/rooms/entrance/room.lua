local items = engine.items

roomDefinition = {
	width = 640,
	height = 144,
	font_size = 8,
	walkareas = { "entrance.walkarea"},
	collide= true,
	id ='entrance'
}

room = scumm.factory.room_ui (roomDefinition)

room:add ( "main",
	{ 
		{ pos = {0,0,-3}, components = { { type="gfx", image="entrance.png" }}},

		scumm.factory.object { id = 'entrance.clock' },
		scumm.factory.object { id = 'entrance.door.out' },
		scumm.factory.object { id = 'entrance.cellar.door' },
		scumm.factory.object { id = 'entrance.vase.l' },
		scumm.factory.object { id = 'entrance.vase.r' },
		scumm.factory.object { id = 'entrance.gargoyle.r' },

	}
)
room:add ( "entrance.walkarea",
	{
		{ pos = {328,18,-2.5}, components = { { type="gfx", image="entranc2.png" }}}
	}
)


