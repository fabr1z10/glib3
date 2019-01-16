--items.scummbar = {}
local d = strings.kitchen

items["kitchen.door"] = factory.door.create {
	name = "kitchen.door",
	pos = {19, 18, -1},
	size = {38, 53},
	walk_to = {32, 18},
	face = "west",
	door_ref = "door_scummbar_kitchen",
	model = "door_kitchen",
	nextroom = "scummbar"
}

items["kitchen.door_pier"] = factory.door.create {
	name ="kitchen.door_pier",	
	pos = {192, 9,-1},
	size = {40, 64},
	walk_to = {182, 9},
	face = "east",
	door_ref = "door_kitchen_pier",
	model = "door_kitchen_pier",
	open = function()
		variables.door_kitchen_pier = 1
		local s = script:new()
		s.actions = {
			action.enable_wall { id = 1, wall=0, active = false},
			action.enable_wall { id = 2, wall=1, active = false},
			action.animate {id = 3, actor="kitchen.door_pier", anim="open" }
		}
		return s
	end,
	close = function()
		variables.door_kitchen_pier = 1
		local s = script:new()
		s.actions = {
			action.enable_wall { id = 1, wall=0, active = true},
			action.enable_wall { id = 2, wall=1, active = true},
			action.animate {id = 3, actor="kitchen.door_pier", anim="close" }
		}
		return s
	end,
	walk = function()
		return nil
	end
}


items["kitchen.table"] = {
	text = strings.objects.kitchen_table,
	pos = {114, 0, 1},
	size = {35, 22},
	model = "kitchen_table",
	anim = "default",
	walk_to = {130, 6},
	face = "south",
	actions = {

	}
}

items["kitchen.potostew"] = {
	text = strings.objects.potostew,
	pos = {153, 39, -1},
	size = {32, 19},
	model = "potostew",
	anim = "default",
	walk_to = {170, 35},
	face ="north",
	actions = {
		look = function() 
			local line = variables.meat_in_pot and 9 or 5
			local a = ms {
				{action.say, {id=1, actor="guybrush", lines={d[line]}} }
			}
			return a()
		end,
		pickup = function() 
			local a = nil
			if (variables.meat_in_pot) then
				a = ms {
					{ action.animate, {id=1, actor="guybrush", anim="operate_back"}},
					{ action.delay, {id=2, sec=0.5}},
					{ action.animate, {id=3, actor="guybrush", anim="idle_back"}},
					{ action.change_text_item, {id=4, name="kitchen.meat", text = strings.objects.stewedmeat }},
					{ action.add_to_inventory, {id=5, name="kitchen.meat", qty=1}},
				}
			else
				a = script.defaultactions.pickup
			end
			return a()

		end,
		use = {
		}
	}
}

items["kitchen.potostew"].actions.use["kitchen.meat"] = ms {
	{ action.animate, {id=1, actor="guybrush", anim="operate_back"}},
	{ action.delay, {id=2, sec=0.5}},
	{ action.animate, {id=3, actor="guybrush", anim="idle_back"}},
	{ action.remove_from_inventory, {id=4, name="kitchen.meat"}},
	{ action.set_variable, { id=5, var="meat_in_pot", value = true}}
}


items["kitchen.meat"] = { 
	tag = "meat",
	text = strings.objects.meat,	
	pos = {79, 40, -1},
	size = {20, 20},
	walk_to = {90, 18},
	face = "north",
	model = "kitchen_meat",
	anim="default",
	actions = {
		pickup = pick_up_item("kitchen.meat", "operate_back"),
		look = ms {
			{ action.say, { id=1, actor="guybrush", lines = {strings.kitchen[1] }}}
		}
	}	
}

items["kitchen.pot"] = { 
	tag="pot",
	text = strings.objects.pot,
	pos = {104, 24, -1},
	size = {15, 7},
	walk_to = { 112, 18},
	face = "north",
	model = "kitchen_pot",
	anim = "default",
	actions = {
		pickup = pick_up_item("kitchen.pot", "kneel_back"),
		look = ms {
			{ action.say, { id=1, actor="guybrush", lines = {strings.kitchen[2] }}}
		},
		give = {
			
		}

	}	
}

