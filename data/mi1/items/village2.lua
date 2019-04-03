-- generally, an item is a blueprint for an object
-- * it can have graphics attached. To do so, model needs to be specified
items["village2.archway_to_village1"] = {
	hotspot = {
		text = strings.objects.archway,
		walk_to = {436, 35}, 
		dir = "north",
		size = {40, 50},			
	},
	actions = {
		walk = { type = action.change_room, args = { room="village1"}}
	},
	pos = {416, 34, 0},
}

items["village2.archway_to_village3"] = {
	hotspot = {
		text = strings.objects.archway,
		walk_to = {160, 59},
		dir="north",
		size={30, 30},
	},
	actions = {
		walk = { type = action.change_room, args = { room="village3"}}
	},
	pos = {146, 63, 0},
}

items["village2.lmf1"] = {
	pos = {18, 10, 0},
	text_color = {255, 85, 255, 255},
	text_offset = {0,60},
	model = "low_moral_fiber_1",
	anim= "rock",
	applydepth = true,
}

items["village2.lmf2"] = {
	pos = {44, 20, 0},
	text_color = {85, 255, 255, 255},
	text_offset = {0,60},
	model = "low_moral_fiber_2",
	anim= "idle",
	applydepth = true,
}

items["village2.lmf3"] = {
	pos = {56, 23, 0},
	text_color = {85, 255, 85, 255},
	text_offset = {0,60},
	model = "lmf3",
	anim= "idle_e",
	applydepth = true,
}

items["village2.rat"] = {
	pos = {56,10,0},
	model ="village2.rat",
	anim="idle",
	applydepth = true,
	text_color = {170, 170, 170, 255},
	text_offset = {0,60},
	flipx = true,
}

items["village2.lmf"] = {
	pos = {0, 0, 0},
	hotspot = {
		text = strings.objects.lowmoralfiber,
		size = {60, 60},
		walk_to = {85, 14},
		dir = "west"
	},
	actions = {
		talk = { type = scumm.action.start_dialogue, args = {dialogue="lowmoralfiber"}} 
	}
}

items["village2.citizen"] = {
	pos = {325, 27, 0},
	hotspot = {
		text = strings.objects.citizen,
		walk_to = {360, 27}, 
		dir = "west",
		size = {30, 40},		
		offset = {-15,0}
	},
	model = "citizen",
	--anim = "idle",
	applydepth = true,
	text_color = {255, 85, 85, 255},
	text_offset = {0,60},
	actions = {
		talk = function() 
			local dp = strings.dialogues.citizen
			local lines = (variables.talked_to_citizen == false) and {dp[1]} or {dp[8], dp[9]}
			if (variables.talked_about_map) then
				table.insert(lines, dp[27])
				table.insert(lines, dp[28])
			end
			local s = {
				{ type = action.disable_controls },
				{ type = action.animate, args = { actor="village2.citizen", anim="idle_e" } },
				{ type = action.say, args = {actor="village2.citizen", lines = lines, animstart="talk_start", animend="talk_end" }},
				{ type = action.start_dialogue, args = {dialogue="citizen"}}
			}
			return s
		end
	}
}

scumm.factory.door {
	id = "village2.voodoolady_door",
	pos = {220, 52, -1},
	size = {26, 26},
	walk_to = {220, 48},
	dir = "east",
	model = "door_village_voodoolady",
	nextroom="voodoolady",
	variable = "door_voodoolady"
}

items["village2.fakedoor1"] = {
	pos = {377, 37, -1},
	hotspot = {
		text = strings.objects.door,
		walk_to= {389, 36},
		dir = "west",
		size = {20, 30}	
	},
	actions = {},
	model = "fakedoor_village_1",
	anim="close"
}

items["village2.fakedoor2"] = {
	pos = {208, 59, -1},
	hotspot = {
		text = strings.objects.door,
		walk_to= {206, 58},
		dir = "east",
		size = {10, 20},
		priority = 10,
	},
	actions = {},
	model = "fakedoor_village_2",
	anim="close"
}

