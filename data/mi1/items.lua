items = {}

require ("items/button")
require ("items/player")
require ("items/object")


objects= {
    guybrush = {
		tag = "player",
		text_color = {255, 255, 255, 255},
		text_offset = {0, 60}
	},
	-- lookout = {
	-- 	stairs = {
	-- 		text = strings.objects.stairs,
	-- 		pos = {250, 0, 0},
	-- 		walk_to = {250, 0}, 
	-- 		face = "south",
	-- 		size = {10, 10},			
	-- 		actions = {
	-- 			walk = curry(changeRoom, "village1")
	-- 		}
	-- 	}
	-- }


}

defaultActions = {
	look = curry (say, {actor=objects.guybrush, lines = {strings.defaultactions[4]} })
}
