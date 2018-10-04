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

end

hitfunc["body"] = function()

end

hitfunc["leg"] = function()

end

local collisionGrid = 80


local startPosition = startPositionTable[variables._previousroom]

room = {
engines = {
	{ type = "scheduler"},
	{ type = "collision", size = {collisionGrid, collisionGrid}, coll25 = true, eps = 0.01,
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
			makeCharacter { template = characters.beast, x = 30, y = 30, player=1},
			--makeCharacter { template = characters.bred, x=120, y = 30, type="enemy" },
			makeShape { pos = {20, 20, 0}, angle = 0, tag=2, flag=2, shape = {type="line", A={0,0},B={100,0}}, offset={0, 0} },
			-- {
			-- 	tag ="c1",
			-- 	gfx = { image="gfx/brick.png", width = 128, height = 128},
			-- 	pos = { 60, 60, computeDepth(60)},
			-- 	depth = d,
			-- 	children = {
			-- 		-- shadow
			-- 		{
			-- 			gfx = { shape={type="rect", width=128, height=5 }, draw="solid", color={0,0,0,128} },
			-- 			shadow = {}
			-- 		}
			-- 	},
			-- },
			{
				gfx = { image="gfx/gnd2.jpg", rep = {4,2}, skew={-0.5,0}, width = 320, height = 160},
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
    table.insert(room.scene[1].children, { gfx = { shape = { type="line", A={collisionGrid*i,0}, B={collisionGrid*i, 200}}, color={255, 255, 255, 255} }})
    table.insert(room.scene[1].children, { gfx = { shape = { type="line", A={0, collisionGrid*i}, B={320, collisionGrid*i}}, color={255, 255, 255, 255} }})
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

	-- local s= script:new()
	-- s.actions = {
	-- 	[1] = { type="callfunc", func = curry(disableDepth, "c1")},
	-- 	[2] = { actor="c1", type ="move", by ={0,120}, speed = 20, after={1}},
	-- 	[3] = { actor="c1", type ="move", by ={0, -120}, speed = 500, after={2} },
	-- 	[4] = { type="collisioncheck", after={3}, shape = {type="rect", width = 128, height = 5}, actor="c1", offset={0,0}, mask=1, func = 
	-- 	function(x) 
	-- 		--print ("opOPOPLPOIJ")
	-- 		x:remove()
	-- 		main = monkey.getEntity("main")
	-- 	    monkey.addEntity ({
	-- 			pos = {x.x, x.y, 0},
	-- 			depth = d,
	-- 			gfx = { model = "expl2", anim = "default"},
	-- 		}, main)
	-- 	end },
	-- }
	-- s.loop = 1
	-- monkey.play(s)
end



