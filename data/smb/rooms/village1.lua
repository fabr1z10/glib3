--assets local to this scene
dt=0.1

require ("funcs")
require ("text")
require ("actions")


assets = {
    makeGuybrush()
}

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
	 shape = { type = "poly", outline = {0,0,0,144,1008,144,1008,0}}
  }
},
{
  tag = "player",
  pos = {20, 20, 0},
  gfx = { model = "guybrush", anim = "idle_front" },
  follow = { cam="maincam" },
  layer = 1
},
{
  pos= {6,60,0},
  hotspot = {
    group =1,
    priority = 1,
    shape = { type="rect", width=37, height=45},
    onenter=curry(hoverOn, "path"),
    onleave=hoverOff,
    onclick=runAction
  },
  layer =1
},
table.unpack(makeUI())
}

groups = {
	{ id=1, cam ="maincam"},
	{ id=2, cam ="uicam"}
}
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
