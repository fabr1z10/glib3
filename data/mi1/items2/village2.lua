-- generally, an item is a blueprint for an object
-- * it can have graphics attached. To do so, model needs to be specified
items2["village2.archway_to_village1"] = {
	hotspot = {
		text = strings.objects.archway,
		walk_to = {436, 35}, 
		dir = "north",
		size = {40, 50},			
	},
	actions = {
		walk = ms { {action.change_room, {id=1,room="village1"}}}
	},
	pos = {416, 34, 0},
}

items2["village2.archway_to_village3"] = {
	hotspot = {
		text = strings.objects.archway,
		walk_to = {160, 80},
		dir="north",
		size={30, 30},

	},
	actions = {
		walk = ms { {action.change_room, {id=1,room="village3"}}}
	},
	pos = {146, 63, 0},
}

items2["village2.citizen"] = {
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