--assets local to this scene


require ("funcs")
require ("text")
require ("actions")

-- begin room
room = {

assets = {
    makeGuybrush()
},

scene = {
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
table.unpack(makeUI())
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
    print ("CAZZONE")
    -- previous room was lookout
    if (variables._previousroom == "lookout") then
       playerpos = {8, 71, 0} 
    end
    
    -- add player
    table.insert (room.scene, {
        tag = "player",
        pos = playerpos,
        gfx = { model = "guybrush", anim = "idle_front" },
        follow = { cam="maincam" },
        layer = 1,
        scaling = {}
    })

end

function room.start() 
    script = {
        startid = 0,
        id = "_walk",
        actions = {},
        edges ={}
    }
    createWalkToPosition ({120, 80}, script)
    monkey.play(script)

end

