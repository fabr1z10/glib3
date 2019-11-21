factory.rotatingfire = {}

factory.rotatingfire.create = function (args, pos) 
	local p = {args.pos[1]*16, args.pos[2]*16, 0}
	local children = {}

	for i =1,args.n do

		table.insert(children, {
			type = "sprite",
			model = args.model,
			components = {
				{ type="ellipsemover", origin = {0,0}, radii ={8*(i-1), 8*(i-1)}, period=1},
				{ 
					type = "smartcollider", 
					tag = variables.collision.tags.plant, 
					flag = variables.collision.flags.foe, 
					mask = variables.collision.flags.player
				},
			}
		})
	end

	return {
		pos = p,
		type = "sprite",
		model = args.model,
		children = children
		-- components = {
		-- 	{ type="ellipsemover", origin = p, radii ={8, 8}, period=1},
		-- 	{ 
		-- 		type = "smartcollider", 
		-- 		tag = variables.collision.tags.plant, 
		-- 		flag = variables.collision.flags.foe, 
		-- 		mask = variables.collision.flags.player
		-- 	},
		-- }

	}

end
