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
				action.say {id=2, actor="village2.citizen", lines = lines, animstart="talkside", animend="idleside" },
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
	anim="idle"
}

items["village2.lmf2"] = {
	tag="lmf2",
	pos = {44, 20, 0},
	text_color = {85, 255, 255, 255},
	text_offset = {0,60},
	model ="lmf2",
	anim="idle"
}

items["village2.lmf3"] = {
	tag="lmf3",
	pos = {56, 23, 0},
	text_color = {85, 255, 85, 255},
	text_offset = {0,60},
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

	}
}