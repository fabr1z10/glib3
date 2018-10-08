_nextTag = 0

function curry(f, arg)
    return function()
       return f(arg) 
    end 
end

-- function to autogenerate tags for entities
function nextTag()
	_nextTag = _nextTag+1
	return "__auto" .. _nextTag
end

-- this is called when the user presses F10 or any other key to restart the current room
function restartRoom()
	local s = script:new()
	s.actions = {
		[1] = { type="gotoroom", room=variables._room }
	}
	monkey.play(s)
end


function makeRect(arg)
	local width = 16 * arg.width
	local height = 16 * arg.height
	local s = { type = "rect", width = width, height = height }
	return {
		pos = arg.pos,
		--gfx = {shape=arg.shape, color={255,255,255,255} },
		gfx = { image="gfx/block1.png", width = width, height = height, rep={arg.width, arg.height}},	
		collider= {shape=s, tag=10, flag = 2}
	}
end

function makeBrick(arg)
	local s = { type = "rect", width = 16, height = 16 }
	-- place the sensor
	local s1 = { type = "rect", width = 14, height = 0.5, offset = {1, -0.25}}
	local b = nextTag()
	local y = arg.pos[2] * 16
	--print ("CREATE BRICK WITH TAG = " .. b)
	return {
		tag = b,
		pos = {arg.pos[1] * 16, y, 0},
		--gfx = {shape=arg.shape, color={255,255,255,255} },
		gfx = { model=arg.sprite, anim="idle", width = 16, height = 16},	
		collider= {shape=s, tag=10, flag = 2},
		info = {
			y = y
		},
		children = {
			
			{
				collider = { shape = s1, tag = 20, flag = 4 },
				gfx = { shape = s1, color = {255,0,0,255}}
			}
		}
	}
end

function makeBonusBrick(arg)
	local s = { type = "rect", width = 16, height = 16 }
	local s1 = { type = "rect", width = 14, height = 0.5, offset = {1, -0.25}}
	local b = nextTag()
	local y = arg.pos[2] * 16
	--print ("CREATE BRICK WITH TAG = " .. b)
	return {
		tag = b,
		pos = {arg.pos[1] * 16, y, 0},
		gfx = { model=arg.sprite, anim="idle", width = 16, height = 16},	
		collider= {shape=s, tag=10, flag = 2},
		info = {
			y = y,
            hits = arg.hits,
			bonus = arg.bonusfactory
		},
		children = {
			-- head sensor
			{
				collider = { shape = s1, tag = 21, flag = 4 },
				gfx = { shape = s1, color = {255,0,0,255}}
			}
		}
	}
end

function makeLine (arg) 

	local s = { type = "line", A = arg.A, B = arg.B }
	return {
		pos = {0,0,0},
		--gfx = {shape=arg.shape, color={255,255,255,255} },
		gfx = { shape = s, color = {255,255,255,255}},	
		collider= {shape=s, tag=10, flag = 2}
	}
end

function ciao(brick)

	local main = monkey.getEntity("main")
	print ("Brick position is " .. tostring(brick.x) .. ", " .. tostring(brick.y))
	local t = nextTag()
	local m = {
		tag = t,
		pos = { brick.x, brick.y, 0.1 },
		gfx = { model = "mushroom", anim="idle" },
		collider = { shape = {type="rect", width=16, height=16, offset={-8,0}}, tag = 22, flag= 1}
	}
	monkey.addEntity (m, main)
	local s = script:new()
	s.actions = {
		[1] = {type="move", by={0, 16}, actor = t, speed = 2}
	}
	monkey.play(s)
end

function basicBrickResponse(e1, e2)
	--print ("Brick is at " .. tostring(e2.x) .. ", " .. tostring(e2.y))
	local brick = e2:parent()
	local brickInfo = brick:getinfo()
	local s = script:new("_brick" .. brick.tag)
	e1.vy = -e1.vy
	s.actions = {
		[1] = { type="movegravity", actor = e2:parent().tag, velocity  = {0,50}, g = 30, ystop = brickInfo.y}
	}
	monkey.play(s)
end

function bonusBrickResponse(e1, e2)
	--print ("Brick is at " .. tostring(e2.x) .. ", " .. tostring(e2.y))
	local brick = e2:parent()
	local brickInfo = brick:getinfo()
	e1.vy = -e1.vy
	if (brickInfo.hits > 0) then
		brickInfo.hits = brickInfo.hits - 1
		local a1 ={ type="noop" }
		local a2 ={ type="noop", after={2}}
		if (brickInfo.hits == 0) then
			a1 = { type="animate", actor=brick.tag, anim="taken" }
			a2 = { type="callfunc", func = curry(brickInfo.bonus, brick), after={2} } 
		end
		local s = script:new()
		s.actions = {
			[1] = a1,
			[2] = { type="movegravity", actor = brick.tag, velocity  = {0,50}, g = 30, ystop = brickInfo.y, after={1} },
			[3] = a2
		}
		monkey.play(s)
	end
end