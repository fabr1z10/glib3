require("template/room2")

local roomInfo = {
	width = 320,
	height = 200,
	startTable = {
		lookout = { pos = {75, 79}, facing = "north"},
	},
	defaultroom = "lookout",
	depth = { type="linear_y", values= {0, 1, 144, 0} },
	scale = { type="constant", value=0.1}

}

room = generateMapRoom (roomInfo)

room:add( {
	{ pos = {0, 0,-3}, components = { { type="gfx", image="gfx/meleemap.png" }}},
	{
		pos = {0,0,0},
		components = {
      		{ 
				type ="walkarea",
				priority = 0,
       			target = "player",
            	shape = { type = "graph", vertices = { {76, 80}, {78, 81}, {71,90}, {64, 96}, {48,99}, {49, 114}, {73, 113}, {88, 114},{118,114}, {135,113}, {83,109},
					{101, 107}, {112, 97}, {157, 78}, {172, 64}, {196, 54}, {217,54}, {232,49}, {245,48}, {254,50}, {275, 95}, {54,131},{57,140}, {60,151},
					{67,161}, {82, 174}, {113, 177}, {146, 168}, {169,168}, {180, 174}, {196,174}, {227,180} }, edges = { 
					{0,1}, {1,2}, {2,3},{3,4}, {4,5}, {5,6}, {6,7}, {7,8}, {8,9}, {6,10}, {10,11}, {11,12}, {12,13}, {13,14}, {14,15}, {15,16},{16,17},{17,18},
					{18,19}, {19,20}, {5,21}, {21,22}, {22,23}, {23,24}, {24,25}, {25,26}, {26,27}, {27, 28}, {28,29}, {29,30}, {30,31}  }},
			}
      	}
	},
})


function room.afterstartup() 
	for k, v in ipairs(room.initstuff) do
		v()
	end
end


