items.parallaxbg = {}					



items.parallaxbg.create = function(args)

	local img = args.img
	local width = args.width
	local height = args.height
	local factor = args.factor
	return {
		pos = {0,0,-2},
		components = {
			{ type="gfx", image = img, width = 2*width, height = height, rep={2,1} },
			{ type="parallax", cam="maincam", factor = factor, width = width, height = height}
		}
	}
end