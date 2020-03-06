engine.items["cellar.walkarea"] = {
	type = 'walkarea',
	shape = { 
		type = 'poly', 
 		outline = {563,119,586,119,604,20,614,20,656,0,0,0,57,23,396,23,396,20,96,20,96,7,512,7,522,23,563,23},
	},
	depth = { type="linear_y", values= {0, 1, 144, 0} },

}

engine.items["cellar.light"] = {
	type = 'object',
	pos ={544, 55, 0},
	hotspot= {
		text = strings.objects.lightswitch,
		size = {10, 10},
		--offset ={-5, -5},
		walk_to = {549, 18},
		dir = 'n',
	},
 	actions = {
 		turnon = { type = action.callfunc, args = { func = function() 
 			variables.cellar_light_on = true
 			mm.switch_cellar_lights()
 		end
 		}},
 		turnoff = { type = action.callfunc, args = { func = function() 
 			variables.cellar_light_on = false
 			mm.switch_cellar_lights()
 		end
 		}},

	}
}

engine.items["cellar.slime"] = {
	type = 'object',
	pos ={143, 0, 0},
	hotspot= {
		text = strings.objects.slime,
		size = {46, 9},
		walk_to = {166, 4},
		dir = 's',
	},
 	actions = {
 		look = {type=scumm.action.say, args ={tag='player', lines = {strings.cellar[1]}}}

	}
}

engine.items["cellar.silverkey"] = {
	type = 'object',
	tag = true,
	model = 'cellar.silverkey',
	pos ={98, 61, 0},
	hotspot= {
		text = strings.objects.silverkey,
		size = {6, 12},
		walk_to = {101, 22},
		dir = 'n',
	},
 	actions = {
 		pick = scumm.script.pickup { id = 'cellar.silverkey'}
 		--look = {type=scumm.action.say, args ={tag='player', lines = {strings.cellar[1]}}}
	}
}

engine.items["cellar.fusebox"] = {
	type = 'object',
	tag = true,
	model = 'cellar.fusebox',
	pos ={64, 47, -2},
	hotspot= {
		text = strings.objects.fusebox,
		size = {32, 32},
		walk_to = {80, 22},
		dir = 'n',
	},
 	actions = {
 		open = {
 			{ type = action.animate, args = {tag='cellar.fusebox', anim='open'}},
 			{ type = action.callfunc, args = { func = function() 
 				variables.fusebox_open = true
 				monkey.getEntity('cellar.circuitbreakers'):setactive(true) end 
 			}},
 		},
 		close = {
 			{ type = action.animate, args = {tag='cellar.fusebox', anim='closed'}},	
 			{ type = action.callfunc, args = { func = function() 
 				variables.fusebox_open = false
 				monkey.getEntity('cellar.circuitbreakers'):setactive(false) end 
 			}},
 		}
	}
}

engine.items["cellar.circuitbreakers"] = {
	type = 'object',
	tag = true,
	pos ={72, 55, -2},
	hotspot= {
		text = strings.objects.circuitbreakers,
		priority = 2,
		size = {16, 16},
		walk_to = {80, 22},
		dir = 'n',
	},
 	actions = {
	}
}

