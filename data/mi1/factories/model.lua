factory.model = {}

local dt = 0.1

factory.model.create_simple = function(args) 
	engine.assets.models[args.id] = {
    	sheet = args.sheet,
    	type = "sprite",
    	ppu=1,
		animations = {
			{ name = "default", frames = { { duration = dt, quads = {{ id = args.frame }}}}}
		}
	}

end