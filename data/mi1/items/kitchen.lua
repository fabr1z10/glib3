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

	}	
}



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
		}

	}
}

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