engine.items["frontdoor.walkarea"] = {
	type = 'walkarea',
	shape = { 
		type = 'poly', 
 		outline = {0,2,0,16,283,16, 283,4, 305,4, 338, 44.1, 123, 44.1, 123, 44.2, 657, 44.2, 657, 44.1, 420, 44.1,  456, 4, 479,4,479,16, 960,16,960,2}
	},
	depth = { type="linear_y", values= {0, 1, 144, 0} },

}

engine.items["frontdoor.path"] = {
	type = 'object',
	pos ={950, 0, 0},
	hotspot= {
		text = strings.objects.path,
		size = {10, 128},
		walk_to = {960, 14},
		dir = 'e',
	},
 	actions = {
 		walk = scumm.script.changeroom { room='1', pos={0, 14}, dir='e' }
	}
}


engine.items["frontdoor.door"] = {
	type = 'object',
	pos ={384, 50, -2},
	model = 'front.door',
	anim = function() return variables.frontdoor_open and 'open' or 'closed' end,
	hotspot= {
		text = strings.objects.frontdoor,
		size = {40, 78},
		walk_to = {402, 49},
		dir = 'n'	
	},
 	actions = {
 		--look = scumm.script.say ({ strings.gate[1], strings.gate[2]})
	}
}

engine.items["frontdoor.mat"] = {
	type = 'object',
	pos ={336, 41, -2},
	model = 'door.mat',
	tag =true,
	anim = function() return variables.doormat_pulled and 'open' or 'closed' end,
	hotspot= {
		text = strings.objects.doormat,
		size = {80, 6},
		walk_to = {398, 46},
		dir = 's',
	},
 	actions = {
 		pull = {
 			{ type = action.callfunc, args = { func = function()
 				variables.doormat_pulled = true
 				local key = monkey.getEntity('frontdoor.key')
				if not key.isnil then key:setactive(true) end end
 			}},
 			{ type = action.animate, args = { tag = 'frontdoor.mat', anim = 'open' }},
 		},
 		push = {
 			{ type = action.callfunc, args = { func = function() 
 				variables.doormat_pulled = false
 				local key = monkey.getEntity('frontdoor.key')
 				if not key.isnil then key:setactive(false) end end
 			}},
 			{ type = action.animate, args = { tag = 'frontdoor.mat', anim = 'closed' }},
 		}

	}
}

engine.items["frontdoor.key"] = {
	type = 'object',
	pos ={405, 43, -2.1},
	tag =true,
	model = 'front.door.key',
	hotspot= {
		text = strings.objects.key,
		size = {10, 3},
		walk_to = {398, 46},
		dir = 's',
		priority = 2
	},
 	actions = {
 		pick = scumm.script.pickup('frontdoor.key', 'frontdoor_key_taken')
	}
}

engine.items["frontdoor.grating"] = {
	type = 'object',
	pos ={257, 16, -4},
	tag =true,
	model = 'front.door.grating',
	hotspot= {
		text = strings.objects.grating,
		size = {50, 16},
		walk_to = {272, 14},
		dir = 'n',
	},
 	actions = {
 		--pick = scumm.script.pickup('frontdoor.key', 'frontdoor_key_taken')
	}
}

engine.items["frontdoor.bush.l"] = {
	type = 'object',
	pos ={257, 16, -3.5},
	tag =true,
	model = 'front.door.bush',
	hotspot= {
		text = strings.objects.bushes,
		size = {50, 16},
		walk_to = {272, 14},
		dir = 'n',
		priority = 2
	},
 	actions = {
 		open = { 
 			{ type = action.callfunc, args = { func = function() variables.frontdoor_bush_removed = true end }},
 			{ type = action.remove_object, args = { tag = 'frontdoor.bush.l'}}
 		}
 		--pick = scumm.script.pickup('frontdoor.key', 'frontdoor_key_taken')
	}
}