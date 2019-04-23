-- generally, an item is a blueprint for an object
-- * it can have graphics attached. To do so, model needs to be specified
local add_item = function(args)
	print (args.name)
	items[args.name] = {
		pos={0,0,0},
		walkarea =args.walkarea,
		hotspot = {
			priority = args.priority,
			shape = { type ="poly", outline=args.outline}

		},
		actions = {
			look = box{ msg = strings[args.msg], sprite = args.sprite },
			walk = function(x, y) return scumm.ui.walk { pos ={x,y}, walkarea = args.wa} end,
			use = args.use
		}
	}

end

	items["room1_room2"] = {
		pos={0,0,0},
		hotspot = {
			priority = 3,
			shape = { type ="rect", width=30, height=2 }
		},
		actions = {
			walk = function(x, y) return { 
				scumm.ui.walk { pos = {x, y}, walkarea = "room1_walkarea_front" },
				{ type = action.change_room, args = {room="room2"}},
			} end
		}
	}
	items["room2_room1"] = {
		pos={172,158,0},
		hotspot = {
			priority = 3,
			shape = { type ="rect", width=20, height=20 }
		},
		actions = {
			walk = function(x, y) return { 
				scumm.ui.walk { pos = {x, y}  },
				{ type = action.change_room, args = {room="room1"}},
			} end
		}
	}
	items["room2_walkarea"] = {
		pos = {0,0,0},
		walkarea = {
			priority=1,
			shape = {type="poly", outline = {
				176,153,183,155,198,155,200,
				151,181,138,159,132,135,122,
				159,119,191,120,214,119,247,
				123,277,130,315,143,320,146,
				320,133,312,127,282,115,255,
				108,223,101,194,90,179,84,163,
				80,153,73,154,63,168,57,183,52,
				208,35,227,29,247,17,283,0,129,
				0,127,31,114,51,61,48,17,43,0,
				39,0,68,17,71,59,75,96,78,121,
				80,150,85,168,90,176,94,168,
				99,137,102,102,111,78,116,74,
				123,92,130,109,131,138,138}},
			depth = { type="linear_y", values= {0, 1, 190, 0} },

		},
		actions = {
			walk = function(x, y) return scumm.ui.walk { pos ={x, y}, walkarea="room2_walkarea"} end,
		}
	}
	items["room1_walkarea_back"] = {
		pos={0,0,0},
		walkarea = {
			priority = 1,
			shape = { type = "poly", outline = {105,11,99,16,93,10,84,3,78,0,5,0,0,16,12,13,27,10,42,8,
            	57,8,60,10,75,17,81,21,72,25,38,27,0,32,0,71,25,75,56,72,61,63,67,62,82,64,89,66,100,65,111,69,
				121,76,135,81,149,83,163,92,176,92,170,82,176,79,187,88,208,87,217,83,230,79,238,81,247,76,262,
				79,273,79,279,77,280,73,256,70,246,66,251,62,251,59,245,59,241,57,247,55,239,52,221,46,206,
				45,178,42,181,47,159,46,147,42,138,42,128,43,117,42,112,38,106,29,107,26,113,26,116,28,123,27,
				137,25,147,21,161,19,189,21,235,20,262,21,282,26,289,36,287,42,277,43,261,46,269,50,276,52,285,
				54,297,52,307,50,320,52,320,5,109,8,105,11},
	 		holes = {
	 			{77,51,65,50,62,47,69,43,57,41,61,33,75,32,82,31,89,40,100,44,117,45,101,46,91,45,83,49},
	 			{211,80,186,82,185,63,210,60}
	 		}},
		  	scale = { type="constant", value = 0.7},
			depth = { type="linear_y", values= {0, 1, 190, 0} },


	 	},
		actions = {
			walk = function(x, y) return scumm.ui.walk { pos ={x, y}, walkarea="room1_walkarea_back"} end,
		}
	}
	items["room1_walkarea_front"] = {
		pos={0,0,0},
		walkarea = {
			priority = 2,
			shape = { type = "poly", outline = {0,16,12,13,27,10,42,8,57,8,60,10,75,17,81,21,87,20,91,16,99,16,93,10,84,3,78,0,5,0,0,0}},
		  	scale = { type="constant", value = 1.0},
			depth = { type="linear_y", values= {0, 1.1, 190, 1} },

	 	},
		actions = {
			walk = function(x, y) return scumm.ui.walk { pos ={x, y}, walkarea="room1_walkarea_front"} end,
		}
	}
	items["room1_walkarea_hidden"] = {
		pos={0,0,0},
		walkarea = {
			priority = 0,
			shape = { type = "poly", outline = {0,16,12,13,27,10,42,8,57,8,60,10,75,17,81,21,87,20,91,16,99,16,93,10,84,3,78,0,5,0,0,0}},
			scale = { type="linear_y", values={18,1,8,0.7}},
			depth = { type="constant", value=0.99},

	 	},
		actions = {
			--walk = function(x, y) return scumm.ui.walk { pos ={x, y}, walkarea="room1_walkarea_front"} end,
		}
	}


add_item { name="crispins_house", priority = 3, wa ="room1_walkarea_back", outline = {17,78,17,101,59,115,111,175,243,175,255,147,252,107,219,87,188,90,174,81,149,86,142,91,100,92,74,71}, msg = 1}
add_item { name="crispins_door", priority = 10, outline = {184,62,184,81,211,79,211,60}, msg = 2,
	use = box{ msg = strings[3], sprite = "cedric.talk" }
}
add_item { name="crispins_window_1", priority = 4, outline = {229,128,246,137,247,117,228,103}, msg = 4 }
add_item { name="crispins_window_2", priority = 4, outline = {105,121,139,121,139,100,104,101}, msg = 4 }
add_item { name="crispins_window_3", priority = 4, outline = {23,105,65,103,64,81,24,82}, msg = 4 }
add_item { name="crispins_window_3", priority = 3, outline = {66,47,76,48,89,45,109,43,126,39,142,38,151,41,156,43,176,44,175,42,194,43,215,43,242,52,249,53,247,57,254,59,249,64,257,68,269,70,288,71,284,68,270,64,274,60,284,56,268,51,257,46,264,44,278,44,287,40,279,36,270,34,251,29,231,24,202,24,175,22,156,22,139,25,123,30,108,32,93,33,78,35,68,37,64,39,73,41
}, msg = 5}


-- items["crispins_house"] = {
-- 	pos={0,0,0},
-- 	hotspot = {
-- 		priority = 3,
-- 		shape = { type ="poly", outline={17,78,17,101,59,115,111,175,243,175,255,147,252,107,219,87,188,90,174,81,149,86,142,91,100,92,74,71}}

-- 	},
-- 	actions = {
-- 		look = box{ msg = strings[1], sprite ="cedric.talk"}
-- 	}
-- }


