engine.items["bridge.path"] = {
	pos = {0, 0, 0},
	hotspot = {
		text = strings.objects.path,
		size = {16, 144},			
		walk_to = {1, 10}, 
		dir = "west"
	},
	actions = {
		walk = { type = action.change_room, args = {room="meleemap"}}
	}
}

engine.items["bridge.troll"] = {
	pos = {134, 24, 0},
	hotspot = {
		text = strings.objects.troll,
		walk_to = {80, 16}, 
		dir = "east",
		size = {30, 40},		
		offset = {-15,0}
	},
	flipx =true,
	model = "bridge.troll",
	--anim = "idle",
	applydepth = true,
	text_offset = {0, 60},
    text_color = {0, 170, 0, 255},
	actions = {
		talk = function()
			return {
				{ type = action.suspend_script, args = { script ="_troll" }},
				{ type = action.start_dialogue, args = {dialogue="troll"}}
			}
		end
	}
}

-- engine.items["bridge.fish"] = {
-- 	pos = {134, 24, 0},
-- 	flipx = true,
-- 	tag = "bridge.fish",
-- 	model = "bridge.fish",
-- 	anim = "idle"
-- }

-- engine.items["bridge.troll"] = {
-- 	pos = {134, 24, 0},
-- 	flipx = true,
-- 	applydepth = true,
-- 	tag = "troll",
-- 	tagSpeak = "bridge.troll",
-- 	text_offset = {0, 60},
--     text_color = {0, 170, 0, 255},
-- 	-- hotspot	
-- 	text = strings.objects.troll,
-- 	walk_to = {80, 26},
-- 	size = {20, 47},
-- 	offset = {-10, 0},
-- 	face = "east",
-- 	nodes = {
-- 		{ name = "body", tag="bridge.troll.body", model = "bridge.troll.body", anim="idle", fh = { { type="pos"}  } },
-- 		{ name = "head", parent="body", tag="bridge.troll", model = "bridge.troll.head", anim="idle" },
-- 		{ name ="helditem", parent="body", tag="bridge.troll.item" }
-- 	},

-- 	talk_script = function()
-- 		local s = script:new()
-- 		local dp = strings.dialogues.troll
-- 		local lines = (variables.talked_to_troll == false) and {dp[2], dp[3]} or {dp[18]}
-- 		variables.talked_to_troll = true
-- 		s.actions = {
-- 			action.suspend_script {id=1, script="_troll"},
-- 			action.disable_controls {id=2},
-- 			action.say {id=3, actor="bridge.troll", lines = lines, animstart="talk", animend="idle" },
-- 			action.start_dialogue{id=4, dialogue="troll"}
-- 		}
-- 		return s
-- 	end,
	
-- 	actions = {
-- 		give = {}
-- 	}
-- }

-- engine.items["bridge.troll"].actions.talk = engine.items["bridge.troll"].talk_script
