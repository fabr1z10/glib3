local items = engine.items

roomDefinition = {
	width = 640,
	height = 144,
	walkareas = { 'scummbar.walkarea' },
	collide = true,
	id = 'scummbar'
}

room = scumm.factory.dynamic_room (roomDefinition)

if engine.state.previousRoom ~= 'kitchen' then 
	variables.door_scummbar_kitchen = 0 
end


room:add ( "scummbar.walkarea", {
	scumm.factory.object { id = 'scummbar.fireplace'},
	scumm.factory.object { id = 'scummbar.door.out' },
	scumm.factory.object { id = 'scummbar.mancomb' },
	scumm.factory.object { id = "scummbar.loompirate"},
	scumm.factory.object { id = 'scummbar.pirate1' },
	scumm.factory.object { id = 'scummbar.pirate2' },
	scumm.factory.object { id = 'scummbar.pirate3' },
	scumm.factory.object { id = 'scummbar.pirate4' },
	scumm.factory.object { id = 'scummbar.pirate6' },
	scumm.factory.object { id = 'scummbar.pirate7' },
	scumm.factory.object { id = 'scummbar.pirate8' },
	scumm.factory.object { id = 'scummbar.pirate9' },
	scumm.factory.object { id = "scummbar.ilp1"},
	scumm.factory.object { id = "scummbar.ilp2"},
	scumm.factory.object { id = "scummbar.ilp3"},
	scumm.factory.object { id = "scummbar.important_looking_pirates"},
})


room:add( "main", {
	{ pos = {0, 0,-3}, components = { { type="gfx", image="scummbar_1.png" }}},
	{ pos = {157, 0, 0.99}, components = { { type="gfx", image="scummbar_3.png" }}},
	{ pos = {20, 0, 0.99}, components = { { type="gfx", image="scummbar_4.png" }}},
	-- { pos = {374, 20, 0.95}, components = { { type="gfx", image="scummbar_2.png" }}},
	scumm.factory.object { id = "scummbar.estevan" },
	scumm.factory.object { id = "scummbar.pirate5" },
	scumm.factory.object { id = "scummbar.door.kitchen"},
})


function run_background_script(actor, a, b, c, d) 	
	local actions = {
		{ ref = 1, type = action.random_delay, args = { min=a, max=b }},
		{ type = action.animate, args = { tag = actor, anim = "idle_2", fwd = true, sync = true }},
		{ type = action.random_delay, args = { min=c, max=d }},
		{ type = action.animate, args = { tag = actor, anim = "idle_2", fwd = false, sync = true }},
		{ type = action.animate, args = { tag = actor, anim = "idle_1", sync = true }},
		--action.animate { id=3, tag = actor, anim = "idle_1", sync = true },
	}
	local s = script.make(actions, 1)
	monkey.play(s)
end

local animate = function() 
	run_background_script("scummbar.mancomb", 1, 4, 0, 0)
	run_background_script("scummbar.pirate1", 1, 4, 1, 4)
	run_background_script("scummbar.pirate2", 1, 4, 1, 4)
	run_background_script("scummbar.pirate3", 1, 4, 0.5, 0.5)
	run_background_script("scummbar.pirate4", 1, 4, 0, 0)
	run_background_script("scummbar.pirate5", 1, 4, 1, 2)
	run_background_script("scummbar.pirate7", 1, 4, 1, 2)
	run_background_script("scummbar.pirate8", 1, 4, 0, 0)
	run_background_script("scummbar.pirate9", 1, 4, 0, 0)
	run_background_script("scummbar.estevan", 1, 4, 0, 0)
	run_background_script("scummbar.loompirate", 1, 4, 0, 0)

end



-- cook script
local cook = function() 
	local a1 = nil
	
	-- if coming from kitchen, cook should be added to the scene!
	if engine.state.previousroom == 'kitchen' then
	 	--variables[items["scummbar.door_kitchen"].variable] = 1
	 	variables.cook_in_kitchen = false
	  	local mancombPos = items['scummbar.mancomb'].hotspot.walk_to
	 	a1 = {
	 		{ type = action.create_object, args = { 
	 			factory = scumm.factory.object, 
	 			args = { id = 'scummbar.cook', params = { pos = {mancombPos[1], mancombPos[2], 0} }},
	 			parent = 'scummbar.walkarea'
	 		}},
	 		{ type = action.delay, args = {sec = 5 }},
	 		{ type = action.walkto, args = { actor ='scummbar.cook', obj = 'scummbar.door.kitchen'}},
	 		{ type = action.remove_object, args = { name ="scummbar.cook" }},
	 		mi.script.open_door { door='scummbar.door_kitchen', value = false },
	 		{ type = action.set_variable, args = {var = 'cook_in_kitchen', value = true }}
	 	}
	else
		variables.cook_in_kitchen = true
	end
	-- 	variables[items["scummbar.door_kitchen"].variable] = 0
	-- end
    local a2 = {
		{ ref = 1, type = action.delay, args = {sec = 10} },
	 	mi.script.open_door { door='scummbar.door.kitchen', value=true },
	 	{ type = action.set_variable, args = { var = 'cook_in_kitchen', value = false }},
		{ type = action.create_object, args = { 
			factory = scumm.factory.object, 
			args = { id="scummbar.cook", params = { pos = mi.rooms.scummbar.door_kitchen, dir='w' } }, 
			parent = "scummbar.walkarea", 				
		}},
		{ type = scumm.action.walkto, args = { tag = 'scummbar.cook', obj = "scummbar.mancomb" }}, --obj = items["scummbar.mancomb"]},		
		{ type = scumm.action.turn, args = { tag = 'scummbar.cook', dir='north'}},
	 	{ type = action.delay, args = {sec = 5 } },
	 	{ type = scumm.action.walkto, args = { tag ="scummbar.cook", obj = 'scummbar.door.kitchen'}},
	 	{ type = action.remove_object, args = { tag = 'scummbar.cook'}},
	 	mi.script.open_door { door='scummbar.door.kitchen', value=false },
		{ type = action.set_variable, args = {var = 'cook_in_kitchen', value = true }},
	 }
	
	local actions = {}
	table.insert(actions, a1)
	table.insert(actions, a2)
	--local s = ms2(actions, 1)

	local s = script.make(actions, 1)
	s.name = "_cook"
	monkey.play(s)
end

table.insert(room.initstuff, cook)
table.insert(room.initstuff, animate)