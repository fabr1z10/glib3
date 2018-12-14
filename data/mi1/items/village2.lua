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
	walk_to = {340, 27}, 
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
			s.actions = {
				action.disable_controls {id=1},
				action.say {id=2, actor="village2.citizen", lines = lines, animstart="talkside", animend="idleside" },
				action.start_dialogue{id=3, dialogue="citizen"}
			}
			return s
		end
	}
}