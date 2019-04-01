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

items["forest2.1"] = fr("forest_1")
items["forest2.3"] = fm(257, "forest_3")

items["forest3.2"] = fm(135, "forest_2")
items["forest3.4"] = fr("forest_4")

items["forest4.3"] = fl("forest_3")
items["forest4.5"] = fr("forest_5")

items["forest5.4"] = fm(241,"forest_4")
items["forest5.6"] = fl("forest_6", 24)

items["forest6.5"] = fl("forest_5")