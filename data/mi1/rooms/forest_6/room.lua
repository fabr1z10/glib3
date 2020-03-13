local items = engine.items

roomDefinition = {
	width = 320,
	height = 144,
	walkareas = { "forest6.walkarea"},
	collide = true,
	id = 'forest_6'
}

room = scumm.factory.room_ui (roomDefinition)

room:add("main", {
	{ pos = {0, 0,-3}, components = { { type="gfx", image="forest_6.png" }}},
	scumm.factory.object { id = "forest6.5" },
	scumm.factory.object { id = "forest6.7" },
})

-- table.insert(room.initstuff, glib.curry (mi.addStorekeeper, { 
-- 	pos = {120, 35, 0}, 
-- 	parent="forest6.walkarea", 
-- 	from = "forest_5",
-- 	walkto = { items["forest6.7"].hotspot.walk_to }
-- }))

