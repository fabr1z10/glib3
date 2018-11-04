function curry(f, arg)
    return function()
       return f(arg) 
    end 
end

_nextTag = 0

function nextTag()
	_nextTag = _nextTag+1
	return "__auto" .. _nextTag
end

function createObject (obj) 
    parent = monkey.getEntity("main")
    monkey.addEntity (obj, parent)
end

 	local d = {
 		depth = { 
 		    type = "linear_y", values = {0, 1, 400, 0}
 		}
 	}


function makeShape (arg)
	return {
		pos = arg.pos,
		angle = arg.angle,
		gfx = {shape=arg.shape, color={255,255,255,255} },
		collider= {shape=arg.shape, tag=arg.tag, flag = arg.flag},
		depth = d,
		info = arg.info
	}
end

local g = 100
local explFactor = 1

function hit(infoBox, entityHit, flip)
	-- create the spinning items
	main = monkey.getEntity("main")

	infoChar = entityHit:getinfo()
	local scale =infoChar.scale or 1
	for i, v in ipairs(infoBox.parts) do
	 	local b = nextTag()
	-- 	local b1 = nextTag()
	-- 	-- adding fx
		local collider = nil
		local info = nil
		if (v.cr ==1) then
			collider = { shape = {type="rect", width=infoChar.bodymetrics.y[v.anim], height=1}, tag=1, flag=4 }
			info = { scale = v.crscale * scale, offset = infoChar.bodymetrics.width[v.anim]*0.5 }
		end
		

	    monkey.addEntity ({
			pos = {entityHit.x, (entityHit.y + infoChar.bodymetrics.y[v.anim])*scale, entityHit.z},
	 		gfx = { model = infoChar.sprite, anim = v.anim, scale = scale},
	 		tag = b,
			collider = collider,
			info = info
	 	}, main)
	  	local s = script:new("_cook" .. tostring(i))
	  	s.actions ={
	 		[1] = {type="movegravity", actor =b, velocity = {flip*math.random(20,60), math.random(10,40)}, g =g, ystop = entityHit.y + infoChar.bodymetrics.width[v.anim]*0.5, rotationspeed=math.random(5,20), finalrotation = 90},
	 	}	
	  	monkey.play(s)
	end
	-- explosion
	entityHit:remove()
 	local b = nextTag()
	monkey.addEntity ({
		pos = {entityHit.x, (entityHit.y + infoChar.bodymetrics.y[infoBox.type])*scale, entityHit.z},
		--depth = d,
		gfx = { model = "expl1", anim = "default", scale = scale*explFactor},
		tag = b
	}, main)
	local s = script:new("_cook")
	s.actions ={
		[1] = {type="noop"},
		[2] = {type="movegravity", actor =b, velocity = {flip*math.random(10,30), -50}, g =g, ystop = entityHit.y, rotationspeed=0, after={1}},
		[3] = {type="animate", actor=b, anim="default", loop=1, after={1}},
		[4] = {type="animate", actor=b, anim="stop", after={3}},

	}	
	monkey.play(s)
	
end

function ciao2(boxHit, entityHitting) 
	boxHit:remove()
	main = monkey.getEntity("main")
	infoChar = boxHit:getinfo()
    monkey.addEntity ({
		pos = {boxHit.x, boxHit.y - infoChar.offset, boxHit.z},
	 	gfx = { model = "expl2", anim = "default", scale = infoChar.scale},
	 }, main)
end

