local w1 = 20
local h1 = 50
local wh = 35


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

items["forest1.1"] = fr("meleemap")
items["forest1.2"] = fm(238, "forest_2")
items["forest1.2b"] = fm(159, "forest_2")

items["forest2.1"] = fr("forest_1")
items["forest2.3"] = fm(257, "forest_3")
items["forest2.9"] = fl("forest_9")

items["forest3.2"] = fm(135, "forest_2")
items["forest3.4"] = fr("forest_4")

items["forest4.3"] = fl("forest_3")
items["forest4.5"] = fr("forest_5")

items["forest5.4"] = fm(241,"forest_4")
items["forest5.6"] = fl("forest_6", 24)
items["forest5.8"] = fr("forest_8", 24)

items["forest6.5"] = fl("forest_5")
items["forest6.7"] = fm(241, "forest_7")

items["forest7.6"] = fl("forest_6")
items["forest7.sm"] = fl("swordmaster")

items["forest8.5"] = fm(134,"forest_5")
items["forest8.19"] = fl("forest_19")
items["forest8.9"] = fr("forest_9")

items["forest9.10"] = fm(154,"forest_10")
items["forest9.2"] = fl("forest_2")
items["forest9.8"] = fr("forest_8")

items["forest10.11"] = fl("forest_11")
items["forest10.9"] = fr("forest_9")

items["forest11.12"] = fm(256, "forest_12")
items["forest11.10"] = fr("forest_10")

items["forest12.13"] = fl("forest_13")
items["forest12.11"] = fr("forest_11")

items["forest13.14"] = fm(256,"forest_14")
items["forest13.12"] = fr("forest_12")

-- items["forest14.13"] = fl("forest_13")
-- items["forest14.15"] = fm("forest_15")

-- items["forest15.18"] = fl("forest_18")
-- items["forest15.14"] = fm("forest_14")
-- items["forest15.16"] = fr("forest_16")

-- items["forest16.17"] = fl("forest_17")
-- items["forest16.15"] = fm("forest_15")

-- items["forest17.21"] = fl("forest_21")
-- items["forest17.treasure"] = fm("treasure")
-- items["forest17.16"] = fr("forest_16")

-- items["forest18.19"] = fl("forest_19")
-- items["forest18.15"] = fm("forest_15")

-- items["forest19.8"] = fl("forest_8")
-- items["forest19.20"] = fm("forest_20")
-- items["forest19.18"] = fr("forest_18")

-- items["forest20.19"] = fr("forest_19")

-- items["forest21.17"] = fr("forest_19")


