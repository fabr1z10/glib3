local w1 = 20
local h1 = 50
local wh = 35


local fw = function(v, e) 

	return {
		type = 'walkarea',
		tag = true,
		shape = { type = 'graph', vertices=v, edges=e},
		priority = 0,
		depth = { type = 'linear_y', values= {0, 1, 144, 0} },
	}	

end



-- make a connection between two forest locations
local f = function(args)
	glib.assert(args.pos, 'pos')
	glib.assert(args.walkto, 'walkto')
	glib.assert(args.dir, 'dir')
	glib.assert(args.size, 'size')
	glib.assert(args.go_to, 'go_to')
 
	return {
		type = 'object',
		pos = {args.pos[1], args.pos[2], 0},
		hotspot = {	
			text = strings.objects.path,
			walk_to = args.walkto, 
			dir = args.dir,
			size = args.size
		},	
		actions = {
			walk = scumm.script.changeroom { 
				room = args.go_to.room,
				pos = args.go_to.pos,
				dir = args.go_to.dir
			}
		}
}
end

local fright = function(args)
	glib.assert(args.walkto, 'walkto')
	glib.assert(args.go_to, 'go_to')
	return f { 
		pos = {310, 0}, 
		size = {10, 144},
		dir = 'e',
		walkto = args.walkto,
		go_to = args.go_to
	}
end

local fleft = function(args)
	glib.assert(args.walkto, 'walkto')
	glib.assert(args.go_to, 'go_to')
	return f {
		pos = {0, 0},
		size = {10, 144}, 
		dir = 'w',
		walkto = args.walkto,
		go_to = args.go_to
	}
end

local fmid = function(args)
	glib.assert(args.pos, 'pos') 
	glib.assert(args.walkto, 'walkto')
	glib.assert(args.go_to, 'go_to')
	return f {
		pos = { args.pos[1] - w1/2, args.pos[2]},
		size = {w1, h1},
		dir = 'n',
		walkto = args.walkto,
		go_to = args.go_to
	}	
end

