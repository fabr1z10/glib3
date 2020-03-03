function scumm.factory.room_dialogue (args) 
	
	glib.assert(args.player, 'player')

	local room_width = engine.device_size[1]
	local room_height = engine.device_size[2] - engine.config.ui.height
	local camWidth = engine.device_size[1]
	local camHeight = engine.device_size[2] - engine.config.ui.height
	local font_size = args.font_size or 8

	local p = Room:new(args)

	-- add the main scene
	table.insert (p.scene, 
	{
		tag = "main",
		camera = {
			tag = "maincam",
			type="ortho",
			size = {room_width, room_height},
			bounds = {0, 0, room_width, room_height},
			viewport = {0, engine.config.ui.height, room_width, room_height}
		},
		children = {
			scumm.factory.object { id = args.player },
		}
	})		

	p.refs['main'] = p.scene[1].children

	-- add the ui
	table.insert(p.scene, 			
	{
		tag = 'ui',
		camera = {
			tag = 'uicam',
			type= 'ortho',
			size = {320, 56},
			bounds = {0, 0, 320, 56},
			viewport = {0, 0, 320, 56}
		},
		children = {
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

	p.refs['ui'] = p.scene[2].children[1].children[1].children
	print ('sfioo')
	return p
end

