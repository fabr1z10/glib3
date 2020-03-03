roomDefinition = {
	player ='loompirate.guybrush',
	id = 'loompirate'
}

room = scumm.factory.room_dialogue (roomDefinition)

room:add( {
	{ pos = {0, 0, -3}, components = { { type="gfx", image="loompirate.png" }}},
	scumm.factory.object { id = "loompirate.loompirate" },
})

local d = strings.dialogues.loom_pirate

local a = function()
 	local actions = {
  		{ type = scumm.action.say, args = {tag="loompirate.loompirate", lines = {d[1]}, animate = false}},
 		{ type = scumm.action.start_dialogue, args ={ dialogue="loompirate"}}
 	}
	local s = script.make(actions)
	monkey.play(s)
end


table.insert(room.initstuff, a)