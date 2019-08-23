factory.mario = {}

factory.mario.supermario = function(player, value) 
	player:getinfo().supermario = value
	if (value == true) then
		player.state = "walk_big"
	else
		player.state = "walk"
	end

end