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
 	pos = {248, 0, 1},
 	model="kitchen.plank", 
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
				print ("QUIAIIFJEIWFJ")
				return glib.curry(scumm.action.pickup2, { id="kitchen.fish", anim1="kneel_s", anim2="idle_s"})()
				--refeturn action.combo.pickup ("kitchen.fish", "kneel_s", "idle_s")
			else
				return {
					{ type = action.animate, args = {tag="player", anim="kneel_s"}},
					{ type = action.delay, args = {sec=0.5}},
					{ type = action.animate, args = {tag="player", anim="idle_s"}},
					{ type = scumm.action.say, args ={actor="guybrush", lines= {strings.kitchen[4]}}}
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

-- 		pickup = function() 
-- 			local a = nil
-- 			if (variables.meat_in_pot) then
-- 				a = ms {
-- 					{ action.animate, {id=1, actor="guybrush", anim="operate_back"}},
-- 					{ action.delay, {id=2, sec=0.5}},
-- 					{ action.animate, {id=3, actor="guybrush", anim="idle_back"}},
-- 					{ action.change_text_item, {id=4, name="kitchen.meat", text = strings.objects.stewedmeat }},
-- 					{ action.add_to_inventory, {id=5, name="kitchen.meat", qty=1}},
-- 				}
-- 			else
-- 				a = script.defaultactions.pickup
-- 			end
-- 			return a()

-- 		end,
-- 		use = {
-- 		}
-- 	}
-- }
--[[
make_door {
	tag = 'scummbar.door.out',
	model = 'door_scummbar_village',
	pos = {32, 24, -1},
	size = {38, 47},
	walk_to = mi.rooms.scummbar.door_out,
	dir = 'w',
	var = 'door_village_scummbar',
	go_to = {
		room = 'village1',
		pos = mi.rooms.village1.door,
		dir = 's'
	}
}--]]


engine['kitchen.door'] = make_door { 
	tag ='kitchen.door',
	model = 'door_kitchen_scummbar',	
	pos = {19, 18, -1},
	size = {38, 53},
	walk_to = {36, 16},
	dir = 'w',
	var = "door_scummbar_kitchen",
	go_to = {
		room = 'scummbar',
		pos = mi.rooms.scummbar.door_kitchen,
		dir = 'e'
	}
}

-- scumm.factory.door {
-- 	id = "kitchen.door.pier",
-- 	pos = {192, 9, -1},
-- 	size = {20, 64},
-- 	walk_to = {182, 9},
-- 	dir = "east",
-- 	model = "door_kitchen_pier",
-- 	nextroom = nil,
-- 	variable = "door_kitchen_pier",
-- 	open = function() return {
-- 		{ type = scumm.action.enable_wall, args = {walkarea = "kitchen.walkarea", wall=0, active=false}},
-- 		{ type = scumm.action.enable_wall, args = {walkarea = "kitchen.walkarea",wall=1, active=false}},
-- 		{ type = action.animate, args = {tag="kitchen.door.pier", anim="open"}}}
-- 	end,
-- 	close = function() return {
-- 		{ type = scumm.action.enable_wall, args = {walkarea = "kitchen.walkarea",wall=0, active=true}},
-- 		{ type = scumm.action.enable_wall, args = {walkarea = "kitchen.walkarea",wall=1, active=true}},
-- 		{ type = action.animate, args = {tag="kitchen.door.pier", anim="close"}}}
-- 	end,
-- 	walk = function() return nil end
-- }
-- engine.items["kitchen.door_pier"] = factory.door.create {
-- 	name ="kitchen.door_pier",	
-- 	pos = {192, 9,-1},
-- 	size = {40, 64},
-- 	walk_to = {182, 9},
-- 	face = "east",
-- 	door_ref = "door_kitchen_pier",
-- 	model = "door_kitchen_pier",
-- 	open = function()
-- 		variables.door_kitchen_pier = 1
-- 		local s = script:new()
-- 		s.actions = {
-- 			action.enable_wall { id = 1, wall=0, active = false},
-- 			action.enable_wall { id = 2, wall=1, active = false},
-- 			action.animate {id = 3, actor="kitchen.door_pier", anim="open" }
-- 		}
-- 		return s
-- 	end,
-- 	close = function()
-- 		variables.door_kitchen_pier = 1
-- 		local s = script:new()
-- 		s.actions = {
-- 			action.enable_wall { id = 1, wall=0, active = true},
-- 			action.enable_wall { id = 2, wall=1, active = true},
-- 			action.animate {id = 3, actor="kitchen.door_pier", anim="close" }
-- 		}
-- 		return s
-- 	end,
-- 	walk = function()
-- 		return nil
-- 	end
-- }


