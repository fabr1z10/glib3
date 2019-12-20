factory.bubble = {}


factory.bubble.response = function(player, bubble) 
	-- if bub is falling on top of bubble AND <jmp> button is pressed, then JUMP
	print ("CAZZONE !!!")
	if (player.state == "jump" and player.vy < 0 and monkey.iskeydown(265)) then
		player.vy = variables.jump_velocity

	else
		bubble:call("pop", {})
	end

	-- otherwise pop bubble
end

factory.bubble.hitenemy = function(bubble, enemy) 
	bubble:remove()
	local info = enemy:getinfo()
	--print ("CALL " .. tostring(enemy.y))
	info.bubble{ x=enemy.x, y=enemy.y, z= 0}
	enemy:remove()
end
