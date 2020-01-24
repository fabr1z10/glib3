roomDefinition = {
	player_pos = {10,0,0}
}

room = scumm.factory.dialogue_room (roomDefinition)

--room:add_asset(sprites.mancomb2)

room:add( {
	{ pos = {0, 0, -3}, components = { { type="gfx", image="estevan.png" }}},
	--scumm.factory.object { id = "mancomb.mancomb" },
})

-- local d = strings.dialogues.estevan

-- function room.afterstartup() 
-- 	local l = variables.first_time_estevan and {d[1]} or {d[6]}	
-- 	variables.first_time_estevan = false
-- 	local actions = {
--  		{ type = action.say, args = {actor="estevan.estevan", lines = l, animate = false}},
-- 		{ type = action.start_dialogue, args ={ dialogue="estevan"}}
-- 	}
-- 	local s = ms2(actions)
-- 	monkey.play(s)
-- end


