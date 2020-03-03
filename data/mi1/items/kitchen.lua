--engine.items.scummbar = {}
local d = strings.kitchen

local showSeagull = function()
	local actions = {
		{ type = action.remove_object, args = { tag='seagull_sensor'}},
		{ type = action.create_object, args ={ factory = scumm.factory.object, args = { id='kitchen.seagull'}}},
		{ type = action.animate, args = { tag='kitchen.seagull', anim='fly', sync=true}},
		{ type = action.animate, args = { tag='kitchen.seagull', anim="eat" }},
		{ type = action.set_variable, args = {var='seagull_on_board', value=true}}
	}
	local s = script.make(actions)
	monkey.play(s)
end

local seagull_return = function() 
	if (variables.fish_taken == true) then
		return {
			{ type = action.remove_object, args ={tag="kitchen.seagull"}}
		}
	else 
		variables.seagull_on_board = true
		variables.seagull_jump = (variables.seagull_jump == 1) and 2 or 1
		return {		
			{ type = action.animate, args = {tag="kitchen.seagull", anim="eat", sync=true }},
		}
	end
end

local seagull_jump = function()
	local n = (variables.seagull_jump == 1) and 2 or 1
	return {	
		{ type = action.set_variable, args = {var="seagull_on_board", value=false}},
		{ ref = 1, type = action.animate, args = {tag="kitchen.seagull", anim="jump" .. tostring(variables.seagull_jump), sync=true }},
		{ type = action.runscript, args = {func = seagull_return}}
	}
end


local push_plank = function() 
	local a = nil
	if variables.seagull_on_board then
		a = { type = action.runscript, after={1}, args = {func = seagull_jump}}
	end

	return {
		{ ref = 1, type = action.animate, args = {tag="player", anim="plank", sync = true }},
		{ type = action.animate, args = {tag="player", anim="idle_s"}},
		{ type = action.animate, after={1}, args = {tag="kitchen.plank", anim="pushed", sync = true}},
		{ type = action.animate, args = {tag="kitchen.plank", anim="idle" }},
		a
	}
end

local pushPlank = function()
	local actions = {
		{ type = scumm.action.walkto, args = {tag="player", pos={292,8}}},
		{ type = action.turn, args = {tag="player", dir="south" }},
		{ type = action.runscript, args = {func = push_plank }}
	}
	local s = script.make(actions)
	monkey.play(s)	
end

engine.items["kitchen.walkarea"] = {
	type = 'walkarea',
	tag = true,
	shape = { 
		type = "poly", 
		outline = {40,16,59,21,155,21,180,18,192,18,294,18,307,12,199,9,207,0,160,0,149,11,112,11,100,0,40,0}
	},
	blockedlines = {
	 	{ A = {190, 0}, B = {190, 144}, active =true },
	 	{ A = {206, 0}, B = {206, 144}, active =true },
	},
	depth = { type="linear_y", values= {0, 1, 144, 0} },	
}

engine.items["kitchen.trap"] = {
	type = 'trap',
	tag="seagull_sensor",
	pos = {100, 10, 0}, 
	shape = {type="rect", width=10, height = 10}, 
	onenter = showSeagull
}

engine.items["kitchen.seagull"] = {
	type = 'object',
	tag = true,
 	pos = {0, 0, 1},
 	model = "kitchen.seagull",
}

engine.items["kitchen.plank"] = {
	type = 'object',
	tag = true,	
 	pos = {248, 0, 1},
 	model="kitchen.plank", 
}

engine.items['kitchen.plankhotspot'] = {
	type = 'hotspot',
	pos = {290, 5, 0},
	shape = { type = 'rect', width = 20, height=10},
	--onenter = function() print ('enter') end,
	onclick = pushPlank,
}

engine.items["kitchen.meat"] = { 
	type = 'object',
	tag = true,
	pos = {79, 40, -1},
	hotspot = {
		text = strings.objects.meat,	
		size = {20, 20},
		walk_to = {90, 18},
		dir = "north"
	},
 	model = "kitchen.meat",
 	actions = {
 		pick = {
 			scumm.script.pickup { id="kitchen.meat", anim_start="operate_n", anim_end="idle_n"},
 			--{ type = scumm.action.say, args = { tag = 'player', lines = {strings.kitchen[1]}}}	
 		},
 		look = { type = scumm.action.say, args = { tag = 'player', lines = {strings.kitchen[1]}}}
 	}	
}

engine.items["kitchen.pot"] = {
	type = 'object',
	tag = true, 
 	pos = {104, 24, -1},
	hotspot = {
		text = strings.objects.pot,
		size = {15, 7},
	 	walk_to = { 112, 18},
	 	dir = 'n'
	},
	model = 'kitchen.pot',
 	actions = {
 		pick = scumm.script.pickup { id="kitchen.pot", anim_start='kneel_n', anim_end='idle_n'},
 		look = { type = scumm.action.say, args ={tag="player", lines = {strings.kitchen[2] }}},
 		give = {
			["circus.greenclown"] = circus_cutscene,
 			["circus.purpleclown"] = circus_cutscene
 		}
	}
}

