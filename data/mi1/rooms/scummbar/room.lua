local items = engine.items

roomDefinition = {
	width = 640,
	height = 144,
	walkareas = { 'scummbar.walkarea' },
	collide = true,
	id = 'scummbar'
}

room = scumm.factory.dynamic_room (roomDefinition)

room:add ( "scummbar.walkarea", {
-- 		scumm.factory.object { id = "scummbar.fireplace"},
	scumm.factory.object { id = "scummbar.door.out" },
	scumm.factory.object { id = "scummbar.mancomb" },
-- 		scumm.factory.object { id = "scummbar.loompirate"},
	scumm.factory.object { id = "scummbar.pirate1" },
	scumm.factory.object { id = "scummbar.pirate2" },
	scumm.factory.object { id = "scummbar.pirate3" },
	scumm.factory.object { id = "scummbar.pirate4" },
-- 		scumm.factory.object { id = "scummbar.pirate6" },
-- 		scumm.factory.object { id = "scummbar.pirate7" },
-- 		scumm.factory.object { id = "scummbar.pirate8" },
-- 		scumm.factory.object { id = "scummbar.pirate9" },

-- 		scumm.factory.object { id = "scummbar.ilp1"},
-- 		scumm.factory.object { id = "scummbar.ilp2"},
-- 		scumm.factory.object { id = "scummbar.ilp3"},
-- 		scumm.factory.object { id = "scummbar.important_looking_pirates"},
})
-- )

