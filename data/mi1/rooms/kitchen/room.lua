local items = engine.items

roomDefinition = {
	width = 320,
	height = 144,
	walkareas = {'kitchen.walkarea'},
	collide = true,
	id = 'kitchen'
}

room = scumm.factory.dynamic_room (roomDefinition)

room:add( "main", {
	{ pos = {0, 0,-3}, components = { { type="gfx", image="kitchen.png" }}},
	{ pos = {115, 0, 1}, components = { { type="gfx", image="kitchen3.png" }}},
	--scumm.factory.object { id = "kitchen.potostew"},
	-- factory.walkarea { 
	-- 	shape = { type = "poly", outline = {40,16,59,21,155,21,180,18,192,18,294,18,307,12,199,9,207,0,160,0,149,11,112,11,100,0,40,0}},
	--  	blockedlines = {
	--  		{ A = {190, 0}, B = {190, 144}, active =true },
	--  		{ A = {206, 0}, B = {206, 144}, active =true },
	--  	},
	-- },
	-- factory.objc { id="kitchen.door"},
	-- factory.objc { id="kitchen.door.pier"},
	-- factory.objc { id="kitchen.plank"},
	
	-- factory.objc { id="kitchen.pot"},
	-- factory.objc { id="kitchen.fish"},
	scumm.factory.object { id="kitchen.potostew"},
	-- factory.objc { id="kitchen.table"},
	--{
	--	pos = {290, 5, 0},
	--	components = {
	--		{type="hotspot", shape = {type="rect", width = 20, height = 10}, priority=0, onclick = pushPlank }
	--	}
	--}
	-- factory.hotspot.create { pos ={290, 5, 0}, width=20, height= 10, onclick = pushPlank }
})

room:add( "kitchen.walkarea", {
	scumm.factory.object { id = "kitchen.meat"},
	--scumm.factory.object { id = "kitchen.pot"},
	--scumm.factory.object { id = "kitchen.door"},
	--scumm.factory.object { id = "kitchen.door.pier"},
	--scumm.factory.object { id = "kitchen.fish"},
	--scumm.factory.object { id = "kitchen.plank"}
	

})



local pushPlank = function()

	local seagull_return = function() 
		if (variables.fish_taken == true) then
			return {
				{ type = action.remove_object, args ={tag="kitchen.seagull"}}
				--{ type = action.animate, args = {tag="kitchen.seagull", anim="eat", sync=true }},

			}
		else 
			variables.seagull_on_board = true
			variables.seagull_jump = (variables.seagull_jump == 1) and 2 or 1
			return {		
				{ type = action.animate, args = {tag="kitchen.seagull", anim="eat", sync=true }},
			}
		end
	end
	local seagull_jump = function()
		local n = (variables.seagull_jump == 1) and 2 or 1
		return {	
			{ type = action.set_variable, args = {var="seagull_on_board", value=false}},
			{ ref = 1, type = action.animate, args = {tag="kitchen.seagull", anim="jump" .. tostring(variables.seagull_jump), sync=true }},
			{ type = action.runscript, args = {func = seagull_return}}
		}
	end
	local push_plank = function() 
		local a = nil
		if (variables.seagull_on_board == true) then
			a = { type = action.runscript, after={1}, args = {func = seagull_jump}}
		
		end

		return {
			{ ref = 1, type = action.animate, args = {tag="player", anim="plank", sync = true }},
			{ type = action.animate, args = {tag="player", anim="idle_s"}},
			{ type = action.animate, after={1}, args = {tag="kitchen.plank", anim="pushed", sync = true}},
			{ type = action.animate, args = {tag="kitchen.plank", anim="idle" }},
			a
			--{ type=action.say, args={actor="guybrush", lines = {"sticazzi!"}}}
		}
	end
	local actions = {
		{ type = scumm.action.walkto, args = {tag="player", pos={292,8}}},
		{ type = action.turn, args = {actor="guybrush", dir="south" }},
		{ type = action.runscript, args = {func = push_plank }}
	}
	local s = script.make(actions)
	monkey.play(s)
end





local showSeagull = function()
	local actions = {
		{ type = action.remove_object, args = {tag="seagull_sensor"}},
		{ type = action.create_object, args ={ factory = scumm.factory.object, args = {id="kitchen.seagull"}}},
		{ type = action.animate, args = {tag="kitchen.seagull", anim="fly", sync=true}},
		{ type = action.animate, args = {tag="kitchen.seagull", anim="eat" }},
		{ type = action.set_variable, args = {var="seagull_on_board", value=true}}

	}
	local s = script.make(actions)
	monkey.play(s)
end






if (not variables.fish_taken) then
  	room:add('main',  { 
  		scumm.factory.object { id = 'kitchen.trap' }
  	})

end

-- function room.afterstartup() 
-- 	for k, v in ipairs(room.initstuff) do
-- 		v()
-- 	end
-- 	variables.seagull_on_board = false
-- end


