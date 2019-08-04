local w1 = 20
local h1 = 50
local wh = 35

engine.items["forest1.walkarea"] = scumm.factory.walkarea {
	shape = { 
		type = "graph", 
		vertices = { {103, 35}, {154,35}, {238, 35}, {320, 35}, {154, 69}, {238, 69}}, 
		edges = { {0,1}, {1,2}, {2,3}, {1, 4}, {2, 5}}
	},
	depth = { type="linear_y", values= {0, 1, 144, 0} },
	priority = 0,
}

engine.items["forest2.walkarea"] = scumm.factory.walkarea {
	shape = { 
		type = "graph", 
		vertices = { {0, 35}, {257,35}, {320, 35}, {257, 69}}, 
		edges = { {0,1}, {1,2}, {1,3}}
	},
	depth = { type="linear_y", values= {0, 1, 144, 0} },
	priority = 0,
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
engine.items["forest6.7"] = fm(241, "forest_7")

engine.items["forest7.6"] = fl("forest_6")
engine.items["forest7.sm"] = fl("swordmaster")

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


