roomDefinition = {
	width = 320,
	height = 320,
	-- startTable = {
	-- 	village1 = { pos = items["lookout.stairs"].hotspot.walk_to, dir="north"},
	-- 	meleemap = { pos = items["lookout.path"].hotspot.walk_to, dir = "east"},
	-- },
	defaultroom = "meleemap",
	walkareas = {
		-- from
		room1_walkarea_front = {
			-- to
			room1_walkarea_back = {
				{ type = scumm.action.walkto, args = {tag="player", pos = { 88, 18} }},
				{ type = scumm.action.turn, args={tag="player", dir="north"}},
				{ type = action.treemove, args = {tag="player", parent="room1_walkarea_hidden"}},
				{ type = action.animate, args ={tag="player", anim="walk_n"}},
				{ type = action.move, args = {tag="player", to = {88, 8}, speed = items["graham"].character.speed}},
				{ type = action.treemove, args = {tag="player", parent="room1_walkarea_back"}},
				--{ type = scumm.action.walkto, args = {tag="player", pos ={x,y}}},			 	
			}
		},
		room1_walkarea_back = {
			room1_walkarea_front = {
				{ type = scumm.action.walkto, args = {tag="player", pos = { 88, 8} }},
				{ type = scumm.action.turn, args={tag="player", dir="south"}},
				{ type = action.treemove, args = {tag="player", parent="room1_walkarea_hidden"}},
				{ type = action.animate, args ={tag="player", anim="walk_s"}},
				{ type = action.move, args = {tag="player", to = {88, 18}, speed = items["graham"].character.speed}},
				{ type = action.treemove, args = {tag="player", parent="room1_walkarea_front"}},
				--{ type = scumm.action.walkto, args = {tag="player", pos ={x,y}}},			 	
			}
		}

	}
}

room = scumm.factory.sci_room (roomDefinition)

--local d = strings.dialogues.lookout.text

