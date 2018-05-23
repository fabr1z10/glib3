--assets local to this scene
dt=0.1
assets = {
    {
        id="guybrush",
        sheet="gfx/sprite1.png",
		type="sprite",
        ppu=1,
        animations = {
	    {
	        name = "idle_front",             
            frames = 
            { 
	    	  	{
					duration = dt,
                    quads = {
			    		{ x = 24, y = 51, width = 22, height = 47, anchor = {12, 0}}
					}
		    	}
			}
	    },
        {
           name="idle_right",
           frames=
           { 
	           {
					duration = dt,
                    quads = {
			    		{ x = 2, y = 51, width = 19, height = 47, anchor = {12, 0}}
					}
		       }
		   }				
        }
		}
    }
    --lookout={},
    --fire={}
}

scene = {
{
  pos = {0, 0, 0},
  gfx = { image="gfx/lookout/bg1.png", width=320, height=144 },
  layer = 1
},
{
  tag = "player",
  pos = {30, 0, 0},
  gfx = { model = "guybrush", anim = "idle_front" },
  layer = 1
},
{
  walkarea = { 
    cam = "maincam", 
    target = "player",
    shape = { type="rect", width="10", height="10" }
  }
}
}


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
    type="ortho",
    size = {320, 56},
    bounds = {0, 0, 320, 56},
    viewport = {0, 0, 320, 56},
    layer = 2
}
}
