engine.items["village2.walkarea"] = {
	type = 'walkarea',
	tag = true,
	shape = { 
		type = 'poly', 
		outline = {0, 24, 123, 63, 199, 63, 299, 30, 377, 30, 385, 35, 454, 35, 470, 0, 0}
	},
	scale = { type = 'linear_y', values= {0, 0.8, 144, 0.1} },
	priority = 0,
	depth = { type="linear_y", values= {0, 1, 144, 0} },
	scale = { 
		type = 'patchwise', 
		rects = {
    		{ pos = {0, 0}, size={480, 30}, func = { type="constant", value = 1} },
    		{ pos = {0, 30}, size={480, 104}, func = { type="linear_y", values = {30, 1, 59, 0.35}}},    		
    	}
	}
}

-- generally, an item is a blueprint for an object
-- * it can have graphics attached. To do so, model needs to be specified
engine.items["village2.archway_to_village1"] = {
	type = 'object',
	pos = {416, 34, 0},
	hotspot = {
		text = strings.objects.archway,
		walk_to = mi.rooms.village2.to_village1,
		dir = 'n',
		size = {40, 50},			
	},
	actions = {
		walk = scumm.script.changeroom { room = 'village1', pos = mi.rooms.village1.to_village2, dir='w' }
	}
}

engine.items["village2.archway_to_village3"] = {
	type = 'object',
	pos = {146, 63, 0},
	hotspot = {
		text = strings.objects.archway,
		walk_to = {160, 59},
		dir = 'n',
		size = {30, 30},
	},
	actions = {
		walk = scumm.script.changeroom { room = 'village3', pos = mi.rooms.village3.to_village2, dir = 'w' }
	},
}





engine.items["village2.lmf"] = {
	type = 'object',
	hotspot = {
		text = strings.objects.lowmoralfiber,
		size = {60, 60},
		walk_to = {85, 14},
		dir = 'w'
	},
	actions = {
		talk = { type = scumm.action.start_dialogue, args = {dialogue="lowmoralfiber"}} 
	}
}



-- scumm.factory.door {
-- 	id = "village2.voodoolady_door",
-- 	pos = {220, 52, -1},
-- 	size = {26, 26},
-- 	walk_to = {220, 48},
-- 	dir = "east",
-- 	model = "door_village_voodoolady",
-- 	nextroom="voodoolady",
-- 	variable = "door_voodoolady"
-- }


engine.items["village2.fakedoor1"] = {
	pos = {377, 37, -1},
	hotspot = {
		text = strings.objects.door,
		walk_to= {389, 36},
		dir = "west",
		size = {20, 30}	
	},
	actions = {},
	model = "fakedoor_village_1",
	anim="close"
}

engine.items["village2.fakedoor2"] = {
	pos = {208, 59, -1},
	hotspot = {
		text = strings.objects.door,
		walk_to= {206, 58},
		dir = "east",
		size = {10, 20},
		priority = 10,
	},
	actions = {},
	model = "fakedoor_village_2",
	anim="close"
}

engine.items["village2.fakedoor3"] = {
	pos = {130, 63, -1},
	hotspot = {
		text = strings.objects.door,
		walk_to= {135, 60},
		dir = "north",
		size = {10, 15}	
	},
	actions = {},
	model = "fakedoor_village_3",
	anim = "close"
}

engine.items["village2.fakedoor4"] = {
	pos = {184, 64, -1},
	hotspot = {
		text = strings.objects.door,
		walk_to= {188, 61},
		dir = "north",
		size = {10, 15}	
	},
	actions = {},
	model = "fakedoor_village_4",
	anim="close"
}

