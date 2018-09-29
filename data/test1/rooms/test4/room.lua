--require("rooms/001/actions")

local dt=0.1
local d = {
	depth = { 
	    type = "linear_y", values = {0, 1, 400, 0}
	}
}

local function computeDepth(y) 
	return 1 - y/400
end

local startPositionTable = {
	['start'] = {212, 77}
}

hitfunc = {}


hitfunc["head"] = function(info, pp)
	main = monkey.getEntity("main")
	player = monkey.getEntity("player")
	flip = player.flipx and 1 or -1
	local b = nextTag()
	local b1 = nextTag()
	print ("Adding object with tag " .. b)
    monkey.addEntity ({
		pos = {pp.x, pp.y, 0},
		depth = d,
		gfx = { model = info.spriteid, anim = "body"},
		tag = b
	}, main)
	-- adding fx
    monkey.addEntity ({
		pos = {pp.x + info.offset[1], pp.y + info.offset[2], 0},
		depth = d,
		gfx = { model = "expl1", anim = "default", scale = info.scale},
		tag = b1
	}, main)
 	local s = script:new("_cook")
	s.actions ={
		[1] = {type="noop"},
		[2] = { type="rotate", speed = flip * 60, acceleration = flip * 200, deg = flip*90, actor = b, after={1} },
		[3] = { type="animate", actor=b1, anim="default", loop = 1, after={1}},
		[4] = { type="animate", actor=b1, anim="stop", after={3}},
		[5] = { type ="movegravity", actor=b1, velocity={0,-100}, g=100, ystop = pp.y, after={1}}
	}	
	monkey.play(s)
end

hitfunc["body"] = function()
	main = monkey.getEntity("main")
	player = monkey.getEntity("player")
	flip = player.flipx and 1 or -1
	local tagHead = nextTag()
	local tagLegs = nextTag()
local b1 = nextTag()
    monkey.addEntity ({
		pos = {pp.x + info.headx, pp.y + info.heady, 0},
		depth = d,
		gfx = { model = info.spriteid, anim = "head"},
		tag = tagHead
	}, main)
    monkey.addEntity ({
		pos = {pp.x, pp.y, 0},
		depth = d,
		gfx = { model = info.spriteid, anim = "legs"},
		tag = tagLegs
	}, main)
	-- adding fx
    monkey.addEntity ({
		pos = {pp.x + info.offset[1], pp.y + info.offset[2], 0},
		depth = d,
		gfx = { model = "expl1", anim = "default", scale = info.scale},
		tag = b1
	}, main)
 	local s = script:new("_cook")
	s.actions ={
		[1] = {type="noop"},
		[2] = { type="rotate", speed = flip * 60, acceleration = flip * 200, deg = flip*90, actor = tagLegs, after={1} },
		[3] = { type="animate", actor=b1, anim="default", loop = 1, after={1}},
		[4] = { type="animate", actor=b1, anim="stop", after={3}},
		[5] = { type ="movegravity", actor=b1, velocity={0,-100}, g=100, ystop = pp.y, after={1}},
		[6] = {type="movegravity", actor=tagHead, velocity = {20, 100}, g = 100,ystop = pp.y, after= {1}}
	}	
	monkey.play(s)
end

hitfunc["leg"] = function()

end

local function ciao(x)
	x:setcolor(255,0,0,255)
	pp =  x:parent()
 	info = x:getinfo()
 	print ("pos = (" .. tostring(pp.x) .. ", " .. tostring(pp.y) .. ")")
 	print ("hitting = " .. info.pos)
	pp:remove()	
	hitfunc[info.pos](info, pp)
	-- create the body

-- s.actions = {
	-- 	[1] = { type = "callfunc", func = curry (createObject, { 
	-- 		pos = {100, 100, 0},
	-- 		gfx = { model = "piece1", anim = "default" },
	-- 		depth = d,
	-- 		tag="p1"
	-- 	})},
	-- 	[2] = {
	-- 		type="movegravity",
	-- 		actor="p1",
	-- 		velocity={50,20},
	-- 		g =20,
	-- 		ystop = x.y,
	-- 		after={1}
	-- 	}
	-- }
	-- monkey.play(s)
end

local startPosition = startPositionTable[variables._previousroom]

