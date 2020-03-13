local items = engine.items

roomDefinition = {
	width = 320,
	height = 144,
	walkareas = { "forest1.walkarea"},
	collide = true,
	id='forest_1'
}

room = scumm.factory.room_ui (roomDefinition)

room:add ( "main",
	{ 
		{ pos = {0, 0,-3}, components = { { type="gfx", image="forest_1.png" }}},
		{ pos = {102, 18,1}, components = { { type="gfx", image="forest_1a.png" }}},        
		scumm.factory.object { id = "forest1.1" },
		scumm.factory.object { id = "forest1.2" },
		scumm.factory.object { id = "forest1.2b" },	
	}
)

-- table.insert(room.initstuff, glib.curry (mi.addStorekeeper, { 
-- 	pos = {240, 35, 0}, 
-- 	parent="forest1.walkarea", 
-- 	from = "meleemap",
-- 	walkto = { items["forest1.2"].hotspot.walk_to }
-- }))

