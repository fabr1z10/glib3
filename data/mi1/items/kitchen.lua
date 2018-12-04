--items.scummbar = {}

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
	actions = {}
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
		}
	}	
}

items["kitchen.fish"] = {
	text = strings.objects.fish,	
	pos = {234, 9, 1},
	size = {12, 7},
	walk_to = {234, 12},
	face="south",
	model = "kitchen_fish",
	anim = "default",
	actions = {}
}
