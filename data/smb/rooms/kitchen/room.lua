--assets local to this scene
require ("funcs")
require ("text")
require ("dialogues")
require ("actions")


local dt = 0.1

room = {

assets = {
    makeGuybrush(),
    {
        id = "door_to_bar",
        sheet = "gfx/anims.png",
        type="sprite",
        ppu=1,
        animations = {
        { name = "close", frames = { {duration = dt, quads = { { x = 222, y = 280, width = 37, height = 53, anchor = {0, 0}}}}}},
        { name = "open", frames = { {duration = dt, quads = { { x = 183, y = 280, width = 37, height = 53, anchor = {0, 0}}}}}}
        }
    },
    {
        id = "door_to_pier",
        sheet = "gfx/anims.png",
        type="sprite",
        ppu=1,
        animations = {
        { name = "close", frames = { {duration = dt, quads = { { x = 399, y = 280, width = 32, height = 60, anchor = {0, 0}}}}}},
        { name = "open", frames = { {duration = dt, quads = { { x = 365, y = 280, width = 32, height = 60, anchor = {0, 0}}}}}}
        }
    },
	{
		id = "kitchen_table",
		sheet = "gfx/anims.png",
		type="sprite",
		ppu = 1,
		animations = {
		{ name="default", frames = { {duration = dt, quads = { { x = 126, y = 208, width = 33, height = 26, anchor = {0, 0}}}}}}
		}
	},
	{
		id ="potostew",
		sheet ="gfx/anims.png",
		type="sprite",
		ppu=1,
		animations = {
		{ 
            name="default", 
            frames = { 
                { duration = dt, quads = { { x = 254, y = 220, width = 29, height = 17, anchor = {0, 0}}}},
                { duration = dt, quads = { { x = 254, y = 239, width = 29, height = 17, anchor = {0, 0}}}},
                { duration = dt, quads = { { x = 254, y = 258, width = 29, height = 17, anchor = {0, 0}}}},
			}
		}}
	}
},

scene = {
    [1] = { 
        tag = "main",
        layer = 1,
        children = {
	        {
	          pos = {0, 0, -5},
	          gfx = { image="gfx/kitchen/bg1.png" },
	          layer = 1
	        },
			{
			  pos = {204, 0, 3},
			  gfx = { image="gfx/kitchen/bg2.png" },
		      layer = 1
			},
	        {
	          pos = {115, 0, 3},
	          gfx = { model = "kitchen_table", anim = "default" },
	          layer =1
	        },
	        {
	          pos = {153, 39, -3},
	          gfx = { model = "potostew", anim = "default" },
	          layer =1
	        },
	        {
	            walkarea = { 
	        	tag = "walkarea",
	        	group = 1,
	        	priority = 0,
	        	target = "player",
	        	shape = { type = "poly", outline = {40,16,59,21,155,21,180,18,192,18,294,18,307,12,199,9,207,0,160,0,149,11,112,11,100,0,40,0}},
				blockedlines = {
					{ A = {194, 0}, B = {194, 144}, active =true },
					{ A = {206, 0}, B = {206, 144}, active =true },
				},
	            scaling = {
	                depth = { 
	                    { rect = {0, 320, 0, 144}, dir = "y", bounds = {1, 0} } 
	                },
	                scale = {
	                    { rect = {0, 320, 0, 144}, dir = "y", bounds = {1, 1} } 
	                }
	            }
	          },
	          layer = 1
	        },
	        make_hotspot { 
	            x = 19,
	            y = 18, 
	            width = 38, 
	            height = 53, 
	            offset = {0, 0},
	            priority = 1, 
	            object = objects.door_kitchen_bar, 
	            gfx = { model="door_to_bar", anim = ((objects.door_kitchen_bar.isopen() == true) and "open" or "close") }
	        },
	        
	        make_hotspot { 
	            x = 192,
	            y = 9, 
	            width = 30, 
	            height = 60,
	            offset = {0, 0},
	            priority = 1, 
	            object = objects.door_kitchen_pier, 
	            gfx = { model="door_to_pier", anim = ((objects.door_kitchen_pier.isopen() == true) and "open" or "close") }
	        },
        },
    },
    [2] = {
        tag = "controls",
        layer = 2,
        children = {
            table.unpack(makeUI())
        }
    }
},

groups = {
  { id=1, cam ="maincam"},
  { id=2, cam ="uicam"}
},

cameras = {
{
    tag="maincam",
    type="ortho",
    size = {320, 144},
    bounds = {0, 0, 320, 144},
    viewport = {0, 56, 320, 144},
    layer = 1
},
{
    tag = "uicam",
    type="ortho",
    size = {320, 56},
    bounds = {0, 0, 320, 56},
    viewport = {0, 0, 320, 56},
    layer = 2
}
}
}

function room.init()
    -- put your initialization code here

    -- add player
    table.insert (room.scene[1].children, {
        tag = characters.guybrush.tag,
        pos = {50,20,0} ,
        gfx = { model = "guybrush", anim = "idle_right" },
        follow = { cam="maincam" },
        layer = 1,
        scaling = {}
    })
end




