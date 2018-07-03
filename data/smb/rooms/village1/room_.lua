--assets local to this scene


require ("funcs")
require ("text")
require ("actions")

local dt = 0.1

-- begin room
room = {

assets = {
    makeGuybrush(),
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
    [1] = {
        tag="main",
        layer = 1,
        children = {
            {
              pos = {0, 0, -5},
              gfx = { image="gfx/village1/bg1.png" },
              layer = 1
            },
            {
              walkarea = { 
                tag = "walkarea",
            	  group = 1,
            	  priority = 0,
            	  target = "player",
            	  shape = { type = "graph", vertices = { {8, 71}, {23, 63}, {49, 49}, {40, 37}, {56, 24}, {84, 13}, {752, 13} }, edges = { {0,1}, {1,2}, {2,3},{3,4}, {4,5},{5,6} }},
                scaling = {
                    depth = { 
                        { rect = {0, 1008, 0, 144}, dir = "y", bounds = {1, 0} } 
                    },
                    scale = {
                        { rect = {0, 1008, 0, 144}, dir = "y", bounds = {1, 0.2} } 
                    }
                }
              },
              layer = 1
            },
            {
                pos= {6,60,0},
                hotspot = {
                    group =1,
                    priority = 1,
                    shape = { type="rect", width=37, height=45},
                    onenter=curry(hoverOn, objects.path),
                    onleave=hoverOff,
                    onclick=runAction
                },
                layer =1
            },
            {
                pos = {258, 26, 0},
                hotspot = {
                    group = 1, priority = 1, 
                    shape = { type = "rect", width=24, height=26},
                    onenter = curry(hoverOn, objects.poster),
                    onleave = hoverOff,
                    onclick = runAction
                },
                layer = 1
            
            },
            make_hotspot { x=699, y=7, width=31, height=47, offset={0,5},priority = 1, object = objects.village1_door, gfx = { model="door", anim = ((objects.village1_door.isopen() == true) and "open" or "close") }}
        }
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
    bounds = {0, 0, 1008, 144},
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
-- end room


-- initial script
function room.init()
    variables._actionInfo:reset()
    -- previous room was lookout
	local fromData = {
        lookout = { playerpos = {8, 71, 0}, anim = "idle_front" },
		scummbar = { playerpos = {715, 13, 0}, anim = "idle_front" }
    }

	f = fromData[variables._previousroom]

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

