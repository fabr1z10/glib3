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