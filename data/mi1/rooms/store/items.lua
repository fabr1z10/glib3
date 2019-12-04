engine.items["store.walkarea"] = scumm.factory.walkarea {

	shape = { 
		type = "poly", 
		outline = {62,14,90,20,115,20,150,31,191,31,231,67,154,67,154,69,235,69,235,67,184,25,175,25,181,21,235,21,235,13,248,2,
 		248,0,62,0}
 	},
	depth = { type="linear_y", values= {0, 1, 144, 0} },
	priority = 0,
	--depth = { type="linear_y", values= {0, 1, 144, 0} },
	--scale = { type="constant", value=0.3 }
}

engine.items["store.walkarea.keeper"] = scumm.factory.walkarea {

	shape = { 
		type = "poly", 
		outline = {62,14,90,20,115,20,150,31,191,31,231,67,154,67,154,69,235,69,235,67,184,25,175,25,181,21,235,21,235,13,248,2,
 		290,2,290,20,320,20,320,0,62,0}
 	},
	depth = { type="patchwise", rects = {
		{ pos = {0, 0}, size = {248, 100}, type="linear_y", values = {0,1,144,0}},
		{ pos = {248, 0}, size = {100, 2}, type="linear_y", values = {0,1,144,0}},
		{ pos = {248, 2}, size = {100, 100}, type="constant", value = -0.5},
	}},
	priority = 0,
	--depth = { type="linear_y", values= {0, 1, 144, 0} },
	--scale = { type="constant", value=0.3 }
}


scumm.factory.door {
	id = "shop.door",
	pos = {59, 16, -1},
	size = {30, 50},			
	walk_to = {81, 15}, 
	dir = "west",
	model = "shop.door",
	variable = "door_shop",
	nextroom = "village3",
	-- override the walk action
	walk = function()
		if (variables.door_shop == 0) then
			return nil
		end
		local haveSword = engine.state.scumm.has("shop.sword")
		local haveShovel = engine.state.scumm.has("shop.shovel")
		print ("worfijrwiofj")
		if (((haveSword and (not variables.sword_paid)) or (haveShovel and (not variables.shovel_paid)))) then
			-- no paid
			print ("no pago")
			return {
				{ type = scumm.action.disable_controls },
				{ type = action.suspend_script, args = {script="_shopkeeper"}},
				{ type = scumm.action.say, args = { actor="shop.shopkeeper", lines = {strings.dialogues.storekeeper[30]}}},
				{ type = scumm.action.walkto, args = { tag="player", obj = "shop.shopkeeper"}},
	 			{ type = scumm.action.start_dialogue, args = {dialogue="storekeeper"}}
			}
		end	
		return { type = action.change_room, args = {room="village3"}}
	end
	-- walk = function()
	-- 	local s = script:new()
	-- 	local haveSword = (variables.inventory["shop.sword"] ~= nil)
	-- 	local haveShovel = (variables.inventory["shop.shovel"] ~= nil)
	-- 	if (((haveSword and (not variables.sword_paid)) or (haveShovel and (not variables.shovel_paid)))) then
	-- 		s.actions = {
	-- 			action.suspend_script { id = 1, script = "shopkeeper"},
	-- 			action.say {id = 2, actor="shop.shopkeeper", lines = {strings.dialogues.storekeeper[30]}},
	-- 			action.walkto {id = 3, actor="guybrush", obj = engine.items["shop.shopkeeper"]},
	-- 			action.start_dialogue {id = 4, dialogue="storekeeper"}
	-- 		}
	-- 		return s
	-- 	else 
	-- 		s.actions = {
	-- 			action.change_room {id=1,room="village3"}
	-- 		}
	-- 	end
	-- 	return s
	-- end
}

engine.items["shop.shopkeeper"] = {
 	pos = {289, 7, 0},
 	hotspot = {
		size = {20, 40},
	 	offset ={-10,0},
	 	text = strings.objects.storekeeper,
		walk_to = {229, 7},
		dir = "east"
	},
 	applyDepth = true,
 	model = "shop.shopkeeper",
	character = {
		state = "idle",
		dir = "west",
		speed = 50,
	},
 	text_offset = {0, 60},
    text_color = {255, 85, 255, 255},
 	actions = {
		talk = { 
			{ type = action.suspend_script, args = {script="_shopkeeper"}},
			{ type = scumm.action.start_dialogue, args = {dialogue ="storekeeper"}},
		}
	}
 }
-- 		talk = function() 
-- 			local d = strings.dialogues.storekeeper
-- 			local haveSword = (variables.inventory["shop.sword"] ~= nil)
-- 			local haveShovel = (variables.inventory["shop.shovel"] ~= nil)
-- 			if ((not haveSword) and (not haveShovel)) then
-- 				local s = script:new()
-- 				s.actions = {
-- 					action.suspend_script {id=1, script="shoskeeper"},
-- 					action.say {id=2, actor="shop.shopkeeper", lines= {d[1]}},
-- 					action.say {id=3, actor="guybrush", lines= {d[2]}},
-- 					action.resume_script {id=4, script="shopkeeper"},
-- 				}
-- 				monkey.play(s)
-- 			end
-- 		end
-- 	}
-- }

engine.items["shop.sword"] = {
 	pos = {212, 45, -1},
 	hotspot = {
		text = strings.objects.sword,
	 	size = {30, 6},
	 	walk_to = {226,18},
	 	dir = "north"
	},
	model ="shop.sword",
 	actions ={
 		look = { type = scumm.action.say, args = {actor="guybrush", lines ={strings.shop[5]}}},
 		pick = scumm.action.pickup { id="shop.sword", anim1="operate_n", anim2="idle_n"}
 	}
}

engine.items["shop.shovel"] = { 
 	pos = {141,	69, -1},
 	hotspot = {
		text = strings.objects.shovel,
	 	size = {8, 20}, 
	 	walk_to = {151, 69},
	 	dir="west",
 	},
 	model = "shop.shovel",
 	actions = {
 		look = { type = scumm.action.say, args = {actor ="guybrush", lines ={strings.shop[6]}}},
 		pickup = scumm.action.pickup { id="shop.shovel", anim1="operate_e", anim2="idle_e"}
 	}
 }

engine.items["shop.sign"] = {
 	pos = {248, 29, 1},
 	hotspot = {
		text = strings.objects.sign,
	 	size = {10, 5},
	 	walk_to = {229, 7},
	 	dir = "east"
	},
	model ="shop.sign",
 	actions ={
 		look = { type = scumm.action.say, args = {actor="guybrush", lines ={strings.shop[7]}}}
 	}
}

engine.items["shop.bell"] = {
 	pos = {264, 26, 1},
 	hotspot = {
		text = strings.objects.bell,
	 	size = {10, 5},
	 	walk_to = {229, 7},
	 	dir = "east"
	},
	model ="shop.bell",
 	actions ={
 	}
}