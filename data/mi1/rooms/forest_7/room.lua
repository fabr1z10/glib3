local items = engine.items

roomDefinition = {
	width = 320,
	height = 144,
	startTable = {
		forest_6 = { walkarea="forest7.walkarea", pos = items["forest7.6"].hotspot.walk_to, dir = "east"},
	},
	defaultroom = "forest_6",
	walkareas = { "forest7.walkarea"},
	font_size = 8,
	playerid="guybrush",
	depth = { type="linear_y", values= {0, 1, 144, 0} },
	collide = true,
}

room = scumm.factory.basic_room (roomDefinition)

-- set the trunk position

table.insert(room.initstuff, function()
	local act = {
		{ type = action.animate, args = {tag="forest7.trunk.bridge", anim=variables.swordmaster_trunk_open and "open" or "closed"}},
		{ type = scumm.action.enable_wall, args = {walkarea="forest7.walkarea", wall=0, active=not variables.swordmaster_trunk_open }}
	}
	local s = script.make(act)
	monkey.play(s)
end)

room:add("main", {
	{ pos = {0, 0,-3}, components = { { type="gfx", image="forest_7.png" }}},
	scumm.factory.object { id = "forest7.6" },
	scumm.factory.object { id = "forest7.sm" },
	scumm.factory.object { id = "forest7.trunk.bridge" },
})


room:add ("forest7.walkarea",
	{ 
		scumm.factory.object{id="swordmaster.sign"},
	}
)