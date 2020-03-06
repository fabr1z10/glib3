local items = engine.items

roomDefinition = {
	width = 656,
	height = 144,
	font_size = 8,
	walkareas = { "cellar.walkarea"},
	collide= true,
	id ='cellar'
}

room = scumm.factory.room_ui (roomDefinition)

room:add ( "main",
	{ 
		{ pos = {0,0,-3}, components = { { type="gfx", image="cellar.png" }}},
	}
)
room:add ( "entrance.walkarea",
	{
		--{ pos = {328,18,-2.5}, components = { { type="gfx", image="entranc2.png" }}}
	}
)


