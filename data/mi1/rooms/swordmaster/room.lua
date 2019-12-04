local items = engine.items

roomDefinition = {
	width = 464,
	height = 144,
	startTable = {
		forest_7 = { walkarea = "swordmaster.walkarea", pos = items["sm.exit"].hotspot.walk_to, dir="east"},
	},
	defaultroom = "forest_7",
	walkareas = { "swordmaster.walkarea"},
	font_size = 8,
	playerid="guybrush",
	collide = true
}

room = scumm.factory.basic_room (roomDefinition)

room:add ( "main",
	{ 
		{ pos = {0,0,-3}, components = { { type="gfx", image="swordmaster.png" }}},
		{ pos = {0,0,2}, components = { { type="gfx", image="swordmaster_bg0.png" }}},
		{ pos = {228,10,2}, components = { { type="gfx", image="swordmaster_bg1.png" }}},
		scumm.factory.object{id="swordmaster.sm"},
		scumm.factory.object{id="sm.exit" },

	}
)

table.insert(room.initstuff, function()
	print ("FANCULAMI")
	variables.know_where_sword_master_is = true
end)