items["kitchen.pot"].actions.give["circus.purpleclown"] = function() 
	local s = script:new()
	local d = strings.dialogues.fettbros
	local explTag = nextTag()
	local fgTag = nextTag()
	s.actions = {
		action.disable_controls{id=1},
		action.animate_once {id=2, actor="guybrush", anim="pot_out"},
		action.animate {id=3, actor="guybrush", anim="show_pot"},
		action.say {id=4, actor="circus.greenclown", lines = {d[82]} },
		action.animate_once {id=5, actor="guybrush", anim="pot_in"},
		action.animate {id=6, actor="guybrush", anim="idle_front"},
		action.say {id=7, actor="circus.purpleclown", lines = {d[83]} },
		action.say {id=8, actor="circus.greenclown", lines = {d[84]} },
		action.walkto {id=9, actor="circus.purpleclown", pos={333, 1}, after={8} },
		action.walkto {id=10, actor="circus.greenclown", pos={296, 24}, after={8} },
		action.walkto {id=11, actor="guybrush", pos={250, 24},after={8}},
		action.scroll {id=12, by = {48, 0}, speed = 50, after={8} },
		action.turn {id =13, actor="circus.purpleclown", dir="north", after={9} },
		action.turn {id =14, actor="circus.greenclown", dir="west", after={10} },
		action.turn {id =15, actor="guybrush", dir="south", after={11} },
		action.say {id=16, actor="circus.purpleclown", after={13,14,15}, lines = {d[85]} },
		action.say {id=17, actor="circus.greenclown", lines = {d[86]} },
		action.say {id=18, actor="circus.purpleclown", lines = {d[87]} },
		action.walkto { id=19, actor="guybrush", pos={264, 23} },
		action.turn {id=20, actor="guybrush", dir="east" },
		action.say {id=21, actor="guybrush", lines ={d[88]}},
		action.walkto {id=22, actor="guybrush", pos={250, 24}},
		action.turn {id=23, actor="guybrush", dir="south"},
		action.animate_once {id = 24, actor="guybrush", anim="get_in_cannon" },
		action.activate {id=25, name="guybrush", value=false},
		action.create_object {id = 26, name="circus.explosion", tag = explTag, pos ={0,0,0}, after={25}},
		action.create_object {id = 27, name="circus.flyingguybrush", tag = fgTag, pos ={0,0,0}, after={25}},
		action.animate_once {id = 28, tag = explTag, anim="default", after={26}},
		action.animate_once {id = 29, tag = fgTag, anim="default", after={27}},
		action.remove_object {id=30, after={28}, tag = explTag },
		action.animate {id=31, tag=fgTag, anim="end", after={29}},
		action.delay {id=32, sec=0.5},
		action.say {id=33, actor="circus.purpleclown", lines = {d[89]} },
		action.say {id=34, actor="circus.greenclown", lines = {d[90]} },
		action.walkto { id=35, actor="circus.purpleclown", pos={87, 29}, after={34}},
		action.walkto { id=36, actor="circus.greenclown", pos={126,29}, after={34}},
		action.turn { id=37, actor="circus.purpleclown", dir="east", after={35}},			
		action.turn { id=38, actor="circus.greenclown", dir="west", after={36}},	
		action.say {id=39, actor="circus.purpleclown", after={37, 38}, lines = {d[91]} },
		action.say {id=40, actor="circus.greenclown", lines = {d[92]} },
		action.start_dialogue {id = 41, dialogue="fettuccini", root=dialogues.fettuccini.nodes[15]}
	}
	return s
end



items["kitchen.fish"] = {
	tag="kitchen.fish",
	text = strings.objects.fish,	
	pos = {234, 9, 1},
	size = {12, 7},
	walk_to = {234, 12},
	face="south",
	model = "kitchen_fish",
	anim = "default",
	actions = {
		pickup = function()
			local a = nil
			if (variables.seagull_flying == true) then
				a = pick_up_item("kitchen.fish", "kneel_front")
			else
				a = ms {
					{ action.animate, {id=1, actor="guybrush", anim="kneel_front"}},
					{ action.delay, {id=2, sec=0.5}},
					{ action.animate, {id=3, actor="guybrush", anim="idle_front"}},
					{ action.say, {id=4, actor="guybrush", lines= {d[4]}}}
				}
			end
			return a()
		end,
		look = ms {
			{ action.say, { id=1, actor="guybrush", lines = {d[3] }}}
		},
		give = {}

	}
}

items["kitchen.fish"].actions.give["bridge.troll"] = function()
	local dp = strings.dialogues.troll
	local s = script:new()
	s.actions = {
		action.suspend_script {id=1, script="_troll"},
		action.animate_once {id=2, actor="bridge.troll", anim="take_fish"},
		action.animate {id=3, after={2}, actor="bridge.troll", anim="wait_fish"},
		action.say { id= 4, after={1}, actor="bridge.troll", lines={dp[48]}, animate=false  },
		action.animate {id=5, actor="guybrush", anim="operate_right", after={2} },
		action.delay {id = 6, sec=0.5},
		action.animate {id=7, after={6}, actor="guybrush", anim="idle_right" },
		action.animate {id=8, after={6}, actor="bridge.troll", anim="hold_fish"},


	}
	return s
end

items["kitchen.seagull"] = {
	pos = {0, 0, 1},
	tag = "seagull",
	model = "seagull",
	anim = "flying",
}

items["kitchen.plank"] = {
	pos = {248, 0, 1},
	tag = "plank",
	model="plank", 
	anim="default"
}