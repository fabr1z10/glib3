engine.items["clearing.walkarea"] = scumm.factory.walkarea {
	shape = { type = "poly", outline = 
		{496,38,496,0, 283, 0, 283, 20, 315, 28,315, 44, 229, 31, 92, 31, 41, 64,54, 75, 80, 64, 115, 58, 119, 48,
		 165, 53, 180,64, 214, 64, 229, 33, 315, 46, 400,38}},
	priority = 0,
	depth = { type="linear_y", values= {0, 1, 144, 0} },
	scale = { type="patchwise", rects = {
   		{ pos = {0, 0}, size={229, 144}, type="constant", value = 0.2},
   		{ pos = {229,31}, size={85, 144}, type="constant", type="linear_x", values={229,0.2,314,1.0}},
 		{ pos = {314,0}, size={200, 144}, type="constant", type="constant", value=1.0},
		{ pos = {283,0}, size={100, 32}, type="constant", type="constant", value=1.0},
	}}		
}
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

