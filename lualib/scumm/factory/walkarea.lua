scumm.factory.walkarea = function(args)
	return {
		walkarea = {
			shape = args.shape,
			priority = args.priority or 0,
			depth = args.depth,
			scale = args.scale,
		},
		actions = {
			walk = function(x,y) return scumm.ui.walk {pos={x, y}} end
		}
	}
end
