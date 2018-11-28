require("template/room_dialogue")

local roomInfo = {
	player_pos = {300,0,0}
}

room = generateDialogueRoom (roomInfo)

room:add_asset(sprites.mancomb2)


room:add( {
	{ pos = {0, 0, -3}, components = { { type="gfx", image="gfx/mancomb.png" }}},
	factory.object.create { object = items.mancomb.mancomb },
})

local d = strings.dialogues.mancomb

function room.afterstartup() 
	local s = script:new()	
	local l = variables.first_time_mancomb and {d[1], d[2]} or {d[8]}
	variables.first_time_mancomb = false
	s.actions = {
		[1] = say2{actor=items.mancomb.mancomb, lines = l, animate=false},
		[2] = { type="callfunc", after={1}, func = function()
			local s1 = start_dialogue { dialogue="mancomb" }
			monkey.play(s1)
		end
		}
	}
	monkey.play(s)
end


