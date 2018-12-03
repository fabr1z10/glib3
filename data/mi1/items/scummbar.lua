--items.scummbar = {}

local cook_text_color = {85, 255, 255, 255}

items["scummbar.door_out"] = factory.door.create {
	name = "scummbar.door_out",
	pos = {32, 24, -1},
	size = {38, 47},
	walk_to = {57, 20},
	face = "west",
	door_ref = "door_village_scummbar",
	model = "door_scummbar_village",
	nextroom = "village1"
}

items["scummbar.door_kitchen"] = factory.door.create {
	name = "scummbar.door_kitchen",
	pos = {591, 9, -1},
	size = {35, 69},
	walk_to = {588, 14},
	face = "east",
	door_ref = "door_scummbar_kitchen",
	model = "door_scummbar_kitchen",
	nextroom = "kitchen",
	open = function()
		local s = script:new()
		if (variables.cook_in_kitchen == true) then
			s.actions = {
				action.animate {id = 1, actor="scummbar.door_kitchen", anim="open" },
				action.show_message { id = 2, message = strings.dialogues.cook[3], color = cook_text_color, pos= {591, 100,1}},
				--action.animate {id = 3, actor="scummbar.door_kitchen", anim="close" },
			}
			return s
		end
	end
}


items["scummbar.mancomb"] = {
	tag="mancomb",
	text = strings.objects.pirate,
	pos = {89, 24, -1},
	size = {30, 30},
	model = "mancomb",
	anim = "idle",
	walk_to = {125, 17},
	face = "north",
	actions = {
		look =  ms { { action.change_room, { id=1, room = "mancomb" }}},
		talk =  ms { { action.change_room, { id=1, room = "mancomb" }}}
	}
}

items["scummbar.estevan"] = {
	tag="estevan",
	text = strings.objects.pirate,
	pos = {164, 21, 1},
	size = {30, 20},
	model = "estevan",
	anim = "idle",
	walk_to = {195, 11},
	face = "south",
	actions = {
		look =  ms { { action.change_room, { id=1, room = "estevan" }}},
		talk =  ms { { action.change_room, { id=1, room = "estevan" }}}
	}
}

items["scummbar.loompirate"] = {
	tag="loompirate",
	text = strings.objects.pirate,
	pos = {260, 17, -1},
	size = {20, 20},
	model = "loompirate",
	anim = "idle",
	walk_to = {250, 16},
	face = "north",
	actions = {
		look =  ms { { action.change_room, { id=1, room = "loompirate" }}},
		talk =  ms { { action.change_room, { id=1, room = "loompirate" }}}
	}
}

items["scummbar.fireplace"] = {
	text = strings.objects.fireplace,
	pos = {509, 44, -1},
	size = {29, 18},
	model = "fireplace",
	anim = "default",
	walk_to = {512, 40},
	face = "east",
	actions = {
		look =  ms { { action.say, { id=1, actor="guybrush", lines = {strings.scummbar[1]} }}}
	}
}

items["scummbar.cook"] = {
	tag = "cook",
	pos = {0,0,-1},
	model = "cook",
	anim = "idle_right",
	face = "east",
	text_color = cook_text_color
}