


objects = {
    guybrush = {
        tag = "player",
        color = {255, 255, 255, 255},
		offset = {0, 60}
    },
    lookout = {
        tag = "lookout",
        text = strings.objects.lookout,
        pos = {160, 36},
        dir ="west",
		offset = {0, 60},
        color = {170, 170, 170, 255},
        talk = curry(talk, { character = "lookout", node = 1}),
		look = curry(_say,{character ="guybrush", lines = {strings.dialogues.lookout.text[50]}})
    },
    cook = {
        tag = "cook",
        color = {85, 255, 255, 255},
    },
    stairs = {
        text = strings.objects.stairs,
        pos = {250, 0}, -- location where the player will go
        walk = curry(changeRoom, "village1")
    },
	cliffside = {
		text = strings.objects.cliffside,
		pos = {8, 71},
		walk = curry(changeRoom, "lookout")
	},
    path = {
        text = strings.objects.path,
        pos = {314, 52},
        walk = curry(changeRoom, "meleemap")  
    },
    poster = {
        text = strings.objects.poster,
        pos = {269, 133},
        dir = "north",
        look = curry (_say, { character="guybrush", lines= { strings.village1[1], strings.village1[2] }} )
    },
    village1_door = {
        text = strings.objects.door,
        tag = "door1",
        pos = {715, 13},
        dir = "north",
		walk = curry(walkToDoor, { obj = "village1_door", roomId = "scummbar"}),
		open = curry(operateDoor, { obj = "village1_door", open = true }),
		close = curry(operateDoor, { obj = "village1_door", open = false }),
		isopen = curry(isOpen, "scummbar"),
		setopen = curry2(setOpen, "scummbar")
    },
    scummbar_door_out = {
        text = strings.objects.door,
        tag = "door1",
        pos = {66, 19},
        dir = "west",
		walk = curry(walkToDoor, {obj = "scummbar_door_out", roomId = "village1"}),
		open = curry(operateDoor, { obj = "scummbar_door_out", open = true }),
		close = curry(operateDoor, { obj = "scummbar_door_out", open = false }),
		isopen = curry(isOpen, "scummbar"),
		setopen = curry2(setOpen, "scummbar")
    },
    door_bar_kitchen = {
        text = strings.objects.door,
        tag = "door_bar_kitchen",
        pos = {600, 14},
		dir = "east",
		open = openBarKitchen,
		walk = enterBarKitchen,
		close = curry(operateDoor, {obj = "door_bar_kitchen", open = false} ),
		isopen = curry(isOpen, "kitchen"),
		setopen = curry2(setOpen, "kitchen")		
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
	fireplace = {
		text = strings.objects.fireplace,
		tag ="fireplace",
		pos = {506, 41},
		dir ="east",
		look = curry (say, { character="guybrush", lines= { strings.scummbar[1] }} )
	},
	ilp = {
		text = strings.objects.ilp,
		tag="ilp",
		pos={474,7},
		dir ="west",
 		talk = talkToPirates
	},
	ilp1 = {
		color = {85, 85, 255, 255},
		offset = {0, 60},
		tag ="ilp1"		

	},
	ilp2 = {
		color = {255, 255, 85, 255},
		offset = {0, 60},
		tag ="ilp2"		
	},
	ilp3 = {
		color = {255, 85, 255, 255},
		offset = {0, 60},
		tag ="ilp3"		
	},
	dog = {
		text = strings.objects.dog,
		tag = "dog",
		pos = {289, 9},
		dir = "north",
		talk = talkToDog,
        color = {170, 170, 170, 255},
		offset = {0, 60},
	},
	loom_pirate = {
		text = strings.objects.pirate,
		tag = "loompirate",
		pos = {239,15},
		dir = "east",
		color = {85, 85, 255, 255},
		offset = {0, 40},
		look = talkToLoom,
		talk = talkToLoom	
	},
	estevan = {
		text = strings.objects.pirate,
		tag = "estevan",
		pos = {200,10},
		dir = "south",
		color = {170, 85, 0, 255},
		offset = {0, 40},
		look = talkToEstevan,
		talk = talkToEstevan	
	},
	mancomb = {
		text = strings.objects.pirate,
		tag = "mancomb",
		pos = {123,17},
		dir = "north",
		color = {255, 85, 85, 255},
		offset = {0, 40},
		look = talkToMancomb,
		talk = talkToMancomb	
	},
	pirates_listening = {
		text = strings.objects.pirates,
		tag="pirateslistening",
		pos = {123,17},
		dir = "north",
		talk = curry (say, { character="guybrush", lines= { strings.scummbar[2], strings.scummbar[3] }} ),
		look = curry (say, { character="guybrush", lines= { strings.scummbar[3] }} )
	},
	sleeping_pirate = {
		text = strings.objects.pirate,
		tag = "sleepingpirate",
		pos = {52,14},
		dir ="south",
		talk = curry (say, { character="guybrush", lines= { strings.scummbar[4] }} ),
		look = curry (say, { character="guybrush", lines= { strings.scummbar[4] }} )
		
	},
    archway = {
        text = strings.objects.archway,
        pos = {1008, 34}, -- location where the player will go
		dir = "east",
        walk = curry(changeRoom, "village2")
    },
	citizen = {
		tag = "citizen",
		text = strings.objects.citizen,
		pos = {359, 27},
		dir = "west",
		color = {255, 85, 85, 255},
		offset = {0,60},
		look = lookCitizen,
		talk = talkCitizen
	},
	lowmoralfiber = {
		text = strings.objects.lowmoralfiber,
		pos = {75,14},
		dir="west",
		talk = curry(talk, { character = "lowmoralfiber", node = 1}),
	},
	lmf1 = {
		tag="lmf1",
		color = {255, 85, 255, 255},
		offset = {0,60}
	},
	lmf2 = {
		tag="lmf2",
		color = {85, 255, 255, 255},
		offset = {0,60}
	},	
	lmf3 = {
		tag="lmf3",
		color = {85, 255, 85, 255},
		offset = {0,60}
	},
	rat = {
		tag="rat",
		color = {170, 170, 170, 255},
		offset = {0,60}
	},
	door_village2_1 = {
		text = strings.objects.door,
		tag="door1",
		pos = {387, 37},
		dir="west",
		open = curry (door_transport, {doorfrom = "door1", doorto = "door4", dest = {172, 72}, playerdest = {188, 62}, anim="idle_front", flip=false})
	},
	door_village2_2 = {
		text = strings.objects.door,
		tag="door2",
		pos = {208, 59},
		dir="east",
		open = curry (door_transport, {doorfrom = "door2", doorto = "door3", dest = {160, 72}, playerdest = {134, 62}, anim="idle_front", flip=false})
	},
	door_village2_3 = {
		text = strings.objects.door,
		tag="door3",
		pos = {134, 62},
		dir="north",
		open = curry (door_transport, {doorfrom = "door3", doorto = "door1", dest = {800,72}, playerdest = {387, 33}, anim="idle_right", flip=false})
	},
	door_village2_4 = {
		text = strings.objects.door,
		tag="door4",
		pos = {188, 62},
		dir="north",
		open = curry (door_transport, {doorfrom = "door4", doorto = "door2", dest = {172, 72}, playerdest = {208, 59}, anim="idle_right", flip=true})
	},
	village2_archway = {
		text = strings.objects.archway,
		pos = {160,65},
		dir = "north",
		walk = curry(changeRoom, "village3")
	},
	village2_archway2 = {
		text = strings.objects.archway,
		pos = {436,36},
		dir = "north",
		walk = curry(changeRoom, "village1")
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

require ("rooms/voodoolady/items")
require ("rooms/village3/items")
require ("rooms/shop/items")
require ("rooms/clearing/items")
require ("rooms/circus/items")
require ("forest")