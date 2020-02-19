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
		scumm.factory.object { id = "frontdoor.door"},
		scumm.factory.object { id = "frontdoor.mat"},
		scumm.factory.object { id = "frontdoor.grating"},
		scumm.factory.object { id = "frontdoor.bush.l"},
		scumm.factory.object { id = "frontdoor.path"},

	}
)

if not variables.frontdoor_key_taken then
    room:add ("main", { scumm.factory.object { id = "frontdoor.key", params = {active=variables.doormat_pulled}} })
end