require("template/room_dialogue")

local roomInfo = {
	player_pos = {300,0,0}
}

room = generateDialogueRoom (roomInfo)

room:add_asset(sprites.mancomb2)


room:add( {
	{ pos = {0, 0, -3}, components = { { type="gfx", image="gfx/mancomb.png" }}},
	factory.object.create { object = "mancomb.mancomb" },
})

local d = strings.dialogues.mancomb

function room.afterstartup() 
	local s = script:new()	
	local l = variables.first_time_mancomb and {d[1], d[2]} or {d[8]}
	variables.first_time_mancomb = false
	print ("CANEBESTIAAAAAA")
	s.actions = {
		action.say { id = 1, actor="mancomb.mancomb", lines = l, animate = false},		
		action.start_dialogue { id = 2, dialogue="mancomb" }
	}
print ("CANEBESTIAAAAA222A")
	monkey.play(s)
end


