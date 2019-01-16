items["bridge.path"] = {
	text = strings.objects.path,
	pos = {0, 0, 0},
	size = {16, 144},			
	walk_to = {1, 10}, 
	face = "west",
	actions = {
		walk = ms { {action.change_room, {id=1,room="meleemap"}}}
	}
}

items["bridge.troll"] = {
	tag = "bridge.troll",
	text_offset = {0, 60},
    text_color = {0, 170, 0, 255},
	text = strings.objects.troll,
	pos = {134, 24, 0},
	walk_to = {80, 26},
	size = {20, 47},
	offset = {-10,0},
	face = "east",
	model ="bridge.troll",
	anim ="idle",
	applydepth = true,
	flip = true,
	talk_script = function()
		local s = script:new()
		local dp = strings.dialogues.troll
		local lines = (variables.talked_to_troll == false) and {dp[2], dp[3]} or {dp[18]}
		variables.talked_to_troll = true
		s.actions = {
			action.suspend_script {id=1, script="_troll"},
			action.disable_controls {id=2},
			action.say {id=3, actor="bridge.troll", lines = lines, animstart="talk", animend="idle" },
			action.start_dialogue{id=4, dialogue="troll"}
		}
		return s
	end,
	actions = {
		give = {}
	}
}

items["bridge.troll"].actions.talk = items["bridge.troll"].talk_script
