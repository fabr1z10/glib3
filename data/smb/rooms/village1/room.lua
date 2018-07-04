--assets local to this scene
require ("funcs")
require ("text")
require ("dialogues")
require ("actions")
require ("dialogues/lookout")

local dt = 0.1

--table.insert(inventory, { item = objects.poster, qty = 1})

-- begin room
room = {

assets = {
    makeGuybrush(),
    makeArrowUp(),
    makeArrowDown(),
    {
        id = "door",
        sheet = "gfx/sprite2.png",
        type="sprite",
        ppu=1,
        animations = {
        {
       	    name = "close",             
            frames = 
            { 
	    	  	{ duration = dt, quads = { { x = 33, y = 35, width = 31, height = 52, anchor = {0, 0}}}}              
		    }
        },
        {
       	    name = "open",             
            frames = 
            { 
	    	  	{ duration = dt, quads = { { x = 1, y = 35, width = 31, height = 52, anchor = {0, 0}}}}              
		    }
        }
        }
    }
},
scene = {
	{
		tag = "main",
		camera = {
			tag = "maincam",
			type="ortho",
			size = {320, 144},
			bounds = {0, 0, 1008, 144},
			viewport = {0, 56, 320, 144}
		},
		children = {
            {
              pos = {0, 0, -5},
              gfx = { image="gfx/village1/bg1.png" }
            },
            {
              walkarea = { 
                  tag = "walkarea",
            	  group = 1,
            	  priority = 0,
            	  target = "player",
            	  shape = { type = "graph", vertices = { {8, 71}, {23, 63}, {49, 49}, {40, 37}, {56, 24}, {84, 13}, {770, 13}, {780,34}, {1000,34} }, edges = { 
					{0,1}, {1,2}, {2,3},{3,4}, {4,5},{5,6},{6,7},{7,8} }},
                  scaling = {
                    depth = { 
                        { rect = {0, 1008, 0, 144}, dir = "y", bounds = {1, 0} } 
                    },
                    scale = {
                        { rect = {0, 1008, 0, 144}, dir = "y", bounds = {1, 0.2} } 
                    }
                }
              }
            },
	        make_hotspot { 
                x=0, 
				y=58, 
				width=74, 
				height=50, 
				priority = 1, 
				object = "cliffside"
			},
	        make_hotspot { 
                x=258, 
				y=26, 
				width=24, 
				height=26, 
				priority = 1, 
				object = "poster"
			},
			make_hotspot { 
				x=699, 
				y=7, 
				width=31, 
				height=47, 
				offset={0,5},
				priority = 1, 
				object = "village1_door", 
				gfx = { 
					model="door", 
					anim = ((objects.village1_door.isopen() == true) and "open" or "close") 
				}
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
    -- previous room was lookout
	local fromData = {
        lookout = { playerpos = {8, 71, 0}, anim = "idle_front" },
		scummbar = { playerpos = {715, 13, 0}, anim = "idle_front" }
    }
	
	f = fromData[variables._previousroom]
	if (f == nil) then
		variables._previousroom = "lookout"
		f = fromData[variables._previousroom]
	end

    -- add player
    table.insert (room.scene[1].children, {
        tag = "player",
        pos = f.playerpos,
        gfx = { model = "guybrush", anim = f.anim },
        follow = { cam="maincam" },
        layer = 1,
        scaling = {}
    })

end


function room.start() 
	if (variables._previousroom == "lookout") then
	    script = {
	        startid = 0,
	        id = "_walk",
	        actions = {},
	        edges ={}
	    }
	    createWalkToPosition ({120, 80}, script)
	    monkey.play(script)

	end

end


function room.afterstartup() 
refreshInventory()
end