room:add( "main", {
	{ pos = {0, 0,-3}, components = { { type="gfx", image="scummbar_1.png" }}},
	{ pos = {157, 0, 0.99}, components = { { type="gfx", image="scummbar_3.png" }}},
	{ pos = {20, 0, 0.99}, components = { { type="gfx", image="scummbar_4.png" }}},
	-- { pos = {374, 20, 0.95}, components = { { type="gfx", image="scummbar_2.png" }}},
	-- scumm.factory.object { id = "scummbar.estevan" },
	-- scumm.factory.object { id = "scummbar.pirate5" },
	-- scumm.factory.object { id = "scummbar.door_kitchen"},




	-- factory.object.create { object = "scummbar.fireplace"},

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

function run_background_script_2(actor, anim_transition, anim2) 
	-- mactions = {
	-- 	{ ref = 1, type = action.random_delay, args = { min=1, max=4 }},

	-- 	-- action.animate_once { id=2, actor = actor, anim = anim_transition },
	-- 	-- action.animate { id=3, actor = actor, anim = anim2, },
	-- 	-- action.random_delay { id=4, min=1, max=4 },
	-- 	-- action.animate_once { id=5, actor = actor, anim = anim_transition },		
	-- 	-- action.animate { id=6, actor = actor, anim = "idle", },
		
	-- }
	-- local s = script.make(actions, 1)

	-- mancomb_script.loop = 1
	-- monkey.play(mancomb_script)
end

local animate = function() 
	--run_background_script("scummbar.mancomb", 1, 4, 0, 0)
	run_background_script("scummbar.pirate1", 1, 4, 1, 4)
	--run_background_script("scummbar.pirate2", 1, 4, 1, 4)
	--run_background_script("scummbar.pirate3", 1, 4, 0.5, 0.5)
	--run_background_script("scummbar.pirate4", 1, 4, 0, 0)
	--run_background_script("scummbar.pirate5", 1, 4, 1, 2)
	--run_background_script("scummbar.pirate7", 1, 4, 1, 2)
	--run_background_script("scummbar.pirate8", 1, 4, 0, 0)
	--run_background_script("scummbar.pirate9", 1, 4, 0, 0)

--	--run_background_script("scummbar.estevan", 1, 4, 0, 0)
	--run_background_script("scummbar.loompirate", 1, 4, 0, 0)

end

local cook = function() 
	local pos = items["scummbar.door_kitchen"].hotspot.walk_to
	print (pos[1])	
	local a1 = nil
	variables.cook_in_kitchen = true
	
	if (variables._previousroom == "kitchen") then
		variables[items["scummbar.door_kitchen"].variable] = 1
		variables.cook_in_kitchen = false
	 	local mancombPos = items["scummbar.mancomb"].hotspot.walk_to
		a1 = {
			{ type = action.create_object, args = { factory = scumm.factory.object, args = { id = "scummbar.cook", pos = {mancombPos[1], mancombPos[2], 0} }}},
			{ type = action.delay, args = {sec = 5 }},
			{ type = action.walkto, args = { actor ="scummbar.cook", obj = "scummbar.door_kitchen"}},
			{ type = action.remove_object, args = {name ="scummbar.cook"}},
			{ type = action.close_door, args = {door="scummbar.door_kitchen"}},
			{ type = action.set_variable, args = {var = "cook_in_kitchen", value = true }},
		}
	else
	print ("UQI")
		variables[items["scummbar.door_kitchen"].variable] = 0
	end
	local a2 = {
		{ ref = 1, type = action.delay, args = {sec=2}},
		{ type = scumm.action.open_door, args = {door="scummbar.door_kitchen"}},
		{ type = action.set_variable, args = {var = "cook_in_kitchen", value = false }},
		{ type = action.create_object, args = { factory = scumm.factory.object, parent = "scummbar.walkarea", args = {id="scummbar.cook", pos = {pos[1], pos[2], 0}}}, parent = "scummbar.walkarea"},
		{ type = scumm.action.walkto, args = { tag ="scummbar.cook", obj = "scummbar.mancomb" }}, --obj = items["scummbar.mancomb"]},
		{ type = scumm.action.turn, args = { tag = "scummbar.cook", dir="north"}},
		--{ type = scumm.action.say, args = { actor = "scummbar.ilp1", lines = { strings.dialogues.cook[1], strings.dialogues.cook[2] }}},
		{ type = action.delay, args = {sec = 5 }},
		{ type = scumm.action.walkto, args = { tag ="scummbar.cook", obj = "scummbar.door_kitchen"}},
		{ type = action.remove_object, args = { tag = "scummbar.cook"}},
		{ type = scumm.action.close_door, args = {door="scummbar.door_kitchen"}},
		{ type = action.set_variable, args = {var = "cook_in_kitchen", value = true }},
	}
	local actions = {}
	table.insert(actions, a1)
	table.insert(actions, a2)
	--local s = ms2(actions, 1)
	local s = script.make(actions, 1)
	s.name = "_cook"
	monkey.play(s)

	-- if (variables._previousroom == "kitchen") then

	-- 	variables["cook_in_kitchen"] = false
	-- 	s.actions = {
	-- 		action.create_object { id = 1, name="scummbar.cook", pos = {mancombPos[1], mancombPos[2], 0}, anim ="idle_back", face = "north", applydepth = true},
	-- 		action.delay { id=2, sec = 5 },
	-- 		action.walkto { id=3, actor ="scummbar.cook", obj = items["scummbar.door_kitchen"]},
	-- 		action.remove_object { id = 4, name = "scummbar.cook" },
	-- 		action.close_door { id = 5, door = "scummbar.door_kitchen"},
	-- 		action.set_variable { id = 6, var = "cook_in_kitchen", value = true },
	-- 	}
	-- end
	-- local s1 = script:new()
	-- s1.actions = {
	-- 	action.delay { id=1, sec = 10 },
	-- 	action.open_door { id = 2, door = "scummbar.door_kitchen"},
	-- 	action.set_variable { id = 3, var = "cook_in_kitchen", value = false },
	-- 	action.create_object { id = 4, name="scummbar.cook", pos = {pos[1], pos[2], 0}, anim ="idle_right", face = "west", applydepth = true},
	-- 	action.walkto { id=5, actor ="scummbar.cook", obj = items["scummbar.mancomb"]},
	-- 	action.turn { id = 6, actor="scummbar.cook", dir="north"},
	-- 	action.delay { id=7, sec = 5 },
	-- 	action.walkto { id=8, actor ="scummbar.cook", obj = items["scummbar.door_kitchen"]},
	-- 	action.remove_object { id = 9, name = "scummbar.cook" },
	-- 	action.close_door { id = 10, door = "scummbar.door_kitchen"},
	-- 	action.set_variable { id = 11, var = "cook_in_kitchen", value = true },
	-- }
	-- s1.loop = 1
	-- s:push{script=s1}
	-- monkey.play(s)

end

--table.insert(room.initstuff, cook)
table.insert(room.initstuff, animate)