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
	variables.know_where_sword_master_is = true
	if (variables.chasing_shopkeeper == true) then
		variables.chasing_shopkeeper = false
		variables.play_swordmaster_storekeeper_cutscene =true
		local act = {
			{ type = scumm.action.disable_controls, args = {value=true}},
			{ type = action.set_follow, args = {tag ="player", value=false}},
			{ ref = 1, type = action.create_object, args = { factory = scumm.factory.object, parent = "swordmaster.walkarea", args = { id="shop.shopkeeper", pos = {80,15,0}} }},
			{ ref = 2, type = scumm.action.walkto, after={1}, args ={tag="shop.shopkeeper",pos=items["swordmaster.sm"].hotspot.walk_to }},
			{ type = scumm.action.walkto, after={1}, args ={tag="player",pos={210, 14} }},
			{ type = action.scroll, after= {1}, args = {to = {304, 72}, speed=50}},
			{ type = scumm.action.turn, after={2}, args = { tag="player", dir ="south"}},
			{ type =scumm.action.say, args = {actor="guybrush", lines = {strings.forest[7]}}},
			{ type = scumm.action.turn, args = { tag="player", dir ="north"}},
			{ type =action.delay, args = {sec=1}},
			{ type = action.change_room, args = {room="smhouse"}},

		}
		local s = script.make(act)
		monkey.play(s)
	end
end)

