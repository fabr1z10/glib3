engine.items["scummbar.walkarea"] = {
	type = 'walkarea',
	tag = true,
	shape = { 
		type = "poly", 
 		outline = {
 			32, 16, 70, 24, 128, 19, 251, 18, 311, 10, 321, 10, 345, 32, 467, 41,
 			492, 50, 514, 40, 565, 40, 580, 35, 629, 6, 626, 0, 256, 0, 200, 16, 149, 0, 90, 0, 85, 10},
		holes = {
		 	{374, 28, 505, 28, 505, 6, 374, 6}
		}
	},
	depth = { type="linear_y", values= {0, 1, 144, 0} },

}

engine.items["scummbar.mancomb"] = {
	type = 'object',
	tag = true,
	hotspot = {
		text = strings.objects.pirate,
		size = {30, 30},	
		walk_to = {125, 17},
		dir = "north",
	},
	model = "scummbar.mancomb",
	pos = {89, 24, -1},
	actions = {
		look = scumm.script.changeroom { room = 'mancomb' },
		talk = scumm.script.changeroom { room = 'mancomb' },
	}
}

engine.items["scummbar.loompirate"] = {
	type = 'object',
	tag = true,
	pos = {260, 17, -1},
	hotspot = {
		text = strings.objects.pirate,
		size = {20, 20},
		walk_to = {250, 16},
		dir = "north"
	},
	model = "scummbar.loompirate",
	actions = {
		look =  scumm.script.changeroom { room = 'loompirate' },
		talk =  scumm.script.changeroom { room = 'loompirate' },
	}
}

engine.items['scummbar.estevan'] = {
	type = 'object',
	tag = true,
 	pos = {164, 21, 1},
	hotspot = {
 		text = strings.objects.pirate,
		size = {30, 20},
		walk_to = {195, 11},
		dir = 's'
	},	
	model = 'scummbar.estevan',
 	actions = {
		look =  scumm.script.changeroom { room = 'estevan' },
		talk =  scumm.script.changeroom { room = 'estevan' },
 	}
}


engine.items["scummbar.pirate1"] = {
	type = 'object',
	tag = true,
	hotspot = {
 		text = strings.objects.pirate,
 		size = {30, 30},	
 		walk_to = {140, 20},
 		dir = "north",
 	},
 	model = "scummbar.pirate1",
 	pos = {138, 38, -1},
 	actions = {
  		look =  { type = scumm.action.say, args = { tag = 'player', lines = {strings.scummbar[3]} }},
  		talk =  { type = scumm.action.say, args = { tag = 'player', lines = {strings.scummbar[3]} }}		
 	}
}


engine.items["scummbar.pirate2"] = {
	type = 'object',
	tag = true,	
 	model = "scummbar.pirate2",
 	pos = {124, 20, -1},
}


engine.items["scummbar.pirate3"] = {
	type = 'object',
	tag = true,	

 	model = "scummbar.pirate3",
 	pos = {30, 0, -1},
}

engine.items["scummbar.pirate4"] = {
	type = 'object',
	tag = true,	
	model = 'scummbar.pirate4',
 	pos = {0, 0, -1},
 	hotspot = {
 		text = strings.objects.pirates,
 		size = {70, 20},	
 		walk_to = {50, 10},
 		dir = "south",
 	},
 	actions = {
  		look = { type = scumm.action.say, args = {tag='player', lines = {strings.scummbar[4]} }},
  		talk = { type = scumm.action.say, args = {tag='player', lines = {strings.scummbar[4]} }}		
 	}
}

engine.items["scummbar.pirate5"] = {
	type = 'object',
 	model = "scummbar.pirate5",
 	tag = true,
 	pos = {200, 18, 1},
}

engine.items["scummbar.pirate6"] = {
	type = 'object',
	tag = true,
	model = "scummbar.pirate6",
	pos = {160, 0, 1},
}

