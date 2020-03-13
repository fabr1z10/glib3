local items = engine.items

roomDefinition = {
	width = 320,
	height = 144,
	walkareas = { "forest5.walkarea"},
	collide = true,
	id = 'forest_5'
}

room = scumm.factory.room_ui (roomDefinition)

room:add("main", {
	{ pos = {0, 0,-3}, components = { { type="gfx", image="forest_5.png" }}},
	scumm.factory.object { id = "forest5.4" },
	scumm.factory.object { id = "forest5.6" },
	--scumm.factory.object { id = "forest5.8" },
})


-- table.insert(room.initstuff, glib.curry (mi.addStorekeeper, { 
-- 	pos = {50, 24, 0}, 
-- 	parent="forest5.walkarea", 
-- 	from = "forest_4",
-- 	walkto = { items["forest5.6"].hotspot.walk_to }
-- }))