-- collision callback
function ciao(boxHit, entityHitting)
	print ("Entity hitting: " .. entityHitting.tag)

	-- print ("Entering collision check .......")
	entityHit = boxHit:parent():parent()
	print ("entity hit in " .. tostring(entityHit.x))
	-- print ("Character hit position is = " .. entityHit.x)
	infoChar = entityHit:getinfo()
	print ("Energy left = " .. infoChar.energy)
 	


	--print ("Info type: " .. info.type)
	-- player = monkey.getEntity("player")
	flip = entityHitting.flipx and -1 or 1
	
 -- 	print ("pos = (" .. tostring(entityHit.x) .. ", " .. tostring(entityHit.y) .. ")")
	-- infoChar.energy = infoChar.energy -1
	if (infoChar.energy <= 0) then
		bh = boxHit:getinfo()
		print ("hit on " .. bh.type)
		-- This will call the special collision handler based on the collision info type
	 	--collisionResponse[info.type](entityHit, info, entityHitting)
		
		hit(bh, entityHit, flip)
	--  	main = monkey.getEntity("main")
	-- -- 	player = monkey.getEntity("player")
	--  	flip = entityHitting.flipx and 1 or -1
	--  	local b = nextTag()
	-- -- 	local b1 = nextTag()
	-- -- 	-- adding fx
	--     monkey.addEntity ({
	-- 		pos = {entityHit.x, entityHit.y, 0},
	--  		depth = d,
	--  		gfx = { model = "expl1", anim = "default", scale = infoChar.killscale},
	--  		tag = b
	--  	}, main)
	--   	local s = script:new("_cook")
	--  	s.actions ={
	-- 		[1] = {type="noop"},
	-- 		[2] = {type="animate", actor=b, loop=1, anim="default", after={1} },
	-- 		[3] = {type="animate", actor=b, loop=1, anim="stop", after={2} },
	--  		[4] = {type="move", actor=b, by = {20,0}, speed=50, acceleration =-10, after={1}}
	-- 	}	
	--  	monkey.play(s)
	else
	 	local s = script:new()
	 	s.actions = {
	 		[1] = { type= "animate", actor = entityHit.tag, anim="idle" },
	 		[2] = { type="move", actor = entityHit.tag, by = {flip*50,0}, speed = 100, acceleration = -20, after={1}},
	 		[3] = { type="changestate", actor=entityHit.tag, state="walk", after={2} }
	 	}
	 	monkey.play(s)
		infoChar.energy = infoChar.energy -1
	 	entityHit:changestate("ishit")
	end
end

require("characters")

collisionMaker = {}
collisionResponse = {}

require("collision/hbl")
require("collision/clear")

function makeCharacter(args)

	local tag =""
	local follow= nil
	if (args.player == 1) then
		tag = "player"
		follow = {cam="maincam", relativepos = {0, 0, 5}, up ={0,1,0}}
	else
		tag = nextTag()
	end
	
	-- Read character scale (by default it's 1)
	local scale = args.template.info.scale or 1

	colliders = {}
	for k, v in ipairs(args.template.colliders) do 
		local width = args.template.info.bodymetrics.width[v.name] * scale
		local height = args.template.info.bodymetrics.height[v.name] * scale
		local y = args.template.info.bodymetrics.y[v.name] * scale
		local s = {type="rect", width = width, height = height}
		table.insert(colliders, { 
			pos = {0, y, 0},
			collider = { shape = s, tag=1, flag=2 },
			gfx = { shape = s, color = {255,255,255,255 }},
			name = v.name,
			info = v.info
		})
	end

	return {
		pos = {args.x, args.y, 0},
		depth = d,
		tag = tag,
		gfx = { model=args.template.info.sprite, anim=args.template.anim, scale = scale},
		statemachine = {
			initialstate = args.template.initialstate,
			states = args.template.states,
			keys = args.template.keys,
			transitionmatrix = args.template.transitionmatrix
		},
		follow = follow,
		info = args.template.info,
		children = {
			{
				name ="colliders",
				children = colliders
			},
 			{
				name ="shadow",
 				gfx = { shape={type="ellipse", semiaxes=args.template.shadowsize }, draw="solid", color={0,0,0,128} },
 				shadow = {}
 			},

		}
		--collider= { shape = {type="rect", width=1, height=1}, tag=1, flag=1},
	}
-- 		pos = {args.x, args.y, 0},
-- 		depth = d,
-- 		children = children,
-- 		statemachine = statemachine,
-- 		info = args.template.info
-- 	}
end

-- Body metrics
-- headY = y where head starts
-- bodyY = y where body starts
-- headHeight = height of head box
-- boxWidth = width of collision boxes
-- function makeCharacter(args) 
-- 	local d = {
-- 		depth = { 
-- 		    type = "linear_y", values = {0, 1, 400, 0}
-- 		}
-- 	}
-- 	local sprite = args.template.sprite
-- 	local scale = args.template.scale or 1

-- 	local statemachine = {
-- 		states = args.template.states
-- 	}



