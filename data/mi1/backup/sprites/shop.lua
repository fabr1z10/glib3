local dt = 0.1

sprites["shop.door"] = {
    id = "shop.door",
    sheet = "gfx/anims.png",
    type="sprite",
    ppu=1,
    animations = {
        { name = "close", frames = { {duration = dt, quads = { { x = 434, y = 280, width = 31, height = 51, anchor = {0, 0}}}}}},
        { name = "open", frames = { {duration = dt, quads = { { x = 467, y = 280, width = 31, height = 51, anchor = {0, 0}}}}}}
    }
}

sprites["shop.shopkeeper"] = {
    id = "shop.shopkeeper",
    sheet = "gfx/anims2.png",
    type="sprite",
    ppu=1,
    animations = {
        {
       	    name = "idle_right",             
            frames = 
            { 
	    	  	{ duration = dt, quads = { { x=246, y=5, width=28, height=42, anchor = {12, 0}}, {x=232, y=4, width=11, height=13, anchor = {-2,-32}}}}
		    }
        },
        {
        	name="walk_right",
        	frames=
            { 
	    	  	{ duration = dt, quads = { { x=380, y=105, width=30, height=45, anchor = {12, 0}}}},
	    	  	{ duration = dt, quads = { { x=412, y=107, width=26, height=44, anchor = {12, 0}}}},
	    	  	{ duration = dt, quads = { { x=440, y=105, width=27, height=46, anchor = {12, 0}}}},
	    	  	{ duration = dt, quads = { { x=469, y=106, width=28, height=45, anchor = {12, 0}}}},
	    	  	{ duration = dt, quads = { { x=380, y=154, width=26, height=43, anchor = {12, 0}}}},
	    	  	{ duration = dt, quads = { { x=407, y=152, width=38, height=45, anchor = {12, 0}}}},
		    }        	
    	},
    	{
        	name="walk_front",
        	frames=
            { 
	    	  	{ duration = dt, quads = { { x=310, y=225, width=34, height=43, anchor = {12, 0}}}},
	    	  	{ duration = dt, quads = { { x=346, y=225, width=29, height=43, anchor = {12, 0}}}},
	    	  	{ duration = dt, quads = { { x=378, y=246, width=28, height=41, anchor = {12, 0}}}},
	    	  	{ duration = dt, quads = { { x=408, y=246, width=29, height=42, anchor = {12, 0}}}},
	    	  	{ duration = dt, quads = { { x=439, y=246, width=30, height=42, anchor = {12, 0}}}},
	    	  	{ duration = dt, quads = { { x=472, y=247, width=31, height=41, anchor = {12, 0}}}},
		    }        	
    	},
    	{
        	name="walk_back",
        	frames=
            { 
	    	  	{ duration = dt, quads = { { x=448, y=155, width=34, height=43, anchor = {12, 0}}}},
	    	  	{ duration = dt, quads = { { x=483, y=155, width=28, height=43, anchor = {12, 0}}}},
	    	  	{ duration = dt, quads = { { x=378, y=201, width=28, height=41, anchor = {12, 0}}}},
	    	  	{ duration = dt, quads = { { x=408, y=200, width=28, height=42, anchor = {12, 0}}}},
	    	  	{ duration = dt, quads = { { x=438, y=201, width=32, height=41, anchor = {12, 0}}}},
	    	  	{ duration = dt, quads = { { x=472, y=200, width=32, height=42, anchor = {12, 0}}}},
		    }        	
    	},
        {
       	    name = "talk_right",             
            frames = 
            { 
	    	  	{ duration = dt, quads = { { x=246, y=5, width=28, height=42, anchor = {12, 0}}, {x=232, y=4, width=11, height=13, anchor = {-2,-32}}}},
				{ duration = dt, quads = { { x=246, y=5, width=28, height=42, anchor = {12, 0}}, {x=168, y=3, width=10, height=14, anchor = {-2,-32}}}},
				{ duration = dt, quads = { { x=246, y=5, width=28, height=42, anchor = {12, 0}}, {x=180, y=4, width=10, height=13, anchor = {-2,-32}}}},
				{ duration = dt, quads = { { x=246, y=5, width=28, height=42, anchor = {12, 0}}, {x=192, y=4, width=12, height=12, anchor = {-2,-32}}}},
				{ duration = dt, quads = { { x=246, y=5, width=28, height=42, anchor = {12, 0}}, {x=207, y=2, width=11, height=15, anchor = {-2,-32}}}},
				{ duration = dt, quads = { { x=246, y=5, width=28, height=42, anchor = {12, 0}}, {x=220, y=2, width=11, height=15, anchor = {-2,-32}}}},
		    }
        },
	}
}

sprites["shop.sword"] = {
    id = "shop.sword",
    sheet = "gfx/anims2.png",
    type="sprite",
    ppu=1,
    animations = {
        {
       	    name = "idle",             
            frames = 
            { 
	    	  	{ duration = dt, quads = { { x=280, y=3, width=30, height=6, anchor = {0, 0}}}}             
		    }
        }		
	}		
}

sprites["shop.sign"] = {
    id = "shop.sign",
    sheet = "gfx/anims2.png",
    type="sprite",
    ppu=1,
    animations = {
        {
       	    name = "idle",             
            frames = 
            { 
	    	  	{ duration = dt, quads = { { x=373, y=292, width=16, height=10, anchor = {0, 0}}}}             
		    }
        }		
	}		
}

sprites["shop.bell"] = {
    id = "shop.bell",
    sheet = "gfx/anims2.png",
    type="sprite",
    ppu=1,
    animations = {
        {
       	    name = "idle",             
            frames = 
            { 
	    	  	{ duration = dt, quads = { { x=391, y=295, width=8, height=5, anchor = {0, 0}}}}             
		    }
        }		
	}		
}
sprites["shop.shovel"] = {
	id = "shop.shovel",
    sheet = "gfx/anims2.png",
    type="sprite",
    ppu=1,
    animations = {
    	{
       	    name = "idle",             
            frames = 
            { 
	    	  	{ duration = dt, quads = { { x=348, y=29, width=8, height=25, anchor = {0, 0}}}}             
		    }
        }		
	}		
}