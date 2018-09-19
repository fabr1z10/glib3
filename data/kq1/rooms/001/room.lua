
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

local function exitpause() 
	if (variables.pause == true) then
	    local parent = monkey.getEntity("main")
		monkey.removeEntity("msg")
		parent:enableupdate(true)
		monkey.enablescriptengine(true) 
		variables.pause = false
	end

end

local function displayBox()
    local parent = monkey.getEntity("main")

    monkey.addEntity ({
		tag = "msg",
		children = {
			{
				tag ="msgtext",
				pos={158, 83, 1},
				text = {
					id="012 0011 12 22110 0122 020 0200 121",
					align = "center",
					font="ui",
					size=7,
					maxwidth = 160,
					color = {0,0,0,255}
				}
			}
		}
	}, parent)
	local m  = monkey.getEntity("msg")
	local mm  = monkey.getEntity("msgtext")
    local a = mm:gettextinfo()
	print ("width = " .. a.width)
	print ("height = " .. a.height)
	local paddingOuter = {10, 6}
	local paddingInner = {6, 4}
	monkey.addEntity ({
		pos={158 - a.width * 0.5 - paddingOuter[1], 83-a.height*0.5-paddingOuter[2], 0.5},
		gfx = {
			shape = {
				type ="rect",
				width = a.width + 2*paddingOuter[1],
				height = a.height + 2*paddingOuter[2]
			},
			draw = "solid",
			color = {255,255,255,255}
		}
	}, m)
	monkey.addEntity ({
		pos={158 - a.width * 0.5 - paddingInner[1], 83-a.height*0.5-paddingInner[2], 0.7},
		gfx = {
			shape = {
				type ="rect",
				width = a.width + 2*paddingInner[1],
				height = a.height + 2*paddingInner[2]
			},
			draw = "solid",
			color = {255,255,255,255}
		}
	}, m)
	monkey.addEntity ({
		pos={158 - a.width * 0.5 - paddingInner[1] - 2, 83-a.height*0.5-paddingInner[2]-1, 0.7},
		gfx = {
			shape = {
				type ="rect",
				width = a.width + 2*paddingInner[1] + 4,
				height = a.height + 2*paddingInner[2]+2,
			},
			draw = "solid",
			color = {170,0,0,255}
		}
	}, m)
	-- monkey.addEntity ({
	-- 	pos={158 - a.width * 0.5 - paddingInner[1] - 2, 83-a.height*0.5-paddingInner[2]-1, 0.6},
	-- 	gfx = {
	-- 		shape = {
	-- 			type ="rect",
	-- 			width = a.width + 2*paddingInner[1]+4,
	-- 			height = a.height + 2*paddingInner[2]+2,
	-- 		},
	-- 		draw = "solid",
	-- 		color = {170,0,0,255}
	-- 	}
	-- }, m)
	parent:enableupdate(false)
	variables.pause = true
	monkey.enablescriptengine(false)
end

room = {
collisionresponse = {
	{ tag = {1, 10}, onenter = enterWater, onleave=exitWater}
},
assets = {
	sprites.graham
},
scene = {
	{
		tag = "ui",
		camera = {
			tag = "maincam",
			type="ortho",
			size = {320, 24},
			bounds = {0, 0, 320, 24},
			viewport = {0, 0, 320, 24}
		},
		children = {
			{
				pos={0,16,0},
				text = {
					id="_",
					font="ui",
					size=8,
					align ="bottomleft"
				},
				keyinput = {
					maxlength = 10,
					func = function(msg) print (msg) end
				}
				
			}
		}
	},
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
		makeShape { pos = {50, 0, 0}, angle=0, tag = 10, flag = 4, shape = {type="rect", width = 100, height=10 }},
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
                vertical_rays = 2,
				anims = {
					{ id = "walk_right", anim = "walk_right" },
					{ id = "walk_front", anim = "walk_front" },
					{ id = "walk_back", anim = "walk_back" },
					{ id = "idle_right", anim = "idle_right" },
					{ id = "idle_front", anim = "idle_front"},
					{ id= "idle_back", anim = "idle_back"}
				} 
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
		{
			--gfx = {shape={type="rect", width=20, height=10}, color={255,255,255,255} },
			tag = "swimming_graham", 
			gfx = { model="graham", anim="swim_right"},
			collider= {shape={type="rect", width=1, height=1}, tag=1, flag=1},
			keyboardcontrollercollision = { 
				width = 1, 
                height = 1, 
                speed = 1, 
                horizontal_rays = 2, 
                vertical_rays = 2,
				anims = {
					{ id = "walk_right", anim = "swim_right" },
					{ id = "walk_front", anim = "swim_front" },
					{ id = "walk_back", anim = "swim_right" },
					{ id = "idle_right", anim = "swim_right" },
					{ id = "idle_front", anim = "swim_front"},
					{ id= "idle_back", anim = "swim_back"}
				} 

            }
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

function room.afterstartup() 
	local a = monkey.getEntity("drowning_graham")
	a:setactive(false)
	local b = monkey.getEntity("swimming_graham")
	b:setactive(false)
end



