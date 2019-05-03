require("template/room_dialogue")

local roomInfo = {
	player_pos = {10,0,0}
}

room = generateDialogueRoom (roomInfo)

room:add( {
	{ pos = {0, 0, -3}, components = { { type="gfx", image="gfx/estevan.png" }}},
	--factory.object.create { object = "estevan.estevan" },
})

local d = strings.dialogues.estevan

function room.afterstartup() 
	local l = variables.first_time_estevan and {d[1]} or {d[6]}	
	variables.first_time_estevan = false
	local actions = {
 		{ type = action.say, args = {actor="estevan.estevan", lines = l, animate = false}},
		{ type = action.start_dialogue, args ={ dialogue="estevan"}}
	}
	local s = ms2(actions)
	monkey.play(s)
end


