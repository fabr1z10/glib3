states = {
}

states.start = function()
	scumm.utils.init { 
		{ id = 'dave_1', room = '1', pos = {10, 10}, dir = 'e', type = 'player'},
		{ id = 'dave_2', room = '1', pos = {200, 10}, dir = 's', type = 'player'},
		{ id = 'dave_3', room = '1', pos = {220, 10}, dir = 'e', type = 'player'},
	}
	engine.state.room = '1'
	-- do other stuff, like setting global vars
end