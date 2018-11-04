


objects = {
    guybrush = {
        tag = "player",
        color = {255, 255, 255, 255},
		offset = {0, 60}
    },

    cook = {
        tag = "cook",
        color = {85, 255, 255, 255},
    },






	door_kitchen_bar = {
		text = strings.objects.door,
		tag = "door_kitchen_bar",
        pos = {50, 15},
		dir = "west",
		walk = curry(walkToDoor, {obj = "door_kitchen_bar", roomId = "scummbar"}),
		open = curry(operateDoor, { obj = "door_kitchen_bar", open = true }),
		close = curry(operateDoor, { obj = "door_kitchen_bar", open = false }),
		isopen = curry(isOpen, "kitchen"),
		setopen = curry2(setOpen, "kitchen")		
	},
	door_kitchen_pier = {
		text = strings.objects.door,
		tag = "door_kitchen_pier",
		openFlag = false,
		isopen = curry(isOpen, "door_kitchen_pier"),
		setopen = curry2(setOpen, "door_kitchen_pier"),
		posfunc = function () 
			player = monkey.getEntity("player")
			if (player.x > 200) then
				return { 210, 14}
			else
				return {190, 14}	
			end
		end,
		dirfunc = function () 
			player = monkey.getEntity("player")
			if (player.x > 200) then
				return "west"
			else
				return "east"	
			end
		end,
		open = openKitchenPierDoor,
		close = closeKitchenPierDoor
	},
	meat = {
		text = strings.objects.meat,
		tag = "meat",
		pos = {76, 19},
		dir = "north",
 		look = curry (_say, { character="guybrush", lines= { strings.kitchen[1] }} ),
		pick = curry (pickup, {obj = "meat"})
	},
	pot = {
		text = strings.objects.pot,
		tag = "pot",
		pos = {109, 19},
		dir ="north",
		pickupAnim = "kneel_back",
		look = curry (_say, { character="guybrush", lines= { strings.kitchen[2] }} ),
		pick = curry (pickup, {obj = "pot"})
	},
	fish = {
		text = strings.objects.fish,
		tag = "fish",
		pos = {239, 16},
		dir ="south",
		pickupAnim = "kneel_front",
		look = curry (_say, { character="guybrush", lines= { strings.kitchen[3] }} ),
		pick = getFish
	},
	pieceofeight = {
		text = strings.objects.pieceofeight,
		plural = strings.objects.piecesofeight,
		look = lookPiecesOfEight		
	},
	minutes = {
		text = strings.objects.minutes,
		look = curry (say, { character="guybrush", lines= { strings.village2[2] }} ),
	},
	potostew = {
		text = strings.objects.potostew,
		tag ="potostew",
		pos = {161, 19},
		dir ="north",
		look = lookatPotoStew,
		meatin = false,
		pick = pickMeatInStew,
		use = {
			meat = stewMeat
		}
	},
	barrel = {
		text = strings.objects.barrel,
		tag ="barrel",
		pos = {47, 6},
		dir ="west",
		look = curry (say, { character="guybrush", lines= { strings.kitchen[6] }} )
	},
	kitchen_table = {		
		text = strings.objects.kitchen_table,
		tag ="kitchentable",
		pos = {132, 14},
		dir ="south"
	},




 	door_voodoolady_out = {
	text = strings.objects.door,
    tag = "door_voodoo",
    pos = {231, 52},
	dir = "east",
	walk = curry(walkToDoor, { obj = "door_voodoolady_out", roomId = "voodoolady"}),
	open = curry(operateDoor, { obj = "door_voodoolady_out", open = true }),
	close = curry(operateDoor, { obj = "door_voodoolady_out", open = false }),
	isopen = curry(isOpen, "voodoolady"),
	setopen = curry2(setOpen, "voodoolady")		
	}
	-- door_voodoolady_in = {
	-- 	text = strings.objects.door,
	-- 	tag = "door_voodoo",
 --        pos = {50, 15},
	-- 	dir = "west",
	-- 	walk = curry(walkToDoor, {obj = "door_kitchen_bar", roomId = "scummbar"}),
	-- 	open = curry(operateDoor, { obj = "door_kitchen_bar", open = true }),
	-- 	close = curry(operateDoor, { obj = "door_kitchen_bar", open = false }),
	-- 	isopen = curry(isOpen, "door_bar_kitchen"),
	-- 	setopen = curry2(setOpen, "door_bar_kitchen")		
	-- },
}

-- require ("rooms/voodoolady/items")
-- require ("rooms/village3/items")
-- require ("rooms/shop/items")
-- require ("rooms/clearing/items")
-- require ("rooms/circus/items")
-- require ("forest")