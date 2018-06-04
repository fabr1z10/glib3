--assets local to this scene
dt=0.1

require ("funcs")
require ("text")
require ("actions")


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
			    		{ x = 2, y = 51, width = 19, height = 47, anchor = {10, 0}}
					}
		       }
		   }				
        },
        {
           name="idle_back",
           frames=
           { 
	           {
					duration = dt,
                    quads = {
			    		{ x = 49, y = 51, width = 20, height = 47, anchor = {12, 0}}
					}
		       }
		   }				
        },
	    {
	        name = "walk_front",             
            frames = 
            { 
	    	  	{
					duration = dt,
                    quads = {
			    		{ x = 207, y = 51, width = 22, height = 47, anchor = {11, 0}}
					}
		    	},
	    	  	{
					duration = dt,
                    quads = {
			    		{ x = 231, y = 51, width = 21, height = 47, anchor = {11, 0}}
					}
		    	},	
	    	  	{
					duration = dt,
                    quads = {
			    		{ x = 3, y = 101, width = 20, height = 47, anchor = {10, 0}}
					}
		    	},
	    	  	{
					duration = dt,
                    quads = {
			    		{ x = 25, y = 101, width = 22, height = 47, anchor = {12, 0}}
					}
		    	},	
	    	  	{
					duration = dt,
                    quads = {
			    		{ x = 49, y = 101, width = 21, height = 47, anchor = {11, 0}}
					}
		    	},						
	    	  	{
					duration = dt,
                    quads = {
			    		{ x = 72, y = 101, width = 20, height = 47, anchor = {11, 0}}
					}
		    	}					
			}
	    },			
        {
           name="walk_right",
           frames=
           { 
	           {
					duration = dt,
                    quads = {
			    		{ x = 4, y = 1, width = 32, height = 47, anchor = {16, 0}}
					}
		       },
			   {
					duration = dt,
                    quads = {
			    		{ x = 40, y = 1, width = 16, height = 47, anchor = {11, 0}}
					}
		       },
			   {
					duration = dt,
                    quads = {
			    		{ x = 60, y = 1, width = 19, height = 47, anchor = {11, 0}}
					}
		       },
			   {
					duration = dt,
                    quads = {
			    		{ x = 83, y = 1, width = 31, height = 47, anchor = {15, 0}}
					}
		       },
			   {
					duration = dt,
                    quads = {
			    		{ x = 117, y = 1, width = 18, height = 47, anchor = {11, 0}}
					}
		       },		
			   {
					duration = dt,
                    quads = {
			    		{ x = 141, y = 1, width = 19, height = 47, anchor = {11, 0}}
					}
		       }					
		   }				
        },		
        {
           name="walk_back",
           frames=
           { 
	           {
					duration = dt,
                    quads = {
			    		{ x = 72, y = 51, width = 21, height = 47, anchor = {11, 0}}
					}
		       },
	           {
					duration = dt,
                    quads = {
			    		{ x = 95, y = 51, width = 21, height = 47, anchor = {11, 0}}
					}
		       },
	           {
					duration = dt,
                    quads = {
			    		{ x = 118, y = 51, width = 19, height = 47, anchor = {11, 0}}
					}
		       },
	           {
					duration = dt,
                    quads = {
			    		{ x = 139, y = 51, width = 21, height = 47, anchor = {11, 0}}
					}
		       },
	           {
					duration = dt,
                    quads = {
			    		{ x = 163, y = 51, width = 21, height = 47, anchor = {11, 0}}
					}
		       },
	           {
					duration = dt,
                    quads = {
			    		{ x = 186, y = 51, width = 19, height = 47, anchor = {9, 0}}
					}
		       }
					
					
					
					
					
		   }				
        }
        }
    },
    --lookout={},
    --fire={}
    {
        id = "fire",
        sheet = "gfx/sprite2.png",
        type="sprite",
        ppu=1,
        animations = {
            {
       	    name = "default",             
            frames = 
            { 
	    	  	{
					duration = dt,
                    quads = {
			    		{ x = 1, y = 1, width = 24, height = 32, anchor = {0, 0}}
					}
		    	},
                {
					duration = dt,
                    quads = {
			    		{ x = 27, y = 1, width = 24, height = 32, anchor = {0, 0}}
					}
		    	},
                {
					duration = dt,
                    quads = {
			    		{ x = 53, y = 1, width = 24, height = 32, anchor = {0, 0}}
					}
		    	},
                {
					duration = dt,
                    quads = {
			    		{ x = 79, y = 1, width = 24, height = 32, anchor = {0, 0}}
					}
		    	}               
			}
            }
        }
        
    }
}

