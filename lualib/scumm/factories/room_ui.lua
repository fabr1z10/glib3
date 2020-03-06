function scumm.factory.room_ui (args) 
	
	glib.assert(args.width, 'required width')
	glib.assert(args.height, 'required height')

	local room_width = args.width
	local room_height = args.height
	local camWidth = engine.device_size[1]
	local camHeight = engine.device_size[2] - engine.config.ui.height
	local font_size = args.font_size or 8

	local p = Room:new(args)


	print ("NOW SCENE HAS SIZE:"..tostring(#p.scene))
	-- add the main scene
	table.insert (p.scene, {
		tag = "main",
		camera = {
			tag = "maincam",
			type="ortho",
			size = {camWidth, camHeight},
			bounds = {0, 0, room_width, room_height},
			viewport = {0, engine.config.ui.height, camWidth, camHeight}
		},
		children = {}
	})
	p.refs['main'] = p.scene[1].children

	-- add the ui
	table.insert(p.scene, 			
	{
	 	tag = "ui",
	 	children = {
	 		{
	 			tag = "mainui",
	 			pos = {0,0,0},
	 			children = {
	 				{
	 					tag = "verbs",
					 	camera = {
					 		tag = "uicam",
					 		type="ortho",
					 		size = {camWidth, engine.config.ui.height},
					 		bounds = {0, 0, camWidth, engine.config.ui.height},
					 		viewport = {0, 0, camWidth, engine.config.ui.height}
					 	},
					 	children = {
					 		{
					 			type = "text",
			 			    	tag = "currentaction",
			 			    	font = engine.config.ui.font,
			 			    	text = engine.config.verbs[engine.config.default_verb].text,
			 			    	align = "bottom",
			 			    	color = engine.config.ui.currentaction_color,
			 			    	pos={160,48,0}
			 				}							 		
					 	}
	 				},
	 			 	{
					 	pos = {0,0,0},
					 	children =  {
			 		    	{
					 			type = 'textview', 
								tag = 'inventory',
					 			pos = {150, 0, 0},
					 			size = {170, 48},
					 			font_size = 8,
					 			lines = 6,
					 			deltax = 26,
					 			factory = scumm.factory.inventorybutton
					  	    }
					 	}
					}
			 	}
			},
			{
				pos  = {0,0,0},
				children =  {
					{
			 			type = 'textview', 
			 			tag = 'dialogueui',
			 	 		pos = {0, 0, 0},
			 	 		size = {320, 56},
			 	 		font_size = 8,
			 	 		lines = 6,
			 	 		deltax = 26,
			 	 		factory = scumm.factory.dialoguebutton
			  		}
			 	}						
			}			 		
		}
	})

	-- add other
	table.insert(p.scene, 			
	{
		tag = "other",
	 	camera = {
	 		tag = "uicam",
	 		type="ortho",
	 		size = {camWidth, camHeight},
	 		bounds = {0, 0, camWidth, camHeight},
	 		viewport = {0, 0, camWidth, camHeight}
	 	},
	 	children = {
		}
	})

	p.refs['ui'] = p.scene[2].children[1].children[1].children
	-- add the verbs
	local row = 2
	local count = 0
	
	for _, verb in ipairs(engine.config.verbset[1]) do
	 	local col = 1+ count // 4
	 	local x = 2 + (col-1)*46
	 	local y = engine.config.ui.height - row*font_size
	 	row = row + 1
	 	if (row > 5) then row = 2 end
	 	count = count +1
		print ('adding veeere')
	 	table.insert (p.refs.ui, scumm.factory.verbbutton {pos={x, y}, verb = verb} )
	end	

	table.insert(p.initstuff, function() 
		scumm.state.actionInfo.verb = engine.config.default_verb
		scumm.func.reset_verb()
		scumm.func.refresh_inventory()
	end)

	
	
	p:add_walkareas(args)
	p:load_dynamic_items()

	return p
end