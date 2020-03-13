local items = engine.items

roomDefinition = {
	width = 320,
	height = 144,
	walkareas = { "forest2.walkarea"},
	collide=true,
	id ='forest_2'
}

room = scumm.factory.room_ui (roomDefinition)

room:add ( "main",
	{ 
		{ pos = {0, 0,-3}, components = { { type="gfx", image="forest_2.png" }}},
		{ pos = {122, 21, 1}, components = { { type="gfx", image="forest_2a.png" }}},        
		{ pos = {247, 0, 1}, components = { { type="gfx", image="forestyp.png" }}},        
		scumm.factory.object { id = "forest2.1" },
		scumm.factory.object { id = "forest2.3" },
		scumm.factory.object { id = "forest.yellowplant" },
	}
)

-- table.insert(room.initstuff, glib.curry (mi.addStorekeeper, { 
-- 	pos = {240, 35, 0}, 
-- 	parent="forest2.walkarea", 
-- 	from = "forest_1",
-- 	walkto = { items["forest2.3"].hotspot.walk_to }
-- }))