-- engine.items["kitchen.table"] = {
-- 	text = strings.objects.kitchen_table,
-- 	pos = {114, 0, 1},
-- 	size = {35, 22},
-- 	model = "kitchen_table",
-- 	anim = "default",
-- 	walk_to = {130, 6},
-- 	face = "south",
-- 	actions = {

-- 	}
-- }



-- engine.items["kitchen.potostew"].actions.use["kitchen.meat"] = ms {
-- 	{ action.animate, {id=1, actor="guybrush", anim="operate_back"}},
-- 	{ action.delay, {id=2, sec=0.5}},
-- 	{ action.animate, {id=3, actor="guybrush", anim="idle_back"}},
-- 	{ action.remove_from_inventory, {id=4, name="kitchen.meat"}},
-- 	{ action.set_variable, { id=5, var="meat_in_pot", value = true}}
-- }





-- engine.items["kitchen.pot"].actions.give["circus.purpleclown"] = function() 
-- 	local s = script:new()
-- 	local d = strings.dialogues.fettbros
-- 	local explTag = nextTag()
-- 	local fgTag = nextTag()
-- 	s.actions = {
-- 		action.disable_controls{id=1},
-- 		action.animate_once {id=2, actor="guybrush", anim="pot_out"},
-- 		action.animate {id=3, actor="guybrush", anim="show_pot"},
-- 		action.say {id=4, actor="circus.greenclown", lines = {d[82]} },
-- 		action.animate_once {id=5, actor="guybrush", anim="pot_in"},
-- 		action.animate {id=6, actor="guybrush", anim="idle_front"},
-- 		action.say {id=7, actor="circus.purpleclown", lines = {d[83]} },
-- 		action.say {id=8, actor="circus.greenclown", lines = {d[84]} },
-- 		action.walkto {id=9, actor="circus.purpleclown", pos={333, 1}, after={8} },
-- 		action.walkto {id=10, actor="circus.greenclown", pos={296, 24}, after={8} },
-- 		action.walkto {id=11, actor="guybrush", pos={250, 24},after={8}},
-- 		action.scroll {id=12, by = {48, 0}, speed = 50, after={8} },
-- 		action.turn {id =13, actor="circus.purpleclown", dir="north", after={9} },
-- 		action.turn {id =14, actor="circus.greenclown", dir="west", after={10} },
-- 		action.turn {id =15, actor="guybrush", dir="south", after={11} },
-- 		action.say {id=16, actor="circus.purpleclown", after={13,14,15}, lines = {d[85]} },
-- 		action.say {id=17, actor="circus.greenclown", lines = {d[86]} },
-- 		action.say {id=18, actor="circus.purpleclown", lines = {d[87]} },
-- 		action.walkto { id=19, actor="guybrush", pos={264, 23} },
-- 		action.turn {id=20, actor="guybrush", dir="east" },
-- 		action.say {id=21, actor="guybrush", lines ={d[88]}},
-- 		action.walkto {id=22, actor="guybrush", pos={250, 24}},
-- 		action.turn {id=23, actor="guybrush", dir="south"},
-- 		action.animate_once {id = 24, actor="guybrush", anim="get_in_cannon" },
-- 		action.activate {id=25, name="guybrush", value=false},
-- 		action.create_object {id = 26, name="circus.explosion", tag = explTag, pos ={0,0,0}, after={25}},
-- 		action.create_object {id = 27, name="circus.flyingguybrush", tag = fgTag, pos ={0,0,0}, after={25}},
-- 		action.animate_once {id = 28, tag = explTag, anim="default", after={26}},
-- 		action.animate_once {id = 29, tag = fgTag, anim="default", after={27}},
-- 		action.remove_object {id=30, after={28}, tag = explTag },
-- 		action.animate {id=31, tag=fgTag, anim="end", after={29}},
-- 		action.delay {id=32, sec=0.5},
-- 		action.say {id=33, actor="circus.purpleclown", lines = {d[89]} },
-- 		action.say {id=34, actor="circus.greenclown", lines = {d[90]} },
-- 		action.walkto { id=35, actor="circus.purpleclown", pos={87, 29}, after={34}},
-- 		action.walkto { id=36, actor="circus.greenclown", pos={126,29}, after={34}},
-- 		action.turn { id=37, actor="circus.purpleclown", dir="east", after={35}},			
-- 		action.turn { id=38, actor="circus.greenclown", dir="west", after={36}},	
-- 		action.say {id=39, actor="circus.purpleclown", after={37, 38}, lines = {d[91]} },
-- 		action.say {id=40, actor="circus.greenclown", lines = {d[92]} },
-- 		action.start_dialogue {id = 41, dialogue="fettuccini", root=dialogues.fettuccini.nodes[15]}
-- 	}
-- 	return s
-- end



