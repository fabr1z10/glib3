scumm.factory.walkarea = function(args)
	return 	{
		pos = {0,0,0},
		components = {
	      	{ 
				type ="walkarea",
				priority = args.priority or 0,
       			target = "player",
				shape = args.shape,
				blockedlines = args.blockedlines
			}
      	}
	}
end
