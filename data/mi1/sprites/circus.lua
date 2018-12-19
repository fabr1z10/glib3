local dt = 0.1

sprites["circus.purpleclown"] = {
	id="circus.purpleclown",
    sheet="gfx/anims2.png",
    type="sprite",
    ppu=1,
    animations = {
        {
            name = "idle_front",             
            frames = { 
            {
                duration = dt,
                quads = {
                    { x = 286, y = 303, width = 27, height = 45, anchor = {14, 0}}
                }
            }}
        },
        {
            name = "idle_right",             
            frames = {
            {
                duration = dt,
                quads = {
                    { x = 290, y = 404, width = 22, height = 38, anchor = {12, 0}},
					{ x = 316, y = 409, width = 11, height = 12, anchor = {2, -34}},
                }
            }}
        },
        {
            name = "idle_back",             
            frames = {
            {
                duration = dt,
                quads = {
                    { x = 331, y = 409, width = 28, height = 45, anchor = {15, 0}}
                }
            }}
        },
        {
            name = "walk_front",             
            frames = {
              { duration = dt, quads = {{ x = 315, y = 315, width = 23, height = 45, anchor = {12, 0}}}},
              { duration = dt, quads = {{ x = 340, y = 314, width = 24, height = 46, anchor = {12, 0}}}},
              { duration = dt, quads = {{ x = 366, y = 314, width = 24, height = 46, anchor = {12, 0}}}},
              { duration = dt, quads = {{ x = 392, y = 315, width = 23, height = 45, anchor = {12, 0}}}},
              { duration = dt, quads = {{ x = 417, y = 314, width = 24, height = 46, anchor = {12, 0}}}},
              { duration = dt, quads = {{ x = 443, y = 315, width = 24, height = 45, anchor = {12, 0}}}}
            }
        }, 
        {
            name = "walk_right",             
            frames = {
              { duration = dt, quads = {{ x = 364, y = 411, width = 28, height = 43, anchor = {13, 0}}}},
              { duration = dt, quads = {{ x = 394, y = 412, width = 24, height = 42, anchor = {12, 0}}}},
              { duration = dt, quads = {{ x = 419, y = 409, width = 15, height = 45, anchor = {12, 0}}}},
              { duration = dt, quads = {{ x = 436, y = 411, width = 26, height = 43, anchor = {13, 0}}}},
              { duration = dt, quads = {{ x = 463, y = 412, width = 21, height = 42, anchor = {12, 0}}}},
              { duration = dt, quads = {{ x = 486, y = 409, width = 15, height = 45, anchor = {11, 0}}}}
            }
        }, 
        {
            name = "talk_right",             
            frames = {
            	{ duration = dt, quads = {{ x = 290, y = 404, width = 22, height = 38, anchor = {12, 0}}, { x = 316, y = 409, width = 11, height = 12, anchor = {2, -34}}}},
            	{ duration = dt, quads = {{ x = 290, y = 404, width = 22, height = 38, anchor = {12, 0}}, { x = 277, y = 397, width = 10, height = 13, anchor = {2, -34}}}},
            	{ duration = dt, quads = {{ x = 290, y = 404, width = 22, height = 38, anchor = {12, 0}}, { x = 276, y = 411, width = 11, height = 12, anchor = {2, -34}}}},
				{ duration = dt, quads = {{ x = 290, y = 404, width = 22, height = 38, anchor = {12, 0}}, { x = 277, y = 424, width = 9, height = 12, anchor = {2, -34}}}}                
            }
        },   
        {
            name = "talk_back",             
            frames = {
            {
                duration = dt,
                quads = {
                    { x = 331, y = 409, width = 28, height = 45, anchor = {15, 0}}
                }
            }}
        },
    }
}

sprites["circus.flyingguy"] = {
	id = "circus.flyingguy",
    sheet = "gfx/anims3.png",
    type="sprite",
    ppu=1,
    animations = {
        {
       	    name = "default",             
            frames = 
            { 
	    	  	{ duration = dt, quads = { { x = 322, y = 217, width = 20, height = 22, anchor = {-213, -75}}}},
				{ duration = dt, quads = { { x = 347, y = 217, width = 26, height = 16, anchor = {-190, -89}}}},
				{ duration = dt, quads = { { x = 377, y = 217, width = 26, height = 27, anchor = {-169, -96}}}},
				{ duration = dt, quads = { { x = 406, y = 217, width = 37, height = 24, anchor = {-148, -100}}}},
				{ duration = dt, quads = { { x = 447, y = 217, width = 31, height = 22, anchor = {-133, -98}}}},
				{ duration = dt, quads = { { x = 481, y = 217, width = 25, height = 24, anchor = {-111, -92}}}},
				{ duration = dt, quads = { { x = 327, y = 243, width = 22, height = 22, anchor = {-93, -89}}}},
				{ duration = dt, quads = { { x = 327, y = 243, width = 22, height = 22, anchor = {-93, -84}}}},
				{ duration = dt, quads = { { x = 327, y = 243, width = 22, height = 22, anchor = {-93, -82}}}},
				{ duration = dt, quads = { { x = 327, y = 243, width = 22, height = 22, anchor = {-93, -70}}}},
				{ duration = dt, quads = { { x = 327, y = 243, width = 22, height = 22, anchor = {-93, -65}}}},
				{ duration = dt, quads = { { x = 327, y = 243, width = 22, height = 22, anchor = {-93, -60}}}},
				{ duration = dt, quads = { { x = 327, y = 243, width = 22, height = 22, anchor = {-93, -55}}}},
				{ duration = dt, quads = { { x = 327, y = 243, width = 22, height = 22, anchor = {-93, -50}}}},
				{ duration = dt, quads = { { x = 327, y = 243, width = 22, height = 22, anchor = {-93, -45}}}},
				{ duration = dt, quads = { { x = 327, y = 243, width = 22, height = 22, anchor = {-93, -40}}}},
				{ duration = dt, quads = { { x = 327, y = 243, width = 22, height = 22, anchor = {-93, -35}}}},
				{ duration = dt, quads = { { x = 327, y = 243, width = 22, height = 22, anchor = {-93, -29}}}},
			}
        },
		{
			name="end",
			frames =
            { 
				{ duration = dt, quads = { { x = 327, y = 243, width = 22, height = 22, anchor = {-93, -29}}}}
			}
		}
    }
}

