items.parallaxbg = {}					



items.parallaxbg.create = function(args)
	local pos = args.pos or {0, 0}
	local z = args.z or -2
	local img = args.img
	local width = args.width
	local height = args.height
	local factor = args.factor

	return {
		tag = args.tag,
		pos = {pos[1], pos[2], z},
		components = {
			{ type="gfx", image = img, width = 2*width, height = height, rep={2,1} },
			{ type="parallax", cam="maincam", factor = factor, width = width, height = height}
		}
	}
end