-- engine.items["kitchen.fish"] = {
-- 	tag="kitchen.fish",
-- 	text = strings.objects.fish,	
-- 	pos = {234, 9, 1},
-- 	size = {12, 7},
-- 	walk_to = {234, 12},
-- 	face="south",
-- 	model = "kitchen_fish",
-- 	anim = "default",
-- 	actions = {
-- 		pickup = function()
-- 			local a = nil
-- 			if (variables.seagull_flying == true) then
-- 				a = pick_up_item("kitchen.fish", "kneel_front")
-- 			else
-- 				a = ms {
-- 					{ action.animate, {id=1, actor="guybrush", anim="kneel_front"}},
-- 					{ action.delay, {id=2, sec=0.5}},
-- 					{ action.animate, {id=3, actor="guybrush", anim="idle_front"}},
-- 					{ action.say, {id=4, actor="guybrush", lines= {d[4]}}}
-- 				}
-- 			end
-- 			return a()
-- 		end,
-- 		look = ms {
-- 			{ action.say, { id=1, actor="guybrush", lines = {d[3] }}}
-- 		},
-- 		give = {}

-- 	}
-- }

-- engine.items["kitchen.fish"].actions.give["bridge.troll"] = function()
-- 	local dp = strings.dialogues.troll
-- 	local s = script:new()
-- 	s.actions = {
-- 		action.disable_controls {id=1},
-- 		action.suspend_script {id=2, after={1}, script="_troll"},
-- 		action.animate_once {id=3, after={2}, tag="bridge.troll.body", anim="take_fish"},
-- 		--action.animate {id=3, after={2}, actor="bridge.troll", anim="wait_fish"},
-- 		action.say { id= 4, after={2}, actor="bridge.troll", lines={dp[48]}, animstart="talk", animend="idle"},
-- 		action.animate {id=5, actor="guybrush", anim="operate_right", after={3} },
-- 		action.create_object {id = 6, name="bridge.fish" },
-- 		action.animate_once {id=7, after={5}, tag="bridge.troll.body", anim="hold_fish"},
-- 		action.animate {id=8, after={5}, actor="guybrush", anim="idle_right"},
-- 		action.say { id= 9, after={7}, actor="bridge.troll", lines={dp[49]}, animstart="talk", animend="idle"},
-- 		action.walkto { id = 10, actor="guybrush", pos= {211,55}},
-- 		action.turn { id = 11, actor="guybrush", dir="north"},
-- 		action.flip {id=12, tag="troll", flip=false},
-- 		action.animate {id=13, tag="bridge.troll.body", anim="idle_front", after={12} },
-- 		action.animate {id=14, tag="bridge.troll", anim="look_around", after={12} },
-- 		action.delay {id=15, sec=2},
-- 		action.animate {id=16, tag="bridge.troll.body", anim="eat_s1", after={15} },
-- 		action.animate {id=17, tag="bridge.troll", anim="look_front", after={15} },


-- 		--action.delay {id = 6, sec=0.5},
-- 		--action.animate {id=7, after={6}, actor="guybrush", anim="idle_right" },
		


-- 	}
-- 	return s
-- end

