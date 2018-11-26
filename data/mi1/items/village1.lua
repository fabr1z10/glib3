items.village1 = {}

-- the local objects
items.village1.cliffside = {
	text = strings.objects.cliffside,
	pos = {0, 0, 0},
	walk_to = {11, 70}, 
	face = "west",
	size = {20, 144},			
	actions = {
		walk = curry(change_room, "lookout")
	}
}

items.village1.door = factory.door.create {
	tag = "door",
	pos = {699, 7, -1},
	size = {30, 45},
	walk_to = {715, 15},
	face = "north",
	door_ref = variables.door_village_scummbar,
	model = "door_village_scummbar",
	nextroom = "lookout"
}

-- {
-- 	tag="door",
-- 	text = strings.objects.door,
-- 	pos = {699, 7,-1},
-- 	size = {30, 45},
-- 	walk_to = {715, 15},
-- 	face = "north",
-- 	model ="door_village_scummbar",
-- 	anim = function() 
-- 		if (variables.door_village_scummbar == 0) then
-- 			return "close"
-- 		else
-- 			return "open"
-- 		end
-- 	end,
-- 	actions = {
-- 		open = function()
-- 			variables.door_village_scummbar = 1
-- 			local s = script:new()
-- 			s.actions = {
-- 				[1] = { type="animate", actor="door", anim="open" }
-- 			}
-- 			return s
-- 		end,
-- 		close = function()
-- 			variables.door_village_scummbar = 0
-- 			local s = script:new()
-- 			s.actions = {
-- 				[1] = { type="animate", actor="door", anim="close" }
-- 			}
-- 			return s
-- 		end,

-- 	}

-- }