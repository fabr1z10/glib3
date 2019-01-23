local dt = 0.2

local quads = {
	troll_body = { x=1, y=2, width=36, height=32, anchor={13, 0} },
	troll_head = { x=38, y=2, width=21, height=15, anchor={11, 0} },
	troll_talk_1 = { x=62, y=2, width=21, height=16, anchor={11, 1} },
	troll_talk_2 = { x=86, y=2, width=21, height=16, anchor={11, 1} },
	troll_talk_3 = { x=40, y=19, width=21, height=17, anchor={11, 2} },
	troll_talk_4 = { x=67, y=19, width=21, height=16, anchor={11, 0} },


}

local f = function(args) 
	local q = {}
	q.x = args.quad.x 
	q.y = args.quad.y
	q.width = args.quad.width 
	q.height = args.quad.height
	q.anchor = {}
	q.anchor[1] = args.quad.anchor[1]
	q.anchor[2] = args.quad.anchor[2]

	
	-- update anchor with pos
	local pos = args.pos or {0, 0}
	q.anchor[1] = q.anchor[1] - pos[1]
	q.anchor[2] = q.anchor[2] - pos[2]
	return (q)

end

sprites["bridge.troll"] = {
    id="bridge.troll",
    sheet="gfx/troll.png",
	type="sprite",
    ppu=1,
    animations = {
		{
	   		name = "idle",             
	        frames = { 
	 	    	{
					duration = dt,
	                quads = {
	                   	f{quad = quads.troll_body},
                        f{quad = quads.troll_head, pos = {8,26}}
					}
	            }
			}
		},
		{
	   		name = "talk",             
	        frames = { 
	 	    	{
					duration = dt,
	                quads = {
	                   	f{quad = quads.troll_body},
                        f{quad = quads.troll_talk_1, pos = {8,26}}
					}
	            },
	 	    	{
					duration = dt,
	                quads = {
	                   	f{quad = quads.troll_body},
                        f{quad = quads.troll_talk_2, pos = {8,26}}
					}
	            },
	 	    	{
					duration = dt,
	                quads = {
	                   	f{quad = quads.troll_body},
                        f{quad = quads.troll_talk_1, pos = {8,26}}
					}
	            },
	 	    	{
					duration = dt,
	                quads = {
	                   	f{quad = quads.troll_body},
                        f{quad = quads.troll_talk_3, pos = {8,26}}
					}
	            },
	 	    	{
					duration = dt,
	                quads = {
	                   	f{quad = quads.troll_body},
                        f{quad = quads.troll_talk_4, pos = {8,26}}
					}
	            }
			}
		},

	}
}

