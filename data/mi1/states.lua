states = {
}

states.start = function()
	local room = 'kitchen'
	scumm.utils.init { 
		{ id = 'guybrush', room = room, pos = {0,0}, dir = 'e', type = 'player'},
	}
	--variables.inventory['dave_1']['frontdoor.key'] = 1
	engine.state.room = room
	-- do other stuff, like setting global vars
end