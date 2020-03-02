states = {
}

states.start = function()
	scumm.utils.init { 
		{ id = 'guybrush', room = 'scummbar', pos = {0,0}, dir = 'e', type = 'player'},
	}
	--variables.inventory['dave_1']['frontdoor.key'] = 1
	engine.state.room = 'scummbar'
	-- do other stuff, like setting global vars
end