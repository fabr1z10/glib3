_nextTag = 0
brickSpeed = 60
brickg = 150
bonusRaiseSpeed = 50

mushroomTag = 100
goombaTag = 101
koopaTag = 102
flowerTag = 103

items = { }

function hitFromAbove(mario, sx, sy)
	return (mario.state == "jump" and mario.vy < 0 and sy > 0 and math.abs(sx) < 0.01)
end

require("items/mario")
require("items/mushroom")
require("items/flower")
require("items/goomba")
require("items/koopa")
require("items/brick")
require("items/bonusbrick")

function resumeplay()
	local ros = monkey.getEntity("restofscene")
	local mario = monkey.getEntity("player")
	ros:enableupdate(true)
	mario:enablestatemachine(true)
	mario:resetstate()

	
end

function suspendplay()
	local ros = monkey.getEntity("restofscene")
local mario = monkey.getEntity("player")
	ros:enableupdate(false)
	mario:enablestatemachine(false)
end

function curry(f, arg)
    return function()
       return f(arg) 
    end 
end
function curry21(f, arg)
    return function(a)
       return f(arg,a) 
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



function marioinit(verb, e) 
	
	return {
		anim = verb .. (e.supermario and "big" or "") .. (e.fire and "fire" or ""),
		collider = (e.supermario and "big" or "small")
	}
		
end

function mario_duck(e) 
	local info = e:getinfo()
	if (info.supermario == true) then
		print ("duck")
		e:changestate("duck")
	end
end

function makeRect(arg)
	local width = 16 * arg.width
	local height = 16 * arg.height
	local s = { type = "rect", width = width, height = height }
	return {
		pos = {arg.pos[1]*16, arg.pos[2]*16, arg.pos[3]},
		components = {
			{ type ="gfx", image=("gfx/" .. arg.gfx .. ".png"), width = width, height = height, rep={arg.width, arg.height} },
			{ type ="collider", shape=s, tag=10, flag = 2 }
		}
	}
end

-- function makeBrick(arg)
-- 	local s = { type = "rect", width = 16, height = 16 }
-- 	-- place the sensor
-- 	local s1 = { type = "rect", width = 14, height = 0.5, offset = {1, -0.25}}
-- 	local b = nextTag()
-- 	local y = arg.pos[2] * 16
-- 	--print ("CREATE BRICK WITH TAG = " .. b)
-- 	return {
-- 		tag = b,
-- 		pos = {arg.pos[1] * 16, y, 0},
-- 		--gfx = {shape=arg.shape, color={255,255,255,255} },
-- 		gfx = { model=arg.sprite, anim="idle", width = 16, height = 16},	
-- 		collider= {shape=s, tag=10, flag = 2},
-- 		info = {
-- 			y = y
-- 		},
-- 		children = {
			
-- 			{
-- 				collider = { shape = s1, tag = 20, flag = 4 },
-- 				gfx = { shape = s1, color = {255,0,0,255}}
-- 			}
-- 		}
-- 	}
-- end



function makeLine (arg) 

	local s = { type = "line", A = arg.A, B = arg.B }
	return {
		pos = {0,0,0},
		--gfx = {shape=arg.shape, color={255,255,255,255} },
		components = {
			{ type="gfx", shape = s, color = {255,255,255,255}  },
			{ type="collider", shape=s, tag=10, flag = 2 }
		}
	}
end

function generateBonus(brick)
	local main = monkey.getEntity("restofscene")
	local args = { x = brick.x+8, y = brick.y, z = 0.1 }
	print ("Brick position is " .. tostring(brick.x) .. ", " .. tostring(brick.y))
	local s = {type="rect", width=16, height=16, offset={-8,0}}
	local brickInfo = brick:getinfo()
	local m = items[brickInfo.item].create(args)
	monkey.addEntity (m, main)
	local s = script:new()
	s.actions = {
		[1] = {type="move", by={0, 16}, actor = m.tag, speed = bonusRaiseSpeed},
		[2] = {type="changestate", actor=m.tag, state="walk", after={1}}
	}
	monkey.play(s)
end



