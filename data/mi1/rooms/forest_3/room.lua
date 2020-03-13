local items = engine.items

roomDefinition = {
	width = 320,
	height = 144,
	walkareas = { "forest3.walkarea"},
	collide = true,
	id = 'forest_3'
}

room = scumm.factory.room_ui (roomDefinition)

room:add("main", {
	{ pos = {0, 0,-3}, components = { { type="gfx", image="forest_3.png" }}},
	scumm.factory.object { id = "forest3.2" },
	scumm.factory.object { id = "forest3.4" },
})


-- table.insert(room.initstuff, glib.curry (mi.addStorekeeper, { 
-- 	pos = {200, 35, 0}, 
-- 	parent="forest3.walkarea", 
-- 	from = "forest_2",
-- 	walkto = { items["forest3.4"].hotspot.walk_to }
-- }))