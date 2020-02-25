engine.items["entrance.walkarea"] = {
	type = 'walkarea',
	shape = { 
		type = 'poly', 
 		outline = {25, 0, 75, 17, 139, 17, 142, 25, 216, 25, 222, 17, 280, 17, 321, 80, 321, 128, 349, 128, 363, 109, 363, 78, 327, 30, 327, 17, 404, 17, 414, 25, 537, 25, 547, 22, 560, 22, 628, 0},
	},
	depth = { type="linear_y", values= {0, 1, 144, 0} },

}

engine.items["entrance.clock"] = {
	type = 'object',
	pos ={113, 24, -2.5},
	model = 'grandfather.clock',
	hotspot= {
		text = strings.objects.gfclock,
		size = {27, 94},
		offset ={-5, -5},
		walk_to = {120, 17},
		dir = 'n',
	},
 	actions = {
 		look = scumm.script.say ({ strings.entrance[1] })
	}
}



engine.items["entrance.door.out"] = {
	type = 'object',
	pos ={24, 3, -2},
	tag = true,
	model = 'entrance.door.out',
	anim = function() return variables.frontdoor_open and 'open' or 'closed' end,
	hotspot= {
		text = strings.objects.frontdoor,
		size = {47, 115},
		walk_to = {52, 8},
		dir = 'w'	
	},
 	actions = {
 		open = function() 
 			variables.frontdoor_open = true
 			return { type = action.animate, args = { tag = 'entrance.door.out', anim='open'}}
 		end,
 		close = function() 
 			variables.frontdoor_open = false
 			return { type = action.animate, args = { tag = 'entrance.door.out', anim='closed'}}
 		end,

 		--look = scumm.script.say ({ strings.gate[1], strings.gate[2]})
	}
}

engine.items["entrance.cellar.door"] = {
	type = 'object',
	pos ={439, 24, -2},
	tag = true,
	model = 'entrance.cellar.door',
	anim = function() return variables.cellar_door_open and 'open' or 'closed' end,
	hotspot= {
		text = strings.objects.door,
		size = {42, 89},
		walk_to = {460, 24},
		dir = 'n'	
	},
 	actions = {
 		open = function() 
 			if variables.cellar_door_open then
				
 			else
				return scumm.script.say ({ strings.entrance[2] })
 			end
 		end,

 		--look = scumm.script.say ({ strings.gate[1], strings.gate[2]})
	}
}


engine.items["entrance.vase.l"] = {
	type = 'object',
	pos ={219, 18, 0},
	hotspot= {
		text = strings.objects.vase,
		size = {28, 44},
		walk_to = {233, 17},
		dir = 'n',
	},
}

engine.items["entrance.vase.r"] = {
	type = 'object',
	pos ={372, 18, 0},
	hotspot= {
		text = strings.objects.vase,
		size = {28, 44},
		walk_to = {386, 17},
		dir = 'n',
	},
}

engine.items["entrance.gargoyle.r"] = {
	type = 'object',
	pos ={329, 46, 0},
	hotspot= {
		text = strings.objects.gargoyle,
		size = {24, 20},
		walk_to = {341, 17},
		dir = 'n',
	},
	actions = {
		push = {
			{ type = action.callfunc, args = { func = function() 
				variables.cellar_door_open = true 
				variables.pending_action[variables.current_player] = {
					{ type = action.callfunc, args = { func = function()  variables.cellar_door_open = false end }},
					{ type = action.animate, args = { tag = 'entrance.cellar.door', anim= 'closed'}},					
				}
			end }},
			{ type = action.animate, args = { tag = 'entrance.cellar.door', anim= 'open'}},
		}
	}
}