require("template/room_dialogue")

local roomInfo = {
	player_pos = {0,0,0}
}

room = generateDialogueRoom (roomInfo)


room:add( {
	{ pos = {0, 0, -3}, components = { { type="gfx", image="gfx/mancomb.png" }}},

})


function room.afterstartup() 
end


