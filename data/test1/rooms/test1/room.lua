room = {

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
			collider= {shape={type="rect", width=20, height=10}},
			keyboardcontroller={}
	    }, 
		{
			pos = {80, 80, 0},
			angle = 30,
			collider= {shape={type="rect", width=30, height=10, offset={-15,-5}}},
	    }
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