-- 	statemachine.states = 
-- 	local tag = ""
-- 	if (args.type == "player") then
-- 		tag = "player"
-- 		statemachine.keys = args.template.keys
-- 		statemachine.states[1] = {
-- 			id = "walk", 
-- 			type="walkcollision", 
-- 			speed = 1, width=5, height=1, 
-- 			horizontal_rays=1, vertical_rays=2,
-- 			anims = {
-- 				{ id = "walk_right", anim = "walk" },
-- 				{ id = "walk_front", anim = "walk" },
-- 				{ id = "walk_back", anim = "walk" },
-- 				{ id = "idle_right", anim = "idle" },
-- 				{ id = "idle_front", anim = "idle"},
-- 				{ id = "idle_back", anim = "idle"}
-- 			}
-- 		}
-- 		statemachine.states[2] = {
-- 			id="ishit", type="empty"
-- 		}
-- 	elseif (args.type == "enemy") then
-- 		tag = nextTag()
-- 		statemachine.transitionmatrix = args.template.transitionmatrix
-- 		statemachine.states[1] = {
-- 			id="walk",
-- 			type ="aiwalk",
-- 			speed = args.template.speed,
-- 			target = "player"
-- 		}
-- 		statemachine.states[2] = {
-- 			id="ishit", type="empty"
-- 		}
-- 		statemachine.states[3] = {
-- 			id ="idle", type="empty"
-- 		}
-- 	end

-- 	-- add hit state
-- 	local keys = args.template.keys
-- 	local prob = args.template.transitionmatrix
-- 	if (args.template.hit ~= nil) then
-- 		for k, v in ipairs(args.template.hit) do
-- 			print ("Adding state " .. v.id)
-- 			table.insert (statemachine.states, 
-- 			{ 
-- 				id=v.id,
-- 				type="hit",
-- 				anim=v.anim,
-- 				frame=v.frame,
-- 				mask=2,
-- 				shape = {type="rect", width=v.width*scale, height=v.height*scale},
-- 				offset = {v.offset[1]*scale, v.offset[2]*scale},
-- 				func = ciao
-- 			})
-- 		end
-- 	end
	
	
-- 	local c = collisionMaker[args.template.collisionType](args)
-- 	local children = {
-- 			-- shadow
-- 			{
-- 				gfx = { shape={type="ellipse", semiaxes={ 50, 10} }, draw="solid", color={0,0,0,128} },
-- 				shadow = {}
-- 			},
-- 			-- collision boxes
-- 		}
-- 	for i, c in ipairs(c) do
-- 		table.insert(children, c)
-- 	end
	


-- 	return 
-- 	{
-- 		tag = tag,
-- 		gfx = { model=args.template.sprite, anim="idle", scale = scale},
-- 		collider= { shape = {type="rect", width=1, height=1}, tag=1, flag=1},
-- 		pos = {args.x, args.y, 0},
-- 		depth = d,
-- 		children = children,
-- 		statemachine = statemachine,
-- 		info = args.template.info
-- 	}
-- end
			-- {


-- args
-- spriteName             the sprite name
-- x, y  				  the position
-- speed				  the speed
-- headY 				  the y pos of the head
-- bodyY				  the y pos of the body
-- boxWidth               the width of the collision box
-- hit                    array of hit objects. Each one must have a anim name, frame, width, height, offset
-- scale                  the sprite scale
function makeEnemy(args) 
	local d = {
		depth = { 
		    type = "linear_y", values = {0, 1, 400, 0}
		}
	}
	local scale = args.scale or 1
	local boxWidth = args.boxWidth * scale
	local headY = args.headY * scale
	local bodyY = args.bodyY * scale
	local headHeight = args.headHeight * scale
	local hw = 0.5 * boxWidth
	local bodyHeight = headY - bodyY
	local headShape = { type = "rect", width = boxWidth, height = headHeight, offset = {-hw, 0}}
	local bodyShape = { type = "rect", width = boxWidth, height = bodyHeight, offset = {-hw, 0}}
	-- generate the state machine 
	local states = {
		{
			id="walk",
			type ="aiwalk",
			speed = args.speed,
			target = "player"
		},
		{
			id="ishit",
			type="empty"
		}
	}
	-- add hit state
	if (args.hit ~= nil) then
		for k, v in ipairs(args.hit) do
			table.insert (states, 
			{ 
				id="hit".. tostring(k), 
				type="hit",
				anim=v.anim,
				frame=v.frame,
				mask=2,
				shape = {type="rect", width=v.width*scale, height=v.height*scale},
				offset = {v.offset[1]*scale, v.offset[2]*scale},
				func = function() print("QUQUQUQU") end
			})
		end
	end

	return {
		tag = nextTag(),
		gfx = { model=args.sprite, anim="idle", scale = scale},	
		pos = {args.x, args.y, 0},
		depth = d,
		statemachine = {
			initialstate = "walk",
			states = states
		},
		info = {
			energy = 10
		},
		children = {
			
		}
	}
end

function restartRoom()
	local s = script:new()
	s.actions = {
		[1] = { type="gotoroom", room=variables._room }
	}
	monkey.play(s)
end