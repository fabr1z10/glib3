engine.items["gate.walkarea"] = {
	type = 'walkarea',
	shape = { 
		type = 'poly', 
 		outline = { 0, 0, 0, 14, 320, 14, 320, 0},
	},
	depth = { type="linear_y", values= {0, 1, 144, 0} },

}

engine.items["gate.sign"] = {
	type = 'object',
	pos ={9, 24, 0},
	hotspot= {
		text = strings.objects.sign,
		size = {31, 23},
		walk_to = {24, 7},
		dir = 's'	
	},
 	actions = {
 		look = scumm.script.say ({ strings.gate[1], strings.gate[2]})
	}
}

engine.items["gate.path"] = {
	type = 'object',
	pos ={0, 0, 0},
	hotspot= {
		text = strings.objects.path,
		size = {10, 140},
		walk_to = {0, 7},
		dir = 'w',
	},
 	actions = {
 		walk = scumm.script.changeroom ('2', 'frontdoor.walkarea', {10, 10}, 'w')
	}
}