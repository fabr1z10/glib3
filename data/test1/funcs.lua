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
		gfx = { model=args.sprite, anim="idle", scale = scale},	
		pos = {args.x, args.y, 0},
		depth = d,
		statemachine = {
			initialstate = "walk",
			states = states
		},
		children = {
			{
				-- head
				pos={0, headY, 0},
		 		gfx = {
		 			shape= headShape,
		 			color={255,255,255,255}
		 		},
				collider = {
					shape= headShape, 
					tag=1, 
					flag=2
				},
				info = {
					pos = "head",
					spriteid = args.sprite,
					offset = {0, headY},
					scale =0.5
				},
			},
			{
				pos={0, bodyY, 0},
				gfx = {
					shape= bodyShape,
				 	color={255,255,255,255}
				},
				collider = {
					shape= bodyShape,
					tag=1, 
					flag=2
				},
				info = {
					pos = "body",
					spriteid = args.ssprite,
					offset = {0, 20},
					headx = 0, 
					heady = headY,
					scale =0.7
				}
			},				
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