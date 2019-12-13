engine.items["001.walkarea"] = scumm.factory.walkarea {
	shape = { 
		type = "poly", 
		holes={}, 
		--outline = {0,0,0,166,316,166,316,0}
		outline = {0, 8, 0, 19, 184, 19, 198, 32, 214, 38, 161, 57, 161,106, 316,106, 316, 10, 269, 26, 245, 26,231,20,219,8}
	},
	priority = 0,
	depth = { type="linear_y", values= {0, 1, 144, 0} },
}

engine.items["001.moat"] = scumm.factory.walkarea {
	shape = { type = "poly", outline = {0, 0, 0, 6, 229, 6, 242, 18, 294, 0}},
	priority = 0,
	depth = { type="linear_y", values= {0, 1, 144, 0} },
}

engine.items["castle"] = makeItem {outline = {0,21,0,126,100,126,100,161,187,161,187,142,173,132,173,21}, msg = strings.room001[1] } 
engine.items["001.bridge"] = makeItem { outline = {187,8,187,21,202,36,228,36,267,28,294,8}, msg = strings.room001[7]}
engine.items["001.moat.item"] = makeItem { outline = {0, 0, 0, 6, 229, 6, 242, 18, 294, 0}, msg = strings.room001[4]}
engine.items["001.tree"] = makeItem { 
	x = 196, y= 39,
	--x=0,y=0,
	outline = {68,2,68,35,40,71,10,71,10,127,120,127,120,60,93,60,84,41,84,2},
	msg = strings.room001[6],
	gfx = "bg002.png",
	hole = { 
	--s	outline = {50, 50, 50, 150, 250, 150, 250, 50}
		outline = {65, -1, 65,2, 87, 2, 87, -1}
	}
}
-- {	
-- 	pos={0,0,0},
-- 	hotspot = {
-- 		priority = 1,
-- 		shape = { type ="poly", outline={0,21,0,126,100,126,100,161,187,161,187,142,173,132,173,21}}
-- 	},
-- 	actions = {
-- 		look = {
-- 			{ type = action.kq.showmessage, args = { msg=strings.room001[1]}}
-- 		}
-- 	}
-- }

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

engine.items["001.alligator_1"] = {
	tag = "alli1",
	pos = {10, 5, 0},
	model = "alligator",
	sci_char = { speed = 50, acceleration=0.1, fliph=true, fourway=false},
	hotspot = {

		priority = 2,
		size = {25,10}, offset = {-12,0}
	},
	actions = {
		look = {
			{ type = action.kq.showmessage, args = { msg=strings.room001[5]}}
		}
	}
}

engine.items["001.alligator_2"] = {
	tag = "alli2",
	pos = {150, 5, 0},
	model = "alligator",
	sci_char = { speed = 40, acceleration=0.1, fliph=true, fourway=false},
	hotspot = {
		priority = 2,
		size = {25,10}, offset = {-12,0}
	},
	actions = {
		look = {
			{ type = action.kq.showmessage, args = { msg=strings.room001[5]}}
		}
	}
}
