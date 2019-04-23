scumm.factory.walkarea = function(args)
    
	return 	{
		pos = {0,0,0},
		tag = args.tag,
		components = {
	      	{ 
				type ="walkarea",
				priority = args.priority or 0,
       			target = "player",
				shape = args.shape,
				blockedlines = args.blockedlines,
				handler = args.handler,
				scale = args.scale,
				depth = args.depth,
			}
      	},
		actions = {
			walk = function(x, y)
				print ("fanculo") 
				return scumm.ui.walk { pos = {x, y}, walkarea = args.tag } 
			end
		},
      	children = args.children
	}
end
