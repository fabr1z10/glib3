--engine.items.scummbar = {}

local cook_text_color = {85, 255, 255, 255}

engine.items["scummbar.walkarea"] = scumm.factory.walkarea {
	shape = { 
		type = "poly", 
		outline = {32,16,70,24,128,19,251,
			18,311,10,321,10,345,32,467,41,492,50,514,40,565,40,580,35,629,6,626,0,256,0,200,16,149,0,90,0,85,10},
		holes = {
			{374,6,505,6,505,28,374,28}
		}
	},
	priority = 0
}

scumm.factory.door {
	id = "scummbar.door_out",
	pos = {32, 24, -1},
	size = {38, 47},
	walk_to = {57, 20},
	dir = "west",
	model = "door_scummbar_village",
	nextroom="village1",
	variable = "door_village_scummbar"
}

scumm.factory.door {
	id = "scummbar.door_kitchen",
	pos = {591, 9, -1},
	size = {35, 69},
	walk_to = {588, 14},
	dir = "east",
	model = "door_scummbar_kitchen",
	nextroom = "kitchen",
	variable = "door_scummbar_kitchen",
	walk = function() 
		if (variables.cook_in_kitchen == false) then
			local m = monkey.getEntity("scummbar.cook")
			if (m.x > 320) then
				return {
					{ type = action.suspend_script, args = {script = "_cook"}},
					{ type = action.turn, args = {actor="scummbar.cook", dir="east"}},
					{ type = action.say, args = {actor="scummbar.cook", lines = { strings.dialogues.cook[1], strings.dialogues.cook[2] }}},
					{ type = action.turn, args = {actor="scummbar.cook", dir="west"}},
					{ type = action.set_state, args = {actor = "scummbar.cook", state="walk"}},
					{ type = action.resume_script, args = {script = "_cook"}},
				}
			else
				-- sneak into kitchen
				return { type = action.change_room, args = { room="kitchen"}}
			end
		else
			return nil
		end
	end,
	open = function() 
		if (variables.cook_in_kitchen == true) then
			return {
				{ type = action.suspend_script, args = {script = "_cook"}},
				{ type = action.animate, args = {actor="scummbar.door_kitchen", anim="open" }},
				{ type = action.show_message, args = {message = strings.dialogues.cook[3], color = cook_text_color, pos= {591, 100,1}}},
				{ type = action.animate, args = {actor="scummbar.door_kitchen", anim="close" }},
				{ type = action.resume_script, args = {script = "_cook"}}
			}
		else
			return { type = action.open_door, args = {door="scummbar.door_kitchen"}}
		end
	end,
}

engine.items["scummbar.cook"] = {
	pos = {0, 0, -1},
	model = "cook",
	--anim = "idle_right",
	dir = "east",
	text_color = cook_text_color,
	text_offset = {0,60},
	applydepth = true,
	character = {
		state = "idle",
		dir ="east"
	}
}

engine.items["scummbar.mancomb"] = {
	hotspot = {
		text = strings.objects.pirate,
		size = {30, 30},	
		walk_to = {125, 17},
		dir = "north",
	},
	model = "scummbar.mancomb",
	pos = {89, 24, -1},
	actions = {
		look = { type=action.change_room, args={room = "mancomb" }},
		talk = { type=action.change_room, args={room = "mancomb" }}
	}
}

engine.items["scummbar.estevan"] = {
 	pos = {164, 21, 1},
	hotspot = {
 		text = strings.objects.pirate,
		size = {30, 20},
		walk_to = {195, 11},
		dir = "south"
	},	
	model = "scummbar.estevan",
 	actions = {
 		look = { type=action.change_room, args={room = "estevan" }},
 		talk = { type=action.change_room, args={room = "estevan" }}
 	}
}

