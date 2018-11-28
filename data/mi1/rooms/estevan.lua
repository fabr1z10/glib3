require("template/room_dialogue")

local roomInfo = {
	player_pos = {10,0,0}
}

room = generateDialogueRoom (roomInfo)

room:add_asset(sprites.estevan2)

room:add( {
	{ pos = {0, 0, -3}, components = { { type="gfx", image="gfx/estevan.png" }}},
	factory.object.create { object = items.estevan.estevan },
})

local d = strings.dialogues.estevan

function room.afterstartup() 
	local s = script:new()	
	local l = variables.first_time_estevan and {d[1]} or {d[6]}
	variables.first_time_estevan = false
	s.actions = {
		[1] = say2{actor=items.estevan.estevan, lines = l, animate=false},
		[2] = { type="callfunc", after={1}, func = function()
			local s1 = start_dialogue { dialogue="estevan" }
			monkey.play(s1)
		end
		}
	}
	monkey.play(s)
end


