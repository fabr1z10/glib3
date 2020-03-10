engine.items["store.walkarea"] = {
	type ='walkarea',
	tag = true,
	shape = { 
		type = "poly", 
		outline = {62,14,90,20,115,20,150,31,191,31,231,67,154,67,154,69,235,69,235,67,184,25,175,25,181,21,235,21,235,13,248,2,
 		248,0,62,0}
 	},
	depth = { type="linear_y", values= {0, 1, 144, 0} },
	scale = { 
		type="patchwise", 
		rects = {
    		{ pos = {0, 0}, size={320, 20}, func = { type = 'constant', value = 1} },
    		{ pos = {0,20}, size={320,10}, func = { type = 'linear_y', values= {20,1,30,0.6} }},
    		{ pos = {0, 30}, size={320, 104}, func = { type='constant', value = 0.6}}
    	}
	},
	priority = 0,
}

engine.items["store.walkarea.keeper"] = {
    type = 'walkarea',
	tag = true,
	shape = { 
		type = "poly", 
		outline = {62,14,90,20,115,20,150,31,191,31,231,67,154,67,154,69,235,69,235,67,184,25,175,25,181,21,235,21,235,13,248,2,
 		290,2,290,20,320,20,320,0,62,0}
 	},
	depth = { type="patchwise", rects = {
		{ pos = {0, 0}, size = {248, 100}, func = { type="linear_y", values = {0,1,144,0}}},
		{ pos = {248, 0}, size = {100, 2}, func = {type="linear_y", values = {0,1,144,0}}},
		{ pos = {248, 2}, size = {100, 100}, func = {type="constant", value = -0.5}},
	}},
	priority = 0,
	--depth = { type="linear_y", values= {0, 1, 144, 0} },
	--scale = { type="constant", value=0.3 }
}

engine.items['shop.door'] = make_door {
	tag = 'shop.door',
	model = 'shop.door',
 	pos = {59, 16, -1},
 	size = {30, 50},
 	walk_to = mi.rooms.store.to_village3,
 	dir = 'w',
	var = 'door_shop',
	go_to = { room = 'village3', pos = mi.rooms.village3.to_shop, dir = 's' },
 	walk = function()
 		if (variables.door_shop == 0) then
 			return nil
 		end
 		local haveSword = scumm.utils.has_player("shop.sword")
 		local haveShovel = scumm.utils.has_player("shop.shovel")
		if (((haveSword and (not variables.sword_paid)) or (haveShovel and (not variables.shovel_paid)))) then
 			-- no paid
 			return {
				{ type = scumm.action.toggle_controls, args = {active=false, ui=true}},
 				{ type = action.suspend_script, args = {script="_shopkeeper"}},
 				{ type = scumm.action.say, args = { tag="storekeeper", lines = {strings.dialogues.storekeeper[30]}}},
 				{ type = scumm.action.walkto, args = { tag="player", obj = "storekeeper"}},
 	 			{ type = scumm.action.start_dialogue, args = {dialogue="storekeeper"}}
			}
 		end	
		return scumm.script.changeroom { room = 'village3', pos = mi.rooms.village3.to_shop, dir = 's' }
	end
}

-- scumm.factory.door {
-- 	id = "shop.door",
-- 	pos = {59, 16, -1},
-- 	size = {30, 50},			
-- 	walk_to = {81, 15}, 
-- 	dir = "west",
-- 	model = "shop.door",
-- 	variable = "door_shop",
-- 	nextroom = "village3",
-- 	-- override the walk action
-- 	walk = function()
-- 		if (variables.door_shop == 0) then
-- 			return nil
-- 		end
-- 		local haveSword = engine.state.scumm.has("shop.sword")
-- 		local haveShovel = engine.state.scumm.has("shop.shovel")
-- 		print ("worfijrwiofj")
-- 		if (((haveSword and (not variables.sword_paid)) or (haveShovel and (not variables.shovel_paid)))) then
-- 			-- no paid
-- 			print ("no pago")
-- 			return {
-- 				{ type = scumm.action.disable_controls },
-- 				{ type = action.suspend_script, args = {script="_shopkeeper"}},
-- 				{ type = scumm.action.say, args = { actor="shop.shopkeeper", lines = {strings.dialogues.storekeeper[30]}}},
-- 				{ type = scumm.action.walkto, args = { tag="player", obj = "shop.shopkeeper"}},
-- 	 			{ type = scumm.action.start_dialogue, args = {dialogue="storekeeper"}}
-- 			}
-- 		end	
-- 		return { type = action.change_room, args = {room="village3"}}
-- 	end
-- 	-- walk = function()
-- 	-- 	local s = script:new()
-- 	-- 	local haveSword = (variables.inventory["shop.sword"] ~= nil)
-- 	-- 	local haveShovel = (variables.inventory["shop.shovel"] ~= nil)
-- 	-- 	if (((haveSword and (not variables.sword_paid)) or (haveShovel and (not variables.shovel_paid)))) then
-- 	-- 		s.actions = {
-- 	-- 			action.suspend_script { id = 1, script = "shopkeeper"},
-- 	-- 			action.say {id = 2, actor="shop.shopkeeper", lines = {strings.dialogues.storekeeper[30]}},
-- 	-- 			action.walkto {id = 3, actor="guybrush", obj = engine.items["shop.shopkeeper"]},
-- 	-- 			action.start_dialogue {id = 4, dialogue="storekeeper"}
-- 	-- 		}
-- 	-- 		return s
-- 	-- 	else 
-- 	-- 		s.actions = {
-- 	-- 			action.change_room {id=1,room="village3"}
-- 	-- 		}
-- 	-- 	end
-- 	-- 	return s
-- 	-- end
-- }

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
	type = 'object',
	tag = true,
 	pos = {212, 45, -1},
 	hotspot = {
		text = strings.objects.sword,
	 	size = {30, 6},
	 	walk_to = {226,18},
	 	dir = "north"
	},
	model ="shop.sword",
 	actions ={
 		look = { type = scumm.action.say, args = {tag="player", lines ={strings.shop[5]}}},
		pick = scumm.script.pickup { id='shop.sword', anim_start='operate_n', anim_end='idle_n'},
 	}
}

engine.items["shop.shovel"] = { 
	type = 'object',
	tag = true,
 	pos = {141,	69, -1},
 	hotspot = {
		text = strings.objects.shovel,
	 	size = {8, 20}, 
	 	walk_to = {151, 69},
	 	dir="west",
 	},
 	model = "shop.shovel",
 	actions = {
 		look = { type = scumm.action.say, args = {tag ="player", lines ={strings.shop[6]}}},
		pick = scumm.script.pickup { id='shop.shovel', anim_start='operate_e', anim_end='idle_e'},

 	}
 }

engine.items["shop.sign"] = {
	type = 'object',
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
	type = 'object',

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