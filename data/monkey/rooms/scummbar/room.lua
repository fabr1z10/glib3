local dt = 0.1

-- set player start position
local startPositionTable = {
    village1 = { pos = {66, 19, 0}, anim = "idle_right" },
	kitchen = { pos = {601, 16, 0}, anim = "idle_right", flip = true},
	loom = {pos = {239, 15, 0}, anim ="idle_right", flip = false },
	estevan = {pos = {200, 10, 0}, anim= "idle_front", flip=false},
	mancomb = {pos = {123, 17, 0}, anim= "idle_back", flip=false},
 	default = { pos = {66, 19, 0}, anim = "idle_right" },
}

local startPosition = startPositionTable[variables._previousroom]
if (startPosition == nil) then
	startPosition = startPositionTable.default
end

-- begin room
room = {

engines = {
	{ type = "hotspotmanager" },
	{ type = "scheduler" }
},

assets = {
    makeGuybrush(),
    makeArrowUp(),
    makeArrowDown(),
    makeCook(),
    {
        id = "door_out",
        sheet = "gfx/anims2.png",
        type="sprite",
        ppu=1,
        animations = {
        { name = "close", frames = { {duration = dt, quads = { { x = 2, y = 243, width = 38, height = 47, anchor = {0, 0}}}}}},
        { name = "open", frames = { {duration = dt, quads = { { x = 2, y = 195, width = 38, height = 47, anchor = {0, 0}}}}}}
        }
    },
    {
        id = "door_kitchen",
        sheet = "gfx/anims2.png",
        type="sprite",
        ppu=1,
        animations = {
        { name = "close", frames = { {duration = dt, quads = { { x = 44, y = 199, width = 35, height = 69, anchor = {0, 0}}}}}},
        { name = "open", frames = { {duration = dt, quads = { { x = 44, y = 270, width = 35, height = 69, anchor = {0, 0}}}}}}
        }
    },
    {
        id = "fireplace",
        sheet = "gfx/anims.png",
        type="sprite",
        ppu=1,
        animations = {
        { name = "default", frames = { 
			{duration = dt, quads = { { x = 262, y = 280, width = 32, height = 26, anchor = {0, 0}}}},
			{duration = dt, quads = { { x = 296, y = 280, width = 32, height = 26, anchor = {0, 0}}}},
			{duration = dt, quads = { { x = 330, y = 280, width = 32, height = 26, anchor = {0, 0}}}},

			}
		}}
    },
    {
        id = "ilp1",
        sheet = "gfx/anims.png",
        type="sprite",
        ppu=1,
        animations = {
        { name = "idle", frames = { 
			{duration = dt*5, quads = { { x = 220, y = 336, width = 35, height = 55, anchor = {0, 0}}}},
			{duration = dt*5, quads = { { x = 257, y = 336, width = 35, height = 55, anchor = {0, 0}}}},
			{duration = dt, quads = { { x = 183, y = 336, width = 35, height = 55, anchor = {0, 0}}}},
			{duration = dt, quads = { { x = 295, y = 335, width = 35, height = 56, anchor = {0, 0}}}},
			{duration = dt, quads = { { x = 183, y = 336, width = 35, height = 55, anchor = {0, 0}}}},
			}
		},
        { name = "talk", frames = { 
			{duration = dt, quads = { { x = 365, y = 341, width = 35, height = 56, anchor = {0, 0}}}},
			{duration = dt, quads = { { x = 402, y = 343, width = 35, height = 54, anchor = {0, 0}}}},
			}
		},
		}
    },
    {
        id = "ilp2",
        sheet = "gfx/anims.png",
        type="sprite",
        ppu=1,
        animations = {
        { name = "idle", frames = { 
			{duration = dt*4, quads = { { x = 257, y = 393, width = 35, height = 53, anchor = {1, 0}}}},
			{duration = dt, quads = { { x = 294, y = 393, width = 34, height = 53, anchor = {1, 0}}}},
			{duration = dt*4, quads = { { x = 330, y = 393, width = 34, height = 53, anchor = {0, 0}}}},
			{duration = dt, quads = { { x = 294, y = 393, width = 34, height = 53, anchor = {0, 0}}}},
			}
		},
        { name = "talk", frames = { 
			{duration = dt, quads = { { x = 439, y = 341, width = 34, height = 56, anchor = {0, 0}}}},
			{duration = dt, quads = { { x = 475, y = 345, width = 35, height = 52, anchor = {1, 0}}}},
			}
		},

		}
    },
    {
        id = "ilp3",
        sheet = "gfx/anims.png",
        type="sprite",
        ppu=1,
        animations = {
        { name = "idle", frames = { 
			{duration = dt*4, quads = { { x = 183, y = 393, width = 35, height = 52, anchor = {0, 0}}}},
			{duration = dt*4, quads = { { x = 220, y = 393, width = 35, height = 52, anchor = {0, 0}}}},
			}
		},
        { name = "talk", frames = { 
			{duration = dt, quads = { { x = 366, y = 399, width = 31, height = 52, anchor = {0, 0}}}},
			{duration = dt, quads = { { x = 399, y = 400, width = 32, height = 51, anchor = {0, 0}}}},
            {duration = dt, quads = { { x = 433, y = 399, width = 31, height = 52, anchor = {0, 0}}}},
			}
		},
        }
    },
	{
		id = "dog",
		sheet = "gfx/anims3.png",
        type="sprite",
        ppu=1,
        animations = {
        { name = "idle1", frames = { 
			{duration = dt, quads = { { x = 71, y = 187, width = 16, height = 14, anchor = {0, 0}}}},
			}
		},
        { name = "idle2", frames = { 
			{duration = dt, quads = { { x = 74, y = 219, width = 19, height = 14, anchor = {3, 0}}}},
			}
		},
        { name = "move", frames = { 
			{duration = dt, quads = { { x = 70, y = 203, width = 18, height = 14, anchor = {2, 0}}}},
			}
		},
        }
	},
	{
		id = "fatpirate",
		sheet = "gfx/anims3.png",
        type="sprite",
        ppu=1,
        animations = {
        { name = "idle", frames = { 
			{duration = dt, quads = { { x = 286, y = 1, width = 30, height = 33, anchor = {0, 0}}}},
			}
		},
        { name = "drink", frames = { 
			{duration = dt, quads = { { x = 317, y = 1, width = 30, height = 35, anchor = {0, 0}}}},
			{duration = dt, quads = { { x = 349, y = 1, width = 30, height = 39, anchor = {0, 0}}}},
			{duration = dt, quads = { { x = 317, y = 1, width = 30, height = 35, anchor = {0, 0}}}},
			}
		},
        }
	},
	{
		id = "estevan",
		sheet = "gfx/anims.png",
        type="sprite",
        ppu=1,
        animations = {
        { name = "idle", frames = { 
			{duration = dt, quads = { { x = 183, y = 455, width = 35, height = 27, anchor = {0, 0}}}},
			}
		},
        { name = "drink", frames = { 
			{duration = dt, quads = { { x = 220, y = 455, width = 39, height = 27, anchor = {0, 0}}}},
			{duration = dt, quads = { { x = 261, y = 455, width = 37, height = 27, anchor = {0, 0}}}},
			{duration = dt, quads = { { x = 220, y = 455, width = 39, height = 27, anchor = {0, 0}}}},
			}
		},
        }
	},
	{
		id = "mancomb",
		sheet = "gfx/anims.png",
        type="sprite",
        ppu=1,
        animations = {
        { name = "idle", frames = { 
			{duration = dt, quads = { { x = 6, y = 405, width = 33, height = 40, anchor = {0, 0}}}},
			}
		},
        { name = "drink", frames = { 
			{duration = dt*2, quads = { { x = 3, y = 446, width = 36, height = 40, anchor = {0, 0}}}},
			}
		},
        }
	},
	{
		id = "loompirate",
		sheet = "gfx/anims.png",
        type="sprite",
        ppu=1,
        animations = {
        { name = "idle1", frames = { 
			{duration = dt, quads = { { x = 352, y = 473, width = 29, height = 38, anchor = {0, 0}}}},
			}
		},
        { name = "idle2", frames = { 
			{duration = dt, quads = { { x = 414, y = 474, width = 29, height = 37, anchor = {0, 0}}}},
			}
		},
        { name = "move", frames = { 
			{duration = dt, quads = { { x = 383, y = 474, width = 29, height = 37, anchor = {0, 0}}}},
			}
		},
        }
	},
	{
		id = "piratewoman",
		sheet = "gfx/anims.png",
        type="sprite",
        ppu=1,
        animations = {
        { name = "idle1", frames = { 
			{duration = dt, quads = { { x = 469, y = 454, width = 20, height = 21, anchor = {0, 0}}}},
			}
		},
        { name = "idle2", frames = { 
			{duration = dt, quads = { { x = 446, y = 454, width = 20, height = 21, anchor = {0, 0}}}},
			}
		},
        { name = "move", frames = { 
			{duration = dt, quads = { { x = 491, y = 454, width = 20, height = 21, anchor = {0, 0}}}},
			}
		},
        }
	},
	{
		id = "piratecouple",
		sheet = "gfx/anims.png",
        type="sprite",
        ppu=1,
        animations = {
        { name = "idle1", frames = { 
			{duration = dt, quads = { { x = 183, y = 484, width = 35, height = 28, anchor = {0, 1}}}},
			}
		},
        { name = "idle2", frames = { 
			{duration = dt, quads = { { x = 257, y = 485, width = 35, height = 26, anchor = {0, 0}}}},
			}
		},
        { name = "move", frames = { 
			{duration = dt, quads = { { x = 220, y = 484, width = 35, height = 27, anchor = {0, 0}}}},
			}
		},
        }
	},
	{
		id = "pirate1",
		sheet = "gfx/anims.png",
        type="sprite",
        ppu=1,
        animations = {
        { name = "idle", frames = { 
			{duration = dt, quads = { { x = 297, y = 485, width = 50, height = 26, anchor = {0, 1}}}},
			}
		},
        }
	},
	{
		id = "pirate2",
		sheet = "gfx/anims.png",
        type="sprite",
        ppu=1,
        animations = {
        { name = "idle1", frames = { 
			{duration = dt, quads = { { x = 380, y = 167, width = 36, height = 37, anchor = {0, 0}}}},
			}
		},
        { name = "idle2", frames = { 
			{duration = dt, quads = { { x = 418, y = 167, width = 36, height = 37, anchor = {0, 0}}}},
			}
		},
        { name = "move", frames = { 
			{duration = dt, quads = { { x = 418, y = 167, width = 36, height = 37, anchor = {0, 0}}}},
			}
		},
        }
	},
	{
		id = "pirate3",
		sheet = "gfx/anims.png",
        type="sprite",
        ppu=1,
        animations = {
        { name = "idle1", frames = { 
			{duration = dt, quads = { { x = 42, y = 470, width = 26, height = 27, anchor = {0, 0}}}},
			}
		},
        { name = "idle2", frames = { 
			{duration = dt, quads = { { x = 99, y = 470, width = 26, height = 27, anchor = {0, 0}}}},
			}
		},
        { name = "move", frames = { 
			{duration = dt, quads = { { x = 70, y = 470, width = 26, height = 27, anchor = {0, 0}}}},
			}
		},
        }
	},
	{
		id = "sleepypirate1",
		sheet = "gfx/anims.png",
        type="sprite",
        ppu=1,
        animations = {
        { name = "idle", frames = { 
			{duration = dt, quads = { { x = 41, y = 418, width = 33, height = 25, anchor = {0, 0}}}},
			}
		},
        { name = "drink", frames = { 
			{duration = dt, quads = { { x = 76, y = 418, width = 33, height = 25, anchor = {0, 0}}}},
			{duration = dt, quads = { { x = 111, y = 418, width = 33, height = 25, anchor = {0, 0}}}},
			{duration = dt, quads = { { x = 76, y = 418, width = 33, height = 25, anchor = {0, 0}}}},
			}
		},
        }
	},
	{
		id = "sleepypirate2",
		sheet = "gfx/anims.png",
        type="sprite",
        ppu=1,
        animations = {
        { name = "idle", frames = { 
			{duration = dt, quads = { { x = 41, y = 445, width = 40, height = 23, anchor = {0, 0}}}},
			}
		},
        { name = "drink", frames = { 
			{duration = dt*2, quads = { { x = 83, y = 445, width = 40, height = 23, anchor = {0, 0}}}},
			}
		},
        }
	},
},

scene = {
	{
		tag = "main",
		camera = {
			tag = "maincam",
			type="ortho",
			size = {320, 144},
			bounds = {0, 0, 640, 144},
			viewport = {0, 56, 320, 144}
		},
		children = {
			{
		    	pos = {0, 0, -5},
          		gfx = { image="gfx/scummbar/bg1.png", width=640, height=144 },
        	},
	        {
	            pos = {374, 20, 0.95},
	            gfx = { image="gfx/scummbar/bg2.png" },
	        },
	        {
	            pos = {157, 0, 1},
	            gfx = { image="gfx/scummbar/bg3.png" },
	        },
	        {
	            pos = {20, 0, 1},
	            gfx = { image="gfx/scummbar/bg4.png" },
	        },
			makePlayer(startPosition, true),
	        {
	          walkarea = { 
	            tag = "walkarea",
	            group = 1,
	            priority = 0,
	            target = "player",
	            shape = { 
	                type = "poly", 
	                outline = {32,16,70,24,128,19,251,18,311,10,321,10,345,32,467,41,492,50,514,40,565,40,580,35,629,6,626,0,256,0,200,16,149,0,90,0,85,10},
	                 holes = {
	               
	                    {374,6,505,6,505,28,374,28}
	                }
	            },
	            scaling = {
	                depth = { 
	                    { rect = {0, 640, 0, 144}, dir = "y", bounds = {1, 0} } 
	                },
	                scale = {
	                    { rect = {0, 640, 0, 144}, dir = "y", bounds = {1, 1} } 
	                }
	            }
	          }
	        },
	        make_hotspot { 
	            x = 32, 
	            y = 25, 
	            width = 38, 
	            height = 47, 
	            offset = {0, 0},
	            priority = 1, 
	            object = "scummbar_door_out",
	            gfx = { model="door_out", anim = ((objects.scummbar_door_out.isopen() == true) and "open" or "close") }
	        },
	        make_hotspot { 
	            x = 591, 
	            y = 9, 
	            width = 35, 
	            height = 69, 
	            offset = {0, 0},
	            priority = 1, 
	            object = "door_bar_kitchen",
	            gfx = { model="door_kitchen", anim = ((objects.door_bar_kitchen.isopen() == true) and "open" or "close") }
	        },
			make_hotspot {
				x = 509,
				y = 44,
				width = 29,
				height = 18,
				offset = {0, 0},
				priority = 1,
				object = "fireplace",
				gfx = { model="fireplace", anim="default" }
			},
			{
				tag ="ilp1",
				pos = {376,11,0.95},
				gfx = {model = "ilp1", anim="idle"}
			},
			{
				tag ="ilp2",
				pos = {413,11,0.95},
				gfx = {model = "ilp2", anim="idle"}
			},
			{
				tag = "ilp3",
				pos = {444,18,0.95},
				gfx = {model = "ilp3", anim="idle"}
			},
			make_hotspot {
				x = 393,
				y = 34,
				width = 80,
				height = 18,
				offset = {0, 0},
				priority = 1,
				object = "ilp"
			},
	        make_hotspot { 
	            x = 300, 
	            y = 15, 
	            width = 15, 
	            height = 15, 
	            offset = {0, 0},
	            priority = 1, 
	            object = "dog",
	            gfx = { model="dog", anim = "idle1" }
	        },
			{
				tag = "fatpirate",
				pos = {289, 36, 0.5},
				gfx = {model = "fatpirate", anim="idle"}
			},
			{
				tag = "piratewoman",
				pos = {260, 42, -1},
				gfx = {model = "piratewoman", anim="idle1"}
			},
			{
				tag = "piratecouple",
				pos = {212, 19, 1},
				gfx = {model = "piratecouple", anim="idle1"}
			},
			{
				pos = {173, 0, 1.01},
				gfx = {model = "pirate1", anim="idle"}
			},
			{
				tag="pirate2",
				pos = {126, 17, 0},
				gfx = {model = "pirate2", anim="idle1"}
			},
			{
				tag="pirate3",
				pos = {138, 38, -0.1},
				gfx = {model = "pirate3", anim="idle1"}
			},
			{
				tag ="sleepypirate1",
				pos = {0, 0, 1.01},
				gfx = {model = "sleepypirate1", anim="idle"}
			},
			{
				tag ="sleepypirate2",
				pos = {38, 0, 1.01},
				gfx = {model = "sleepypirate2", anim="idle"}
			},
	        make_hotspot { 
	            x = 260, 
	            y = 17, 
	            width = 20, 
	            height = 20, 
	            offset = {0, 0},
	            priority = 1, 
	            object = "loom_pirate",
	            gfx = { model="loompirate", anim = "idle1" }
	        },
	        make_hotspot { 
	            x = 164, 
	            y = 21, 
                z = 1,
	            width = 30, 
	            height = 20, 
	            offset = {0, 0},
	            priority = 1, 
	            object = "estevan",
	            gfx = { model="estevan", anim = "idle" }
	        },
	        make_hotspot { 
	            x = 89, 
	            y = 24, 
	            width = 30, 
	            height = 30, 
	            offset = {0, 0},
	            priority = 1, 
	            object = "mancomb",
	            gfx = { model="mancomb", anim = "idle" }
	        },
	        make_hotspot { 
	            x = 136, 
	            y = 32, 
	            width = 30, 
	            height = 20, 
	            offset = {0, 0},
	            priority = 1, 
	            object = "pirates_listening"
	        },
	        make_hotspot { 
	            x = 0, 
	            y = 0, 
	            width = 40, 
	            height = 20, 
	            offset = {0, 0},
	            priority = 1, 
	            object = "sleeping_pirate"
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
    -- put your initialization code here
    variables._actionInfo:reset()


end

function room.afterstartup() 
refreshInventory()
end

function runBackgroundScript(name)
	
	local s = script:new("_" .. name)
    s.actions = {
   		[1] = { type = "delay", sec = 2.0 },
		[2] = { type = "animate", actor = name, anim="move", loop=1, after={1} },
		[3] = { type = "animate", actor = name, anim="idle2", after={2} },
		[4] = { type = "delay", sec = 2.0, after={3} },
		[5] = { type = "animate", actor =name, anim="move", loop=1, after={4} },
		[6] = { type = "animate", actor =name, anim="idle1", after={5} }	
	}
	--s:setsequence()
	s.loop = 1
	monkey.play(s)
	
end

function runBackgroundScript2(name)
	local s = script:new("_" .. name)
    s.actions = {
        [1] = { type = "delay", sec = 2.0 },
		[2] = { type = "animate", actor = name, anim="drink", loop=1, after={1} },
		[3] = { type = "animate", actor = name, anim="idle", after={2} },
	}
	--s:setsequence()
	s.loop = 1
	monkey.play(s)

end

function room.start() 
    --cook script
	runBackgroundScript("dog")
	runBackgroundScript("loompirate")
	runBackgroundScript("piratewoman")
	runBackgroundScript("piratecouple")
	runBackgroundScript("pirate2")
	runBackgroundScript("pirate3")
	-- fat pirate
	runBackgroundScript2("fatpirate")
	runBackgroundScript2("estevan")
	runBackgroundScript2("mancomb")
	runBackgroundScript2("sleepypirate1")
	runBackgroundScript2("sleepypirate2")

 	local s = script:new("_cook")
	local n = 0
	if (variables._previousroom == "kitchen") then
		local c1 = script:new()
		c1.actions = {
			[1] = { type = "callfunc", func = curry (createObject, { 
				pos = {100, 20, 0},
				gfx = { model = "cook", anim = "idle_back" },
				scaling = {},
				tag = "cook"
			})},
			[2] = { type = "delay", sec = 3.0, after = {1} },
			[3] = { type = "walkto", walkarea = "walkarea", actor = "cook", pos = {607, 20}, after={2} },
			[4] = { type = "delay", sec = 0.5, after ={3} },
			[5] = { type = "animate", actor ="door_bar_kitchen", anim="close", after={4} },
			[6] = { type = "callfunc", after={5}, func = function() objects.door_bar_kitchen.setopen(false) end },
			[7] = { type = "callfunc", after={6}, func = curry(removeObject, "cook") }
		}
		s:push {script = c1, at="end" }
	end
	 	local c = script:new()
	 	c.actions = {
	 		[1] = { type = "delay", sec = 5.0 },
			[2] = { type = "animate", actor ="door_bar_kitchen", anim="open", after={1} },
			[3] = { type = "callfunc", func = function() objects.door_bar_kitchen.setopen(true) end, after={2} },
 			[4] = { type = "callfunc", after={3}, func = curry (createObject, { 
 				pos = {607, 20, 0},
 				gfx = { model = "cook", anim = "idle_back" },
 				scaling = {},
 				tag = "cook"
 			})},
 			[5] = {
 				type = "walkto",
 				walkarea = "walkarea",
 				actor = "cook",
				pos = {100, 20},
				after = {4}
 			},
 			[6] = { type ="turn", actor="cook", face="north", after={5} },
 			[7] = { type = "delay", sec = 3.0, after={6} },
 			[8] = {
				type = "walkto",
 				walkarea = "walkarea",
 				actor = "cook",
				pos = {607, 20},
				after= {7}
			},
			[9] = { type = "delay", sec = 0.5, after={8} },
			[10] = { type = "animate", actor ="door_bar_kitchen", anim="close", after={9} },
			[11] = { type = "callfunc", after={10}, func = function() objects.door_bar_kitchen.setopen(false) end },
			[12] = { type = "callfunc", after={11}, func = curry(removeObject, "cook") }
		}
	s:push { script = c, at ="end", id="main" }
	s.loop = s:getid("main", 1)
	print ("Set loop at = " .. s.loop)
	

	monkey.play(s)
end

