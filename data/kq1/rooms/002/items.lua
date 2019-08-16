engine.items["002.walkarea"] = scumm.factory.walkarea {
	shape = { type = "poly", outline = {0, 0, 0, 107, 154, 107, 154, 58, 95, 36, 129, 21, 198, 21, 198, 47, 249, 47, 247, 21, 316, 21, 316, 7, 92, 7, 73, 25,  47, 25, 17, 10}},
	priority = 0,
	depth = { type="linear_y", values= {0, 1, 144, 0} },
}

-- engine.items["001.moat"] = scumm.factory.walkarea {
-- 	shape = { type = "poly", outline = {0, 0, 0, 6, 229, 6, 242, 18, 294, 0}},
-- 	priority = 0,
-- 	depth = { type="linear_y", values= {0, 1, 144, 0} },
-- }

-- engine.items["castle"] = makeItem {outline = {0,21,0,126,100,126,100,161,187,161,187,142,173,132,173,21}, msg = strings.room001[1] } 
-- engine.items["001.bridge"] = makeItem { outline = {187,8,187,21,202,36,228,36,267,28,294,8}, msg = strings.room001[7]}
-- engine.items["001.moat.item"] = makeItem { outline = {0, 0, 0, 6, 229, 6, 242, 18, 294, 0}, msg = strings.room001[4]}
-- engine.items["001.tree"] = makeItem { outline = {264,41,264,74,236,110,206,110,206,166,316,166,316,99,289,99,280,80,280,41}, msg = strings.room001[6]}

-- engine.items["flags"] = {
-- 	pos={0,0,0},
-- 	hotspot = {
-- 		priority = 1,
-- 		shape = { type ="poly", outline={4,129,4,162,92,162,92,129}}
-- 	},
-- 	actions = {
-- 		look = {
-- 			{ type = action.kq.showmessage, args = { msg=strings.room001[2]}}
-- 		}
-- 	--		look = box{ msg = strings[args.msg], sprite = args.sprite },
-- 	--		walk = function(x, y) return scumm.ui.walk { pos ={x,y}, walkarea = args.wa} end,
-- 	--		use = args.use
-- 	}
-- }

engine.items["002.flags"] = makeItem { x=221, y=130, width =86, height=32, msg = strings.room002[3]} 
engine.items["002.lion1"] = makeItem { x=168, y=40, width =30, height=41, msg = strings.room002[5]} 
engine.items["002.lion2"] = makeItem { x=257, y=40, width =30, height=41, msg = strings.room002[5]} 


engine.items["002.door"] = {
 	pos = {206, 46, 0},
 	model = "castle_door",
	hotspot = {
		priority = 1,
		size = {42,52},
	},
	actions = {
		look = {
			{ type = action.kq.showmessage, args = { msg=strings.room002[2]}}
		},
		use = {
			{ type = scumm.action.walkto, args = {tag="player", pos ={227, 46}}},
			{ type = action.animate, args = { tag="002.door", anim="open", sync = true}},
			{ type = action.delay, args = {sec=1}},
			{ type = action.change_room, args ={ room="003" }}
		}
	}
}

engine.items["002.purple_flag"] = {
 	pos = {226, 150, 0},
 	model = "purple_flag"
}

engine.items["002.yellow_flag"] = {
	pos = {256, 150, 0},
	model = "yellow_flag"
}

engine.items["002.cyan_flag"] = {
	pos = {286, 150, 0},
	model = "cyan_flag"
}

-- engine.items["alligator_1"] = {
-- 	tag = "alli1",
-- 	pos = {10, 5, 0},
-- 	model = "alligator",
-- 	sci_char = { speed = 50, acceleration=0.1, fliph=true, fourway=false},
-- 	hotspot = {

-- 		priority = 2,
-- 		size = {25,10}, offset = {-12,0}
-- 	},
-- 	actions = {
-- 		look = {
-- 			{ type = action.kq.showmessage, args = { msg=strings.room001[5]}}
-- 		}
-- 	}
-- }

-- engine.items["alligator_2"] = {
-- 	tag = "alli2",
-- 	pos = {150, 5, 0},
-- 	model = "alligator",
-- 	sci_char = { speed = 40, acceleration=0.1, fliph=true, fourway=false},
-- 	hotspot = {
-- 		priority = 2,
-- 		size = {25,10}, offset = {-12,0}
-- 	},
-- 	actions = {
-- 		look = {
-- 			{ type = action.kq.showmessage, args = { msg=strings.room001[5]}}
-- 		}
-- 	}
-- }
