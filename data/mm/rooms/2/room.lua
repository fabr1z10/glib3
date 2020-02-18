local items = engine.items

roomDefinition = {
	width = 960,
	height = 144,
	font_size = 8,
	defaultroom = "lookout",
	walkareas = { "frontdoor.walkarea"},
	collide= true,
	id ='2'
}

room = scumm.factory.dynamic_room (roomDefinition)

room:add ( "main",
	{ 
		{ pos = {0,0,-3}, components = { { type="gfx", image="frontdoor.png" }}},
	}
)