sprites["circus.explosion"] = {
	id = "circus.explosion",
    sheet = "gfx/anims3.png",
    type="sprite",
    ppu=1,
    animations = {
        {
       	    name = "default",             
            frames = 
            { 
	    	  	{ duration = dt, quads = { { x = 287, y = 46, width = 22, height = 20, anchor = {-246, -56}}}},
                { duration = dt, quads = { { x = 313, y = 44, width = 36, height = 36, anchor = {-244, -43}}}},
                { duration = dt, quads = { { x = 352, y = 45, width = 48, height = 41, anchor = {-244, -40}}}},
                { duration = dt, quads = { { x = 404, y = 46, width = 44, height = 46, anchor = {-244, -38}}}},               
				{ duration = dt, quads = { { x = 363, y = 108, width = 46, height = 50, anchor = {-244, -40}}, {x=320,y=97,width=32,height=29,anchor={-201,-72}}}},
				{ duration = dt, quads = { { x = 414, y = 99, width = 51, height = 48, anchor = {-244, -36}}, {x=363,y=87,width=33,height=20,anchor={-200,-78}}}},
                { duration = dt, quads = { { x = 337, y = 169, width = 48, height = 43, anchor = {-244, -35}}}},               
                { duration = dt, quads = { { x = 393, y = 165, width = 44, height = 46, anchor = {-244, -34}}}},               
			}
        }
    }
}


sprites["circus.greenclown"] = {
    id="circus.greenclown",
    sheet="gfx/anims2.png",
    type="sprite",
    ppu=1,
    animations = {
        {
            name = "idle_front",             
            frames = { 
            {
                duration = dt,
                quads = {
                    { x = 286, y = 350, width = 27, height = 45, anchor = {14, 0}}
                }
            }}
        },
        {
            name = "idle_right",             
            frames = {
            {
                duration = dt,
                quads = {
                    { x = 290, y = 450, width = 22, height = 38, anchor = {12, 0}},
					{ x = 316, y = 423, width = 10, height = 12, anchor = {2, -34}},
                }
            }}
        },
        -- {
        --     name = "idle_back",             
        --     frames = {
        --     {
        --         duration = dt,
        --         quads = {
        --             { x = 331, y = 409, width = 28, height = 45, anchor = {15, 0}}
        --         }
        --     }}
        -- },
        {
            name = "walk_front",             
            frames = {
              { duration = dt, quads = {{ x = 315, y = 362, width = 23, height = 45, anchor = {12, 0}}}},
              { duration = dt, quads = {{ x = 340, y = 361, width = 24, height = 46, anchor = {12, 0}}}},
              { duration = dt, quads = {{ x = 366, y = 361, width = 24, height = 46, anchor = {12, 0}}}},
              { duration = dt, quads = {{ x = 392, y = 362, width = 23, height = 45, anchor = {12, 0}}}},
              { duration = dt, quads = {{ x = 417, y = 362, width = 24, height = 46, anchor = {12, 0}}}},
              { duration = dt, quads = {{ x = 443, y = 362, width = 24, height = 45, anchor = {12, 0}}}}
            }
        }, 
        {
            name = "walk_right",             
            frames = {
              { duration = dt, quads = {{ x = 364, y = 458, width = 28, height = 43, anchor = {13, 0}}}},
              { duration = dt, quads = {{ x = 394, y = 459, width = 24, height = 42, anchor = {12, 0}}}},
              { duration = dt, quads = {{ x = 419, y = 456, width = 15, height = 45, anchor = {12, 0}}}},
              { duration = dt, quads = {{ x = 436, y = 458, width = 26, height = 43, anchor = {13, 0}}}},
              { duration = dt, quads = {{ x = 463, y = 459, width = 21, height = 42, anchor = {12, 0}}}},
              { duration = dt, quads = {{ x = 486, y = 456, width = 15, height = 45, anchor = {11, 0}}}}
            }
        }, 
        {
            name = "talk_right",             
            frames = {
            	{ duration = dt, quads = {{ x = 290, y = 450, width = 22, height = 38, anchor = {12, 0}}, { x = 316, y = 423, width = 10, height = 12, anchor = {2, -34}}}},
            	{ duration = dt, quads = {{ x = 290, y = 450, width = 22, height = 38, anchor = {12, 0}}, { x = 276, y = 443, width = 10, height = 12, anchor = {2, -34}}}},
            	{ duration = dt, quads = {{ x = 290, y = 450, width = 22, height = 38, anchor = {12, 0}}, { x = 276, y = 456, width = 10, height = 12, anchor = {2, -34}}}},
            	{ duration = dt, quads = {{ x = 290, y = 450, width = 22, height = 38, anchor = {12, 0}}, { x = 276, y = 469, width = 10, height = 12, anchor = {2, -34}}}},
            }
        },   
    }
}