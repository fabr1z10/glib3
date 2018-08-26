--assets local to this scene
require ("funcs")
require ("text")
require ("dialogues")

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
        id = "sign",
        sheet = "gfx/anims2.png",
        type="sprite",
        ppu=1,
        animations = {
        {
       	    name = "idle",             
            frames = 
            { 
	    	  	{ duration = dt, quads = { { x=373, y=292, width=16, height=10, anchor = {0, 0}}}}             
		    }
        }		
		}		
	},
	{
        id = "bell",
        sheet = "gfx/anims2.png",
        type="sprite",
        ppu=1,
        animations = {
        {
       	    name = "idle",             
            frames = 
            { 
	    	  	{ duration = dt, quads = { { x=391, y=295, width=8, height=5, anchor = {0, 0}}}}             
		    }
        }		
		}		
	},
	{
        id = "shovel",
        sheet = "gfx/anims2.png",
        type="sprite",
        ppu=1,
        animations = {
        {
       	    name = "idle",             
            frames = 
            { 
	    	  	{ duration = dt, quads = { { x=348, y=29, width=8, height=25, anchor = {0, 0}}}}             
		    }
        }		
		}		
	},
    {
        id = "door_out",
        sheet = "gfx/anims.png",
        type="sprite",
        ppu=1,
        animations = {
        { name = "close", frames = { {duration = dt, quads = { { x = 434, y = 280, width = 31, height = 51, anchor = {0, 0}}}}}},
        { name = "open", frames = { {duration = dt, quads = { { x = 467, y = 280, width = 31, height = 51, anchor = {0, 0}}}}}}
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
        id = "desk",
        sheet = "gfx/anims2.png",
        type="sprite",
        ppu=1,
        animations = {
        {
       	    name = "idle",             
            frames = 
            { 
	    	  	{ duration = dt, quads = { { x=177, y=19, width=50, height=35, anchor = {0, 0}}}}             
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
        	name="walk_right",
        	frames=
            { 
	    	  	{ duration = dt, quads = { { x=380, y=105, width=30, height=45, anchor = {12, 0}}}},
	    	  	{ duration = dt, quads = { { x=412, y=107, width=26, height=44, anchor = {12, 0}}}},
	    	  	{ duration = dt, quads = { { x=440, y=105, width=27, height=46, anchor = {12, 0}}}},
	    	  	{ duration = dt, quads = { { x=469, y=106, width=28, height=45, anchor = {12, 0}}}},
	    	  	{ duration = dt, quads = { { x=380, y=154, width=26, height=43, anchor = {12, 0}}}},
	    	  	{ duration = dt, quads = { { x=407, y=152, width=38, height=45, anchor = {12, 0}}}},
		    }        	
    	},
    	{
        	name="walk_front",
        	frames=
            { 
	    	  	{ duration = dt, quads = { { x=310, y=225, width=34, height=43, anchor = {12, 0}}}},
	    	  	{ duration = dt, quads = { { x=346, y=225, width=29, height=43, anchor = {12, 0}}}},
	    	  	{ duration = dt, quads = { { x=378, y=246, width=28, height=41, anchor = {12, 0}}}},
	    	  	{ duration = dt, quads = { { x=408, y=246, width=29, height=42, anchor = {12, 0}}}},
	    	  	{ duration = dt, quads = { { x=439, y=246, width=30, height=42, anchor = {12, 0}}}},
	    	  	{ duration = dt, quads = { { x=472, y=247, width=31, height=41, anchor = {12, 0}}}},
		    }        	
    	},
        {
       	    name = "talk_right",             
            frames = 
            { 
	    	  	{ duration = dt, quads = { { x=246, y=5, width=28, height=42, anchor = {12, 0}}, {x=232, y=4, width=11, height=13, anchor = {-2,-32}}}},
				{ duration = dt, quads = { { x=246, y=5, width=28, height=42, anchor = {12, 0}}, {x=168, y=3, width=10, height=14, anchor = {-2,-32}}}},
				{ duration = dt, quads = { { x=246, y=5, width=28, height=42, anchor = {12, 0}}, {x=180, y=4, width=10, height=13, anchor = {-2,-32}}}},
				{ duration = dt, quads = { { x=246, y=5, width=28, height=42, anchor = {12, 0}}, {x=192, y=4, width=12, height=12, anchor = {-2,-32}}}},
				{ duration = dt, quads = { { x=246, y=5, width=28, height=42, anchor = {12, 0}}, {x=207, y=2, width=11, height=15, anchor = {-2,-32}}}},
				{ duration = dt, quads = { { x=246, y=5, width=28, height=42, anchor = {12, 0}}, {x=220, y=2, width=11, height=15, anchor = {-2,-32}}}},
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
              tag = "mainbg",
              pos = {249, 0, 0.98},
              gfx = { model="desk", anim="idle" }
            },
	        {
	          walkarea = { 
	            tag = "walkarea",
	            priority = 0,
	            target = "player",
	            shape = { 
	                type = "poly", 
	                outline = {62,14,90,20,115,20,150,31,191,31,231,67,154,67,154,69,235,69,235,67,184,25,175,25,181,21,235,21,235,13,248,2,
	                290,2,290,20,320,20,320,0,62,0}
	            },
	            scaling = {
	                depth = { 
	                    { rect = {0, 800, 0, 144}, dir = "y", bounds = {1, 0} } 
	                },
	                scale = {
	                    { rect = {0, 800, 0, 144}, dir = "y", bounds = {1.0, 1.0} } 
	                }
	            },
	            blockedlines = {
					{ A = {248, 0}, B = {248, 3}, active =true }
				},
	          }
	        },

			make_hotspot { 
				x=141,
				y=69,
				width=8, 
				height=20, 
				offset={0,0},
				priority = 1, 
 				gfx = { model="shovel", anim="idle" },
				object = "shovel"				
			},
			make_hotspot { 
				x=248,
				y=29,
				z=0.991,
				width=16, 
				height=10, 
				offset={0,0},
				priority = 1, 
 				gfx = { model="sign", anim="idle" },
				object = "sign"				
			},
			make_hotspot { 
				x=264,
				y=27,
				z=0.991,
				width=8, 
				height=8, 
				offset={0,0},
				priority = 1, 
 				gfx = { model="bell", anim="idle" },
				object = "bell"				
			},
			make_hotspot { 
				x=289,
				y=7,
				width=20, 
				height=40, 
				offset={0,0},
				priority = 1, 
				scaling = {},
 				gfx = { model="storekeeper", anim="idle_right", flip=true },
				object = "storekeeper"
			},
	        make_hotspot { 
	            x = 59, 
	            y = 16, 
	            width = 30, 
	            height = 50, 
	            offset = {0, 0},
	            priority = 1, 
	            object = "door_shop_village",
	            gfx = { model="door_out", anim = ((objects.door_shop_village.isopen() == true) and "open" or "close") }
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
    if (variables.swordPaid == false) then
    	table.insert(room.scene[1].children, 
    		make_hotspot { 
				x=212,
				y=45,
				width=30, 
				height=6, 
				offset={0,0},
				priority = 1, 
 				gfx = { model="sword", anim="idle" },
				object = "sword"				
			})
    end

end

function room.afterstartup() 
	refreshInventory()
	setActive { id="sign", active = false }
	setActive { id="bell", active = false }
	local s = script:new("_storekeeper")
	s.actions = {
		[1] = { type="delay", sec =2},
		[2] = say { character = "storekeeper", lines = { strings.shop[1]}, after={1} }
	}
	s.loop = 1
	monkey.play(s)
end