scene = {
{
  pos = {0, 0, -5},
  gfx = { image="gfx/lookout/bg1.png", width=320, height=144 },
  layer = 1
},
{
  pos = {81, 16, 5},
 gfx = { image="gfx/lookout/bg2.png" },
  layer = 1
},
{
  pos = {294, 33, 5},
  gfx = { image="gfx/lookout/bg3.png" },
  layer = 1
},
{
  tag = "player",
  pos = {240, 40, 0},
  gfx = { model = "guybrush", anim = "idle_front" },
  layer = 1
},
{
  pos = {126, 52, -1},
  gfx = { model = "fire", anim = "default" },
  layer =1

},
{
  walkarea = { 
	group = 1,
	priority = 0,
	target = "player",
	shape = { type = "poly", outline = {203,51,315,62,315,19,260,10,260,0,260,-20,234,-20,234,0,234,10,221,26,152,33,152,51}}
  }
},
{
  pos= {221,0,0},
  hotspot = {
    group =1,
    priority = 1,
    shape = { type="rect", width=57, height=27},
    onenter=curry(hoverOn, "path"),
    onleave=hoverOff,
    onclick=runAction
  },
  layer =1
},
makeButton(2, 40, variables._verbs.open),
makeButton(2, 32, variables._verbs.close),
makeButton(2, 24, variables._verbs.push),
makeButton(2, 16, variables._verbs.pull),
makeButton(48, 40, variables._verbs.walk),
makeButton(48, 32, variables._verbs.pick),
makeButton(48, 24, variables._verbs.talk),
makeButton(48, 16, variables._verbs.give),
makeButton(100, 40, variables._verbs.use),
makeButton(100, 32, variables._verbs.look),
makeButton(100, 24, variables._verbs.turnon),
makeButton(100, 16, variables._verbs.turnoff),
{
    tag = "currentaction",
    pos={160,48,0},
    text = {
        id = strings.ui.walkto, font="ui", align = "bottom", color = config.ui_currentaction_color
    },
    layer=2
    
}

--{
--  pos = { 2, 32, 0 },
--  button = { id=strings.ui.close, font="ui", align="bottomleft", group = 2, priority =1, layer=2,
--            onenter = curry2(changecolor, config.ui_selected_color),
--            onleave = curry2(changecolor, config.ui_unselected_color),
--            onclick = curry(setverb, "close") },
--  layer = 2
--},
--{
--  pos = { 2, 24, 0 },
--  button = { id=strings.ui.push, font="ui", align="bottomleft", group = 2, priority =1, layer=2,
--            onenter = curry2(changecolor, { r = 255, g = 255, b = 85, a = 255}),
--            onleave = curry2(changecolor, { r = 0, g = 170, b = 0, a = 255}),
--            onclick = curry(setverb, "push") },
--  layer = 2
--},
--{
--  pos = { 2, 16, 0 },
--  button = { id=strings.ui.pull, font="ui", align="bottomleft", group = 2, priority =1, layer=2,
--            onenter = curry2(changecolor, { r = 255, g = 255, b = 85, a = 255}),
--            onleave = curry2(changecolor, { r = 0, g = 170, b = 0, a = 255}),
--            onclick = curry(setverb, "pull") },
--  layer = 2
--}

	

}



function prova2(a)
  a:parent():setcolor(255, 255, 255, 255)
  print "qua!!"
end

groups = {
	{ id=1, cam ="maincam"},
	{ id=2, cam ="uicam"}
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
    tag = "uicam",
    type="ortho",
    size = {320, 56},
    bounds = {0, 0, 320, 56},
    viewport = {0, 0, 320, 56},
    layer = 2
}
}
