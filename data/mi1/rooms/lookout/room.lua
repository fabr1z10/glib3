local items = engine.items

roomDefinition = {
	width = 320,
	height = 144,
	walkareas = { 'lookout.walkarea'},
	collide = true,
	id = 'lookout'
}

room = scumm.factory.room_ui (roomDefinition)

room:add ( "lookout.walkarea",
 	{ 
 		scumm.factory.object{id="lookout.fire"},
-- 		scumm.factory.object{id="lookout.lookout"},
 	}
)

room:add ( "main",
	{ 
		{ pos = {0,0,-3}, components = { { type="gfx", image="lookout_1.png" }}},
		{ pos = {81, 16, 3}, components = { { type="gfx", image="lookout_2.png" }}},
        { pos = {294, 33, 3}, components = { { type="gfx", image ="lookout_3.png" }}},
        { pos = {226, 0, 3}, components = { { type="gfx", image="lookout_4.png" }}},
        scumm.factory.object { id = "lookout.stairs" },
		scumm.factory.object { id = "lookout.path" },
	}
)

-- local entry_cutscene = function() 
-- 	local actions = scumm.ui.walk { pos = {240, 30} }
-- 	local s = script.make(actions)
-- 	s.name="_walk"
-- 	monkey.play(s)
-- end

-- table.insert(room.initstuff, entry_cutscene)

-- table.insert(room.initstuff, glib.curry (mi.addStorekeeper, { 
-- 	pos = {240, 30, 0}, 
-- 	parent="lookout.walkarea", 
-- 	from = "village1",
-- 	walkto = { items["lookout.path"].hotspot.walk_to }
-- }))