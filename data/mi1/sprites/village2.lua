local dt = 0.1

sprites.citizen = {
	id = "citizen",
    sheet = "gfx/anims.png",
    type="sprite",
    ppu=1,
    animations = {
        {
       	    name = "idle",             
            frames = 
            { 
	    	  	{ duration = dt*2, quads = { { x=103, y=41, width=29, height=36, anchor = {15, 0}}, {x=158, y=39, width=9, height=9, anchor = {5,-28}} }},              
				{ duration = dt, quads = { { x=103, y=41, width=29, height=36, anchor = {15, 0}}, {x=136, y=39, width=9, height=9, anchor = {5,-28}} }},
				{ duration = dt, quads = { { x=103, y=41, width=29, height=36, anchor = {15, 0}}, {x=158, y=39, width=9, height=9, anchor = {5,-28}} }},
				{ duration = dt, quads = { { x=103, y=41, width=29, height=36, anchor = {15, 0}}, {x=147, y=39, width=9, height=9, anchor = {5,-28}} }},              
		    }
        },
        {
       	    name = "idleside",             
            frames = 
            { 
	    	  	{ duration = dt*2, quads = { { x=171, y=42, width=22, height=36, anchor = {11, 0}}, {x=158, y=50, width=9, height=9, anchor = {1,-28}} }},              
	    	  	{ duration = dt, quads = { { x=171, y=42, width=22, height=36, anchor = {11, 0}}, {x=136, y=39, width=9, height=9, anchor = {1,-28}} }},              
				{ duration = dt, quads = { { x=171, y=42, width=22, height=36, anchor = {11, 0}}, {x=158, y=39, width=9, height=9, anchor = {1,-28}} }},              
				{ duration = dt, quads = { { x=171, y=42, width=22, height=36, anchor = {11, 0}}, {x=136, y=39, width=9, height=9, anchor = {1,-28}} }},          
		    }
        },
        {
       	    name = "talkfront",             
            frames = 
            { 
	    	  	{ duration = dt, quads = { { x=103, y=41, width=29, height=36, anchor = {15, 0}}, {x=136, y=50, width=9, height=9, anchor = {5,-28}} }},              
				{ duration = dt, quads = { { x=103, y=41, width=29, height=36, anchor = {15, 0}}, {x=147, y=50, width=9, height=9, anchor = {5,-28}} }},
				{ duration = dt, quads = { { x=103, y=41, width=29, height=36, anchor = {15, 0}}, {x=158, y=50, width=9, height=9, anchor = {5,-28}} }},
		    }
        },
        {
       	    name = "talkside",             
            frames = 
            { 
	    	  	{ duration = dt, quads = { { x=171, y=42, width=22, height=36, anchor = {11, 0}}, {x=136, y=50, width=9, height=9, anchor = {1,-28}} }},              
	    	  	{ duration = dt, quads = { { x=171, y=42, width=22, height=36, anchor = {11, 0}}, {x=147, y=50, width=9, height=9, anchor = {1,-28}} }},              
				{ duration = dt, quads = { { x=171, y=42, width=22, height=36, anchor = {11, 0}}, {x=158, y=50, width=9, height=9, anchor = {1,-28}} }},              
		    }
        },
        {
       	    name = "openjacket",             
            frames = 
            { 
	    	  	{ duration = dt, quads = { { x=195, y=50, width=26, height=36, anchor = {16, 0}}, {x=158, y=50, width=9, height=9, anchor = {4,-28}} }},              
	    	  	{ duration = dt, quads = { { x=223, y=50, width=23, height=36, anchor = {13, 0}}, {x=158, y=50, width=9, height=9, anchor = {4,-28}} }},              
				{ duration = dt, quads = { { x=247, y=50, width=33, height=36, anchor = {21, 0}}, {x=158, y=50, width=9, height=9, anchor = {4,-28}} }},              
				{ duration = dt, quads = { { x=282, y=50, width=38, height=36, anchor = {21, 0}}, {x=158, y=50, width=9, height=9, anchor = {4,-28}} }},          
		    }
        },
        {
       	    name = "openjacketidle",             
            frames = 
            { 
	    	  	{ duration = dt*2, quads = { { x=282, y=50, width=38, height=36, anchor = {21, 0}}, {x=158, y=50, width=9, height=9, anchor = {4,-28}} }},              
	    	  	{ duration = dt, quads = { { x=282, y=50, width=38, height=36, anchor = {21, 0}}, {x=136, y=39, width=9, height=9, anchor = {4,-28}} }},              
				{ duration = dt, quads = { { x=282, y=50, width=38, height=36, anchor = {21, 0}}, {x=158, y=39, width=9, height=9, anchor = {4,-28}} }},              
				{ duration = dt, quads = { { x=282, y=50, width=38, height=36, anchor = {21, 0}}, {x=136, y=39, width=9, height=9, anchor = {4,-28}} }},          
		    }
        },
        {
       	    name = "openjackettalk",             
            frames = 
            { 
	    	  	{ duration = dt, quads = { { x=282, y=50, width=38, height=36, anchor = {21, 0}}, {x=136, y=50, width=9, height=9, anchor = {4,-28}} }},              
	    	  	{ duration = dt, quads = { { x=282, y=50, width=38, height=36, anchor = {21, 0}}, {x=147, y=50, width=9, height=9, anchor = {4,-28}} }},              
				{ duration = dt, quads = { { x=282, y=50, width=38, height=36, anchor = {21, 0}}, {x=158, y=50, width=9, height=9, anchor = {4,-28}} }},              
		    }
        },
        {
       	    name = "closejacket",             
            frames = 
            { 
				{ duration = dt, quads = { { x=282, y=50, width=38, height=36, anchor = {21, 0}}, {x=158, y=50, width=9, height=9, anchor = {4,-28}} }},          
				{ duration = dt, quads = { { x=247, y=50, width=33, height=36, anchor = {21, 0}}, {x=158, y=50, width=9, height=9, anchor = {4,-28}} }},              
	    	  	{ duration = dt, quads = { { x=223, y=50, width=23, height=36, anchor = {13, 0}}, {x=158, y=50, width=9, height=9, anchor = {4,-28}} }},              
	    	  	{ duration = dt, quads = { { x=195, y=50, width=26, height=36, anchor = {16, 0}}, {x=158, y=50, width=9, height=9, anchor = {4,-28}} }},              
		    }
        },
        {
       	    name = "rollmap",             
            frames = 
            { 
	    	  	{ duration = dt, quads = { { x=197, y=88, width=29, height=36, anchor = {13, 0}}, {x=158, y=50, width=9, height=9, anchor = {4,-28}} }},              
	    	  	{ duration = dt, quads = { { x=229, y=88, width=26, height=36, anchor = {12, 0}}, {x=158, y=50, width=9, height=9, anchor = {4,-28}} }},              
				{ duration = dt, quads = { { x=258, y=88, width=26, height=36, anchor = {12, 0}}, {x=136, y=39, width=9, height=9, anchor = {4,-28}} }},              
				{ duration = dt, quads = { { x=289, y=88, width=26, height=36, anchor = {12, 0}}, {x=158, y=39, width=9, height=9, anchor = {4,-28}} }},          
				{ duration = dt, quads = { { x=318, y=88, width=26, height=36, anchor = {12, 0}}, {x=136, y=39, width=9, height=9, anchor = {4,-28}} }},          
		    }
        },
        {
       	    name = "rollmapidle",             
            frames = 
            { 
	    	  	{ duration = dt*2, quads = { { x=318, y=88, width=26, height=36, anchor = {12, 0}}, {x=158, y=50, width=9, height=9, anchor = {4,-28}} }},              
	    	  	{ duration = dt, quads = { { x=318, y=88, width=26, height=36, anchor = {12, 0}}, {x=136, y=39, width=9, height=9, anchor = {4,-28}} }},              
				{ duration = dt, quads = { { x=318, y=88, width=26, height=36, anchor = {12, 0}}, {x=158, y=39, width=9, height=9, anchor = {4,-28}} }},              
				{ duration = dt, quads = { { x=318, y=88, width=26, height=36, anchor = {12, 0}}, {x=136, y=39, width=9, height=9, anchor = {4,-28}} }},          
		    }
        },
        {
       	    name = "rollmaptalk",             
            frames = 
            { 
	    	  	{ duration = dt, quads = { { x=318, y=88, width=26, height=36, anchor = {12, 0}}, {x=136, y=50, width=9, height=9, anchor = {4,-28}} }},              
	    	  	{ duration = dt, quads = { { x=318, y=88, width=26, height=36, anchor = {12, 0}}, {x=147, y=50, width=9, height=9, anchor = {4,-28}} }},              
				{ duration = dt, quads = { { x=318, y=88, width=26, height=36, anchor = {12, 0}}, {x=158, y=50, width=9, height=9, anchor = {4,-28}} }},              
		    }
        },
        {
       	    name = "unrollmap",             
            frames = 
            { 
				{ duration = dt, quads = { { x=318, y=88, width=26, height=36, anchor = {12, 0}}, {x=136, y=39, width=9, height=9, anchor = {4,-28}} }},          
				{ duration = dt, quads = { { x=289, y=88, width=26, height=36, anchor = {12, 0}}, {x=158, y=39, width=9, height=9, anchor = {4,-28}} }},          
				{ duration = dt, quads = { { x=258, y=88, width=26, height=36, anchor = {12, 0}}, {x=136, y=39, width=9, height=9, anchor = {4,-28}} }},              
	    	  	{ duration = dt, quads = { { x=229, y=88, width=26, height=36, anchor = {12, 0}}, {x=158, y=50, width=9, height=9, anchor = {4,-28}} }},              
	    	  	{ duration = dt, quads = { { x=197, y=88, width=29, height=36, anchor = {13, 0}}, {x=158, y=50, width=9, height=9, anchor = {4,-28}} }},              
		    }
        },
    }
}