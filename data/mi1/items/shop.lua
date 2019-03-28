scumm.factory.door {
	id = "shop.door",
	pos = {59, 16, 0},
	size = {30, 50},			
	walk_to = {81, 15}, 
	dir = "west",
	model = "shop.door",
	variable = "door_shop",
	nextroom = "village3",
	-- walk = function()
	-- 	local s = script:new()
	-- 	local haveSword = (variables.inventory["shop.sword"] ~= nil)
	-- 	local haveShovel = (variables.inventory["shop.shovel"] ~= nil)
	-- 	if (((haveSword and (not variables.sword_paid)) or (haveShovel and (not variables.shovel_paid)))) then
	-- 		s.actions = {
	-- 			action.suspend_script { id = 1, script = "shopkeeper"},
	-- 			action.say {id = 2, actor="shop.shopkeeper", lines = {strings.dialogues.storekeeper[30]}},
	-- 			action.walkto {id = 3, actor="guybrush", obj = items["shop.shopkeeper"]},
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

items["shop.shopkeeper"] = {
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
		dir = "west"
	},
 	text_offset = {0, 60},
    text_color = {255, 85, 255, 255},
 	actions = {}
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

items["shop.sword"] = {
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
 		--pickup = pick_up_item("shop.sword", "operate_back"),
 	}
}

items["shop.shovel"] = { 
 	pos = {141,	69, -1},
 	hotspot = {
		text = strings.objects.shovel,
	 	size = {8, 20}, 
	 	walk_to = {151, 69},
	 	dir="west",
 	},
 	model = "shop.shovel",
 	actions = {
 		look = { type = scumm.action.say, args = {actor ="guybrush", lines ={strings.shop[6]}}}
-- 			
-- 		},
-- 		pickup = pick_up_item("shop.shovel", "operate_right"),
 	}
 }