local w1 = 20
local h1 = 50
local wh = 35


local fw = function(v, e) 
	return scumm.factory.walkarea {
		shape = { 
			type = "graph", 
			vertices = v,
			edges = e
		},
		depth = { type="linear_y", values= {0, 1, 144, 0} },
		priority = 0
	}

end

engine.items["forest1.walkarea"] = fw (
	{{103, 35}, {154,35}, {238, 35}, {320, 35}, {154, 69}, {238, 69}}, 
	{{0,1}, {1,2}, {2,3}, {1, 4}, {2, 5}}
)
engine.items["forest2.walkarea"] = fw (
	{{0, 35}, {257,35}, {320, 35}, {257, 69}, {271,35},{271,15}}, 
	{{0,1}, {1,4}, {4,2}, {4,5}, {1,3}}
)
engine.items["forest3.walkarea"] = fw ({ {135, 69}, {135,35}, {320, 35}}, { {0,1}, {1,2} })
engine.items["forest4.walkarea"] = fw ({ {0, 35}, {266,35}, {320, 35}, {266, 20}}, { {0,1}, {1,2}, {1,3} })
engine.items["forest5.walkarea"] = fw ({ {0, 24}, {241,24}, {320, 24}, {241, 69}}, { {0,1}, {1,2}, {1,3} })
engine.items["forest6.walkarea"] = fw ({ {0, 35}, {151,35}, {151, 69}}, { {0,1}, {1,2} })
engine.items["forest7.walkarea"] = scumm.factory.walkarea {
	shape = { 
		type = "poly", 
		outline = {0, 30, 0,31,77,31,213,48,320,48,213,47,197,0,140,0,77,30}
	},
	blockedlines = {
	 	{ A = {212, 0}, B = {212, 144}, active =true },
	},	
	depth = { type="linear_y", values= {0, 1, 144, 0} },
	priority = 0
}

local f = function(x, y, wx, wy, dir, width, height, roomTo) 
	return {
		pos = {x, y, 0},
		hotspot = {	
			text = strings.objects.path,
			walk_to = {wx, wy}, 
			dir = dir,
			size = {width, height}
		},	
		actions = {
			walk = { type = action.change_room, args ={room=roomTo}}
		}
}
end

local fr = function(dest, walk_h)
	return f(310, 0, 310, walk_h or wh, "east", 10, 144, dest)
end
local fl = function(dest, walk_h)
	return f(0, 0, 10, walk_h or wh, "west", 10, 144, dest)
end
local fm = function(x, dest) 
	return f (x-w1/2, 69, x, 69, "north", w1, h1, dest)
end

engine.items["forest1.1"] = fr("meleemap")
engine.items["forest1.2"] = fm(238, "forest_2")
engine.items["forest1.2b"] = fm(159, "forest_2")

engine.items["forest2.1"] = fr("forest_1")
engine.items["forest2.3"] = fm(257, "forest_3")
engine.items["forest2.9"] = fl("forest_9")

engine.items["forest3.2"] = fm(135, "forest_2")
engine.items["forest3.4"] = fr("forest_4")

engine.items["forest4.3"] = fl("forest_3")
engine.items["forest4.5"] = fr("forest_5")

engine.items["forest5.4"] = fm(241,"forest_4")
engine.items["forest5.6"] = fl("forest_6", 24)
engine.items["forest5.8"] = fr("forest_8", 24)

engine.items["forest6.5"] = fl("forest_5")
engine.items["forest6.7"] = fm(151, "forest_7")

engine.items["forest7.6"] = fl("forest_6",30)
engine.items["forest7.sm"] = fr("swordmaster")
engine.items["sm.exit"] = fl("meleemap",10)

engine.items["forest8.5"] = fm(134,"forest_5")
engine.items["forest8.19"] = fl("forest_19")
engine.items["forest8.9"] = fr("forest_9")

engine.items["forest9.10"] = fm(154,"forest_10")
engine.items["forest9.2"] = fl("forest_2")
engine.items["forest9.8"] = fr("forest_8")

engine.items["forest10.11"] = fl("forest_11")
engine.items["forest10.9"] = fr("forest_9")

engine.items["forest11.12"] = fm(256, "forest_12")
engine.items["forest11.10"] = fr("forest_10")

