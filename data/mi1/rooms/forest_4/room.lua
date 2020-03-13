local items = engine.items

roomDefinition = {
	width = 320,
	height = 144,
	walkareas = { "forest4.walkarea"},
	collide = true,
	id = 'forest_4'
}

room = scumm.factory.room_ui (roomDefinition)

room:add("main", {
	{ pos = {0, 0,-3}, components = { { type="gfx", image="forest_4.png" }}},
	scumm.factory.object { id = "forest4.3" },
	scumm.factory.object { id = "forest4.5" },
	scumm.factory.object { id = "forest.redplant" },
})

-- table.insert(room.initstuff, glib.curry (mi.addStorekeeper, { 
-- 	pos = {130, 35, 0}, 
-- 	parent="forest4.walkarea", 
-- 	from = "forest_3",
-- 	walkto = { items["forest4.5"].hotspot.walk_to }
-- }))
