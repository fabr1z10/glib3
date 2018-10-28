_nextTag = 0
tilesize = 16
brickSpeed = 60
brickg = 150
bonusRaiseSpeed = 50
warpFunction = nil

mushroomTag = 100
goombaTag = 101
koopaTag = 102
flowerTag = 103
mushroom1upTag = 104
starTag = 105
invisibleBrickTag = 106
spawnTag = 107
warpTag = 108
coinTag = 109
warpTouch = 110
movingPlatformTag = 90

items = { }

-- create object at runtime
function CreateItem (args) 
	if (items[args.id].create == nil) then
		print ("Item " .. args.id .. " does not exist!")
		return nil
	end
	local parent = monkey.getEntity("restofscene")
	local item = items[args.id].create(args.args)
	monkey.addEntity (item, parent)
	if (items[args.id].script ~= nil) then
		items[args.id].script(item)
	end
end

function Pos(a) 
	if (#a == 2) then
		print ("DUE")
		return {a[1]*tilesize, a[2]*tilesize}
	elseif (#a == 3) then
		print ("CANANENENENEE")
		return {a[1]*tilesize, a[2]*tilesize, a[3]}
	else
		return nil
	end

end

function hitFromAbove(mario, sx, sy)
	return (mario.state == "jump" and mario.vy < 0 and sy > 0 and math.abs(sx) < 0.01)
end

function bonusRise(m) 
	local s = script:new()
	s.actions = {
		[1] = {type="move", by={0, 16}, actor = m.tag, speed = bonusRaiseSpeed},
		[2] = {type="changestate", actor=m.tag, state="walk", after={1}}
	}
	monkey.play(s)
end

require("items/mario")
require("items/mushroom")
require("items/mushroom1up")
require("items/flower")
require("items/star")
require("items/goomba")
require("items/koopa")
require("items/brick")
require("items/bonusbrick")
require("items/brickcoin")
require("items/invisiblebrick")
require("items/movingplatform")
require("items/spawn")
require("items/score")
require("items/warp")
require("items/coin")


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

function character_movingplatform(ch, platform, sx, sy)
	
	if (hitFromAbove(ch, sx, sy)) then
		print ("ECCOMI")
		local p = platform:parent()
		monkey.register_platform(ch, p)
	end
end

function marioinit(verb, e) 
	
	return {
		anim = verb .. (e.supermario and "big" or "") .. (e.fire and "fire" or ""),
		collider = (e.supermario and "big" or "small")
	}
		
end

function marioinit2(verb, e) 
	print ("CANEBESTIA")
	return {
		anim = verb .. (e.supermario and "big" or "") .. (e.fire and "fire" or ""),
		collider=""
	}
		
end

function makeRect(arg)
	local width = 16 * arg.width
	local height = 16 * arg.height
	local s = { type = "rect", width = width, height = height }
	local gfxComponent = nil
	if (arg.gfx ~= nil) then
		gfxComponent = { type ="gfx", image=("gfx/" .. arg.gfx .. ".png"), width = width, height = height, rep={arg.width, arg.height} }
	else
		gfxComponent = { type ="gfx", img="gfx/smb1.png", width=arg.width, height=arg.height, size=16, tiledata=arg.tiledata, sheetsize={16, 16} }
	end
	local z = arg.z or 0
	return {
		pos = {arg.pos[1], arg.pos[2], z},
		components = {
			gfxComponent,	
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
	local args = { pos = {brick.x+8, brick.y}, z = 0.1 }
	local s = {type="rect", width=16, height=16, offset={-8,0}}
	local brickInfo = brick:getinfo()
	local m = items[brickInfo.item].create(args)
	print ("CREATO ITEM")
	monkey.addEntity (m, main)
	if (items[brickInfo.item].script ~= nil) then
	print ("CHIAMO SCRIPT")
		items[brickInfo.item].script(m)
	end
end



