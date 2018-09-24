local function ciao(x)
	x:setcolor(255,0,0,255)
end
local function ciao1(x)
	x:setcolor(255,255,255,255)
end

local function makeShape (arg)
	return {
		pos = arg.pos,
		angle = arg.angle,
		gfx = {shape=arg.shape, color={255,255,255,255} },
		collider= {shape=arg.shape, tag=2},
	}
end

room = {
collisionresponse = {
	{ tag = {1,2}, onenter = ciao, onleave=ciao1}
},
assets = {},
scene = {
	{
		tag = "main",
		camera = {
			tag = "maincam",
			type="ortho",
			size = {320, 200},
			bounds = {0, 0, 320, 200},
			viewport = {0, 0, 320, 200}
		},
		children = {
		{
			gfx = {shape={type="rect", width=20, height=10}, color={255,255,255,255} },
			collider= {shape={type="rect", width=20, height=10}, tag=1},
			keystatemachine = {
				initialstate = "walk",
				states = {
					{ id = "walk", type="walk", speed = 10 }
				}
			
			}
	    }, 
	    makeShape { pos = {80, 80, 0}, angle = 30, shape = {type="rect", width=30, height=10, offset={-15,-5}} },
	    makeShape { pos = {130, 90, 0}, angle=45, shape = {type="line", A={0,0}, B={30,0}}},
	    makeShape { pos = {170, 90, 0}, shape = {type="poly", outline = {0, 0, 10, 20, 20, 0}}},
		makeShape { pos = {100, 140, 0}, shape = {type="circle", radius = 10}},
		{
			pos = {150, 140, 0},
			angle =10,
			gfx = { shape = { type = "poly", outline = {0,0,0,50,10,50,10,30,40,30,40,50,50,50,50,0,40,0,40,20,10,20,10,0}}, color={255,255,255,255}},
			collider = { tag =2, shape = {type="compound", shapes = {
				{ type = "rect", width = 10, height = 50 },
				{ type = "rect", width = 30, height = 10, offset={10, 20} },
				{ type = "rect", width = 10, height = 50, offset={40, 0} },
			}}}
		}
		}
		-- {
		-- 	pos = {80, 80, 0},
		-- 	angle = 30,
		-- 	gfx = {shape=, color={255,255,255,255} },
		-- 	collider= {shape={type="rect", width=30, height=10, offset={-15,-5}}, tag = 2},
	 --    }
		
	},
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
end



