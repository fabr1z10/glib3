-- the local objects
engine.items['lookout.walkarea'] = { 
	type = 'walkarea',
	tag = true,
	shape = { 
		type = 'poly', 
		outline = {203,51,315,62,315,40,293,40,260,10,260,0,260,-20,234,-20,234,0,234,10,221,26,152,33,152,51}
	},
	depth = { type = 'linear_y', values= {0, 1, 144, 0} },	
	priority = 0
}

engine.items["lookout.stairs"] = {
	type ='object',
	pos = {230, 0, 0},
	hotspot = {
		text = strings.objects.stairs,
		walk_to = {250, 0}, 
		dir = "south",
		size = {30, 10}
	},
	actions = {
		walk = scumm.script.changeroom { room = 'village1', pos = mi.rooms.village1.to_lookout, dir='e' }
	}
}

engine.items["lookout.path"] = {
	type ='object',
	pos = {294, 0, 0},
	hotspot = {
		text = strings.objects.path,
		walk_to = {320, 50}, 
		dir = "west",
		size = {26, 144},			
	},
	actions = {
		walk = scumm.script.changeroom { room = 'meleemap', pos = mi.rooms.meleemap.lookout, dir='n'}
	}
}




engine.items["lookout.fire"] = {
	type ='object',
	pos = {126, 52, 0},
	model = "lookout.fire",
}