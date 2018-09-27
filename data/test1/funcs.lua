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

function makeEnemy(spriteName, x, y, speed, headY, bodyY, boxWidth, headHeight) 
	local d = {
		depth = { 
		    type = "linear_y", values = {0, 1, 400, 0}
		}
	}
	local hw = 0.5 * boxWidth
	local bodyHeight = headY - bodyY
	local headShape = { type = "rect", width = boxWidth, height = headHeight, offset = {-hw, 0}}
	local bodyShape = { type = "rect", width = boxWidth, height = bodyHeight, offset = {-hw, 0}}
	return
	{
		gfx = { model=spriteName, anim="idle"},	
		pos = {x, y, 0},
		depth = d,
		statemachine = {
			initialstate = "walk",
			states = {
				{
					id="walk",
					type ="aiwalk",
					speed = speed,
					target = "player"
				}
			}
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
					spriteid = spriteName,
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
					spriteid = spriteName,
					offset = {0, 20},
					headx = 0, 
					heady = headY,
					scale =0.7
				}
			},				
		}
	}
end