-- engine.items["scummbar.door_kitchen"] = factory.door.create {
-- 	name = "scummbar.door_kitchen",
-- 	pos = {591, 9, -1},
-- 	size = {35, 69},
-- 	walk_to = {588, 14},
-- 	face = "east",
-- 	door_ref = "door_scummbar_kitchen",
-- 	model = "door_scummbar_kitchen",
-- 	nextroom = "kitchen",
-- 	open = function()
-- 		local s = script:new()
-- 		if (variables.cook_in_kitchen == true) then
-- 			s.actions = {
-- 				action.suspend_script { id = 1, script = "cook"},
-- 				action.animate {id = 2, actor="scummbar.door_kitchen", anim="open" },
-- 				action.show_message { id = 3, message = strings.dialogues.cook[3], color = cook_text_color, pos= {591, 100,1}},
-- 				action.animate {id = 4, actor="scummbar.door_kitchen", anim="close" },
-- 				action.resume_script { id = 5, script = "cook"},
-- 			}
-- 			return s
-- 		end
		
-- 	end,
-- 	walk = function() 
-- 		local s = script:new()
-- 		local m = monkey.getEntity("cook")
-- 		if (variables.cook_in_kitchen == false and m.x > 320) then			
-- 			-- we need this to restore the animation!
-- 			local a = m.anim
-- 			local f = m.flipx
-- 			print ("anim = " .. a)
-- 			s.actions = {
-- 				action.suspend_script { id = 1, script = "cook"},
-- 				action.turn { id = 2, actor="scummbar.cook", dir="east"},
-- 				action.say {id = 3, actor="scummbar.cook", lines = { strings.dialogues.cook[1], strings.dialogues.cook[2] }},
-- 				action.animate {id=4, actor ="scummbar.cook", anim = a, flip = f},
-- 				action.resume_script { id = 5, script = "cook"},
-- 			}
-- 			return s
-- 		else 
-- 			-- you can get in the kitchen
-- 			s.actions = { action.change_room { id=1, room = "kitchen" }}
-- 			return s
-- 		end
-- 	end
-- }


-- engine.items["scummbar.mancomb"] = {
-- 	tag="mancomb",
-- 	text = strings.objects.pirate,
-- 	pos = {89, 24, -1},
-- 	size = {30, 30},
-- 	model = "mancomb",
-- 	anim = "idle",
-- 	walk_to = {125, 17},
-- 	face = "north",
-- 	actions = {
-- 		look =  ms { { action.change_room, { id=1, room = "mancomb" }}},
-- 		talk =  ms { { action.change_room, { id=1, room = "mancomb" }}}
-- 	}
-- }



-- engine.items["scummbar.loompirate"] = {
-- 	tag="loompirate",
-- 	text = strings.objects.pirate,
-- 	pos = {260, 17, -1},
-- 	size = {20, 20},
-- 	model = "loompirate",
-- 	anim = "idle",
-- 	walk_to = {250, 16},
-- 	face = "north",
-- 	actions = {
-- 		look =  ms { { action.change_room, { id=1, room = "loompirate" }}},
-- 		talk =  ms { { action.change_room, { id=1, room = "loompirate" }}}
-- 	}
-- }

engine.items["scummbar.fireplace"] = {
 	pos = {509, 44, -1},
	hotspot = {
 		text = strings.objects.fireplace,
	 	size = {29, 18},
	 	walk_to = {512, 40},
	 	dir = "east",
	},
	model = "scummbar.fireplace",
 	actions = {
 		look =  { type = action.say, args = {actor="guybrush", lines = {strings.scummbar[1]} }}
 	}
}



-- engine.items["scummbar.ilp1"] = {
-- 	tag ="ilp1",
-- 	pos = {376, 11, 0.95},
-- 	text_color = {85, 85, 255, 255},
-- 	text_offset = {0, 60},
-- 	model = "ilp1", 
-- 	anim="idle"
-- }

-- engine.items["scummbar.ilp2"] = {
-- 	tag ="ilp2",
-- 	pos = {413, 11, 0.95},
-- 	text_color = {255, 255, 85, 255},
-- 	text_offset = {0, 60},
-- 	model = "ilp2", 
-- 	anim="idle"
-- }

-- engine.items["scummbar.ilp3"] = {
-- 	tag ="ilp3",
-- 	pos = {444, 18, 0.95},
-- 	text_color = {255, 85, 255, 255},
-- 	text_offset = {0, 60},
-- 	model = "ilp3", 
-- 	anim="idle"
-- }

-- engine.items["scummbar.important_looking_pirates"] = {
-- 	text = strings.objects.ilp,
-- 	pos = {370,30,0},
-- 	size= {110,25},
-- 	walk_to = {460, 2},
-- 	face="west",
-- 	actions = {
-- 		talk = function() 
-- 			local s = script:new()
-- 			local dp = strings.dialogues.pirates
-- 			local lines = (variables.talked_to_important_pirates == false) and {dp[1]} or {dp[40], dp[41]}
-- 			s.actions = {
-- 				action.disable_controls {id=1},
-- 				action.say {id=2, actor="scummbar.ilp1", lines = lines, animstart="talk", animend="idle"},
-- 				action.start_dialogue{id=3, dialogue="importantpirates"}
-- 			}
-- 			return s
-- 		end

-- 	}
-- }