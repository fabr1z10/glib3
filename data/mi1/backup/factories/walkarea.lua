factory.walkarea = function(args)
	return 	{
		pos = {0,0,0},
		components = {
	      	{ 
				type ="walkarea",
				priority = 0,
       			target = "player",
				shape = args.shape,
				blockedlines = args.blockedlines
			}
      	}
	}
end
	-- {
	-- 	pos = {0,0,0},
	-- 	components = {
 --      		{ 
	-- 			type ="walkarea",
	-- 			priority = 0,
 --       			target = "player",
	-- 			shape = { 
	--                 type = "poly", 
	--                 outline = {0,24, 123,63,199,63,299,30,377,30,385,35,454,35,470,0,0}
	--             }
	-- 		}
 --      	}
	-- },