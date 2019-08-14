engine.items["001.walkarea"] = scumm.factory.walkarea {
	shape = { type = "poly", outline = {0, 8, 0, 19, 184, 19, 198, 32, 214, 38, 161, 57, 161,106, 316,106, 316, 10, 269, 26, 245, 26,231,20,219,8}},
	priority = 0,
	depth = { type="linear_y", values= {0, 1, 144, 0} },
}

engine.items["001.moat"] = scumm.factory.walkarea {
	shape = { type = "poly", outline = {0, 0, 0, 6, 229, 6, 242, 18, 294, 0}},
	priority = 0,
	depth = { type="linear_y", values= {0, 1, 144, 0} },
}

engine.items["castle"] = {

	pos={0,0,0},
	hotspot = {
		priority = 1,
		shape = { type ="poly", outline={0,21,0,126,100,126,100,161,187,161,187,142,173,132,173,21}}
	},
	actions = {
		look = {
			{ type = action.kq.showmessage, args = { msg=strings.room001[1]}}
		}
	--		look = box{ msg = strings[args.msg], sprite = args.sprite },
	--		walk = function(x, y) return scumm.ui.walk { pos ={x,y}, walkarea = args.wa} end,
	--		use = args.use
	}
}

engine.items["flags"] = {
	pos={0,0,0},
	hotspot = {
		priority = 1,
		shape = { type ="poly", outline={4,129,4,162,92,162,92,129}}
	},
	actions = {
		look = {
			{ type = action.kq.showmessage, args = { msg=strings.room001[2]}}
		}
	--		look = box{ msg = strings[args.msg], sprite = args.sprite },
	--		walk = function(x, y) return scumm.ui.walk { pos ={x,y}, walkarea = args.wa} end,
	--		use = args.use
	}
}


engine.items["purple_flag"] = {
	pos = {6, 150, 0},
	model = "purple_flag"
}

engine.items["yellow_flag"] = {
	pos = {36, 150, 0},
	model = "yellow_flag"
}

engine.items["cyan_flag"] = {
	pos = {66, 150, 0},
	model = "cyan_flag"
}

engine.items["alligator_1"] = {
	tag = "alli1",
	pos = {10, 5, 0},
	model = "alligator",
	sci_char = { speed = 50, acceleration=0.1, fliph=true, fourway=false},
	hotspot = {

		priority = 1,
		size = {25,10}, offset = {-12,0}
	},
	actions = {
		look = {
			{ type = action.kq.showmessage, args = { msg=strings.room001[5]}}
		}
	}
}

engine.items["alligator_2"] = {
	tag = "alli2",
	pos = {150, 5, 0},
	model = "alligator",
	sci_char = { speed = 40, acceleration=0.1, fliph=true, fourway=false},
	hotspot = {
		priority = 1,
		size = {25,10}, offset = {-12,0}
	},
	actions = {
		look = {
			{ type = action.kq.showmessage, args = { msg=strings.room001[5]}}
		}
	}
}
