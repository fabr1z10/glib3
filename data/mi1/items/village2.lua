items.village2 = {}

items["village2.archway1"] = {
	text = strings.objects.archway,
	pos = {416, 34, 0},
	walk_to = {436, 35}, 
	face = "north",
	size = {40, 50},			
	actions = {
		walk = ms { {action.change_room, {id=1,room="village1"}}}
	}
}

items["village2.archway2"] = {
	text = strings.objects.archway,
	pos = {146, 63, 0},
	walk_to = {160, 80}, 
	face = "north",
	size = {30, 30},			
	actions = {
		walk = ms { {action.change_room, {id=1,room="village3"}}}
	}
}

items["village2.citizen"] = {
	tag="citizen",
	text = strings.objects.citizen,
	pos = {325, 27, 0},
	walk_to = {360, 27}, 
	face = "west",
	model = "citizen",
	anim ="idle",
	size = {30, 40},	
	offset = {-15,0},		
	applydepth = true,
	text_color = {255, 85, 85, 255},
	text_offset = {0,60},
	actions = {
		talk = function() 
			local s = script:new()
			local dp = strings.dialogues.citizen
			local lines = (variables.talked_to_citizen == false) and {dp[1]} or {dp[8], dp[9]}
			if (variables.talked_about_map) then
				table.insert(lines, dp[27])
				table.insert(lines, dp[28])
			end
			s.actions = {
				action.disable_controls {id=1},
				action.say {id=2, actor="village2.citizen", lines = lines, animstart="talk_start", animend="talk_end" },
				action.start_dialogue{id=3, dialogue="citizen"}
			}
			return s
		end
	}
}

items["village2.lmf1"] = {
	tag="lmf1",
	pos = {18, 10, 0},
	text_color = {255, 85, 255, 255},
	text_offset = {0,60},
	model ="lmf1",
	anim="idle",
	applydepth = true
}

items["village2.lmf2"] = {
	tag="lmf2",
	pos = {44, 20, 0},
	text_color = {85, 255, 255, 255},
	text_offset = {0,60},
	model ="lmf2",
	anim="idle",
	applydepth = true,
}

items["village2.lmf3"] = {
	tag="lmf3",
	pos = {56, 23, 0},
	text_color = {85, 255, 85, 255},
	text_offset = {0,60},
	applydepth = true,
	model ="lmf3",
	anim="idle"

}

items["village2.lmf"] = {
	text = strings.objects.lowmoralfiber,
	pos = {0, 0, 0},
	size = {50, 30},
	walk_to = {70, 18},
	face = "west",
	actions = {
		talk = ms {
			{ action.start_dialogue, {id=1, dialogue="lowmoralfiber"}}

		} 

	}
}

items["village2.rat"] = {
	tag="rat",
	pos = {56,10,0},
	applydepth = true,
	text_color = {170, 170, 170, 255},
	text_offset = {0,60},
	model = "rat",
	anim="idle",
	flip=true

}

items["village2.door_voodoolady"] = factory.door.create {
	name = "village2.door_voodoolady",
	pos = {220, 52, -1},
	size = {26, 26},
	walk_to = {220, 48},
	face = "east",
	door_ref = "door_voodoolady",
	model = "village2.door_voodoo",
	nextroom = "voodoolady"
}