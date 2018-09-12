local function ciao(x)
end

local function ciao1(x)
end

local function makeShape (arg)
	return {
		pos = arg.pos,
		angle = arg.angle,
		gfx = {shape=arg.shape, color={255,255,255,255} },
		collider= {shape=arg.shape, tag=arg.tag, flag = arg.flag},
	}
end


local function ciao1() 
print ("LEAVE WATER")
end


room = {
collisionresponse = {
	{ tag = {1, 10}, onenter = enterWater, onleave=ciao1}
},
assets = {
	sprites.graham
},
scene = {
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
		{
			pos = {0, 0, -5},
			gfx = { image="gfx/bg001.png", width=316, height=166 }
		},
		makeShape { pos = {265, 39, 0}, angle = 0, tag=2, flag=2, shape = {type="rect", width=17, height=7, offset={0, 0}} },
		makeShape { pos = {0, 23, 0}, angle = 0, tag=2, flag=2, shape = {type="line", A={0,0},B={179,0}}, offset={0, 0} },
		makeShape { pos = {50, 0, 0}, angle=0, tag = 10, flag = 4, shape = {type="rect", width = 20, height=10 }},
		{
			--gfx = {shape={type="rect", width=20, height=10}, color={255,255,255,255} },
			tag = "graham", 
			gfx = { model="graham", anim="idle_right"},
			collider= {shape={type="rect", width=1, height=1}, tag=1, flag=1},
			keyboardcontrollercollision = { 
				width = 1, 
                height = 1, 
                speed = 1, 
                horizontal_rays = 2, 
                vertical_rays = 2 
            }
	    }, 
		{
			--gfx = {shape={type="rect", width=20, height=10}, color={255,255,255,255} },
			tag = "drowning_graham", 
			active = false,
			gfx = { model="graham", anim="drown"},
			collider= {shape={type="rect", width=1, height=1}, tag=1, flag=1},
			--keyboardcontrollercollision = { width = 1, height = 1, speed = 1, horizontal_rays = 2, vertical_rays = 2 }
	    }, 
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
						{ key = 61, func = startSwimming }
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

function room.afterstartup() 
	local a = monkey.getEntity("drowning_graham")
	a:setactive(false)
end



