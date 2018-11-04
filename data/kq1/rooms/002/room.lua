--require("rooms/002/actions")

local dt=0.1
local d = {
	depth = { 
	    { rect = {0, 316, 0, 166}, dir = "y", bounds = {1, 0} } 
	}
}

room = {
collisionresponse = {
	{ tag = {1, 10}, onenter = enterWaterDie, onleave=exitWater},
	{ tag = {1, 11}, onenter = changeRoom }
},
assets = {
	sprites.graham,
    {
        id = "purple_flag",
        sheet = "gfx/sprites.png",
        type="sprite",
        ppu=1,
        animations = {
        {
       	    name = "default",             
            frames = 
            { 
	    	  	{ duration = dt, quads = { { x = 1, y = 1, width = 24, height = 8, anchor = {0, -1}}}},
                { duration = dt, quads = { { x = 1, y = 11, width = 25, height = 9, anchor = {0, 0}}}},
                { duration = dt, quads = { { x = 1, y = 21, width = 20, height = 9, anchor = {0, 0}}}},
                { duration = dt, quads = { { x = 1, y = 31, width = 22, height = 9, anchor = {0, 0}}}},
				{ duration = dt, quads = { { x = 1, y = 41, width = 22, height = 9, anchor = {0, 0}}}}                              
			}
        }
        }
    },
    {
        id = "yellow_flag",
        sheet = "gfx/sprites.png",
        type="sprite",
        ppu=1,
        animations = {
        {
       	    name = "default",             
            frames = 
            { 
	    	  	{ duration = dt, quads = { { x = 26, y = 1, width = 24, height = 9, anchor = {0, 0}}}},
                { duration = dt, quads = { { x = 26, y = 11, width = 22, height = 9, anchor = {0, 0}}}},
                { duration = dt, quads = { { x = 26, y = 21, width = 22, height = 9, anchor = {0, 0}}}},
                { duration = dt, quads = { { x = 26, y = 31, width = 22, height = 9, anchor = {0, 0}}}},
				{ duration = dt, quads = { { x = 26, y = 41, width = 24, height = 9, anchor = {0, 0}}}}                              
			}
        }
        }
    },
    {
        id = "cyan_flag",
        sheet = "gfx/sprites.png",
        type="sprite",
        ppu=1,
        animations = {
        {
       	    name = "default",             
            frames = 
            { 
	    	  	{ duration = dt, quads = { { x = 51, y = 1, width = 22, height = 9, anchor = {0, 0}}}},
                { duration = dt, quads = { { x = 51, y = 11, width = 22, height = 9, anchor = {0, 0}}}},
                { duration = dt, quads = { { x = 51, y = 21, width = 22, height = 9, anchor = {0, 0}}}},
                { duration = dt, quads = { { x = 51, y = 31, width = 22, height = 9, anchor = {0, 0}}}},
				{ duration = dt, quads = { { x = 52, y = 41, width = 22, height = 9, anchor = {0, 0}}}}                              
			}
        }
        }
    },
    {
        id = "alligator",
        sheet = "gfx/sprites.png",
        type="sprite",
        ppu=1,
        animations = {
        {
       	    name = "default",             
            frames = 
            { 
	    	  	{ duration = dt, quads = { { x = 75, y = 1, width = 26, height = 8, anchor = {12, 0}}}},
                { duration = dt, quads = { { x = 75, y = 11, width = 24, height = 11, anchor = {12, 0}}}},
                { duration = 4*dt, quads = { { x = 75, y = 23, width = 26, height = 4, anchor = {12, 0}}}},
			}
        }
        }
    },
},
scene = {
	makeui(),
	{
		tag = "main",
		camera = {
			tag = "maincam",
			type="ortho",
			size = {316, 166},
			bounds = {0, 0, 316, 166},
			viewport = {2, 25, 318, 25+166}
		},
		children = {
	 		{ pos = {0, 0, -5}, gfx = { image="gfx/bg003.png", width=316, height=166 }},
			makeGraham(20, 10, d),
		}
	},
	{
		tag = "diag",
		camera = {
			tag = "maincam",
			type="ortho",
			size = {320, 200},
			bounds = {0, 0, 320, 200},
			viewport = {0, 0, 320, 200}
		},
		children = 
		{
			{
				luakey = {
					keys = {
						{ key = 61, func = startSwimming },
                        { key = 48, func = displayBox },
						{ key = 257, func = exitpause }
					}
				}
			}
		}
	}
}
}

for i = 1,10 do
    table.insert(room.scene[1].children, { gfx = { shape = { type="line", A={40*i,0}, B={40*i, 200}}, color={255, 255, 255, 255} }})
    table.insert(room.scene[1].children, { gfx = { shape = { type="line", A={0, 40*i}, B={320, 40*i}}, color={255, 255, 255, 255} }})
end

-- end room

function room.init()
end

function room.start()

end

function moveAlligator(name)
	local s = script:new(name)
	local x = math.random(0, 243)
	local y = math.random(0, 5)
	local a = monkey.getEntity(name)
	local flip = false
	if (x < a.x) then
		flip = true
	else
		flip = false
	end
	--print ("Moving alligator to " .. tostring(x) .. ", " .. tostring(y))
	s.actions = {
		[1] = { type ="animate", actor =name, anim="default", flipx = flip },
		[2] = { type = "move", actor=name, to={x, y}, speed=30.0, after={1} },
		[3] = { type = "callfunc", func = curry(moveAlligator, name),after={2}}
	}
	monkey.play(s)
	
end

function room.afterstartup() 
	--moveAlligator("alli1")
	--moveAlligator("alli2")
end



