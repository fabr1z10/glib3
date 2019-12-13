factory.image = {}
factory.bgcolor = {}

-- display image with repetition, and opt parallax
factory.image.create = function(args) 
	assert(args.pos, "pos")	
	assert(args.img, "img")

	-- optional params
	local repx = args.repx or 1
	local repy = args.repy or 1
	local z = args.z or 0

	local components = {
		{ 
			type = "gfx", 
			image = args.img,
			rep = {repx, repy},
		},
	}
	if (args.parallax) then
		table.insert(components, { type="parallax", cam="maincam", factor = args.parallax })
	end
	return {
		pos = { args.pos[1] * engine.tilesize, args.pos[2] * engine.tilesize, z },
		components = components
	}
end

factory.bgcolor.create = function(args)
	assert(args.pos, "pos")	
	assert(args.color, "color")
	assert(args.width, "width")
	assert(args.height, "height")
	local px = args.px or 1
	local py = args.py or 1
	return { 
 		tag = args.tag,
		pos = {0, 0, args.z or -5}, 
		components = { 
			{
				type="gfx", 
				draw="solid", 
				shape = { type="rect", width=args.width, height=args.height}, 
				--color= {92,148,252,255} 
				color = args.color,
			},
			{ type="parallax", cam="maincam", factor = {px,py}}

		}
	}

end