_nextTag = 0
tilesize = 16
brickSpeed = 60
brickg = 150
bonusRaiseSpeed = 50
warpFunction = nil
currentArea = nil

-- collision flags
collisionFlags = {
	player = 1,
	platform = 2,
	platform_transparent = 32,
	enemy = 4
}


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
plantTag = 111
banzaiTag = 112
rexTag = 113
cornerTag = 114
brickTag = 115
checkpointTag = 116
infobrickTag = 117
bonusBrickTag = 118
movingPlatformTag = 90

items = { }

-- create object at runtime
function CreateItem (args) 
	if (items[args.id].create == nil) then
		print ("Item " .. args.id .. " does not exist!")
		return nil
	end
	print ("CREATING " .. args.id)
	local parent = monkey.getEntity("restofscene")
	local item = items[args.id].create(args.args)
	monkey.addEntity (item, parent)
	if (items[args.id].script ~= nil) then
		items[args.id].script(item)
	end
end

function RemoveAdvice() 
	if (variables.advice == true) then
		local ros = monkey.getEntity("restofscene")
		local player = monkey.getEntity("player")
		print ("CIAO")
		local a1 = monkey.getEntity("_advice")
		print ("CIAO2")
		local a2 = monkey.getEntity("_advice_bg")
		print ("CIAO3")
		a1:remove()
		a2:remove()
		ros:enableupdate(true)
		player:enableupdate(true)
		variables.advice = false
	end
end


function ShowAdvice (arg) 
	local text = arg.text

	local ros = monkey.getEntity("restofscene")
	local mario = monkey.getEntity("player")
	ros:enableupdate(false)
	mario:enableupdate(false)
	
	local diag = monkey.getEntity("diag")
	monkey.addEntity ( { 
		tag ="_advice", 
		active=false, 
		pos = {128, 176, 1}, 
		components = { 
			{ type="text", align="top", maxwidth = 160, id = text, font="diag"} }
		}, diag)
	local poa = monkey.getEntity("_advice")
	local ti = poa:gettextinfo()
	local center = { 128, 176-ti.height*0.5}
	ti.width = ti.width * 1.1
	ti.height = ti.height * 1.1
			
	monkey.addEntity ( { 
		tag = "_advice_bg",
		pos = {center[1], center[2], 0.9}, 
		scale = 0.5,
		components = { 
			{type="gfx", shape={type="rect", width = ti.width, height = ti.height, offset = {-ti.width*0.5, -ti.height*0.5}}, color = {0,0,0,255}, draw ="solid"} }
		}, diag)
	local s1 = script:new()
	s1.actions = {
		[1] = { type="scale", duration = 0.5, scale = 1.0, actor = "_advice_bg" },
		[2] = { type="callfunc", after={1}, func = function() poa:setactive(true) end }
	}
	monkey.play(s1)
	variables.advice = true
end

function Pos(a) 
	if (#a == 2) then
		return {a[1]*tilesize, a[2]*tilesize}
	elseif (#a == 3) then
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

function switchToArea(name) 
	if (currentArea ~= nil) then
		print ("current area is " .. currentArea)
		for k, v in ipairs(areas[currentArea].background) do
			monkey.getEntity(v):setactive(false)
		end
	end
	print ("CHOOSING Main1")
	local area = areas[name]
	if (area == nil) then
		print ("area " .. name .. " not found")
	end
	for k, v in ipairs(area.background) do
		print ("enabling background " .. v)
		monkey.getEntity(v):setactive(true)
	end
print ("set bvackgrounds")
	currentArea = name
	local s = script:new()
	s.actions = {
		[1] = { type="setcambounds", cam ="maincam", xmin=area.range[1], xmax = area.range[3], ymin = area.range[2], ymax = area.range[4] },
 		[2] = { type="move", to=area.startPos, immediate=true, actor="player", after={1}},
	}
	monkey.play(s)
end

-- require("cutscene")
require("tilesets")
require("items/mario")
require("items/banzaibill")
require("items/rex")
require("items/parallax")
require("items/midwaygate")
require("items/finalgate")
require("items/infobrick")
-- require("items/mushroom")
-- require("items/mushroom1up")
-- require("items/flower")
-- require("items/star")
-- require("items/goomba")
-- require("items/koopa")
require("items/brick")
require("items/bonusbrick")
require("items/brickpiece")

-- require("items/bonusbrick")
-- require("items/brickcoin")
-- require("items/invisiblebrick")
-- require("items/movingplatform")
require("items/spawn")
-- require("items/score")
require("items/warp")
-- require("items/coin")
require("items/background")
-- require("items/plant")
require("template/template")


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

function makeTiledRect (arg) 
	local width = arg.width
	local height = arg.height
	local pos = arg.pos
	local solid = arg.solid or false
	local z = arg.z or 0

	local tiledata = {}
	for i = 1, width*height do
		table.insert(tiledata, arg.tile[1])
		table.insert(tiledata, arg.tile[2])
	end

	

	local gfxComponent = {
		type="gfx",
		img="gfx/sprites.png",
		width = width,
		height = height,
		size = 16,
		tiledata = tiledata,
		sheetsize ={32, 32}
	}

	local comp = {
		gfxComponent
	}
	if (solid == true) then
		table.insert(comp, { type ="collider", shape={type="rect", width = width*16, height=height*16}, tag=10, flag = collisionFlags.platform, mask = 0 })
	end

	return {
		pos = {pos[1], pos[2], z},
		components = comp
	}	
end

function makePlatformRect(arg)
	local width = arg.size[1]
	local height = arg.size[2]
	local pos = arg.pos
	local z = arg.z or 0
	local s = { type="rect", width=width, height=height}
	return {
		pos = {pos[1], pos[2], z},
		components = {
			{ type ="collider", shape=s, tag=10, flag = collisionFlags.platform, mask = 0 }
		}
	}
end

function makePlatformLine(arg)
	local A = arg.A
	local B = arg.B
	local z = arg.z or 0
	local s = { type="line", A=A, B=B}
	return {
		pos = {0, 0, z},
		components = {
			{ type ="collider", shape=s, tag=10, flag = 32, mask = 0 }
		}
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
			{ type ="collider", shape=s, tag=10, flag = collisionFlags.platform, mask = 0 }
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
			{ type="collider", shape=s, tag=10, flag = collisionFlags.platform, mask = 0 }
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




-- function mario_corner(mario, rex, sx, sy)
-- 	print ("MOVING MARIO BY  " .. tostring(sy) .. " " .. tostring(sx))
-- 	if (mario.vy < 0) then
-- 		mario:move(sx, sy + 1, 0)
-- 		mario.vy = 0
-- 	end
-- end