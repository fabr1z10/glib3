states = {
}

states.start = function()
	local room = 'forest_1'
	scumm.utils.init { 
		{ id = 'guybrush', room = room, pos = {0,0}, dir = 'e', type = 'player'},
	}
	--variables.chasing_shopkeeper=true
	--engine.state.previousRoom ='store'
	variables.inventory['guybrush']['pieces_of_eight'] = 120
	engine.state.room = room
	-- do other stuff, like setting global vars
end