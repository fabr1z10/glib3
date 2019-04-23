roomDefinition = {
	width = 320,
	height = 320,
	-- startTable = {
	-- 	village1 = { pos = items["lookout.stairs"].hotspot.walk_to, dir="north"},
	-- 	meleemap = { pos = items["lookout.path"].hotspot.walk_to, dir = "east"},
	-- },
	defaultroom = "meleemap",
}

room = scumm.factory.sci_room (roomDefinition)

--local d = strings.dialogues.lookout.text

room:add( {
	{ pos = {0, 0,-3}, components = { { type="gfx", image="gfx/002.png" }}},
	{ pos = {132, 96,1}, components = { { type="gfx", image="gfx/002a.png" }}},
	{ pos = {0, 0,1}, components = { { type="gfx", image="gfx/002c.png" }}},

	scumm.factory.sciobject { id="room2_walkarea", children = {
  		    scumm.factory.object {
	 			id="graham", 
	 			pos={160,50, 0}, 
	 	 		dir = "south",
	 			follow = false,
				--collide = args.c
	 		},
			{ pos = {0, 92, 0}, components = { { type="gfx", image="gfx/002b.png",offset = {0,-20}}, { type="properties", additional_info = { walkarea_scale = false }}}},

	}},
	scumm.factory.sciobject { id="room2_room1" },	

})

-- local entry_cutscene = function() 
-- 	local actions = {
-- 		{ type = scumm.action.walkto, args = {tag="player", pos = {240, 30}}}
-- 	}
-- 	local s = script.make(actions)
-- 	s.name = "_walk"
-- 	monkey.play(s)
-- end

-- table.insert(room.initstuff, entry_cutscene)