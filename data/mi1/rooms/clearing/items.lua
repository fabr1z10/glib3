engine.items["clearing.path"] = {	
	pos = {480, 0, 0},
	hotspot = {
		text = strings.objects.path,
		size = {16, 144},			
		walk_to = {496, 10}, 
		dir = "east",
	},	
	actions = {
		walk = { { type=action.change_room, args={room="meleemap"} } }
	}
}

engine.items["clearing.tent"] = {
	pos = {47, 63, 0},
	hotspot = {
		text = strings.objects.circustent,
		size = {135, 70},
		walk_to = {82, 66}, 
		dir = "north",
	},
	actions = {
		walk = function() 
			if (variables.circus_feat_done == false) then
				return { {type=action.change_room, args={room="circus"} }}
			else
				return { {type=scumm.action.say, args={actor="guybrush", lines = {strings.circus[1]}} }}
			end
		end
	}
}