room = {
engines = {
	{ type = "scheduler"},
	{ type = "collision", size = {80, 80}, coll25 = true, eps = 0.01,
		response = {
			{ tag = {1,10}, onenter = function() print("DIEIEIEIEI") end}
		}
	}
},
assets = {
	sprites.player,
	sprites.character_1,
	sprites.expl1,
	sprites.expl2

},
scene = {
	{
		tag = "main",
		camera = {
			tag = "maincam",
			type="ortho",
			size = {640, 400},
			bounds = {0, 0, 1280, 400},
			viewport = {0, 0, 640, 400}
		},
		children = 
		{
			{
				luakey = {
					keys = {
						{ key = 299, func = restartRoom }
					}
				}
		    },
			makeEnemy ("character_1", 60, 30, 40, 50, 20, 10, 10),
			{
				tag ="c1",
				gfx = { image="gfx/brick.png", width = 128, height = 128},
				pos = { 60, 60, computeDepth(60)},
				depth = d,
				children = {
					-- shadow
					{
						gfx = { shape={type="rect", width=128, height=5 }, draw="solid", color={0,0,0,128} },
						shadow = {}
					}
				},
			},
			{
				gfx = { image="gfx/floor1.png", rep = {4,2}, width = 320, height = 160},
				pos = {0,0,-1}
			},
			-- {
			-- 	gfx = { model="character_1", anim="idle"},	
			-- 	pos = {60, 30, 0},
			-- 	depth = d,
			-- 	statemachine = {
			-- 		initialstate = "walk",
			-- 		states = {
			-- 			{
			-- 				id="walk",
			-- 				type ="aiwalk",
			-- 				speed = 5,
			-- 				target = "player"
			-- 			}
			-- 		}
			-- 	},
			-- 	children = {
			-- 		{
			-- 			pos={0,50,1},
			-- 	 		gfx = {
			-- 	 			shape= {type="rect", width=10, height=10, offset={-5,0}},
			-- 	 			color={255,255,255,255}
			-- 	 		},
			-- 			collider = {
			-- 				shape= {type="rect", width=10, height=10, offset={-5,0}}, 
			-- 				tag=1, 
			-- 				flag=2
			-- 			},
			-- 			info = {
			-- 				pos = "head",
			-- 				spriteid ="character_1",
			-- 				offset = {0, 50},
			-- 				scale =0.5
			-- 			}
			-- 		},
			-- 		{
			-- 			pos={0,20,1},
			-- 	 		gfx = {
			-- 	 			shape= {type="rect", width=10, height=30},
			-- 	 			color={255,255,255,255}
			-- 	 		},
			-- 		collider = {
			-- 			shape= {type="rect", width=10, height=30}, 
			-- 			tag=1, 
			-- 			flag=2
			-- 		},
			-- 		info = {
			-- 			pos = "body",
			-- 			spriteid ="character_1",
			-- 			offset = {0, 20},
			-- 			headx = 0, heady=50,
			-- 			scale =0.7
			-- 		}
			-- 		},				
			-- 	}

			-- },

			{
				tag = "player",
				gfx = { model="player", anim="idle"},
				collider= {shape={type="rect", width=1, height=1}, tag=1, flag=1},
				pos = {30,30,0},
				depth = d,
				children = {
					-- shadow
					{
						gfx = { shape={type="ellipse", semiaxes={ 50, 10} }, draw="solid", color={0,0,0,128} },
						shadow = {}
					}
				},
				statemachine = {
					initialstate = "walk",
					states = {
						{ 
							id = "walk", 
							type="walkcollision", 
							speed = 1, width=5, height=1, 
							horizontal_rays=1, vertical_rays=2,
							anims = {
								{ id = "walk_right", anim = "walk" },
								{ id = "walk_front", anim = "walk" },
								{ id = "walk_back", anim = "walk" },
								{ id = "idle_right", anim = "idle" },
								{ id = "idle_front", anim = "idle"},
								{ id = "idle_back", anim = "idle"}
							}
						},
						{	
							id = "punch",
							type ="hit",
							anim = "punch",
							frame = 2,
							mask = 2,
							shape = { type = "rect", width = 10, height = 10 },
							offset = {32, 52},
							func = ciao
						},
						{	
							id = "kick",
							type ="hit",
							anim = "kick",
							mask = 2,
							frame = 2,
							shape = { type = "rect", width = 18, height = 8 },
							offset = {38, 19},
							func = ciao
						},
						{	
							id = "cr",
							type ="hit",
							anim = "cr",
						},
					},
					keys = {
						{ key = 65, current = "walk", next= "punch"},
						{ key = 83, current = "walk", next= "kick"},
						{ key = 84, current = "walk", next= "cr"},

					}
				
				}
			},
			{
				pos = {50, 50, 0},
				gfx = { image="gfx/tree1.png" },
				depth = d,
			},
			-- {
			-- 	-- a collider object
			-- 	pos = {100,50,0},
			-- 	depth =d,
			-- 	collider = {
			-- 		shape= {type="rect", width=10, height=51}, 
			-- 		tag=1, 
			-- 		flag=2
			-- 	},
			-- 	gfx = {
			-- 		shape= {type="rect", width=10, height=51},
			-- 		color={255,255,255,255}
			-- 	}
			-- }
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

function disableDepth(actor)
	local m = monkey.getEntity(actor)
	m:enabledepth(false)
end

function room.afterstartup() 

	local s= script:new()
	s.actions = {
		[1] = { type="callfunc", func = curry(disableDepth, "c1")},
		[2] = { actor="c1", type ="move", by ={0,120}, speed = 20, after={1}},
		[3] = { actor="c1", type ="move", by ={0, -120}, speed = 500, after={2} },
		[4] = { type="collisioncheck", after={3}, shape = {type="rect", width = 128, height = 5}, actor="c1", offset={0,0}, mask=1, func = 
		function(x) 
			--print ("opOPOPLPOIJ")
			x:remove()
			main = monkey.getEntity("main")
		    monkey.addEntity ({
				pos = {x.x, x.y, 0},
				depth = d,
				gfx = { model = "expl2", anim = "default"},
			}, main)
		end },
	}
	s.loop = 1
	monkey.play(s)
end



