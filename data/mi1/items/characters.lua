local text_offset = {0, 60}
local speed = 500
local normal_speed = 100

engine.items["guybrush"] = {
	type = 'char',
	model = 'guybrush',
	state = 'idle',
	speed = speed,
	text_color = {255, 255, 255, 255},
	text_offset = text_offset,
	collide = {
		size = {10, 1},
		offset = {-5, 0},
		tag = 1,
		flag = 1,
		mask = 2
	}
}

engine.items["lookout.lookout"] = {
	type = 'char',
	model ="lookout.lookout",
	tag =true,
	text_offset = {0, 60},
    text_color = {170, 170, 170, 255},
	state = 'idle',
	dir = 'west',
	speed = normal_speed,
	pos = {114, 36, 0},
	hotspot = {
		text = strings.objects.lookout,
		walk_to = {134, 36},
		size = {20, 47},
		offset = {-10,0},
		dir = "west",
	},
	actions = {
		look = { type = scumm.action.say, args = { tag="player", lines = {strings.dialogues.lookout[50]} }},
		talk = { type= scumm.action.start_dialogue, args = {dialogue = "lookout"}}
	}
}
engine.items["fester"] = {
	type = 'char',
	model ="fester",
	tag =true,
	pos = {0,0,0},
	text_offset = {0, 60},
    text_color = {255, 85, 85, 255},
	--applyDepth = true,
	state = "idle",
	dir = "east",
	speed = normal_speed,
	actions = {}
}

engine.items["storekeeper"] = {
 	type = 'char',
 	model = 'shop.shopkeeper',
	tag = true,	
	pos = {289, 7, 0},
 	hotspot = {
		size = {20, 40},
	 	offset ={-10,0},
	 	text = strings.objects.storekeeper,
		walk_to = {229, 7},
		dir = "east"
	},
	state = "idle",
	dir = "west",
	speed = normal_speed,
 	text_offset = {0, 60},
    text_color = {255, 85, 255, 255},
 	actions = {
		talk = { 
			{ type = action.suspend_script, args = {script="_shopkeeper"}},
			{ type = scumm.action.start_dialogue, args = {dialogue ="storekeeper"}},
		}
	}
 }




engine.items["scummbar.cook"] = {
	type = 'char',
	tag=true,
 	model = 'cook',
 	state = 'idle',
 	speed = normal_speed,
 	text_color = mi.data.cook_text_color,
 	text_offset = {0, 60}
 }



engine.items['mancomb.guybrush'] = {
	tag = 'player',
	type = 'mockchar',
	pos = {200, 100, 0},
	text_color = {255, 255, 255, 255},
	text_offset = {0, 0}
}


engine.items['loompirate.guybrush'] = {
	tag = 'player',
	type = 'mockchar',
	pos = {20, 100, 0},
	text_color = {255, 255, 255, 255},
	text_offset = {0, 0}
}

engine.items['estevan.guybrush'] = {
	tag = 'player',
	type = 'mockchar',
	pos = {20, 100, 0},
	text_color = {255, 255, 255, 255},
	text_offset = {0, 0}
}

engine.items["scummbar.ilp1"] = {
	type = 'char',
	model = 'scummbar.ilp1', 	
	tag = true,		
	pos = {376, 11, 0.95},
	text_color = {85, 85, 255, 255},
	text_offset = {0, 60},
	state = 'idle',
	speed = 0,
	dir='e'
}

engine.items["scummbar.ilp2"] = {
	type = 'char',
	model = 'scummbar.ilp2', 	
	tag = true,		
	pos = {413, 11, 0.95},
	text_color = {255, 255, 85, 255},
	text_offset = {0, 60},
	state= 'idle',
	dir = 'east',
	speed = 0
}

engine.items["scummbar.ilp3"] = {
	type = 'char',
	model = 'scummbar.ilp3', 	
	tag = true,			
	pos = {444, 18, 0.95},
	text_color = {255, 85, 255, 255},
	text_offset = {0, 60},
	state = "idle",
	dir = "east",
	speed = 0
}

engine.items["village2.lmf1"] = {
	type = 'object',
	model = "low_moral_fiber_1",
	anim = 'rock',
	tag = true,
	pos = {18, 10, 0},
	info = { id = 'village2.lmf1'},
	text_color = {255, 85, 255, 255},
	text_offset = {0,60},
	speed = 0
	
	
}

engine.items["village2.lmf2"] = {
	type = 'object',
	model = "low_moral_fiber_2",	
	tag = true,
	pos = {44, 20, 0},
	text_color = {85, 255, 255, 255},
	text_offset = {0,60},
	-- in order to use the SAY action, I need to add an id to the info, 
	-- so say can read the text_color and text_offset here!
	info = { id = 'village2.lmf2'},
	anim= "idle",
	speed = 0,
}

engine.items["village2.lmf3"] = {
	type = 'object',
	model = "low_moral_fiber_3",
	tag = true,
	pos = {56, 23, 0},
	text_color = {85, 255, 85, 255},
	text_offset = {0,60},
	info = { id = 'village2.lmf3'},
	anim= "idle_e",
	speed = 0
}

engine.items["village2.rat"] = {
	type = 'object',
	model ="village2.rat",
	tag =true,
	pos = {56,10,0},
	anim="idle",
	applydepth = true,
	text_color = {170, 170, 170, 255},
	info = { id = 'village2.rat'},	
	text_offset = {0,60},
	flipx = true,
}

engine.items["village2.citizen"] = {
	type = 'object',
	tag =true,
	pos = {325, 27, 0},
	hotspot = {
		text = strings.objects.citizen,
		walk_to = {360, 27}, 
		dir = "west",
		size = {30, 40},		
		offset = {-15,0}
	},
	model = "citizen",
	text_color = {255, 85, 85, 255},
	text_offset = {0,60},
	info = { id = 'village2.citizen'},	
	actions = {
		talk = function() 
			local dp = strings.dialogues.citizen
			local lines = (variables.talked_to_citizen == false) and {dp[1]} or {dp[8], dp[9]}
			if (variables.talked_about_map) then
				table.insert(lines, dp[27])
				table.insert(lines, dp[28])
			end
			local s = {
				{ type = scumm.action.disable_controls },
				{ type = action.animate, args = { tag="village2.citizen", anim="idle_e" } },
				{ type = scumm.action.say, args = {tag="village2.citizen", lines = lines, animstart="talk_e", animend="idle_e" }},
				{ type = scumm.action.start_dialogue, args = {dialogue="citizen"}}
			}
			return s
		end
	}
}

