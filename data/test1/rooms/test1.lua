
room = {
engines = { 
    { type = "scheduler" }
},
scene = {
	{
				tag = "main",
				camera = {
					tag = "maincam",
					type="ortho",
					size = {800, 600},
					bounds = {0, 0, 800, 600},
					viewport = {0, 0, 800, 600}
				},
				children = {
					{
					tag = "ciao",
					pos={400,300,0},
					components = {
						{ type="gfx", shape = { type="rect", width=300, height=30, offset={-150,-15}}, color={255,0,0,255}}
				    },
				    children = {
				        {
							pos={140,0,0},
							angle = 30,
							components = {
								{ type="gfx", shape = { type="rect", width=60, height=30, offset={-30,-15}}, color={255,0,0,255}}
					    	}
					    },
					    {
							pos={-140,0,0},
							angle = -30,
							components = {
								{ type="gfx", shape = { type="rect", width=60, height=30, offset={-30,-15}}, color={255,0,0,255}}
					    	}
					    }
					}
					}
				}
}}}


function room.afterstartup() 
local s = script:new()
s.actions = {
	{ id=1,after={0},action = {type="rotate", speed=100, deg = 700000, actor="ciao"}}
}
monkey.play(s)
end
					-- factory.player.create { 
					-- 	pos= startPos.pos, 
					-- 	model="guybrush", 
					-- 	facing = startPos.facing, 
					-- 	scroll = (room_width > 320 and enableScroll),
					-- 	depth = args.depth,
					-- 	scale = args.scale,
					-- 	collide = args.collide
					-- }
				

