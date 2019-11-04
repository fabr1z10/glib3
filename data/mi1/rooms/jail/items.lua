--engine.items.scummbar = {}
local d = strings.kitchen

engine.items["jail.walkarea"] = scumm.factory.walkarea {
	shape = { type = "poly", outline = {0,14,218,26,320,18,320,0,0,0}},
	priority = 0,
	depth = { type="linear_y", values= {0, 1, 144, 0} },

}
engine.items["jail.walkarea2"] = scumm.factory.walkarea {
	shape = { type = "poly", outline = {24,29,56,30,81,26,81,22,29,19}},
	priority = 0,
	depth = { type="linear_y", values= {0, -1, 144, -2} },

}

engine.items["jail.door"] = {
	pos = {249, 12, 0},
	hotspot = {		
		text = strings.objects.doorway,
		walk_to = {265, 12}, 
		dir = "north",
		size = {33, 53}
	},		
	actions = {
		walk = { type = action.change_room, args = {room="village3"}}
	}
}

engine.items["otis"] = {
	pos = {45, 24, 0},
	--pos = {35, 5, 0},
	hotspot = {
		text = strings.objects.prisoner,
		walk_to = {72, 14},
		size = {20, 45},
		offset = {-10,0},
		dir = "west",
	},	
	text_offset = {0, 60},
    text_color = {255, 255, 85, 255},
	applyDepth = true,
	character = {
		state = "idle",
		dir = "east",
		speed = 50
	},
	model ="otis",
	actions = {
 		look = { type = scumm.action.say, args = {actor="guybrush", lines = {strings.jail[1]}}},
		talk = function()
			if (not variables.talked_to_otis) then
				variables.talked_to_otis = true
				return {
					{type = action.suspend_script, args = { script ="_otis"}},
					{type = scumm.action.disable_controls },
					{type = scumm.action.walkto, args = {tag="otis", pos = {55,19}}},
					{type = scumm.action.say, args = {actor="otis", animstart="idle_e", animend="idle_e", lines = {strings.dialogues.otis[1], strings.dialogues.otis[2]}}},
					{type = scumm.action.turn, args = {tag="player", dir="s"}},
					{type = scumm.action.say, args = {actor="guybrush", lines = {strings.dialogues.otis[3]}}},
					{type = scumm.action.walkto, args = {tag="player", pos = {72, 2}}},
					{type = scumm.action.say, args = {actor="guybrush", lines = {strings.dialogues.otis[4]}}},
					{type = scumm.action.say, args = {actor="otis", animstart="idle_e", animend="idle_e", lines = {strings.dialogues.otis[5]}}},
					{type = action.resume_script, args = { script ="_otis"}},
					{type = scumm.action.disable_controls, args = {value = false}},
				}
			else 
				if (not variables.mint_given) then
					return {type = scumm.action.say, args = {actor="guybrush", lines = {strings.dialogues.otis[6]}}}
				end
			end
		end
		--look = { type = scumm.action.say, args = { actor="guybrush", lines = {strings.dialogues.lookout[50]} }},
		--talk = { type= scumm.action.start_dialogue, args = {dialogue = "lookout"}}
	}
}
