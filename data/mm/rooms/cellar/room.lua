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
		{ tag = 'ciao', pos = {0,0,-3}, components = { { type="gfx", image="cellar.png" }}},
		scumm.factory.object { id = 'cellar.light' },
		scumm.factory.object { id = 'cellar.slime' },
		scumm.factory.object { id = 'cellar.silverkey' },
		scumm.factory.object { id = 'cellar.fusebox' },
		scumm.factory.object { id = 'cellar.circuitbreakers' },

	}
)
room:add ( "cellar.walkarea",
	{
		{ tag = 'ciao2', pos = {112, 8, 0}, components = { { type="gfx", offset = {0,-8}, image="cellar2.png" }}},
		--{ pos = {328,18,-2.5}, components = { { type="gfx", image="entranc2.png" }}}
	}
)

table.insert(room.initstuff, function()

	mm.switch_cellar_lights()
	monkey.getEntity('cellar.circuitbreakers'):setactive(variables.fusebox_open)
end)
