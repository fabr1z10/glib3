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

room = scumm.factory.room_ui (roomDefinition)

room:add ( "main",
	{ 
		{ pos = {0,0,-3}, components = { { type="gfx", image="frontdoor.png" }}},
		{ pos = {0,1,1}, components = { { type="gfx", image="frdoor3.png" }}},
		scumm.factory.object { id = "frontdoor.door"},
		scumm.factory.object { id = "frontdoor.mat"},
		scumm.factory.object { id = "frontdoor.grating"},
		scumm.factory.object { id = "frontdoor.bush.l"},
		scumm.factory.object { id = "frontdoor.bush.r"},		
		scumm.factory.object { id = "frontdoor.path"},
		scumm.factory.object { id = "frontdoor.flag"},
		scumm.factory.object { id = "frontdoor.mailbox"},

	}
)

if not variables.frontdoor_key_taken then
    room:add ("main", { scumm.factory.object { id = "frontdoor.key", params = {active=variables.doormat_pulled}} })
end