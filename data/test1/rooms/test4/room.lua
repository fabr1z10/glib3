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
	-- check energy left
	info = pp:getinfo()
	


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
	--x:setcolor(255,0,0,255)
	pp =  x:parent()
 	info = x:getinfo()
	player = monkey.getEntity("player")
	flip = player.flipx and -1 or 1
	infoChar = pp:getinfo()
 	print ("pos = (" .. tostring(pp.x) .. ", " .. tostring(pp.y) .. ")")
 	print ("hitting = " .. info.pos)
	print ("Energy left = " .. infoChar.energy)
	infoChar.energy = infoChar.energy -1
	if (infoChar.energy <= 0) then
		pp:remove()		
	else
		local s = script:new()
		s.actions = {
			[1] = { type= "animate", actor = pp.tag, anim="idle" },
			[2] = { type="move", actor = pp.tag, by = {flip*50,0}, speed = 100, acceleration = -20, after={1}},
			[3] = { type="changestate", actor=pp.tag, state="walk", after={2} }
		}
		monkey.play(s)
		pp:changestate("ishit")
	end
	--hitfunc[info.pos](info, pp)
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
	sprites.beast,
	sprites.character_1,
	sprites.character_2,
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
			--makeEnemy ("character_1", 60, 30, 40, 50, 20, 10, 10),
			makeCharacter { template = characters.beast, x = 30, y = 30, type="player" },
			makeCharacter { template = characters.bred, x=120, y = 30, type="enemy" },
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
			{
				pos = {50, 50, 0},
				gfx = { image="gfx/tree1.png" },
				depth = d,
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



