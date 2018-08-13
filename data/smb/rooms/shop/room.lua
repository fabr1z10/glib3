--assets local to this scene
require ("funcs")
require ("text")
require ("dialogues")
--require ("actions")

local dt = 0.1

--table.insert(inventory, { item = objects.poster, qty = 1})

-- begin room
room = {

assets = {
    makeGuybrush(),
    makeArrowUp(),
    makeArrowDown(),
	{
        id = "sword",
        sheet = "gfx/anims2.png",
        type="sprite",
        ppu=1,
        animations = {
        {
       	    name = "idle",             
            frames = 
            { 
	    	  	{ duration = dt, quads = { { x=280, y=3, width=30, height=6, anchor = {0, 0}}}}             
		    }
        }		
		}		
	},
	{
        id = "shopbarrels",
        sheet = "gfx/anims2.png",
        type="sprite",
        ppu=1,
        animations = {
        {
       	    name = "idle",             
            frames = 
            { 
	    	  	{ duration = dt, quads = { { x=279, y=16, width=65, height=38, anchor = {0, 0}}}}             
		    }
        }		
		}		
	},
	{
        id = "storekeeper",
        sheet = "gfx/anims2.png",
        type="sprite",
        ppu=1,
        animations = {
        {
       	    name = "idle_right",             
            frames = 
            { 
	    	  	{ duration = dt, quads = { { x=246, y=5, width=28, height=42, anchor = {12, 0}}, {x=232, y=4, width=11, height=13, anchor = {-2,-32}}}}
		    }
        },
        {
       	    name = "talk_right",             
            frames = 
            { 
	    	  	{ duration = dt, quads = { { x=246, y=5, width=28, height=42, anchor = {12, 0}}, {x=232, y=4, width=11, height=13, anchor = {-2,-32}}}}
		    }
        },
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
			bounds = {0, 0, 320, 144},
			viewport = {0, 56, 320, 144}
		},
		children = {
            {
              tag = "mainbg",
              pos = {0, 0, -5},
              gfx = { image="gfx/shop/bg1.png" }
            },
            {
              tag = "mainbg",
              pos = {117, 0, 2},
              gfx = { model="shopbarrels", anim="idle" }
            },
	        {
	          walkarea = { 
	            tag = "walkarea",
	            priority = 0,
	            target = "player",
	            shape = { 
	                type = "poly", 
	                outline = {62,14,90,20,115,20,150,31,191,31,231,67,154,67,154,69,235,69,235,67,184,25,175,25,181,21,235,21,235,13,248,0,62,0}
	            },
	            scaling = {
	                depth = { 
	                    { rect = {0, 800, 0, 144}, dir = "y", bounds = {1, 0} } 
	                },
	                scale = {
	                    { rect = {0, 800, 0, 144}, dir = "y", bounds = {1.0, 1.0} } 
	                }
	            }
	          }
	        },
			make_hotspot { 
				x=212,
				y=45,
				width=30, 
				height=6, 
				offset={0,0},
				priority = 1, 
 				gfx = { model="sword", anim="idle" },
				object = "sword"				
			},
			make_hotspot { 
				x=289,
				y=7,
				width=20, 
				height=40, 
				offset={0,0},
				priority = 1, 
 				gfx = { model="storekeeper", anim="idle_right", flip=true },
				object = "storekeeper"
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
	local fromData = {
        village3 = { playerpos = {85, 15, 0}, anim = "idle_right", flip = false },
    }
    -- add player
	local d = fromData[variables._previousroom]
	if (d == nil) then
		d = fromData["village3"]
	end

    table.insert (room.scene[1].children, {
        tag = objects.guybrush.tag,
        pos = d.playerpos,
        gfx = { model = "guybrush", anim = d.anim, flip = d.flip },
        follow = { cam="maincam" },
        scaling = {}
    })

end

function room.afterstartup() 
	refreshInventory()
	local s = script:new("_pippo")
	s.actions = {
		[1] = { type="delay", sec =2},
		[2] = say { character = "storekeeper", lines = { strings.shop[1]}, after={1} }
	}
	s.loop = 1
	monkey.play(s)
end




