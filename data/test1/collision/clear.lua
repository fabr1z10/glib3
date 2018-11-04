
collisionMaker.clear = function(args)
	-- compute metrics
	local scale = args.template.scale or 1
	local boxWidth = args.template.boxWidth * scale
	local boxHeight = (args.template.headY + args.template.headHeight) * scale
	local hw = 0.5 * args.template.boxWidth
	local shape = { type = "rect", width = boxWidth, height = boxHeight, offset = {-hw, 0}}
	return {
		{
			pos={0, 0, 0},
		 	gfx = {
		 		shape= shape,
		 		color={255,255,255,255}
		 	},
			collider = {
				shape= shape, 
				tag=1, 
				flag=2
			},
			info = {
				type = "clear",
				spriteid = args.template.sprite,
				offset = {0, headY},
				scale =0.5
			}
		}
	}
end

collisionResponse.clear = function (entityHit, infoBox, entityHitting)
	entityHit:remove()		
end