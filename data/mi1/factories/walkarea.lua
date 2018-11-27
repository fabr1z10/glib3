factory.walkarea = {}

factory.walkarea.create = function(args)
	return 	{
		pos = {0,0,0},
		components = {
	      	{ 
				type ="walkarea",
				priority = 0,
       			target = "player",
				shape = args.shape,
			}
      	}
	}
end
