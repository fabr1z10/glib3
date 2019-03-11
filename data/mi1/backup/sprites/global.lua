local dt = 0.1

sprites.arrowup = {
	id = "arrowup",
	sheet ="gfx/anims.png",
	type="sprite",
	ppu=1,
	animations = {
		{
	    	name = "unselected",             
	        frames = { 
		   		{ duration = dt, quads = { { x = 485, y = 4, width = 12, height = 20, anchor = {0, 0}}}}             
			}
	    },
		{
			name = "selected",
	        frames = { 
		    	{ duration = dt, quads = { { x = 485, y = 25, width = 12, height = 20, anchor = {0, 0}}}}             
			}
		}
    }	
}


sprites.arrowdown = {
	id = "arrowdown",
	sheet ="gfx/anims.png",
	type="sprite",
	ppu=1,
	animations = {
		{
	    	name = "unselected",             
	        frames = { 
		    	{ duration = dt, quads = { { x = 472, y = 4, width = 12, height = 20, anchor = {0, 0}}}}             
			}
	    },
		{
			name = "selected",
	        frames = { 
		    	{ duration = dt, quads = { { x = 472, y = 25, width = 12, height = 20, anchor = {0, 0}}}}             
			}
		}
    }	
}

sprites.guybrush = {
	id="guybrush",
    sheet="gfx/sprite1.png",
	type="sprite",
    ppu=1,
    animations = {
		{
			name = "idle_front",             
	        frames = 
	        { 
	    	  	{ duration = dt, quads = { { x = 24, y = 51, width = 22, height = 47, anchor = {12, 0}}}}
			}
		},
	    {
	        name="idle_right",
	        frames=
	        { 
		    	{ duration = dt, quads = { { x = 2, y = 51, width = 19, height = 47, anchor = {10, 0}}}}
			}				
	    },
	    {
	        name="idle_back",
	        frames=
	        { 
		        { duration = dt, quads = { { x = 49, y = 51, width = 20, height = 47, anchor = {12, 0}}}}
			}				
	    },
	    {
	        name="idle_front_look_left",
	        frames=
	        { 
		        { duration = dt, quads = { { x = 125, y = 200, width = 22, height = 47, anchor = {12, 0}}}}
			}				
	    },
	    {
	        name="idle_front_look_right",
	        frames=
	        { 
		    	{ duration = dt, quads = { { x = 148, y = 200, width = 21, height = 47, anchor = {12, 0}}}}
			}				
	    },
		{
		    name = "walk_front",             
	        frames = 
	        { 
		  	  	{ duration = dt, quads = { { x = 207, y = 51, width = 22, height = 47, anchor = {11, 0}}}},
 	    	  	{ duration = dt, quads = { { x = 231, y = 51, width = 21, height = 47, anchor = {11, 0}}}},
	    	  	{ duration = dt, quads = { { x = 3, y = 101, width = 20, height = 47, anchor = {10, 0}}}},
	    	  	{ duration = dt, quads = { { x = 25, y = 101, width = 22, height = 47, anchor = {12, 0}}}},
	    	  	{ duration = dt, quads = { { x = 49, y = 101, width = 21, height = 47, anchor = {11, 0}}}},
	    	  	{ duration = dt, quads = { { x = 72, y = 101, width = 20, height = 47, anchor = {11, 0}}}}
		    }
		},
	    {
	        name="walk_right",
	        frames=
	        { 
	        	{ duration = dt, quads = { { x = 4, y = 1, width = 32, height = 47, anchor = {16, 0}}}},
			   	{ duration = dt, quads = { { x = 40, y = 1, width = 16, height = 47, anchor = {11, 0}}}},
  			 	{ duration = dt, quads = { { x = 60, y = 1, width = 19, height = 47, anchor = {11, 0}}}},
				{ duration = dt, quads = { { x = 83, y = 1, width = 31, height = 47, anchor = {15, 0}}}},
				{ duration = dt, quads = { { x = 117, y = 1, width = 18, height = 47, anchor = {11, 0}}}},
            	{ duration = dt, quads = { { x = 141, y = 1, width = 19, height = 47, anchor = {11, 0}}}}
			}					
		},
        {
        	name="walk_back",
	        frames=
	        { 
		    	{ duration = dt, quads = { { x = 72, y = 51, width = 21, height = 47, anchor = {11, 0}}}},
 	          	{ duration = dt, quads = { { x = 95, y = 51, width = 21, height = 47, anchor = {11, 0}}}},
  	          	{ duration = dt, quads = { { x = 118, y = 51, width = 19, height = 47, anchor = {11, 0}}}},
	            { duration = dt, quads = { { x = 139, y = 51, width = 21, height = 47, anchor = {11, 0}}}},
                { duration = dt, quads = { { x = 163, y = 51, width = 21, height = 47, anchor = {11, 0}}}},
                { duration = dt, quads = { { x = 186, y = 51, width = 19, height = 47, anchor = {9, 0}}}}
			}
		},
        {
            name="talk_front",
            frames=
			{ 
	            { duration = dt, quads = {
	            	{ x = 164, y = 12, width = 22, height = 36, anchor = {12, 0}},
	                { x = 179, y = 129, width = 11, height = 13, anchor = {6, -34} 
				}}},
                { duration = dt, quads = {
	                { x = 164, y = 12, width = 22, height = 36, anchor = {12, 0}},
	                { x = 192, y = 129, width = 11, height = 13, anchor = {6, -34}
	            }}},
	            { duration = dt, quads = {
	                { x = 164, y = 12, width = 22, height = 36, anchor = {12, 0}},
	                { x = 179, y = 129, width = 11, height = 13, anchor = {6, -34}
	            }}},
                { duration = dt, quads = {
	                { x = 164, y = 12, width = 22, height = 36, anchor = {12, 0}},
	                { x = 192, y = 129, width = 11, height = 13, anchor = {6, -34}
	            }}},
                { duration = dt, quads = {
	                { x = 164, y = 12, width = 22, height = 36, anchor = {12, 0}},
	                { x = 205, y = 129, width = 11, height = 13, anchor = {6, -34}
	            }}},
	            { duration = dt, quads = {
	                { x = 164, y = 12, width = 22, height = 36, anchor = {12, 0}},
	                { x = 179, y = 143, width = 11, height = 13, anchor =  {6, -34}
	            }}},
                { duration = dt,quads = {
	                { x = 164, y = 12, width = 22, height = 36, anchor = {12, 0}},
	                { x = 192, y = 129, width = 11, height = 13, anchor = {6, -34} 
	            }}},
                { duration = dt, quads = {
	                { x = 164, y = 12, width = 22, height = 36, anchor = {12, 0}},
	                { x = 192, y = 143, width = 11, height = 13, anchor = {6, -34}
	            }}},
                { duration = dt, quads = {
	                { x = 164, y = 12, width = 22, height = 36, anchor = {12, 0}},
	                { x = 205, y = 143, width = 11, height = 13, anchor = {6, -34} 
	            }}},
                { duration = dt, quads = {
	                { x = 164, y = 12, width = 22, height = 36, anchor = {12, 0}},
	                { x = 192, y = 143, width = 11, height = 13, anchor = {6, -34}
	            }}},
	            { duration = dt, quads = {
	                { x = 164, y = 12, width = 22, height = 36, anchor = {12, 0}},
	                { x = 179, y = 129, width = 11, height = 13, anchor = {6, -34}
	            }}},
                { duration = dt, quads = {
	                { x = 164, y = 12, width = 22, height = 36, anchor = {12, 0}},
	                { x = 192, y = 129, width = 11, height = 13, anchor = {6, -34}
	            }}},
                { duration = dt, quads = {
	                { x = 164, y = 12, width = 22, height = 36, anchor = {12, 0}},
	                { x = 205, y = 143, width = 11, height = 13, anchor =  {6, -34}
	            }}}
	        }
	    },
        {
	    	name = "talk_right",
	        frames = 
			{ 
	        	{ duration = dt, quads = {
	            	{ x = 157, y = 112, width = 19, height = 36, anchor = {10, 0}},
	                { x = 179, y = 101, width = 11, height = 12, anchor = {7, -35}
	            }}},
                { duration = dt, quads = {
	                { x = 157, y = 112, width = 19, height = 36, anchor = {10, 0}},
	                { x = 192, y = 101, width = 11, height = 12, anchor = {7,-35}
                }}},
                { duration = dt, quads = {
	                { x = 157, y = 112, width = 19, height = 36, anchor = {10, 0}},
	                { x = 205, y = 101, width = 11, height = 12, anchor = {7,-35}
	            }}},
                { duration = dt, quads = {
	                { x = 157, y = 112, width = 19, height = 36, anchor = {10, 0}},
	                { x = 179, y = 115, width = 11, height = 12, anchor = {7,-35}
	            }}},
                { duration = dt, quads = {
	                { x = 157, y = 112, width = 19, height = 36, anchor = {10, 0}},
	                { x = 192, y = 101, width = 11, height = 12, anchor = {7,-35}
				}}},
                { duration = dt, quads = {
	                { x = 157, y = 112, width = 19, height = 36, anchor = {10, 0}},
	                { x = 179, y = 101, width = 11, height = 12, anchor = {7,-35}
	            }}},
                { duration = dt, quads = {
	                { x = 157, y = 112, width = 19, height = 36, anchor = {10, 0}},
	                { x = 192, y = 115, width = 11, height = 12, anchor = {7,-35}
	           	}}},
                { duration = dt, quads = {
	                { x = 157, y = 112, width = 19, height = 36, anchor = {10, 0}},
	                { x = 205, y = 115, width = 11, height = 12, anchor = {7,-35}
	            }}},
                { duration = dt, quads = {
	                { x = 157, y = 112, width = 19, height = 36, anchor = {10, 0}},
	                { x = 179, y = 101, width = 11, height = 12, anchor = {7,-35}
	            }}},
                { duration = dt, quads = {
	                { x = 157, y = 112, width = 19, height = 36, anchor = {10, 0}},
	                { x = 192, y = 115, width = 11, height = 12, anchor = {7,-35}
                }}},
                { duration = dt, quads = {
	                { x = 157, y = 112, width = 19, height = 36, anchor = {10, 0}},
	                { x = 179, y = 101, width = 11, height = 12, anchor = {7,-35}
	            }}},
                { duration = dt, quads = {
	                { x = 157, y = 112, width = 19, height = 36, anchor = {10, 0}},
	                { x = 205, y = 101, width = 11, height = 12, anchor = {7,-35}
	            }}}
	        }                
	    },
	    {
	        name = "talk_back",
	        frames =            
			{ 
	            { duration = dt, quads = {
	                { x = 189, y = 12, width = 20, height = 36, anchor = {12, 0}},
	                { x = 220, y = 101, width = 11, height = 12, anchor = {6, -34}
	            }}},
                { duration = dt, quads = {
	                { x = 189, y = 12, width = 20, height = 36, anchor = {12, 0}},
	                { x = 233, y = 101, width = 11, height = 12, anchor = {6, -34}
	            }}},
                { duration = dt, quads = {
	                { x = 189, y = 12, width = 20, height = 36, anchor = {12, 0}},
	                { x = 220, y = 101, width = 11, height = 12, anchor = {6, -34}
	            }}},
                { duration = dt, quads = {
	                { x = 189, y = 12, width = 20, height = 36, anchor = {12, 0}},
	                { x = 233, y = 101, width = 11, height = 12, anchor = {6, -34}
                }}},
                { duration = dt, quads = {
	                { x = 189, y = 12, width = 20, height = 36, anchor = {12, 0}},
	                { x = 220, y = 115, width = 11, height = 12, anchor = {6, -34}
	            }}}
	        }
	    },
	    {
	        name = "operate_right",
	        frames =            
			{
	            { duration = dt, quads = {{ x = 2, y = 150, width = 28, height = 45, anchor = {10, 0}}}}
	        },
		},
	    {
	        name = "operate_back",
	        frames =          
			{ 
	            { duration = dt, quads = { { x = 33, y = 150, width = 19, height = 45, anchor = {12, 0}}}}
            }
        },
        {
            name = "operate_front",
            frames =            
			{ 
	        	{ duration = dt, quads = { { x = 125, y = 151, width = 18, height = 46, anchor = {12, 0}}}}
            }
        },
        {
	        name = "kneel_front",
	        frames =            
			{ 
	        	{ duration = dt, quads = { { x = 80, y = 163, width = 17, height = 33, anchor = {10, 0}}}}
	        }
	    },
	    {
	    	name = "kneel_back",
	        frames =       
			{ 
	        	{ duration = dt, quads = {{ x = 100, y = 163, width = 19, height = 33, anchor = {10, 0}}}}
            }
	    },
	    {
	    	name = "plank",
	        frames =            
			{ 
	        	{ duration = dt, quads = {{ x = 57, y = 150, width = 21, height = 47, anchor = {10, 0}}}}
            }
	    },
	    {
	        name = "pot_out",
	        frames = 
			{ 
	           	{ duration = dt, quads = {{ x = 1, y = 199, width = 26, height = 47, anchor = {13, 0}}}},
				{ duration = dt, quads = {{ x = 30, y = 199, width = 26, height = 47, anchor = {13, 0}}}},
				{ duration = dt, quads = {{ x = 59, y = 199, width = 26, height = 47, anchor = {13, 0}}}},
				{ duration = dt, quads = {{ x = 88, y = 199, width = 36, height = 48, anchor = {13, 0}}}}
	        }
	    },
	    {
	        name = "show_pot",
	        frames = 
			{ 
				{ duration = dt, quads = {{ x = 88, y = 199, width = 36, height = 48, anchor = {13, 0}}}},
	        }
	    },
	    {
	        name = "pot_in",
	        frames = 
			{ 
				{ duration = dt, quads = {{ x = 88, y = 199, width = 36, height = 48, anchor = {13, 0}}}},
				{ duration = dt, quads = {{ x = 59, y = 199, width = 26, height = 47, anchor = {13, 0}}}},
				{ duration = dt, quads = {{ x = 30, y = 199, width = 26, height = 47, anchor = {13, 0}}}},
	            { duration = dt, quads = {{ x = 1, y = 199, width = 26, height = 47, anchor = {13, 0}}}},
	        }
	    },
	    {
	        name = "get_in_cannon",
	        frames = { 
	       		{ duration = dt, quads = {{ x = 1, y = 199, width = 26, height = 47, anchor = {13, 0}}}},
				{ duration = dt, quads = {{ x = 30, y = 199, width = 26, height = 47, anchor = {13, 0}}}},
				{ duration = dt, quads = {{ x = 59, y = 199, width = 26, height = 47, anchor = {13, 0}}}},
				{ duration = 3*dt, quads = {{ x = 88, y = 199, width = 36, height = 48, anchor = {13, 0}}}},
				{ duration = dt, quads = {{ x = 176, y = 193, width = 21, height = 54, anchor = {7, 2}}}},
				{ duration = dt, quads = {{ x = 200, y = 200, width = 18, height = 47, anchor = {7, 2}}}},
				{ duration = dt, quads = {{ x = 222, y = 198, width = 26, height = 49, anchor = {7, 2}}}},
				{ duration = dt, quads = {{ x = 2, y = 249, width = 26, height = 49, anchor = {7, 1}}}},
				{ duration = dt, quads = {{ x = 31, y = 248, width = 23, height = 50, anchor = {5, -6}}}},
				{ duration = dt, quads = {{ x = 57, y = 248, width = 19, height = 46, anchor = {5, -6}}}},
				{ duration = dt, quads = {{ x = 80, y = 249, width = 21, height = 41, anchor = {6, -5}}}},
				{ duration = dt, quads = {{ x = 104, y = 249, width = 15, height = 29, anchor = {0, -13}}}},
				{ duration = dt, quads = {{ x = 124, y = 249, width = 19, height = 20, anchor = {4, -16}}}},
				{ duration = dt, quads = {{ x = 147, y = 249, width = 23, height = 20, anchor = {4, -22}}}},
				{ duration = dt, quads = {{ x = 172, y = 252, width = 21, height = 13, anchor = {4, -22}}}},
	        }
	    }
	}
}
