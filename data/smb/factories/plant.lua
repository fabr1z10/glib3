factory.plant = {}

factory.plant.create = function (args, pos) 
	glib.assert (args.sprite, "sprite")
	glib.assert (args.pos, "pos")
	return {
		pos = {args.pos[1]*16, args.pos[2]*16, -2},
		type = "sprite",
		model = args.sprite,
		components = {
			{ 
				type = "smartcollider", 
				tag = variables.collision.tags.plant, 
				flag = variables.collision.flags.foe, 
				mask = variables.collision.flags.player
			},
			{
				type = "polymover",
				origin = {0,0},
				loop_type = 1,
				movements = {
					{ delta = {0,-32}, speed = 50, hold = 1},
					{ delta = {0,32}, speed = 50, hold = 1},

				}
			}
		}
	}
end