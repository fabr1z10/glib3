--assets local to this scene
require ("funcs")
require ("text")
require ("dialogues")
require ("actions")
require ("dialogues/lookout")

local dt = 0.1

function provaciccio() 
print ("STICAZI")
end

room = {

assets = {
    makeGuybrush(),
    makeLookout(),
    {
        id = "fire",
        sheet = "gfx/anims.png",
        type="sprite",
        ppu=1,
        animations = {
        {
       	    name = "default",             
            frames = 
            { 
	    	  	    { duration = dt, quads = { { x = 1, y = 1, width = 24, height = 32, anchor = {0, 0}}}},
                { duration = dt, quads = { { x = 27, y = 1, width = 24, height = 32, anchor = {0, 0}}}},
                { duration = dt, quads = { { x = 53, y = 1, width = 24, height = 32, anchor = {0, 0}}}},
                { duration = dt, quads = { { x = 79, y = 1, width = 24, height = 32, anchor = {0, 0}}}}               
			      }
        }
        }
    },
	{
		id = "arrowup",
		sheet ="gfx/anims.png",
		type="sprite",
		ppu=1,
	    animations = {
        {
       	    name = "unselected",             
            frames = 
            { 
	    	  	{ duration = dt, quads = { { x = 485, y = 4, width = 12, height = 20, anchor = {0, 0}}}}             
			}
        },
		{
			name = "selected",
            frames = 
            { 
	    	  	{ duration = dt, quads = { { x = 485, y = 25, width = 12, height = 20, anchor = {0, 0}}}}             
			}
		}
        }	
	},
	{
		id = "arrowdown",
		sheet ="gfx/anims.png",
		type="sprite",
		ppu=1,
	    animations = {
        {
       	    name = "unselected",             
            frames = 
            { 
	    	  	{ duration = dt, quads = { { x = 472, y = 4, width = 12, height = 20, anchor = {0, 0}}}}             
			}
        },
		{
			name = "selected",
            frames = 
            { 
	    	  	{ duration = dt, quads = { { x = 472, y = 25, width = 12, height = 20, anchor = {0, 0}}}}             
			}
		}
        }	
	},



},
scene = {
	-- {
	-- 	-- main
	-- 	tag = "main",
	-- 	camera = {
	-- 		type="ortho",
	-- 		size = {320, 144},
	-- 		bounds = {0, 0, 320, 144},
	-- 		viewport = {0, 56, 320, 144}
	-- 	},
	-- 	children = {
	-- 		-- {
	-- 		-- 	pos = {0, 0, -5},
	-- 		-- 	gfx = { image="gfx/lookout/bg1.png", width=320, height=144 }
	-- 		-- }
	-- 	}
	-- },
	{
		tag="container",
	 	camera = {
			type="ortho",
	 		size = {160, 100},
	 		bounds = {0, 0, 160, 100},
	 		viewport = {80, 50, 160, 100}
	 	},	
		-- textview = {
		-- 	width = 160,
		-- 	height = 100,
		-- 	viewport = {80, 50, 160, 100},
		-- 	font = "ui",
		-- 	size = 8,
		-- 	bg = {32, 32, 32, 255}
		-- },
		children = {
			{
				tag = "rectsolid",
				gfx = { shape = { type="rect", width=160.0, height=100.0}, color = {32, 0, 0, 255}, draw = "solid" }
			},
			{
				tag="border",
				pos = {5,5,1},
				gfx = { shape = { type="rect", width=150.0, height=90.0}, color = {192, 0, 0, 255}, draw = "outline" }
			},
			-- {
			-- 	pos = {20, 20, 1},
			-- 	gfx = { model = "arrowup", anim="unselected" }
			-- },
			{
				tag="textview",
				textview = {
					width = 140.0,
					height = 80.0,
                    viewport = {10, 10, 140, 80},
                    font = "ui",
                    size = 8,
					arrowup = "arrowup",
                    arrowdown = "arrowdown"
				}
			}
			-- {
			-- 	pos = {5, 5, 1},
   --              gfx = { shape = { type="rect", width=150.0, height=90.0}, color = {255, 0, 0, 255}, draw = "outline" }
			-- }
		}
	}

-- [1] = { 
--     tag = "main",
--     layer = 1,
-- 	camera = {
--     	type="ortho",
--     	size = {320, 144},
--     	bounds = {0, 0, 320, 144},
--     	viewport = {0, 56, 320, 144}
--     }
--     children = {
--         {
--           pos = {0, 0, -5},
--           gfx = { image="gfx/lookout/bg1.png", width=320, height=144 },
--           layer = 1
--         },
--         {
--           pos = {81, 16, 3},
--          gfx = { image="gfx/lookout/bg2.png" },
--           layer = 1
--         },
--         {
--           pos = {294, 33, 3},
--           gfx = { image="gfx/lookout/bg3.png" },
--           layer = 1
--         },
--         {
--           tag = "player",
--           pos = {240, 40, 0},
--           gfx = { model = "guybrush", anim = "idle_front" },
--           scaling={},
--           layer = 1
--         },
--         --{
--         --  tag = "lookout",
--         --  pos = {240, 40, 1},
--         --  scaling = {},
--         --  gfx = { model = "lookout", anim = "idle_right", flip = true },
--         --  layer = 1
--         --},
--         make_hotspot { x=114, y=36, width=20, height=47, offset={-10,0}, priority = 1, object = characters.lookout,
--                       gfx = { model="lookout", anim = "idle_right", flip = true }, scaling = {} },
        
--         {
--           pos = {126, 52, -1},
--           gfx = { model = "fire", anim = "default" },
--           layer =1
        
--         },
--         {
--           walkarea = { 
--         	tag = "walkarea",
--         	group = 1,
--         	priority = 0,
--         	target = "player",
--         	shape = { type = "poly", outline = {203,51,315,62,315,19,260,10,260,0,260,-20,234,-20,234,0,234,10,221,26,152,33,152,51}},
--             scaling = {
--                 depth = { 
--                     { rect = {0, 320, 0, 144}, dir = "y", bounds = {1, 0} } 
--                 },
--                 scale = {
--                     { rect = {0, 320, 0, 144}, dir = "y", bounds = {1, 1} } 
--                 }
--             }
--           },
--           layer = 1
--         },
--         {
--           pos= {221,0,0},
--           hotspot = {
--             group =1,
--             priority = 1,
--             shape = { type="rect", width=57, height=27},
--             onenter=curry(hoverOn, objects.stairs),
--             onleave=hoverOff,
--             onclick=runAction
--           },
--           layer =1
--         }
--     }
--   },
--   [2] = {
--         tag = "controls",
--         layer = 2,
--         children = {
--             table.unpack(makeUI()),
--             {
--                 tag = "dialogue"
--             }
--         }
--   },
-- [3] =
-- {
--    tag ="prova",
--    textview = {
--       width=160,
--       height=100,
-- 	  viewport = {80, 50, 160, 100},
-- 	  size = 8,
--       font = "ui" 
--    }
-- },
},




-- groups = {
--   { id=1, cam ="maincam"},
--   { id=2, cam ="uicam"}
-- },
-- cameras = {
-- {
--     tag="maincam",
-- 	root="main",
--     type="ortho",
--     size = {320, 144},
--     bounds = {0, 0, 320, 144},
--     viewport = {0, 56, 320, 144},
--     layer = 1
-- },
-- {
--     tag = "uicam",
--     root="ui",
-- 	type="ortho",
--     size = {320, 56},
--     bounds = {0, 0, 320, 56},
--     viewport = {0, 0, 320, 56},
--     layer = 2
-- }

hotkeys = {
	{ key = 32, func = provaciccio }
}
}

function room.init()
variables._actionInfo:reset()
end

function prova2(a)
  a:parent():setcolor(255, 255, 255, 255)
  print "qua!!"
end



