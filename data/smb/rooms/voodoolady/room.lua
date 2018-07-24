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
		id = "voodoolady_body",
		sheet = "gfx/anims.png",
        type="sprite",
        ppu=1,
        animations = {
        { name = "idle", frames = { 
			{duration = dt*10, quads = { { x = 184, y = 187, width = 42, height = 33, anchor = {20, 0}}}},
			{duration = dt, quads = { { x = 184, y = 141, width = 42, height = 33, anchor = {20, 0}}}},
			{duration = dt*10, quads = { { x = 229, y = 141, width = 42, height = 33, anchor = {20, 0}}}},
			{duration = dt, quads = { { x = 184, y = 141, width = 42, height = 33, anchor = {20, 0}}}},
			}
		},
        { name = "raisehands", frames = { 
			{duration = dt, quads = { { x = 146, y = 245, width = 35, height = 33, anchor = {12, 0}}}},
			{duration = dt, quads = { { x = 122, y = 142, width = 61, height = 33, anchor = {24, 0}}}},
			{duration = dt, quads = { { x = 77, y = 312, width = 40, height = 44, anchor = {14, 0}}}},
			{duration = dt, quads = { { x = 120, y = 313, width = 40, height = 43, anchor = {13, 0}}}},
			{duration = dt, quads = { { x = 77, y = 312, width = 40, height = 44, anchor = {14, 0}}}},
			{duration = dt, quads = { { x = 120, y = 313, width = 40, height = 43, anchor = {13, 0}}}},
			{duration = dt, quads = { { x = 77, y = 312, width = 40, height = 44, anchor = {14, 0}}}},
			{duration = dt, quads = { { x = 120, y = 313, width = 40, height = 43, anchor = {13, 0}}}},
			}
		},

		}
	},
	{
		id = "baskets",
		sheet = "gfx/anims.png",
        type="sprite",
        ppu=1,
        animations = {
        { name = "idle", frames = { 
			{duration = dt, quads = { { x = 2, y = 238, width = 79, height = 35, anchor = {0, 0}}}},
			}
		}}
	},
	{
		id = "basket",
		sheet = "gfx/anims.png",
        type="sprite",
        ppu=1,
        animations = {
        { name = "idle", frames = { 
			{duration = dt, quads = { { x = 83, y = 238, width = 23, height = 20, anchor = {0, 0}}}},
			}
		}}
	},
	{	
		id ="voodoolady",
		sheet = "gfx/anims.png",
        type="sprite",
        ppu=1,
        animations = {
        { name = "idle", frames = { 
			{duration = dt, quads = { { x = 228, y = 175, width = 12, height = 15, anchor = {-20, -30}}}},
		}
			
		},
        { name = "talk", frames = { 
			{duration = dt, quads = { { x = 241, y = 175, width = 12, height = 15, anchor = {-20, -30}}}},
			{duration = dt, quads = { { x = 254, y = 175, width = 12, height = 15, anchor = {-20, -30}}}},
			{duration = dt, quads = { { x = 228, y = 191, width = 13, height = 15, anchor = {-20, -30}}}},
			{duration = dt, quads = { { x = 242, y = 191, width = 13, height = 15, anchor = {-20, -30}}}},
			{duration = dt, quads = { { x = 256, y = 191, width = 12, height = 15, anchor = {-20, -30}}}}
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
			bounds = {0, 0, 496, 144},
			viewport = {0, 56, 320, 144}
		},
		children = {
            {
              tag = "mainbg",
              pos = {0, 0, -5},
              gfx = { image="gfx/voodoolady/bg1.png" }
            },
			{
				tag = "bg2",
				children = {
		            {
		              pos = {258, 0, -4},
		              gfx = { image="gfx/voodoolady/bg2.png" }
		            },
					{
					  tag = "voodooladybody",
					  pos = {366, 46, 0},
					  gfx = {model = "voodoolady_body", anim="idle"}				
					},
					{
					  tag="voodoolady",
					  pos = {346, 46, 0},
					  gfx = {model = "voodoolady", anim="idle"}				
					},

				}
			},
	        make_hotspot { 
	            x = 74, 
	            y = 0, 
				z = 1,
	            width = 70, 
	            height = 30, 
	            offset = {0, 0},
	            priority = 1, 
	            object = "baskets",
	            gfx = { model="baskets", anim = "idle" }
	        },
	        make_hotspot { 
	            x = 168, 
	            y = 10, 
				z = 1,
	            width = 20, 
	            height = 20, 
	            offset = {0, 0},
	            priority = 1, 
	            object = "basket",
				scaling = true,
	            gfx = { model="basket", anim = "idle" }
	        },
			{
				walktrigger = {				
			 		shape = { type = "rect", width=64, height=132, offset = {255, 12}},
			 		target = "player",
			 		onenter = gotoLady,
			 		onleave = function() end,
					onstay = function() end,
			 	}
			},
	        {
	            walkarea = { 
	        	tag = "walkarea",
	        	group = 1,
	        	priority = 0,
	        	target = "player",
	        	shape = { 
					type = "poly", 
					outline = {78,37,124,47,146,42,320,42,320,40,320,0,156,0,145,22},
	                holes = {
	                    {164,21,164,7,194,7,194,21}
	                }
				},
	            scaling = {
	                depth = { 
	                    { rect = {0, 320, 0, 144}, dir = "y", bounds = {1, 0} } 
	                },
	                scale = {
	                    { rect = {0, 320, 0, 144}, dir = "y", bounds = {1, 1} } 
	                }
	            }
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
	local fromData = {
        village2 = { playerpos = {77, 36, 0}, anim = "idle_right" },
    }

    -- add player
	local d = fromData[variables._previousroom]
	if (d == nil) then
		d = fromData["village2"]
	end

    table.insert (room.scene[1].children, {
        tag = objects.guybrush.tag,
        pos = d.playerpos,
        gfx = { model = "guybrush", anim = d.anim, flip = d.flip },
        scaling = {}
    })


end

function room.afterstartup() 
	setActive {id="bg2", active=false}
refreshInventory()
end




