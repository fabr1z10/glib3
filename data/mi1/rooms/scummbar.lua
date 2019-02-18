require("template/room1")

roomDefinition = {
	width = 640,
	height = 144,
	startTable = {
		village1 = { pos = items2["scummbar.door_out"].hotspot.walk_to, dir = "east"},
		--mancomb = { pos = items2["scummbar.mancomb"].hotspot.walk_to, dir = "north"},
		--estevan = { pos = items2["scummbar.estevan"].hotspot.walk_to, dir = "south"},
		--kitchen = { pos = items2["scummbar.door_kitchen"].hotspot.walk_to, dir="west" }

	},
	defaultroom = "village1",
	depth = { type="linear_y", values= {0, 1, 144, 0} },
	--depth = { type="linear_y", values= {0, 1, 144, 0} },
	--scale = { type="linear_y", values= {0, 0.8, 144, 0.2}}
}

room = generateBasicRoom (roomDefinition)

-- room:add_asset(sprites.door_scummbar_village)
-- room:add_asset(sprites.door_scummbar_kitchen)
-- room:add_asset(sprites.mancomb)
-- room:add_asset(sprites.estevan)
-- room:add_asset(sprites.loompirate)
-- room:add_asset(sprites.fireplace)
-- room:add_asset(sprites.cook)
-- room:add_asset(sprites.ilp1)
-- room:add_asset(sprites.ilp2)
-- room:add_asset(sprites.ilp3)
variables[items2["scummbar.door_kitchen"].variable] = 0


room:add( {
	{ pos = {0, 0,-3}, components = { { type="gfx", image="gfx/scummbar_1.png" }}},
	factory.walkarea { shape = { type = "poly", outline = {32,16,70,24,128,19,251,
		18,311,10,321,10,345,32,467,41,492,50,514,40,565,40,580,35,629,6,626,0,256,0,200,16,149,0,90,0,85,10},
		holes = {
			{374,6,505,6,505,28,374,28}
		}
	}},
	factory.objc { id="scummbar.door_out" },
	factory.objc { id="scummbar.door_kitchen" },


	-- { pos = {157, 0, 0.99}, components = { { type="gfx", image="gfx/scummbar_3.png" }}},
	-- { pos = {20, 0, 0.99}, components = { { type="gfx", image="gfx/scummbar_4.png" }}},
	-- { pos = {374, 20, 0.95}, components = { { type="gfx", image="gfx/scummbar_2.png" }}},
	-- factory.object.create { object = "scummbar.door_out" },
	-- factory.object.create { object = "scummbar.mancomb" },
	-- factory.object.create { object = "scummbar.estevan" },
	-- factory.object.create { object = "scummbar.loompirate"},
	-- factory.object.create { object = "scummbar.fireplace"},
	-- factory.object.create { object = "scummbar.ilp1"},
	-- factory.object.create { object = "scummbar.ilp2"},
	-- factory.object.create { object = "scummbar.ilp3"},
	-- factory.object.create { object = "scummbar.important_looking_pirates"},
	-- factory.walkarea.create {
 --   		shape = { 
	--     	type = "poly", 
	--         outline = {32,16,70,24,128,19,251,18,311,10,321,10,345,32,467,41,492,50,514,40,565,40,580,35,629,6,626,0,256,0,200,16,149,0,90,0,85,10},
	--         holes = {
	--         	{374,6,505,6,505,28,374,28}
	--         }
	--     }
	-- }

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
	--local s = script:new("cook")
	local pos = items2["scummbar.door_kitchen"].hotspot.walk_to
	-- coming from village
	local actions = {
		{ type = action.delay, args = {sec=10}},
		{ type = action.open_door, args = {door="scummbar.door_kitchen"}},
		{ type = action.set_variable, args = {var = "cook_in_kitchen", value = false }},
		{ type = action.create_object, args = {name="scummbar.cook", pos = {pos[1], pos[2], 0} }}


	}

	local s = ms2(actions)
	monkey.play(s)

	-- if (variables._previousroom == "kitchen") then
	-- 	local mancombPos = items["scummbar.mancomb"].walk_to
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


function room.afterstartup() 
	for k, v in ipairs(room.initstuff) do
		v()
	end
	cook()
	--run_background_script ("scummbar.mancomb", "drink")
	--run_background_script ("scummbar.estevan", "drink")
	--run_background_script_2 ("scummbar.loompirate", "move", "idle2")
	--scripts.cook()
end


