mm = {
}

mm.switch_cellar_lights = function() 
	local mult = nil
	local add = nil
	if not variables.cellar_light_on then
		mult = {0, 0, 0, 255}
		add = {85, 85, 85, 255}
	end
	
	monkey.getEntity('ciao'):setcolors { mult = mult }
	monkey.getEntity('ciao2'):setcolors { mult = mult }	
	monkey.getEntity('ciao3'):setcolors { mult = mult }	

	monkey.getEntity('player'):setcolors { mult = mult, add = add }
	

end

newkid = function()
	local m = monkey.getEntity('ui')
	m:setactive(false)
	-- display three buttons, one for each kid
	local o = monkey.getEntity('other')

	for i, p in ipairs(variables.players) do
		monkey.addEntity (scumm.factory.button {
			pos = {(i) * 80,27},
			align = 'center',
			font = 'ui',
			text = p,
			color = engine.config.ui.verb_unselected_color,
			onenter = glib.curry2(scumm.func.changecolor, engine.config.ui.verb_selected_color),
			onleave = glib.curry2(scumm.func.changecolor, engine.config.ui.verb_unselected_color),
			onclick = function()
				if variables.current_player == p then
					--local m = monkey.getEntity('ui')
					o:clear()					
					m:setactive(true)					

				end
				-- save the position and direction


				
				local player = monkey.getEntity('player')

				local a = variables.dynamic_items[engine.state.room][variables.current_player]
				a.pos = { player.x, player.y }
				a.dir = monkey.getdir(player)

				variables.current_player = p


				-- if current player is in another room, move to room
				local actions = {
					{ type = action.change_room, args = { room = variables.player_pos[variables.current_player] }}
				}
				local s = script.make(actions)
				monkey.play(s)	
			end

		}, o)

	end
end