engine.items["forest1.walkarea"] = fw ({ 
	{103, 35}, {154,35}, {238, 35}, {320, 35}, {154, 69}, {238, 69}}, 
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
engine.items["forest7.walkarea"] =
{
    type = 'walkarea',
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

local m = mi.rooms

-- forest 1
engine.items["forest1.1"] = fright { go_to = { room = 'meleemap', pos = m.meleemap.fork, dir='e'}, walkto = m.forest_1.to_map }
engine.items["forest1.2"] = fmid { pos = {238, 68}, go_to = { room = 'forest_2', pos = m.forest_2.to_forest_1, dir = 'w' }, walkto = m.forest_1.to_forest_2_1 }
engine.items["forest1.2b"] = fmid { pos = {159, 68}, go_to = { room = 'forest_2', pos = m.forest_2.to_forest_1, dir = 'w' }, walkto = m.forest_1.to_forest_2_2 }

-- forest 2
engine.items["forest2.1"] = fright { go_to = { room = 'forest_1', pos = m.forest_1.to_forest_2_1, dir='s'}, walkto = m.forest_2.to_forest_1 }
engine.items["forest2.3"] = fmid { pos = {257,68}, go_to = {room='forest_3', pos = m.forest_3.to_forest_2, dir = 's'}, walkto = m.forest_2.to_forest_3 }
engine.items["forest2.9"] = fleft { go_to = {room = 'forest_9', pos = m.forest_9.to_forest_2, dir = 'e'}, walkto = m.forest_2.to_forest_9 }

engine.items["forest3.2"] = fmid { pos = {135, 68}, go_to = {room='forest_2', pos = m.forest_2.to_forest_3, dir = 's'}, walkto = m.forest_3.to_forest_2 } 
engine.items["forest3.4"] = fright { go_to = { room = 'forest_4', pos = m.forest_4.to_forest_3, dir='e'}, walkto = m.forest_3.to_forest_4 }

engine.items["forest4.3"] = fleft { go_to = { room = 'forest_3', pos = m.forest_3.to_forest_4, dir = 'e'}, walkto = m.forest_4.to_forest_3 }
engine.items["forest4.5"] = fright { go_to = { room ='forest_5', pos = m.forest_5.to_forest_4, dir = 'e'}, walkto = m.forest_4.to_forest_5 }

engine.items["forest5.4"] = fmid { pos = {241, 68}, go_to = { room='forest_4', pos = m.forest_4.to_forest_5, dir = 'w'}, walkto=m.forest_5.to_forest_4 }
engine.items["forest5.6"] = fleft { go_to = { room = "forest_6", pos = m.forest_6.to_forest_5, dir = 'e' }, walkto = m.forest_5.to_forest_6 }
engine.items["forest5.8"] = fright { go_to = { room = "forest_8", pos = m.forest_8.to_forest_5, dir = 'e' }, walkto = m.forest_5.to_forest_8 }

engine.items["forest6.5"] = fleft { go_to = { room = 'forest_5', pos = m.forest_5.to_forest_6, dir = 'e' }, walkto = m.forest_6.to_forest_5 }
engine.items["forest6.7"] = fmid { pos = {151, 68}, go_to = { room='forest_7', pos = m.forest_7.to_forest_6, dir = 'w'}, walkto=m.forest_6.to_forest_7 }

engine.items["forest7.6"] = fleft { go_to = { room = 'forest_6', pos = m.forest_6.to_forest_7, dir = 's'}, walkto = m.forest_7.to_forest_6 }
engine.items["forest7.sm"] = fright { go_to = { room = "swordmaster", pos = m.swordmaster.to_map, dir = 'e'}, walkto = m.forest_7.to_swordmaster }

--engine.items["sm.exit"] = fl("meleemap",10)

-- engine.items["forest8.5"] = fm(134,"forest_5")
-- engine.items["forest8.19"] = fl("forest_19")
-- engine.items["forest8.9"] = fr("forest_9")

-- engine.items["forest9.10"] = fm(154,"forest_10")
-- engine.items["forest9.2"] = fl("forest_2")
-- engine.items["forest9.8"] = fr("forest_8")

-- engine.items["forest10.11"] = fl("forest_11")
-- engine.items["forest10.9"] = fr("forest_9")

-- engine.items["forest11.12"] = fm(256, "forest_12")
-- engine.items["forest11.10"] = fr("forest_10")

-- engine.items["forest12.13"] = fl("forest_13")
-- engine.items["forest12.11"] = fr("forest_11")

-- engine.items["forest13.14"] = fm(256,"forest_14")
-- engine.items["forest13.12"] = fr("forest_12")

-- engine.items["forest14.13"] = fl("forest_13")
-- engine.items["forest14.15"] = fm(48, "forest_15")

-- engine.items["forest15.18"] = fl("forest_18")
-- engine.items["forest15.14"] = fm(153, "forest_14")
-- engine.items["forest15.16"] = fr("forest_16")

-- engine.items["forest16.17"] = fl("forest_17")
-- engine.items["forest16.15"] = fm(30,"forest_15")

-- engine.items["forest17.21"] = fl("forest_21")
-- engine.items["forest17.treasure"] = fm(155, "treasure")
-- engine.items["forest17.16"] = fr("forest_16")

-- engine.items["forest18.19"] = fl("forest_19")
-- engine.items["forest18.15"] = fm(135, "forest_15")

-- engine.items["forest19.8"] = fl("forest_8")
-- engine.items["forest19.20"] = fm(155, "forest_20")
-- engine.items["forest19.18"] = fr("forest_18")

-- engine.items["forest20.19"] = fr("forest_19")

-- engine.items["forest21.17"] = fr("forest_17")


engine.items["forest.yellowplant"] = { 
	type = 'object',
	tag = true,
 	pos = {253, 12, 1},
	hotspot = {
 		text = strings.objects.plants,
 		size = {39, 29},
 		walk_to = {271, 15},
 		dir='s'
	},	
	actions = {
        look = { type = scumm.action.say, args = { tag = 'player', lines = { strings.forest[1] } } },
        pick = function()
            if scumm.utils.has_player ( 'yellowpetal') then
                return nil
            else
                return { type = scumm.action.add_to_inventory, args = { id = 'yellowpetal' } }
            end
        end
    }
}

engine.items["forest.redplant"] = { 
	type = 'object',
	tag = true,
	pos = {253, 0, 1},
	hotspot = {
		text = strings.objects.plants,
		size = {53, 40},
		walk_to = {271, 15},
		dir="s"
	},	
	actions = {
		look = { type = scumm.action.say, args = {tag="player", lines = {strings.forest[4]}}},
		pick = { type = scumm.action.say, args = {tag="player", lines = {strings.forest[5]}}},
	}
}

-- engine.items["swordmaster.sign"] = { 
-- 	pos = {171, 20, 0},
-- 	model = "swordmaster.sign",
-- 	hotspot = {
-- 		text = strings.objects.sign,
-- 		size = {26, 25},
-- 		walk_to = {160, 20},
-- 		dir="east"
-- 	},	
-- 	actions = {
-- 		look = { type = scumm.action.say, args = {actor="guybrush", lines = {strings.forest[6]}}},
-- 		use = function()
-- 			variables.swordmaster_trunk_open = not variables.swordmaster_trunk_open
-- 			return {
-- 				{ type = scumm.action.disable_controls, args = {value=true} },
-- 				{ ref=1, type = action.animate, args = {tag="player", anim="operate_e", sync = true}},
-- 				{ type = action.animate, args = {tag="player", anim="idle_e"}, after={1}},
-- 				{ type = action.animate, args = {tag="swordmaster.sign", anim="activated"}, after={1}},
-- 				{ type = action.delay, args = {sec = 2}},
-- 				{ type = action.animate, args = {tag="swordmaster.sign", anim="default"}},			
-- 				{ type = scumm.action.enable_wall, args = {walkarea="forest7.walkarea", wall=0, active=not variables.swordmaster_trunk_open}},
-- 				{ type = action.animate, args = {tag="forest7.trunk.bridge", anim=variables.swordmaster_trunk_open and "open" or "closed"}},			
-- 				{ type = scumm.action.disable_controls, args = {value=false} },
-- 			}
-- 		end
-- 	}
-- }

-- engine.items["forest7.trunk.bridge"] = { 
-- 	pos = {229, 22, 0},
-- 	model = "trunk.bridge",
-- }

engine.items["yellowpetal"] = {
	hotspot = {
		text = strings.objects.yellowpetal,
	},
	actions = {
		look = {
			{ type = scumm.action.say, args= { tag='player', lines = {strings.forest[2]}}}
		}
	}
}

--  -- function () 
-- 	-- 		print ("123")		
-- 	-- 		local s = script:new()
-- 	-- 		s.actions = {
-- 	-- 			action.say {id=1, actor="guybrush", lines = {strings.pieces_of_eight()}}
-- 	-- 		}
-- 	-- 		return s
-- 	-- 	end

-- 	}
-- }