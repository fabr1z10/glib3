

collisionMaker.headBodyLegs = function(args)
	-- compute metrics
	local scale = args.template.scale or 1
	local boxWidth = args.template.boxWidth * scale
	local headY = args.template.headY * scale
	local bodyY = args.template.bodyY * scale
	local headHeight = args.template.headHeight * scale
	local hw = 0.5 * args.template.boxWidth
	local bodyHeight = (headY - bodyY)
	local legsHeight = bodyY 
	local headShape = { type = "rect", width = boxWidth, height = headHeight, offset = {-hw, 0}}
	local bodyShape = { type = "rect", width = boxWidth, height = bodyHeight, offset = {-hw, 0}}
	local legsShape = { type = "rect", width = boxWidth, height = legsHeight, offset = {-hw, 0}}
	return {	
		{
			-- head
			pos={0, headY, 0},
		 	gfx = {
		 		shape= headShape,
		 		color={255,255,255,255},
				scale = scale
		 	},
			collider = {
				shape= headShape, 
				tag=1, 
				flag=2
			},
			info = {
				type = "head",
				spriteid = args.sprite,
				offset = {0, headY},
				scale =0.5
			},
		},
		{
			pos={0, bodyY, 0},
			gfx = {
				shape= bodyShape,
			 	color={255,255,255,255},
				scale = scale

			},
			collider = {
				shape= bodyShape,
				tag=1, 
				flag=2
			},
			info = {
				type = "body",
				spriteid = args.template.sprite,
				offset = {0, args.template.bodyY},
				headx = 0, 
				heady = args.template.headY,
				scale =0.7
			}
		},
		{
			pos={0, 0, 0},
			gfx = {
				shape= legsShape,
			 	color={255,255,255,255},
				scale = scale

			},
			collider = {
				shape= legsShape,
				tag=1, 
				flag=2
			},
			info = {
				type = "legs",
				spriteid = args.ssprite,
			}
		}
	}
end

collisionResponse.head = function (entityHit, infoBox, entityHitting)
print ("Hitting head")
end
collisionResponse.legs = function (entityHit, infoBox, entityHitting)
print ("Hitting legs")
end

collisionResponse.body = function (entityHit, infoBox, entityHitting)
		
	print ("Hitting body")
	-- 	main = monkey.getEntity("main")
	-- 	player = monkey.getEntity("player")
	-- 	flip = player.flipx and 1 or -1
	-- 	local b = nextTag()
	-- 	local b1 = nextTag()
	-- 	print ("Adding object with tag " .. b)
	--     monkey.addEntity ({
	-- 		pos = {pp.x, pp.y, 0},
	-- 		depth = d,
	-- 		gfx = { model = info.spriteid, anim = "body"},
	-- 		tag = b
	-- 	}, main)
	-- 	-- adding fx
	--     monkey.addEntity ({
	-- 		pos = {pp.x + info.offset[1], pp.y + info.offset[2], 0},
	-- 		depth = d,
	-- 		gfx = { model = "expl1", anim = "default", scale = info.scale},
	-- 		tag = b1
	-- 	}, main)
	--  	local s = script:new("_cook")
	-- 	s.actions ={
	-- 		[1] = {type="noop"},
	-- 		[2] = { type="rotate", speed = flip * 60, acceleration = flip * 200, deg = flip*90, actor = b, after={1} },
	-- 		[3] = { type="animate", actor=b1, anim="default", loop = 1, after={1}},
	-- 		[4] = { type="animate", actor=b1, anim="stop", after={3}},
	-- 		[5] = { type ="movegravity", actor=b1, velocity={0,-100}, g=100, ystop = pp.y, after={1}}
	-- 	}	
	-- 	monkey.play(s)
	--end

	main = monkey.getEntity("main")
	
	flip = entityHitting.flipx and 1 or -1
	local tagHead = nextTag()
	local tagLegs = nextTag()
	local b1 = nextTag()
    monkey.addEntity ({
		pos = {entityHit.x + infoBox.headx, entityHit.y + infoBox.heady, 0},
		depth = d,
		gfx = { model = info.spriteid, anim = "head"},
		tag = tagHead
	}, main)
    monkey.addEntity ({
		pos = {entityHit.x, entityHit.y, 0},
		depth = d,
		gfx = { model = info.spriteid, anim = "legs"},
		tag = tagLegs
	}, main)
	-- adding fx
    monkey.addEntity ({
		pos = {entityHit.x + info.offset[1], entityHit.y + info.offset[2], 0},
		depth = d,
		gfx = { model = "expl1", anim = "default", scale = info.scale},
		tag = b1
	}, main)
 	local s = script:new("a")
	s.actions ={
		[1] = {type="noop"},
		[2] = { type="rotate", speed = flip * 60, acceleration = flip * 200, deg = flip*90, actor = tagLegs, after={1} },
		[3] = { type="animate", actor=b1, anim="default", loop = 1, after={1}},
		[4] = { type="animate", actor=b1, anim="stop", after={3}},
		[5] = { type ="movegravity", actor=b1, velocity={0,-100}, g=100, ystop = entityHit.y, after={1}},
		[6] = {type="movegravity", actor=tagHead, velocity = {20, 100}, g = 100,ystop = entityHit.y, after= {1}},
	}	
	entityHit:remove()
	monkey.play(s)

end