engine.items["kitchen.fish"] = {
	type = 'object',
	tag = true, 	
	pos = {234, 9, 1},
	hotspot = {
		text = strings.objects.fish,	
		size = {12, 7},
		walk_to = {234, 12},
		dir='south',
	},
	model = 'kitchen.fish',
	actions = {
		pick = function()
			if (variables.seagull_on_board == false) then
				variables.fish_taken = true
				return scumm.script.pickup { id='kitchen.fish', anim_start='kneel_s', anim_end='idle_s' }
			else
				return {
					{ type = action.animate, args = {tag="player", anim="kneel_s"}},
					{ type = action.delay, args = {sec=0.5}},
					{ type = action.animate, args = {tag="player", anim="idle_s"}},
					{ type = scumm.action.say, args ={tag="player", lines= {strings.kitchen[4]}}}
				}
			end
		end,
		look = { type = scumm.action.say, args = {tag='player', lines = {strings.kitchen[3] }}},
		give = {	
			["bridge.troll"] = { 
				{ type = scumm.action.disable_controls, args = nil},
				{ ref = 1, type = action.suspend_script, args = {script="_troll"}},
				{ type = action.remove_object, args = {tag="troll_sensor"}},
				{ ref = 2, type = action.animate, 
					after={1}, 
					args ={tag="bridge.troll", anim="pickup_fish", sync = true}},
				{ ref = 3, type = scumm.action.say, 
                    after={1}, 
                    args={actor="bridge.troll", lines={ strings.dialogues.troll[48] }, animate = false}},
				{ type = scumm.action.say, after={2, 3}, args={actor="bridge.troll", lines={ strings.dialogues.troll[49] }, animstart="talk_fish", animend="idle_fish"}},
				{ type = scumm.action.walkto, args ={tag="player", pos={209, 60}}},
				{ type = scumm.action.turn, args ={tag="player", dir = "north"}},
				{ type = action.animate, args= {tag="bridge.troll", anim="fish_cutscene", sync=true}},
				{ type = scumm.action.turn, args = {tag="player", dir="south"}},
				{ type = action.delay, args ={ sec = 1}},
				{ type = scumm.action.turn, args = {tag="player", dir="north"}},
				{ type = action.set_variable, args = {var="troll_fed", value=true}},
				{ type = action.change_room, args = {room="meleemap"}}
			}

		}
	}
}


engine.items["kitchen.table"] = { 
	pos = {114, 0, 1},
	hotspot = {
		text = strings.objects.kitchen_table,
		size = {35, 22},
		walk_to = {130, 6},
		dir="south"
	},	
	model = "kitchen.table",
	actions = {
	}
}

local df = strings.dialogues.fettbros

local circus_cutscene = {
	{ type = scumm.action.disable_controls, args = {value=true} },
	{ type = action.animate, args = {tag="player", anim="show_pot", sync = true}},
	{ type = scumm.action.say, args = {actor="circus.greenclown", lines = {df[82]} }},
	{ type = action.animate, args = {tag="player", anim="show_pot", fwd = false, sync=true}},
	{ type = scumm.action.say, args = {actor="circus.purpleclown", lines = {df[83]}}},
	{ ref=1, type = scumm.action.say, args = {actor="circus.greenclown", lines = {df[84]}}},
	{ ref=2, type = scumm.action.walkto, after={1}, args = {tag = "circus.purpleclown", pos={333, 1}}},
	{ ref=3, type = scumm.action.walkto, after={1}, args = {tag = "circus.greenclown", pos={296, 24}}},
	{ ref=4, type = scumm.action.walkto, after={1}, args = {tag = "player", pos={250, 24}}},
	{ type = action.scroll, after={1}, args = {by = {48, 0}, speed = 50}},
	{ ref=5, type = scumm.action.turn, after={2}, args = {tag="circus.purpleclown", dir="north" }},
	{ ref=6, type = scumm.action.turn, after={3}, args = {tag="circus.greenclown", dir="west" }},
	{ ref=7, type = scumm.action.turn, after={4}, args = {tag="player", dir="south" }},
	{ type = scumm.action.say, after = {5,6,7}, args = {actor="circus.purpleclown", lines = {df[85]}}},
	{ type = scumm.action.say, args = {actor="circus.greenclown", lines = {df[86]} }},
	{ type = scumm.action.say, args = {actor="circus.purpleclown", lines = {df[87]} }},
	{ type = scumm.action.walkto, args = {tag="player", pos={264, 23}}},
	{ type = scumm.action.turn, args = {tag="player", dir="east" }},
	{ type = scumm.action.say, args = {actor="guybrush", lines ={df[88]}}},
	{ type = scumm.action.walkto, args = {tag="player", pos={250, 24}}},
	{ type = scumm.action.turn, args = {tag="player", dir="south" }},
	{ type = action.animate, args = {tag="player", anim="get_in_cannon", sync = true}},
	{ ref = 8, type = action.activate, args = {tag="player", active=false}},
	{ ref = 9, type = action.create_object, after = {8}, args = { factory = scumm.factory.object, args = { id="circus.explosion"}}},
	{ ref = 10, type = action.create_object, after = {8}, args = { factory = scumm.factory.object, args = { id="circus.flyingguybrush"}}},
	{ type = action.animate, after={9}, args = {tag="circus.explosion", anim="default", sync=true}},
	{ type = action.remove_object, args = { tag="circus.explosion" }},
	{ type = action.animate, after={10}, args = {tag="circus.flyingguybrush", anim="default", sync=true}},
	{ type = scumm.action.say, args = {actor="circus.purpleclown", lines = {df[89]} }},
	{ ref = 11, type = scumm.action.say, args = {actor="circus.greenclown", lines = {df[90]} }},
	{ type = scumm.action.walkto, after = {11}, args = {tag="circus.purpleclown", pos={87, 29}}},
	{ ref = 12, type = scumm.action.turn, args = {tag="circus.purpleclown", dir="east"}},
	{ type = scumm.action.walkto, after = {11}, args = {tag="circus.greenclown", pos={126,29}}},
	{ ref = 13, type = scumm.action.turn, args = {tag="circus.greenclown", dir="west"}},
	{ type = scumm.action.say, after = {12, 13}, args = {actor="circus.purpleclown", lines = {df[91]} }},
	{ type = scumm.action.say, args = {actor="circus.greenclown", lines = {df[92]}}},
	{ type = action.set_variable, args = { var = "circus_feat_done", value=true}},
	{ type = scumm.action.add_to_inventory, args = { id="pieces_of_eight", qty = 478}},
	{ type = scumm.action.remove_from_inventory, args = { id="kitchen.pot" }},
	{ type = scumm.action.disable_controls, args = {value=false} },
	{ type = scumm.action.start_dialogue, args = { dialogue="fettuccini", root=15 }}
}





