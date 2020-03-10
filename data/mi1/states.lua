states = {
}

states.start = function()
	local room = 'village3'
	scumm.utils.init { 
		{ id = 'guybrush', room = room, pos = {0,0}, dir = 'e', type = 'player'},
	}
	variables.inventory['guybrush']['pieces_of_eight'] = 120
	engine.state.room = room
	-- do other stuff, like setting global vars
end