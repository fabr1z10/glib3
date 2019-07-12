local items = engine.items

roomDefinition = {
	width = 640,
	height = 144,
	startTable = {
		village1 = { walkarea = "scummbar.walkarea", pos = items["scummbar.door_out"].hotspot.walk_to, dir = "east"},
		mancomb = { walkarea = "scummbar.walkarea", pos = items["scummbar.mancomb"].hotspot.walk_to, dir = "north"},
		estevan = { walkarea = "scummbar.walkarea", pos = items["scummbar.estevan"].hotspot.walk_to, dir = "south"},
		kitchen = { walkarea = "scummbar.walkarea", pos = items["scummbar.door_kitchen"].hotspot.walk_to, dir="west"}
	},
	defaultroom = "village1",
	depth = { type="linear_y", values= {0, 1, 144, 0} },
	font_size = 8,
	playerid="guybrush",
	walkareas = { "scummbar.walkarea"},

	--depth = { type="linear_y", values= {0, 1, 144, 0} },
	--scale = { type="linear_y", values= {0, 0.8, 144, 0.2}}
}

room = scumm.factory.basic_room (roomDefinition)

room:add ( "scummbar.walkarea",
	{ 
		scumm.factory.object { id = "scummbar.fireplace"},
		scumm.factory.object { id = "scummbar.door_out" },
		scumm.factory.object { id = "scummbar.door_kitchen"},
		scumm.factory.object { id = "scummbar.mancomb" },
		scumm.factory.object { id = "scummbar.estevan" },
		scumm.factory.object { id = "scummbar.loompirate"},
		scumm.factory.object { id = "scummbar.ilp1"},
		scumm.factory.object { id = "scummbar.ilp2"},
		scumm.factory.object { id = "scummbar.ilp3"},
		scumm.factory.object { id = "scummbar.important_looking_pirates"},
	}
)

room:add( "main", {
	{ pos = {0, 0,-3}, components = { { type="gfx", image="scummbar_1.png" }}},
	{ pos = {157, 0, 0.99}, components = { { type="gfx", image="scummbar_3.png" }}},
	{ pos = {20, 0, 0.99}, components = { { type="gfx", image="scummbar_4.png" }}},
	{ pos = {374, 20, 0.95}, components = { { type="gfx", image="scummbar_2.png" }}},
	


	-- factory.object.create { object = "scummbar.fireplace"},

})


function run_background_script(actor, anim) 
	local mancomb_script = script:new()
	mancomb_script.actions = {
		action.random_delay { id=1, min=1, max=4 },
		action.animate_once { id=2, actor = actor, anim = anim },
		action.animate { id=3, actor = actor, anim = "idle" },
	}
	mancomb_script.loop = 1
	monkey.play(mancomb_script)
end

function run_background_script_2(actor, anim_transition, anim2) 
	local mancomb_script = script:new()
	mancomb_script.actions = {
		action.random_delay { id=1, min=1, max=4 },
		action.animate_once { id=2, actor = actor, anim = anim_transition },
		action.animate { id=3, actor = actor, anim = anim2, },
		action.random_delay { id=4, min=1, max=4 },
		action.animate_once { id=5, actor = actor, anim = anim_transition },		
		action.animate { id=6, actor = actor, anim = "idle", },
		
	}
	mancomb_script.loop = 1
	monkey.play(mancomb_script)
end

local cook = function() 
	print ("starting cook")
	local pos = items["scummbar.door_kitchen"].hotspot.walk_to
	
	local a1 = nil
	variables.cook_in_kitchen = true
	
	if (variables._previousroom == "kitchen") then
		variables[items["scummbar.door_kitchen"].variable] = 1
		variables.cook_in_kitchen = false
	 	local mancombPos = items["scummbar.mancomb"].hotspot.walk_to
		a1 = {
			{ type = action.create_object, args = {name="scummbar.cook", pos = {mancombPos[1], mancombPos[2], 0} }},
			{ type = action.delay, args = {sec = 5 }},
			{ type = action.walkto, args = { actor ="scummbar.cook", obj = "scummbar.door_kitchen"}},
			{ type = action.remove_object, args = {name ="scummbar.cook"}},
			{ type = action.close_door, args = {door="scummbar.door_kitchen"}},
			{ type = action.set_variable, args = {var = "cook_in_kitchen", value = true }},
		}
	else
		variables[items["scummbar.door_kitchen"].variable] = 0
	end
	local a2 = {
		{ ref = 1, type = action.delay, args = {sec=2}},
		{ type = scumm.action.open_door, args = {door="scummbar.door_kitchen"}},
		{ type = action.set_variable, args = {var = "cook_in_kitchen", value = false }},
		{ type = action.create_object, args = { factory = scumm.factory.object, args = { id="scummbar.cook", pos = {pos[1], pos[2], 0} }, parent = "scummbar.walkarea"}},
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

table.insert(room.initstuff, cook)