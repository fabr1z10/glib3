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

sprites.lmf1 =  {
    id = "lmf1",
    sheet = "gfx/anims.png",
    type="sprite",
    ppu=1,
    animations = {
        {
            name = "idle",             
            frames = 
            { 
                { duration = dt, quads = { { x=1, y=58, width=34, height=39, anchor = {17, 0}} }},              
                { duration = dt, quads = { { x=1, y=99, width=31, height=40, anchor = {13, 0}} }},              
                { duration = dt, quads = { { x=39, y=79, width=27, height=39, anchor = {9, 0}} }},              
                { duration = dt, quads = { { x=1, y=99, width=31, height=40, anchor = {13, 0}} }},              
            }
        },
        {
            name = "talk",             
            frames = 
            { 
                { duration = dt, quads = { { x=1, y=99, width=31, height=40, anchor = {13, 0}} }},              
                { duration = dt, quads = { { x=70, y=78, width=31, height=40, anchor = {13, 0}} }},              
                { duration = dt, quads = { { x=104, y=80, width=31, height=38, anchor = {13, 0}} }},              
            }
        },
        {
            name = "idle2",             
            frames = 
            { 
                { duration = dt, quads = { { x=1, y=99, width=31, height=40, anchor = {13, 0}} }},              
            }
        },
        {
            name = "looknorth",             
            frames = 
            { 
                { duration = dt, quads = { { x=140, y=78, width=31, height=40, anchor = {13, 0}} }},              
            }
        },
    }       
}

sprites.lmf2 =  {
    id = "lmf2",
    sheet = "gfx/anims.png",
    type="sprite",
    ppu=1,
    animations = {
        {
            name = "idle",             
            frames = 
            { 
                { duration = dt, quads = { { x=244, y=7, width=25, height=38, anchor = {12, 0}} }}             
            }
        },
        {
            name = "laugh",             
            frames = 
            { 
                { duration = dt, quads = { { x=273, y=7, width=24, height=39, anchor = {12, 0}} }},             
                { duration = dt, quads = { { x=299, y=8, width=25, height=38, anchor = {13, 0}} }},
                { duration = dt, quads = { { x=324, y=46, width=24, height=39, anchor = {12, 0}} }},
            }
        },
        {
            name = "hit",             
            frames = 
            { 
                { duration = dt*3, quads = { { x=370, y=28, width=24, height=30, anchor = {12, 0}}, {x = 400, y=50, width=11, height=8, anchor={4,-30}} }}             
            }
        },
        {
            name = "idlefront",             
            frames = 
            { 
                { duration = dt*2, quads = { { x=370, y=28, width=24, height=30, anchor = {12, 0}}, {x = 400, y=30, width=10, height=9, anchor={5,-29}} }},
                { duration = dt*2, quads = { { x=370, y=28, width=24, height=30, anchor = {12, 0}}, {x = 400, y=40, width=10, height=9, anchor={5,-29}} }},
                { duration = dt, quads = { { x=370, y=28, width=24, height=30, anchor = {12, 0}}, {x = 400, y=20, width=10, height=9, anchor={5,-29}} }}
            }
        }        
    }       
}

sprites.lmf3 =  {
    id = "lmf3",
    sheet = "gfx/anims.png",
    type="sprite",
    ppu=1,
    animations = {
        {
            name = "idle",             
            frames = 
            { 
                { duration = dt, quads = { { x=328, y=7, width=24, height=37, anchor = {12, 0}}, {x = 353, y=3, width=13, height=15, anchor={11,-34}} }}             
            }
        },
        {
            name = "idlefront",
            frames = 
            { 
                { duration = dt, quads = { { x=328, y=7, width=24, height=37, anchor = {12, 0}}, {x = 355, y=20, width=11, height=13, anchor={9,-35}} }},
            }
        },
        {
            name = "talkfront",
            frames = 
            { 
                { duration = dt, quads = { { x=328, y=7, width=24, height=37, anchor = {12, 0}}, {x = 355, y=20, width=11, height=13, anchor={9,-35}} }},
                { duration = dt, quads = { { x=328, y=7, width=24, height=37, anchor = {12, 0}}, {x = 354, y=35, width=13, height=14, anchor={10,-35}} }}             
            }
        },
        {
            name = "talk",
            frames = 
            { 
                { duration = dt, quads = { { x=328, y=7, width=24, height=37, anchor = {12, 0}}, {x = 368, y= 3, width=13, height=15, anchor={10,-35}} }},
                { duration = dt, quads = { { x=328, y=7, width=24, height=37, anchor = {12, 0}}, {x = 383, y= 3, width=13, height=15, anchor={10,-35}} }},
                { duration = dt, quads = { { x=328, y=7, width=24, height=37, anchor = {12, 0}}, {x = 398, y= 3, width=13, height=15, anchor={10,-35}} }}                          
            }
        },
        {
            name = "punch1",
            frames = 
            { 
                { duration = dt, quads = { { x=358, y=62, width=24, height=48, anchor = {12, 0}} }},
                { duration = dt, quads = { { x=383, y=61, width=23, height=48, anchor = {11, 0}} }},
                { duration = dt, quads = { { x=407, y=62, width=30, height=48, anchor = {18, 0}} }},
                { duration = dt, quads = { { x=439, y=62, width=30, height=48, anchor = {18, 0}} }},            
            }
        },
        {
            name = "punch2",
            frames = 
            { 
                { duration = dt*3, quads = { { x=473, y=62, width=32, height=48, anchor = {20, 0}} }}
            }
        },
        {
            name = "openjacket",
            frames = 
            { 
                { duration = dt, quads = { { x=414, y=7, width=23, height=37, anchor = {12, 0}}, {x = 353, y= 3, width=13, height=15, anchor={11,-34}} }},
                { duration = dt*4, quads = { { x=439, y=7, width=24, height=37, anchor = {12, 0}}, {x = 353, y= 3, width=13, height=15, anchor={11,-34}} }},
                { duration = dt, quads = { { x=414, y=7, width=23, height=37, anchor = {12, 0}}, {x = 353, y= 3, width=13, height=15, anchor={11,-34}} }},
            }
        },
    }       
}

sprites.rat = {
    id = "rat",
    sheet = "gfx/anims.png",
    type="sprite",
    ppu=1,
    animations = {
        {
       	    name = "idle",             
            frames = 
            { 
	    	  	{ duration = dt, quads = { { x=54, y=126, width=13, height=12, anchor = {4, 0}}, { x=40, y=121, width=5, height=4, anchor={7,0} } }},             
	    	  	{ duration = dt*2, quads = { { x=54, y=126, width=13, height=12, anchor = {4, 0}}, { x=47, y=123, width=6, height=2, anchor={7,0} } }},             
	    	  	{ duration = dt, quads = { { x=40, y=126, width=13, height=10, anchor = {5, 0}}, { x=47, y=123, width=6, height=2, anchor={7,0} } }}             
		    }
        },
		
	}	
}

sprites["village2.door_voodoo"] = {
	id = "village2.door_voodoo",
    sheet = "gfx/anims.png",
    type="sprite",
    ppu=1,
    animations = {
        {
       	    name = "open",             
            frames = 
            { 
	    	  	{ duration = dt, quads = { { x=301, y=130, width=26, height=24, anchor = {0, 0}}}}             
		    }
        },
        {
       	    name = "close",             
            frames = 
            { 
	    	  	{ duration = dt, quads = { { x=273, y=130, width=26, height=24, anchor = {0, 0}}}}             
		    }
        },
	}	
}
