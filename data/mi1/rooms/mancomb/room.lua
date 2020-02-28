roomDefinition = {
	player_pos = {300,0,0}
}

room = scumm.factory.dialogue_room (roomDefinition)

--room:add_asset(sprites.mancomb2)

room:add( {
	{ pos = {0, 0, -3}, components = { { type="gfx", image="mancomb.png" }}},
	scumm.factory.object { id = "mancomb.mancomb" },
	scumm.factory.object { id = "mancomb.guybrush" },

})

local d = strings.dialogues.mancomb

local a = function() 
	local l = variables.first_time_mancomb and {d[1], d[2]} or {d[8]}
  	variables.first_time_mancomb = false
	local actions = {
  		{ type = scumm.action.say, args = { tag='mancomb.mancomb', lines = l, animate = false}},
 		{ type = scumm.action.start_dialogue, args ={ dialogue="mancomb"}}
 	}
	local s = script.make(actions)
	monkey.play(s)

end

table.insert(room.initstuff, a)

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


