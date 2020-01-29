roomDefinition = {
	player_pos = {10,0,0}
}

room = scumm.factory.dialogue_room (roomDefinition)

--room:add_asset(sprites.mancomb2)

room:add( {
	{ pos = {0, 0, -3}, components = { { type="gfx", image="estevan.png" }}},
	scumm.factory.object { id = "estevan.estevan" },
})

local d = strings.dialogues.estevan

local a = function()
 	local l = variables.first_time_estevan and {d[1]} or {d[6]}	
 	variables.first_time_estevan = false
 	local actions = {
  		{ type = scumm.action.say, args = {actor="estevan.estevan", lines = l, animate = false}},
 		{ type = scumm.action.start_dialogue, args ={ dialogue="estevan"}}
 	}
	local s = script.make(actions)
	monkey.play(s)
end


table.insert(room.initstuff, a)