local function ciao(x)
end

local function ciao1(x)
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
			pos = {2, 25, -5},
			gfx = { image="gfx/bg001.png", width=316, height=166 }
		},
		{
			gfx = {shape={type="rect", width=20, height=10}, color={255,255,255,255} },
			collider= {shape={type="rect", width=20, height=10}, tag=1, flag=1},
			keyboardcontroller={}
	    }, 
		}
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