engine.items["forest12.13"] = fl("forest_13")
engine.items["forest12.11"] = fr("forest_11")

engine.items["forest13.14"] = fm(256,"forest_14")
engine.items["forest13.12"] = fr("forest_12")

engine.items["forest14.13"] = fl("forest_13")
engine.items["forest14.15"] = fm(48, "forest_15")

engine.items["forest15.18"] = fl("forest_18")
engine.items["forest15.14"] = fm(153, "forest_14")
engine.items["forest15.16"] = fr("forest_16")

engine.items["forest16.17"] = fl("forest_17")
engine.items["forest16.15"] = fm(30,"forest_15")

engine.items["forest17.21"] = fl("forest_21")
engine.items["forest17.treasure"] = fm(155, "treasure")
engine.items["forest17.16"] = fr("forest_16")

engine.items["forest18.19"] = fl("forest_19")
engine.items["forest18.15"] = fm(135, "forest_15")

engine.items["forest19.8"] = fl("forest_8")
engine.items["forest19.20"] = fm(155, "forest_20")
engine.items["forest19.18"] = fr("forest_18")

engine.items["forest20.19"] = fr("forest_19")

engine.items["forest21.17"] = fr("forest_17")


engine.items["forest.yellowplant"] = { 
	pos = {253, 12, 1},
	hotspot = {
		text = strings.objects.plants,
		size = {39, 29},
		walk_to = {271, 15},
		dir="south"
	},	
	actions = {
		look = { type = scumm.action.say, args = {actor="guybrush", lines = {strings.forest[1]}}},
		pick = scumm.action.pickup { id="forest.yellowplant", id_inv = "yellowpetal", alreadyhave = {strings.forest[3]} }
	}
}

engine.items["forest.redplant"] = { 
	pos = {253, 0, 1},
	hotspot = {
		text = strings.objects.plants,
		size = {53, 40},
		walk_to = {271, 15},
		dir="south"
	},	
	actions = {
		look = { type = scumm.action.say, args = {actor="guybrush", lines = {strings.forest[4]}}},
		pick = { type = scumm.action.say, args = {actor="guybrush", lines = {strings.forest[5]}}},
	}
}

engine.items["swordmaster.sign"] = { 
	pos = {171, 20, 0},
	model = "swordmaster.sign",
	hotspot = {
		text = strings.objects.sign,
		size = {26, 25},
		walk_to = {160, 20},
		dir="east"
	},	
	actions = {
		look = { type = scumm.action.say, args = {actor="guybrush", lines = {strings.forest[6]}}},
		use = function()
			variables.swordmaster_trunk_open = not variables.swordmaster_trunk_open
			return {
				{ type = scumm.action.disable_controls, args = {value=true} },
				{ ref=1, type = action.animate, args = {tag="player", anim="operate_e", sync = true}},
				{ type = action.animate, args = {tag="player", anim="idle_e"}, after={1}},
				{ type = action.animate, args = {tag="swordmaster.sign", anim="activated"}, after={1}},
				{ type = action.delay, args = {sec = 2}},
				{ type = action.animate, args = {tag="swordmaster.sign", anim="default"}},			
				{ type = scumm.action.enable_wall, args = {walkarea="forest7.walkarea", wall=0, active=not variables.swordmaster_trunk_open}},
				{ type = action.animate, args = {tag="forest7.trunk.bridge", anim=variables.swordmaster_trunk_open and "open" or "closed"}},			
				{ type = scumm.action.disable_controls, args = {value=false} },
			}
		end
	}
}

engine.items["forest7.trunk.bridge"] = { 
	pos = {229, 22, 0},
	model = "trunk.bridge",
}

engine.items["yellowpetal"] = {
	hotspot = {
		text = strings.objects.yellowpetal,
	},
	actions = {
		look = {
			{ type = scumm.action.say, args= { actor="guybrush", lines = {strings.forest[2]}}}
		}

 -- function () 
	-- 		print ("123")		
	-- 		local s = script:new()
	-- 		s.actions = {
	-- 			action.say {id=1, actor="guybrush", lines = {strings.pieces_of_eight()}}
	-- 		}
	-- 		return s
	-- 	end

	}
}