engine.items["scummbar.pirate7"] = {
	type = 'object',
	tag = true,
	model = "scummbar.pirate7",
	pos = {255, 38, 1},
}

engine.items["scummbar.pirate8"] = {
	type = 'object',
	tag = true,
	model = "scummbar.pirate8",
	pos = {215, 44, 1},
}

engine.items["scummbar.pirate9"] = {
	type = 'object',
	tag = true,
	model = "scummbar.pirate9",
	pos = {278, 40, 1},
}





engine.items['scummbar.door.out'] = make_door {
	tag = 'scummbar.door.out',
	model = 'door_scummbar_village',
	pos = {32, 24, -1},
	size = {38, 47},
	walk_to = mi.rooms.scummbar.door_out,
	dir = 'w',
	var = 'door_village_scummbar',
	go_to = {
		room = 'village1',
		pos = mi.rooms.village1.door,
		dir = 's'
	}
}

engine.items['scummbar.door.kitchen'] = make_door {
	tag = 'scummbar.door.kitchen',
 	model = 'door_scummbar_kitchen',
 	pos = {591, 9, -1},
 	size = {35, 69},
 	walk_to = mi.rooms.scummbar.door_kitchen, 
 	dir = 'east',
 	go_to = {
 		room = 'kitchen',
 		pos = mi.rooms.kitchen.door,
 		dir = 'e'
 	},
 	var = 'door_scummbar_kitchen',
 	walk = function() 
 		if not variables.cook_in_kitchen then
 			local m = monkey.getEntity('scummbar.cook')
 			if (m.x > 320) then
 				return {
	 				{ type = scumm.action.toggle_controls, args =  { active = false, ui = false }},
 					{ type = action.suspend_script, args = {script = "_cook"}},
 					{ type = scumm.action.turn, args = { tag = "scummbar.cook", dir="east"}},
 					{ type = scumm.action.say, args = { tag = "scummbar.cook", lines = { strings.dialogues.cook[1], strings.dialogues.cook[2] }}},
 					{ type = scumm.action.turn, args = { tag = "scummbar.cook", dir="west"}},
 					{ type = action.set_state, args = {tag = "scummbar.cook", state="walk"}},
 					{ type = action.resume_script, args = {script = "_cook"}},
	 				{ type = scumm.action.toggle_controls, args =  { active = true, ui = false }},

 				}
 			else
 				-- sneak into kitchen
 				return scumm.script.changeroom { room = 'kitchen', pos = mi.rooms.kitchen.door, dir='e' }
 			end
 		else
 			return nil
 		end
 	end,
 	open = function() 
 		if variables.cook_in_kitchen then
 			return {
 				{ type = scumm.action.toggle_controls, args =  { active = false, ui = false }},
 				{ type = action.suspend_script, args = {script = "_cook"}},
 				{ type = action.animate, args = {tag ="scummbar.door.kitchen", anim="open" }},
 				{ type = action.show_message, args = { 
 					message = strings.dialogues.cook[3], 
 					color = mi.data.cook_text_color, 
 					pos= {591, 100,1},
 					font = 'monkey'
 				}},
 				{ type = action.animate, args = {tag="scummbar.door.kitchen", anim="close" }},
 				{ type = action.resume_script, args = {script = "_cook"}},
 				{ type = scumm.action.toggle_controls, args =  { active = true, ui = false }},
 			}
 		else
 			return { type = action.open_door, args = {door="scummbar.door.kitchen"}}
 		end
 	end
}



engine.items["scummbar.fireplace"] = {
	type = 'object',
	tag = true,
 	pos = {509, 44, -1},
 	hotspot = {
  		text = strings.objects.fireplace,
 	 	size = {29, 18},
 	 	walk_to = {512, 40},
 	 	dir = 'east',
 	},
 	model = 'scummbar.fireplace',
  	actions = {
  		look =  { type = scumm.action.say, args = {tag='player', lines = {strings.scummbar[1]} }}
  	}
}

