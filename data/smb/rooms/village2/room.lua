--assets local to this scene
require ("funcs")
require ("text")
require ("dialogues")



local dt = 0.1

--table.insert(inventory, { item = objects.poster, qty = 1})

-- begin room
room = {

assets = {
    makeGuybrush(),
    makeArrowUp(),
    makeArrowDown(),
    {
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
    },
	{
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
	},
	{
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
	},
	{
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
	},
	{
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
	},
	{
        id = "door_voodoo",
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
	},
	{
        id = "door_1",
        sheet = "gfx/anims.png",
        type="sprite",
        ppu=1,
        animations = {
        {
       	    name = "open",             
            frames = 
            { 
	    	  	{ duration = dt, quads = { { x=144, y=176, width=16, height=29, anchor = {0, 0}}}}             
		    }
        },
        {
       	    name = "close",             
            frames = 
            { 
	    	  	{ duration = dt, quads = { { x=126, y=176, width=16, height=29, anchor = {0, 0}}}}             
		    }
        },
		
		}		
	},
	{
        id = "door_2",
        sheet = "gfx/anims.png",
        type="sprite",
        ppu=1,
        animations = {
        {
       	    name = "open",             
            frames = 
            { 
	    	  	{ duration = dt, quads = { { x=303, y=156, width=8, height=14, anchor = {0, 0}}}}             
		    }
        },
        {
       	    name = "close",             
            frames = 
            { 
	    	  	{ duration = dt, quads = { { x=293, y=156, width=8, height=14, anchor = {0, 0}}}}             
		    }
        },
		
		}		
	},
	{
        id = "door_3",
        sheet = "gfx/anims.png",
        type="sprite",
        ppu=1,
        animations = {
        {
       	    name = "open",             
            frames = 
            { 
	    	  	{ duration = dt, quads = { { x=283, y=156, width=8, height=13, anchor = {0, 0}}}}             
		    }
        },
        {
       	    name = "close",             
            frames = 
            { 
	    	  	{ duration = dt, quads = { { x=273, y=156, width=8, height=13, anchor = {0, 0}}}}             
		    }
        },
		
		}		
	},
	{
        id = "door_4",
        sheet = "gfx/anims.png",
        type="sprite",
        ppu=1,
        animations = {
        {
       	    name = "open",             
            frames = 
            { 
	    	  	{ duration = dt, quads = { { x=283, y=170, width=8, height=12, anchor = {0, 0}}}}             
		    }
        },
        {
       	    name = "close",             
            frames = 
            { 
	    	  	{ duration = dt, quads = { { x=273, y=170, width=8, height=12, anchor = {0, 0}}}}             
		    }
        },
		
		}		
	},
},
scene = {
	{
		tag = "main",
		camera = {
			tag = "maincam",
			type="ortho",
			size = {320, 144},
			bounds = {0, 0, 480, 144},
			viewport = {0, 56, 320, 144}
		},
		children = {
            {
              pos = {0, 0, -5},
              gfx = { image="gfx/village2/bg1.png" }
            },
	        {
	          walkarea = { 
	            tag = "walkarea",
	            priority = 0,
	            target = "player",
	            shape = { 
	                type = "poly", 
	                outline = {0,24, 123,63,199,63,299,30,377,30,385,35,454,35,470,0,0}

	            },
	            scaling = {
	                depth = { 
	                    { rect = {0, 640, 0, 144}, dir = "y", bounds = {1, 0} } 
	                },
	                scale = {
	                    { rect = {0, 640, 0, 144}, dir = "y", bounds = {1, 1} } 
	                }
	            }
	          }
	        },
	        make_hotspot { 
	            x = 325, 
	            y = 27,
	            width = 30, 
	            height = 40, 
	            offset = {-15, 0},
	            priority = 1, 
	            object = "citizen",
				scaling =true,
	            gfx = { model="citizen", anim = "idle" }
	        },
			{
				tag ="lmf1",
				pos = {18, 10, 0},
				scaling = true,
				gfx = {model = "lmf1", anim="idle"}
			},
			{
				tag ="lmf2",
				pos = {44, 20, 0},
				scaling = true,
				gfx = {model = "lmf2", anim="idle"}
			},
			{
				tag ="lmf3",
				pos = {56, 23, 0},
				scaling = true,
				gfx = {model = "lmf3", anim="idle"}
			},
			{
				tag ="rat",
				pos = {56, 10, 0},
				scaling = true,
				gfx = {model = "rat", anim="idle", flip = true}
			},
	        make_hotspot { 
	            x = 0, 
	            y = 0, 
	            width = 40, 
	            height = 50, 
	            offset = {0, 0},
	            priority = 1, 
	            object = "lowmoralfiber"
	        },
			make_hotspot { 
				x=220, 
				y=52, 
				width=26, 
				height=26, 
				offset={0,0},
				priority = 1, 
				object = "door_voodoolady_out", 
				gfx = { 
					model="door_voodoo", 
					anim = ((objects.door_voodoolady_out.isopen() == true) and "open" or "close") 
				}
			},
			make_hotspot { 
				x=377,
				y=37,
				width=16, 
				height=29, 
				offset={0,0},
				priority = 1, 
				object = "door_village2_1", 
				gfx = { model="door_1", anim = "close" }
			},
			make_hotspot { 
				x=208,
				y=59,
				width=8, 
				height=14, 
				offset={0,0},
				priority = 1, 
				object = "door_village2_2", 
				gfx = { model="door_2", anim = "close" }
			},
			make_hotspot { 
				x=130,
				y=63,
				width=8, 
				height=13, 
				offset={0,0},
				priority = 1, 
				object = "door_village2_3", 
				gfx = { model="door_3", anim = "close" }
			},
			make_hotspot { 
				x=184,
				y=64,
				width=8, 
				height=12, 
				offset={0,0},
				priority = 1, 
				object = "door_village2_4", 
				gfx = { model="door_4", anim = "close" }
			},
			make_hotspot { 
				x=146,
				y=63,
				width=35, 
				height=30, 
				offset={0,0},
				priority = 1, 
				object = "village2_archway"				
			},
		}
	},
	makescummui1(),
	{
		tag = "diag",
		camera = {
			tag = "maincam",
			type="ortho",
			size = {320, 200},
			bounds = {0, 0, 320, 200},
			viewport = {0, 0, 320, 200}
		},
		children = {}
	}
}
}
-- end room

function room.init()
	variables._actionInfo:reset()
	local fromData = {
        village1 = { playerpos = {436, 34, 0}, anim = "idle_front", flip = false },
		voodoolady = { playerpos = {231, 52, 0}, anim = "idle_right", flip = true },
		village3 = { playerpos = {160, 65, 0}, anim = "idle_front", flip = false },
    }
    -- add player
	local d = fromData[variables._previousroom]
	if (d == nil) then
		d = fromData["village1"]
	end

    table.insert (room.scene[1].children, {
        tag = objects.guybrush.tag,
        pos = d.playerpos,
        gfx = { model = "guybrush", anim = d.anim, flip = d.flip },
        follow = { cam="maincam" },
        scaling = {}
    })
end

function room.afterstartup() 
refreshInventory()
end