engine.items['kitchen.potostew'] = {
	type = 'object',
 	model = 'kitchen.potostew',
 	pos = {153, 39, -1},
	hotspot = {
		text = strings.objects.potostew,
		size = {32, 19},
		walk_to = {170, 35},
		dir = 'n'
	},
 	actions = {
		use = {
			["kitchen.meat"] = {
				{ type = action.animate, args = {tag="player", anim="operate_n"}},
				{ type = action.delay, args = {sec=0.5}},
				{ type = action.animate, args = {tag="player", anim="idle_n"}},
				{ type = scumm.action.remove_from_inventory, args = {id="kitchen.meat"}},
				{ type = action.set_variable, args = {var="meat_in_pot", value = true}}
			}
		},
 		look = function() 
 			local line = variables.meat_in_pot and 9 or 5
			return { type = scumm.action.say, args = {tag='player', lines={strings.kitchen[line]}} }
 		end,
		pick = function()
			if (variables.meat_in_pot) then
				return {
 					{ type = action.animate, args = {tag="player", anim="operate_n"}},
 					{ type = action.delay, args = {sec=0.5}},
 					{ type = action.animate, args = {tag="player", anim="idle_n"}},
 					{ type = scumm.action.change_text_item, args = {id="kitchen.meat", text = strings.objects.stewedmeat }},
 					{ type = scumm.action.add_to_inventory, args = {id="kitchen.meat"}}
				}
			else
				return script.defaultactions.pickup
			end
		end
	}
}

engine.items['kitchen.door'] = make_door { 
	tag ='kitchen.door',
	model = 'door_kitchen_scummbar',	
	pos = {19, 18, -1},
	size = {38, 53},
	walk_to = {45, 12},
	dir = 'w',
	var = "door_scummbar_kitchen",
	go_to = {
		room = 'scummbar',
		pos = mi.rooms.scummbar.door_kitchen,
		dir = 'w'
	}
}

engine.items['kitchen.door.pier'] = {
	type = 'object',
	tag = true,
	model = 'door_kitchen_pier',
	anim = function() return variables.door_kitchen_pier == 0 and 'close' or 'open' end,
	pos = {192, 9, -1},
	hotspot = {
		text = strings.objects.door,
		size = {20, 64},
		walk_to = {182, 9},
		dir = 'e'
	},
	actions = {
		open = {
			{ type = scumm.action.enable_wall, args = {walkarea = "kitchen.walkarea", wall=0, active=false}},	
	 		{ type = scumm.action.enable_wall, args = {walkarea = "kitchen.walkarea",wall=1, active=false}},
	 		{ type = action.animate, args = {tag="kitchen.door.pier", anim="open"}}
		},
		close = {
	 		{ type = scumm.action.enable_wall, args = {walkarea = "kitchen.walkarea",wall=0, active=true}},
 			{ type = scumm.action.enable_wall, args = {walkarea = "kitchen.walkarea",wall=1, active=true}},
 			{ type = action.animate, args = {tag="kitchen.door.pier", anim="close"}}
		}

	}

}