room:add( {
	{ pos = {0, 0,-3}, components = { { type="gfx", image="gfx/001.png" }}},
	{ pos = {78, 0,2}, components = { { type="gfx", image="gfx/001a.png" }}},
	{ pos = {0, 0,1}, components = { { type="gfx", image="gfx/001c.png" }}},
	scumm.factory.sciobject { id="room1_walkarea_back", children =
		{
  		    scumm.factory.object {
	 			id="graham", 
	 			pos={160,50, 0}, 
	 	 		dir = "south",
	 			follow = false,
				--collide = args.c
	 		},
			{ pos = {109, 28, 0}, components = { { type="gfx", image="gfx/001b.png" }, { type="properties", additional_info = { walkarea_scale = false }}}},
			{ pos = {75, 45, 0}, components = { { type="gfx", image="gfx/001d.png", offset = {0,-12} }, { type="properties", additional_info = { walkarea_scale = false }}}},
			{ pos = {156, 36, 0}, components = { { type="gfx", image="gfx/001e.png" }, { type="properties", additional_info = { walkarea_scale = false }}}},
		}
	},
	scumm.factory.sciobject { id="room1_walkarea_front" },
	scumm.factory.sciobject { id="room1_walkarea_hidden" },	
	scumm.factory.sciobject { id="room1_room2" },	

	-- scumm.factory.hilly {
	-- 	shape_front = { type = "poly", outline = {0,16,12,13,27,10,42,8,57,8,60,10,75,17,81,21,87,20,91,16,99,16,93,10,84,3,78,0,5,0,0,0} },
	-- 	shape_back = { type = "poly", outline = {105,11,99,16,93,10,84,3,78,0,5,0,0,16,12,13,27,10,42,8,57,8,60,10,75,17,81,21,72,25,38,27,0,32,0,71,25,75,56,72,61,63,67,62,82,64,89,66,100,65,111,69,121,76,135,81,149,83,163,92,176,92,170,82,176,79,187,88,208,87,217,83,230,79,238,81,247,76,262,79,273,79,279,77,280,73,256,70,246,66,251,62,251,59,245,59,241,57,247,55,239,52,221,46,206,45,178,42,181,47,159,46,147,42,138,42,128,43,117,42,112,38,106,29,107,26,113,26,116,28,123,27,137,25,147,21,161,19,189,21,235,20,262,21,282,26,289,36,287,42,277,43,261,46,269,50,276,52,285,54,297,52,307,50,320,52,320,5,109,8,105,11},
	-- 		holes = {
	-- 			{77,51,65,50,62,47,69,43,57,41,61,33,75,32,82,31,89,40,100,44,117,45,101,46,91,45,83,49},
	-- 			{211,80,186,82,185,63,210,60}
	-- 		}
	-- 	},
	-- 	scale_back = { type="constant", value=0.7},
	--  	depth_front = { type="linear_y", values= {0, 1.1, 190, 1} },
	--  	scale_transition = { type="linear_y", values={18,1,8,0.7}},
	--  	depth_transition = { type="constant", value=-0.5},
	--  	connection_point_front = {88, 18},
	--  	connection_point_back = {88, 8},
	--  	children_back = {
 -- 		    scumm.factory.object {
	-- 			id="graham", 
	-- 			pos={160,50, 0}, 
	-- 	 		dir = "south",
	-- 			follow = false,
	-- 			--collide = args.c
	-- 		},

	-- 	}
	-- -- },
	scumm.factory.sciobject { id="crispins_house"},
	-- scumm.factory.sciobject { id="crispins_door"},
	-- scumm.factory.sciobject { id="crispins_window_1"},
	-- scumm.factory.sciobject { id="crispins_window_2"},
	-- scumm.factory.sciobject { id="crispins_window_3"},
	-- scumm.factory.walkarea {
	-- 	tag = "walkarea_1",
	-- 	priority = 1, 
	-- 	scale = { type="constant", value=0.5},
	-- 	depth = { type="linear_y", values= {0, 1, 190, 0} },
	-- 	shape = { 
	-- 		type = "poly", 
	-- 		outline = {0,71,27,72,61,70,65,63,74,63,88,65,103,70,113,73,123,79,135,82,149,82,
	-- 			163,93,176,92,171,82,172,81,180,82,190,88,209,85,222,82,236,80,246,78,263,82,272,90,
	-- 			310,90,303,80,271,74,250,69,244,65,253,61,241,59,245,55,221,47,213,46,180,43,183,48,
	-- 			163,46,152,44,149,41,136,41,123,44,115,39,107,33,107,28,113,27,116,29,145,23,150,21,
	-- 			192,20,221,22,251,22,285,23,294,35,282,42,265,45,270,52,285,55,314,59,319,59,319,9,
	-- 			125,10,109,14,101,14,83,1,76,0,0,1,0,18,6,15,27,11,46,9,56,9,63,13,79,17,88,19,74,22,47,27,17,28,0,31},
	-- 		holes = {
	-- 			{83,33,90,41,110,47,92,46,80,52,63,49,65,44,70,41,62,38,69,34},
	-- 			{185,81,184,62,210,59,212,79}
	-- 		}

	-- 	},
	-- 	children = {
 --        	scumm.factory.object {
	-- 			id="graham", 
	-- 			pos={160,50, 0}, 
	-- 			dir = "south",
	-- 			follow = false,
	-- 			--collide = args.collide
	-- 		},
	-- 		-- you can supply additional info to the walkareas for instance: do not scale this!

	-- 	}
	-- },
	-- 	scumm.factory.walkarea {
	-- 	tag = "walkarea_front",
	-- 	priority = 2, 
	-- 	scale = { type="constant", value=0.5},
	-- 	depth = { type="linear_y", values= {0, 1, 190, 0} },
	-- 	shape = { 
	-- 		type = "poly", 
	-- 		outline = {0,0,0,16,26,11,54,8,72,14,85,19,91,16,98,16,81,0},
	-- 	},
	-- 	children = {
	-- 	}
	-- },

	
	-- scumm.factory.message { 
	-- 	pos = {160, 100, 2}, 
	-- 	message = "The red fox jumped over the ceiling. I am very happy because of it.", 
 --        font="ui", 
 --        size = 8,
	-- 	maxwidth = 100, 
 --        color = {0,0,0,255}, 
 --        bgcolor = {235, 186, 130, 255}, 
 --        padding = 16,
	-- 	border = {
	-- 		img = "gfx/border2.png", thickness=3
	-- 	},
	-- 	corner = {
	-- 		img = "gfx/border.png"
	-- 	} 
 --    }	

 --    { pos = {81, 16, 3}, components = { { type="gfx", image="gfx/lookout_2.png" }}},
 --    { pos = {294, 33, 3}, components = { { type="gfx", image ="gfx/lookout_3.png" }}},
 --    scumm.factory.walkarea {
	-- 	shape = { type = "poly", outline = {203,51,315,62,315,40,293,40,260,10,260,0,260,-20,234,-20,234,0,234,10,221,26,152,33,152,51}}
 --    },
	-- scumm.factory.object { id = "lookout.stairs" },
	-- scumm.factory.object { id = "lookout.lookout" },
	-- scumm.factory.object { id = "lookout.fire" },
	-- scumm.factory.object { id = "lookout.path" },
})

-- local entry_cutscene = function() 
-- 	local actions = {
-- 		{ type = scumm.action.walkto, args = {tag="player", pos = {240, 30}}}
-- 	}
-- 	local s = script.make(actions)
-- 	s.name = "_walk"
-- 	monkey.play(s)
-- end

-- table.insert(room.initstuff, entry_cutscene)