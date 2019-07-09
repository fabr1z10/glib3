local items = engine.items

roomDefinition = {
	width = 320,
	height = 144,
	startTable = {
		village1 = { walkarea = "lookout.walkarea", pos = items["lookout.stairs"].hotspot.walk_to, dir="north"},
		meleemap = { walkarea = "lookout.walkarea", pos = items["lookout.path"].hotspot.walk_to, dir = "east"},
	},
	defaultroom = "village1",
	walkareas = { "lookout.walkarea"},
	font_size = 8,
	playerid="guybrush",
	--depth = { type="linear_y", values= {0, 1, 144, 0} },
}

room = scumm.factory.basic_room (roomDefinition)

room:add ( "lookout.walkarea",
	{ 
		-- scumm.factory.object{id="lookout.fire"},
		-- scumm.factory.object{id="lookout.lookout"},

	}
)

room:add ( "main",
	{ 
		-- { pos = {0,0,-3}, components = { { type="gfx", image="lookout_1.png" }}},
		-- { pos = {81, 16, 3}, components = { { type="gfx", image="lookout_2.png" }}},
  --       { pos = {294, 33, 3}, components = { { type="gfx", image ="lookout_3.png" }}},
  --       { pos = {226, 0, 3}, components = { { type="gfx", image="lookout_4.png" }}},
  --       scumm.factory.object { id = "lookout.stairs" },
		-- scumm.factory.object { id = "lookout.path" },
	}
)

local entry_cutscene = function() 
	local actions = scumm.ui.walk { pos = {240, 30} }
	local s = script.make(actions)
	s.name="_walk"
	monkey.play(s)
end

table.insert(room.initstuff, entry_cutscene)