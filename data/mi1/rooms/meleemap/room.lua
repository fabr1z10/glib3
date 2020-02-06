
roomDefinition = {
	width = 320,
	height = 200,
	startTable = {
		lookout = { walkarea="meleemap.walkarea", pos = {75, 79}, dir = "north"},
		clearing = { walkarea="meleemap.walkarea", pos = {135, 113}, dir = "west"},
		bridge = { walkarea="meleemap.walkarea", pos = {169, 67}, dir = "east"},
		forest_1 = { walkarea="meleemap.walkarea", pos = {74, 112}, dir = "west"},
		swordmaster = { walkarea="meleemap.walkarea", pos = {74, 112}, dir = "west"},
	},
	defaultroom = "lookout",
	walkareas = { "meleemap.walkarea" },
	--depth = { type="linear_y", values= {0, 1, 144, 0} },
	--scale = { type="constant", value=0.1},
	collide = true
}

room = scumm.factory.map_room(roomDefinition)

room:add ( "main",
	{ 
		{ pos = {0, 0,-3}, components = { { type="gfx", image="meleemap.png" }}},
		scumm.factory.mapitem { pos={75, 79}, name = strings.objects.lookout, room="lookout" },
		--scumm.factory.mapitem { pos={169, 67}, name = strings.objects.bridge, room="bridge" },
		scumm.factory.mapitem { pos={74, 112}, name = strings.objects.fork, room ="forest_1"},
		scumm.factory.mapitem { pos={136, 113}, name = strings.objects.clearing, room ="clearing"}

	}
)

if (variables.know_where_sword_master_is) then
	room:add ("main", {
		scumm.factory.mapitem { pos={100, 152}, name = "Sword Master's", room="swordmaster" },
	})
end



table.insert(room.initstuff, glib.curry (mi.addStorekeeper, { 
	pos = {55, 97, 0}, 
	parent="meleemap.walkarea", 
	from = "lookout",
	walkto = { {74, 112} }
}))
-- room:add( {
-- 	{ pos = {0, 0,-3}, components = { { type="gfx", image="gfx/meleemap.png" }}},
-- 	scumm.factory.walkarea { shape = { 
-- 		type = "graph", 
-- 		vertices = { {76, 80}, {78, 81}, {71,90}, {64, 96}, {48,99}, {49, 114}, {73, 113}, {88, 114},{118,114}, {135,113}, {83,109},
-- 			{101, 107}, {112, 97}, {157, 78}, {172, 64}, {196, 54}, {217,54}, {232,49}, {245,48}, {254,50}, {275, 95}, {54,131},{57,140}, {60,151},
-- 	 		{67,161}, {82, 174}, {113, 177}, {146, 168}, {169,168}, {180, 174}, {196,174}, {227,180} }, 
-- 		edges = { {0,1}, {1,2}, {2,3},{3,4}, {4,5}, {5,6}, {6,7}, {7,8}, {8,9}, {6,10}, {10,11}, {11,12}, {12,13}, {13,14}, {14,15}, {15,16},{16,17},{17,18},
-- 			{18,19}, {19,20}, {5,21}, {21,22}, {22,23}, {23,24}, {24,25}, {25,26}, {26,27}, {27, 28}, {28,29}, {29,30}, {30,31} }}
-- 	},

-- 	-- {
-- 	-- 	pos = {0,0,0},
-- 	-- 	components = {
--  --      		{ 
-- 	-- 			type ="walkarea",
-- 	-- 			priority = 0,
--  --       			target = "player",
--  --            	shape = { type = "graph", vertices = { {76, 80}, {78, 81}, {71,90}, {64, 96}, {48,99}, {49, 114}, {73, 113}, {88, 114},{118,114}, {135,113}, {83,109},
-- 	-- 				{101, 107}, {112, 97}, {157, 78}, {172, 64}, {196, 54}, {217,54}, {232,49}, {245,48}, {254,50}, {275, 95}, {54,131},{57,140}, {60,151},
-- 	-- 				{67,161}, {82, 174}, {113, 177}, {146, 168}, {169,168}, {180, 174}, {196,174}, {227,180} }, edges = { 
-- 	-- 				{0,1}, {1,2}, {2,3},{3,4}, {4,5}, {5,6}, {6,7}, {7,8}, {8,9}, {6,10}, {10,11}, {11,12}, {12,13}, {13,14}, {14,15}, {15,16},{16,17},{17,18},
-- 	-- 				{18,19}, {19,20}, {5,21}, {21,22}, {22,23}, {23,24}, {24,25}, {25,26}, {26,27}, {27, 28}, {28,29}, {29,30}, {30,31}  }},
-- 	-- 		}
--  --      	}
-- 	-- },
-- 	scumm.factory.mapitem { pos={75, 79}, name = "lookout", room="lookout" },
-- 	scumm.factory.mapitem { pos={135, 113}, name = "clearing", room="clearing" },
-- 	scumm.factory.mapitem { pos={169, 67}, name = "bridge", room="bridge" },
-- 	scumm.factory.mapitem { pos={74, 112}, name="fork", room="forest_1"}
-- 	-- factory.trap.create { pos ={164, 62, 0}, tag="bridge_sensor", width=12, height = 12, onenter = 
-- 	--   	function()			
-- 	-- 		local s = script:new()
-- 	-- 	 	s.actions = {	
-- 	-- 			action.change_room { id = 1, room = "bridge" }
-- 	-- 		}
-- 	-- 		monkey.play(s)
-- 	--   	end
-- 	-- }
-- })


-- function room.afterstartup() 
-- 	for k, v in ipairs(room.initstuff) do
-- 		v()
-- 	end
-- end