engine.items["scummbar.important_looking_pirates"] = {
	type = 'object',
	pos = {370,30,0},
	hotspot = {
		text = strings.objects.ilp,
		walk_to = {460, 2},
		size = {110,25},
		dir = 'w',
	},
	actions = {
 		talk = function() 
 			local dp = strings.dialogues.pirates
 			local actions = {
				{ type = scumm.action.toggle_controls, args = { active=false, ui=true } },
				{ type = scumm.action.say, args = { tag='scummbar.ilp1', lines = { dp[1] }}},
				{ type = scumm.action.start_dialogue, args = { dialogue = "importantpirates" }}
			}
 			return actions
 		end
 	}
}



-- scumm.factory.door {
-- 	id = "scummbar.door_out",
-- 	pos = {32, 24, -1},
-- 	size = {38, 47},
-- 	walk_to = {57, 20},
-- 	dir = "west",
-- 	model = "door_scummbar_village",
-- 	nextroom="village1",
-- 	variable = "door_village_scummbar"
-- }








-- }








-- -- engine.items["scummbar.door_kitchen"] = factory.door.create {
-- -- 	name = "scummbar.door_kitchen",
-- -- 	pos = {591, 9, -1},
-- -- 	size = {35, 69},
-- -- 	walk_to = {588, 14},
-- -- 	face = "east",
-- -- 	door_ref = "door_scummbar_kitchen",
-- -- 	model = "door_scummbar_kitchen",
-- -- 	nextroom = "kitchen",
-- -- 	open = function()
-- -- 		local s = script:new()
-- -- 		if (variables.cook_in_kitchen == true) then
-- -- 			s.actions = {
-- -- 				action.suspend_script { id = 1, script = "cook"},
-- -- 				action.animate {id = 2, actor="scummbar.door_kitchen", anim="open" },
-- -- 				action.show_message { id = 3, message = strings.dialogues.cook[3], color = cook_text_color, pos= {591, 100,1}},
-- -- 				action.animate {id = 4, actor="scummbar.door_kitchen", anim="close" },
-- -- 				action.resume_script { id = 5, script = "cook"},
-- -- 			}
-- -- 			return s
-- -- 		end
		
-- -- 	end,
-- -- 	walk = function() 
-- -- 		local s = script:new()
-- -- 		local m = monkey.getEntity("cook")
-- -- 		if (variables.cook_in_kitchen == false and m.x > 320) then			
-- -- 			-- we need this to restore the animation!
-- -- 			local a = m.anim
-- -- 			local f = m.flipx
-- -- 			print ("anim = " .. a)
-- -- 			s.actions = {
-- -- 				action.suspend_script { id = 1, script = "cook"},
-- -- 				action.turn { id = 2, actor="scummbar.cook", dir="east"},
-- -- 				action.say {id = 3, actor="scummbar.cook", lines = { strings.dialogues.cook[1], strings.dialogues.cook[2] }},
-- -- 				action.animate {id=4, actor ="scummbar.cook", anim = a, flip = f},
-- -- 				action.resume_script { id = 5, script = "cook"},
-- -- 			}
-- -- 			return s
-- -- 		else 
-- -- 			-- you can get in the kitchen
-- -- 			s.actions = { action.change_room { id=1, room = "kitchen" }}
-- -- 			return s
-- -- 		end
-- -- 	end
-- -- }


-- -- engine.items["scummbar.mancomb"] = {
-- -- 	tag="mancomb",
-- -- 	text = strings.objects.pirate,
-- -- 	pos = {89, 24, -1},
-- -- 	size = {30, 30},
-- -- 	model = "mancomb",
-- -- 	anim = "idle",
-- -- 	walk_to = {125, 17},
-- -- 	face = "north",
-- -- 	actions = {
-- -- 		look =  ms { { action.change_room, { id=1, room = "mancomb" }}},
-- -- 		talk =  ms { { action.change_room, { id=1, room = "mancomb" }}}
-- -- 	}
-- -- }










