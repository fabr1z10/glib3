local items = engine.items

roomDefinition = {
	width = 320,
	height = 144,
	walkareas = { "smhouse.walkarea"},
	font_size = 8,
	collide=true
}

room = scumm.factory.basic_room (roomDefinition)

room:add ( "main",
	{ 
		{ pos = {0,0,-3}, components = { { type="gfx", image="smhouse.png" }}},

	}
)


table.insert(room.initstuff, function()
	if (variables.play_swordmaster_storekeeper_cutscene == true) then
		variables.play_swordmaster_storekeeper_cutscene = false
		local act = {
			{ type = scumm.action.disable_controls, args = {value=true}},
		}
		local s = script.make(act)
		monkey.play(s)
	end
end)
