states = {
}

states.start = function()
	scumm.utils.init { 
		{ id = 'dave_1', room = '2', pos = {10, 10}, dir = 'e', type = 'player'},
		{ id = 'dave_2', room = '1', pos = {200, 10}, dir = 's', type = 'player'},
		{ id = 'dave_3', room = '1', pos = {220, 10}, dir = 'e', type = 'player'},
	}
	variables.inventory['dave_1']['frontdoor.key'] = 1
	engine.state.room = '2'
	-- do other stuff, like setting global vars
end