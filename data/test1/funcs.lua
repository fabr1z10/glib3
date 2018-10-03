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

characters = {

	beast = {
		sprite = "beast",
		-- body metrics
		headY = 60,
		bodyY = 41,
		boxWidth = 21,
		headHeight = 10,
		speed = 50,
		shadowsize ={50,10},
		hit = {
			{ id = "punch", anim = "punch", frame = 2, mask = 2, width = 10, height = 10, offset = {32, 52} },
			{ id = "kick", anim = "kick", frame = 2, mask = 2, width = 18, height = 8, offset = {38, 19}},
			{ id = "cr", anim="cr", frame = 2, mask = 2, width = 1, height = 1, offset={0,0}}
		},
		keys = {
			{ current = "walk", key =  65, next="punch" },
			{ current = "walk", key =  83, next="kick" },
			{ current = "walk", key =  84, next="cr" }
		},
		collisionType = "clear",
		info = {	
			energy = 3
		}
	},
	bred = {
		sprite = "character_2", 
		-- body metrics
		headY = 77, 
		bodyY = 50, 
		boxWidth = 10, 
		headHeight = 10, 
		--x = 120, y = 30, 
		speed = 40, 
		shadowsize ={50,10},
		scale = 0.7,
		hit = { 
			{ id ="punch", anim="hit1", frame=1, width=16, height=8, offset={52,70}}
		},
		transitionmatrix = {
			{ current = "idle", next="punch", prob = 0.01 }
		},
		--collisionType = "clear",
		collisionType = "headBodyLegs",
		info = {
			energy = 2
		}
	}



}

-- collision callback
function ciao(boxHit, entityHitting)
	print ("Entity hitting: " .. entityHitting.tag)

	-- print ("Entering collision check .......")
	entityHit = boxHit:parent()
	-- print ("Character hit position is = " .. entityHit.x)
	infoChar = entityHit:getinfo()
	print ("Energy left = " .. infoChar.energy)
 	

	info = boxHit:getinfo()
	print ("Info type: " .. info.type)
	-- player = monkey.getEntity("player")
	flip = entityHitting.flipx and -1 or 1
	
 -- 	print ("pos = (" .. tostring(entityHit.x) .. ", " .. tostring(entityHit.y) .. ")")
	-- infoChar.energy = infoChar.energy -1
	if (infoChar.energy <= 0) then

		-- This will call the special collision handler based on the collision info type
	 	collisionResponse[info.type](entityHit, info, entityHitting)
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


collisionMaker = {}
collisionResponse = {}

require("collision/hbl")
require("collision/clear")


-- Body metrics
-- headY = y where head starts
-- bodyY = y where body starts
-- headHeight = height of head box
-- boxWidth = width of collision boxes
function makeCharacter(args) 
	local d = {
		depth = { 
		    type = "linear_y", values = {0, 1, 400, 0}
		}
	}
	local sprite = args.template.sprite
	
	-- Compute metrics
	local scale = args.template.scale or 1

	print ("scale =  " .. tostring(scale))
	local statemachine = { initialstate = "walk"} 
	statemachine.states = {}
	local tag = ""
	if (args.type == "player") then
		tag = "player"
		statemachine.keys = args.template.keys
		statemachine.states[1] = {
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
		}
		statemachine.states[2] = {
			id="ishit", type="empty"
		}
	elseif (args.type == "enemy") then
		tag = nextTag()
		statemachine.transitionmatrix = args.template.transitionmatrix
		statemachine.states[1] = {
			id="walk",
			type ="aiwalk",
			speed = args.template.speed,
			target = "player"
		}
		statemachine.states[2] = {
			id="ishit", type="empty"
		}
		statemachine.states[3] = {
			id ="idle", type="empty"
		}
	end

	-- add hit state
	local keys = args.template.keys
	local prob = args.template.transitionmatrix
	if (args.template.hit ~= nil) then
		for k, v in ipairs(args.template.hit) do
			print ("Adding state " .. v.id)
			table.insert (statemachine.states, 
			{ 
				id=v.id,
				type="hit",
				anim=v.anim,
				frame=v.frame,
				mask=2,
				shape = {type="rect", width=v.width*scale, height=v.height*scale},
				offset = {v.offset[1]*scale, v.offset[2]*scale},
				func = ciao
			})
		end
	end
	
	
	local c = collisionMaker[args.template.collisionType](args)
	local children = {
			-- shadow
			{
				gfx = { shape={type="ellipse", semiaxes={ 50, 10} }, draw="solid", color={0,0,0,128} },
				shadow = {}
			},
			-- collision boxes
		}
	for i, c in ipairs(c) do
		table.insert(children, c)
	end
	


	return 
	{
		tag = tag,
		gfx = { model=args.template.sprite, anim="idle", scale = scale},
		collider= { shape = {type="rect", width=1, height=1}, tag=1, flag=1},
		pos = {args.x, args.y, 0},
		depth = d,
		children = children,
		statemachine = statemachine,
		info = args.template.info
	}
end
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