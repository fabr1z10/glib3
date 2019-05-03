roomDefinition = {
	player_pos = {300,0,0}
}

room = scumm.factory.dialogue_room (roomDefinition)

--room:add_asset(sprites.mancomb2)

room:add( {
	{ pos = {0, 0, -3}, components = { { type="gfx", image="gfx/mancomb.png" }}},
	--factory.objc { id = "mancomb.mancomb" },
})

-- local d = strings.dialogues.mancomb

-- function room.afterstartup() 
--  	local l = variables.first_time_mancomb and {d[1], d[2]} or {d[8]}
--  	variables.first_time_mancomb = false
-- 	local actions = {
--  		{ type = action.say, args = {actor="mancomb.mancomb", lines = l, animate = false}},
-- 		{ type = action.start_dialogue, args ={ dialogue="mancomb"}}
-- 	}
-- 	local s = ms2(actions)
-- 	monkey.play(s)
-- end


