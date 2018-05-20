--assets local to this scene
assets = {
    guybrush = {
	type="sprite",
        animations = {
	    {
	        name = "idle_front",
                frames = { 
		    { 24, 51, 22, 47, -12, 0, dt }
		}
	    },
            {
                name="idle_right",
                frames={}
            }

 	}
    },
    lookout={},
    fire={}
}

scene = {
{
  pos = {0, 0, 0},
  gfx = { image="gfx/lookout/bg1.png", width=320, height=144 },
  layer = 1
},
{
    pos = {}
}

}

cameras = {
{
    type="ortho",
    size = {320, 144},
    bounds = {0, 0, 320, 144},
    viewport = {0, 56, 320, 144},
    layer = 1
},
{
    type="ortho",
    size = {320, 56},
    bounds = {0, 0, 320, 56},
    viewport = {0, 0, 320, 56},
    layer = 2
}
}
