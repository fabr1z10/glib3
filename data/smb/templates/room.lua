--assets local to this scene
require ("funcs")
require ("text")
require ("dialogues")
require ("actions")


local dt = 0.1

room = {

assets = {
},

scene = {
    [1] = { 
        tag = "main",
        layer = 1,
        children = {},
    },
    [2] = {
        tag = "controls",
        layer = 2,
        children = {}
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

end




