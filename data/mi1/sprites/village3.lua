local dt = 0.1

sprites["village3.shop_door"] = {
	id = "village3.shop_door",
    sheet = "gfx/anims.png",
    type="sprite",
    ppu=1,
    animations = {
        {
       	    name = "open",             
            frames = 
            { 
	    	  	{ duration = dt, quads = { { x=78, y=150, width=20, height=31, anchor = {0, 0}}}}             
		    }
        },
        {
       	    name = "close",             
            frames = 
            { 
	    	  	{ duration = dt, quads = { { x=101, y=150, width=20, height=31, anchor = {0, 0}}}}             
		    }
        },
	}		
}

sprites["fester"] = {
    id = "fester",
    sheet = "gfx/anims2.png",
    type="sprite",
    ppu=1,
    animations = {
        {
            name = "idle_front",             
            frames = 
            { 
                { duration = dt, quads = { 
                    { x=404, y=64, width=28, height=39, anchor = {14, 0}},
                    { x=436, y=60, width=9, height=12, anchor = {0, -39}},                    
                }}             
            }
        },
        {
            name = "idle_right",             
            frames = 
            { 
                { duration = dt, quads = { 
                    { x=404, y=64, width=28, height=39, anchor = {14, 0}},
                    { x=493, y=74, width=9, height=13, anchor = {1, -34}},                    
                }}             
            }        
        },
        {
            name = "idle_back",             
            frames = 
            { 
                { duration = dt, quads = { 
                    { x=404, y=64, width=28, height=39, anchor = {14, 0}},
                    { x=436, y=60, width=9, height=12, anchor = {0, -39}},                    
                }}             
            }        
        },
        {
            name = "walk_right",             
            frames = 
            { 
                { duration = dt, quads = { { x=359, y=9, width=26, height=45, anchor = {16, 0}}}},
                { duration = dt, quads = { { x=387, y=8, width=22, height=46, anchor = {18, 0}}}},
                { duration = dt, quads = { { x=411, y=9, width=31, height=45, anchor = {16, 0}}}},
                { duration = dt, quads = { { x=444, y=9, width=27, height=45, anchor = {15, 0}}}},
                { duration = dt, quads = { { x=473, y=8, width=23, height=46, anchor = {16, 0}}}},
                { duration = dt, quads = { { x=368, y=57, width=32, height=45, anchor = {16, 0}}}},
            }
        },
        {
            name = "walk_front",             
            frames = 
            { 
                { duration = dt, quads = { { x=359, y=9, width=26, height=45, anchor = {16, 0}}}},
                { duration = dt, quads = { { x=387, y=8, width=22, height=46, anchor = {18, 0}}}},
                { duration = dt, quads = { { x=411, y=9, width=31, height=45, anchor = {16, 0}}}},
                { duration = dt, quads = { { x=444, y=9, width=27, height=45, anchor = {15, 0}}}},
                { duration = dt, quads = { { x=473, y=8, width=23, height=46, anchor = {16, 0}}}},
                { duration = dt, quads = { { x=368, y=57, width=32, height=45, anchor = {16, 0}}}},
            }
        },
        {
            name = "walk_back",             
            frames = 
            { 
                { duration = dt, quads = { { x=359, y=9, width=26, height=45, anchor = {16, 0}}}},
                { duration = dt, quads = { { x=387, y=8, width=22, height=46, anchor = {18, 0}}}},
                { duration = dt, quads = { { x=411, y=9, width=31, height=45, anchor = {16, 0}}}},
                { duration = dt, quads = { { x=444, y=9, width=27, height=45, anchor = {15, 0}}}},
                { duration = dt, quads = { { x=473, y=8, width=23, height=46, anchor = {16, 0}}}},
                { duration = dt, quads = { { x=368, y=57, width=32, height=45, anchor = {16, 0}}}},
            }
        },
        {
            name = "talk_right",             
            frames = 
            { 
                { duration = dt, quads = { {x=404,y=64,width=28,height=39,anchor = {14, 0}}, {x=436,y=74,width=9,height=13,anchor={1,-34}}}},
                { duration = dt, quads = { {x=404,y=64,width=28,height=39,anchor = {14, 0}}, {x=447,y=74,width=10,height=13,anchor={1,-34}}}},
                { duration = dt, quads = { {x=404,y=64,width=28,height=39,anchor = {14, 0}}, {x=459,y=74,width=10,height=13,anchor={1,-34}}}},
                { duration = dt, quads = { {x=404,y=64,width=28,height=39,anchor = {14, 0}}, {x=436,y=74,width=9,height=13,anchor={1,-34}}}},
                { duration = dt, quads = { {x=404,y=64,width=28,height=39,anchor = {14, 0}}, {x=471,y=74,width=9,height=13,anchor={1,-34}}}},
                { duration = dt, quads = { {x=404,y=64,width=28,height=39,anchor = {14, 0}}, {x=436,y=74,width=9,height=13,anchor={1,-34}}}},
                { duration = dt, quads = { {x=404,y=64,width=28,height=39,anchor = {14, 0}}, {x=482,y=74,width=9,height=13,anchor={1,-34}}}},
                { duration = dt, quads = { {x=404,y=64,width=28,height=39,anchor = {14, 0}}, {x=493,y=74,width=9,height=13,anchor={1,-34}}}},
                { duration = dt, quads = { {x=404,y=64,width=28,height=39,anchor = {14, 0}}, {x=447,y=74,width=10,height=13,anchor={1,-34}}}},
                { duration = dt, quads = { {x=404,y=64,width=28,height=39,anchor = {14, 0}}, {x=459,y=74,width=10,height=13,anchor={1,-34}}}},
            }
        },
        {
            name = "talk_front",             
            frames = 
            { 
                { duration = dt, quads = { {x=404,y=64,width=28,height=39,anchor = {14, 0}}, {x=436,y=74,width=9,height=13,anchor={1,-34}}}},
                { duration = dt, quads = { {x=404,y=64,width=28,height=39,anchor = {14, 0}}, {x=447,y=74,width=10,height=13,anchor={1,-34}}}},
                { duration = dt, quads = { {x=404,y=64,width=28,height=39,anchor = {14, 0}}, {x=459,y=74,width=10,height=13,anchor={1,-34}}}},
                { duration = dt, quads = { {x=404,y=64,width=28,height=39,anchor = {14, 0}}, {x=436,y=74,width=9,height=13,anchor={1,-34}}}},
                { duration = dt, quads = { {x=404,y=64,width=28,height=39,anchor = {14, 0}}, {x=471,y=74,width=9,height=13,anchor={1,-34}}}},
                { duration = dt, quads = { {x=404,y=64,width=28,height=39,anchor = {14, 0}}, {x=436,y=74,width=9,height=13,anchor={1,-34}}}},
                { duration = dt, quads = { {x=404,y=64,width=28,height=39,anchor = {14, 0}}, {x=482,y=74,width=9,height=13,anchor={1,-34}}}},
                { duration = dt, quads = { {x=404,y=64,width=28,height=39,anchor = {14, 0}}, {x=493,y=74,width=9,height=13,anchor={1,-34}}}},
                { duration = dt, quads = { {x=404,y=64,width=28,height=39,anchor = {14, 0}}, {x=447,y=74,width=10,height=13,anchor={1,-34}}}},
                { duration = dt, quads = { {x=404,y=64,width=28,height=39,anchor = {14, 0}}, {x=459,y=74,width=10,height=13,anchor={1,-34}}}},
            }
        },
        {
            name = "talk_back",             
            frames = 
            { 
                { duration = dt, quads = { {x=404,y=64,width=28,height=39,anchor = {14, 0}}, {x=436,y=74,width=9,height=13,anchor={1,-34}}}},
                { duration = dt, quads = { {x=404,y=64,width=28,height=39,anchor = {14, 0}}, {x=447,y=74,width=10,height=13,anchor={1,-34}}}},
                { duration = dt, quads = { {x=404,y=64,width=28,height=39,anchor = {14, 0}}, {x=459,y=74,width=10,height=13,anchor={1,-34}}}},
                { duration = dt, quads = { {x=404,y=64,width=28,height=39,anchor = {14, 0}}, {x=436,y=74,width=9,height=13,anchor={1,-34}}}},
                { duration = dt, quads = { {x=404,y=64,width=28,height=39,anchor = {14, 0}}, {x=471,y=74,width=9,height=13,anchor={1,-34}}}},
                { duration = dt, quads = { {x=404,y=64,width=28,height=39,anchor = {14, 0}}, {x=436,y=74,width=9,height=13,anchor={1,-34}}}},
                { duration = dt, quads = { {x=404,y=64,width=28,height=39,anchor = {14, 0}}, {x=482,y=74,width=9,height=13,anchor={1,-34}}}},
                { duration = dt, quads = { {x=404,y=64,width=28,height=39,anchor = {14, 0}}, {x=493,y=74,width=9,height=13,anchor={1,-34}}}},
                { duration = dt, quads = { {x=404,y=64,width=28,height=39,anchor = {14, 0}}, {x=447,y=74,width=10,height=13,anchor={1,-34}}}},
                { duration = dt, quads = { {x=404,y=64,width=28,height=39,anchor = {14, 0}}, {x=459,y=74,width=10,height=13,anchor={1,-34}}}},
            }
        },


    }       
    

}