local dt = 0.1

sprites.door_kitchen = {
	id = "door_kitchen",
    sheet = "gfx/anims.png",
    type="sprite",
    ppu=1,
    animations = {
        { name = "close", frames = { {duration = dt, quads = { { x = 222, y = 280, width = 37, height = 53, anchor = {0, 0}}}}}},
        { name = "open", frames = { {duration = dt, quads = { { x = 183, y = 280, width = 37, height = 53, anchor = {0, 0}}}}}}
    }
}

sprites.door_kitchen_pier = 
{
	id = "door_kitchen_pier",
    sheet = "gfx/anims.png",
    type="sprite",
    ppu=1,
    animations = {
    	{ name = "close", frames = { {duration = dt, quads = { { x = 399, y = 280, width = 32, height = 60, anchor = {0, 0}}}}}},
        { name = "open", frames = { {duration = dt, quads = { { x = 365, y = 280, width = 32, height = 60, anchor = {0, 0}}}}}}
    }
}

sprites.kitchen_table = 
{
	id = "kitchen_table",
	sheet = "gfx/anims.png",
	type="sprite",
	ppu = 1,
	animations = {
		{ name="default", frames = { {duration = dt, quads = { { x = 126, y = 208, width = 33, height = 26, anchor = {0, 0}}}}}}
	}
}

sprites.potostew =
{
	id ="potostew",
	sheet ="gfx/anims.png",
	type="sprite",
	ppu=1,
	animations = {
	{ 
           name="default", 
           frames = { 
               { duration = dt, quads = { { x = 254, y = 220, width = 29, height = 17, anchor = {0, 0}}}},
               { duration = dt, quads = { { x = 254, y = 239, width = 29, height = 17, anchor = {0, 0}}}},
               { duration = dt, quads = { { x = 254, y = 258, width = 29, height = 17, anchor = {0, 0}}}},
		}
	}}
}

sprites.kitchen_meat = 
{
	id = "kitchen_meat",
	sheet = "gfx/anims.png",
	type="sprite",
	ppu = 1,
	animations = {
	{ name="default", frames = { {duration = dt, quads = { { x = 49, y = 37, width = 24, height = 6, anchor = {0, 0}}}}}}
	}
}

sprites.kitchen_pot= 
{
	id = "kitchen_pot",
	sheet = "gfx/anims.png",
	type="sprite",
	ppu = 1,
	animations = {
	{ name="default", frames = { {duration = dt, quads = { { x = 75, y = 36, width = 15, height = 7, anchor = {0, 0}}}}}}
	}
}

sprites.kitchen_fish = 
{
	id = "kitchen_fish",
	sheet = "gfx/anims.png",
	type="sprite",
	ppu = 1,
	animations = {
	{ name="default", frames = { {duration = dt, quads = { { x = 33, y = 36, width = 12, height = 7, anchor = {0, 0}}}}}}
	}
}

sprites.plank = {
	id = "plank",
	sheet = "gfx/anims3.png",
	type="sprite",
	ppu = 1,
	animations = {
	{ name="default", frames = { {duration = dt, quads = { { x = 2, y = 194, width = 67, height = 24, anchor = {0, 0}}}}}},
	{ name="pushed", frames = { {duration = dt, quads = { { x = 2, y = 169, width = 61, height = 24, anchor = {0, 0}}}}}}
	}
}

sprites.seagull = {
	id = "seagull",
	sheet = "gfx/anims3.png",
	type ="sprite",
	ppu = 1,
	animations = {
		{
			name = "flying",
			frames = {	
				{duration = dt, quads = {{x=39, y = 33, width=20, height=14, anchor = {-307,-37}}}},
				{duration = dt, quads = {{x=39, y = 49, width=25, height=12, anchor = {-295,-35}}}},
				{duration = dt, quads = {{x=39, y = 33, width=20, height=14, anchor = {-292,-33}}}},
				{duration = dt, quads = {{x=39, y = 63, width=19, height=25, anchor = {-285,-29}}}},
				{duration = dt, quads = {{x=39, y = 90, width=19, height=19, anchor = {-277,-32}}}},
				{duration = dt, quads = {{x=39, y = 63, width=19, height=25, anchor = {-269,-22}}}},
				{duration = dt, quads = {{x=39, y = 33, width=20, height=14, anchor = {-260,-25}}}},
				{duration = dt, quads = {{x=39, y = 49, width=25, height=12, anchor = {-247,-23}}}},
				{duration = dt, quads = {{x=39, y = 33, width=20, height=14, anchor = {-244,-21}}}},
				{duration = dt, quads = {{x=39, y = 90, width=19, height=19, anchor = {-245,-23}}}},
				{duration = dt, quads = {{x=39, y = 90, width=19, height=19, anchor = {-250,-17}}}},
				{duration = dt, quads = {{x=39, y = 111, width=23, height=15, anchor = {-248,-14}}}},
				{duration = dt, quads = {{x=39, y = 128, width=25, height=11, anchor = {-246,-13}}}},
				{duration = dt, quads = {{x=39, y = 111, width=23, height=15, anchor = {-243,-12}}}},
				{duration = dt, quads = {{x=39, y = 141, width=19, height=9, anchor = {-243,-10}}}}
			}
		},
		{
			name = "eating",
			frames = {	
				{duration = dt, quads = {{x=39, y = 152, width=15, height=13, anchor = {-245,-10}}}},
				{duration = dt, quads = {{x=61, y = 36, width=18, height=11, anchor = {-242,-10}}}},
				{duration = dt, quads = {{x=66, y = 51, width=17, height=10, anchor = {-243,-10}}}},
				{duration = dt, quads = {{x=60, y = 63, width=19, height=9, anchor = {-242,-10}}}},
				{duration = dt, quads = {{x=60, y = 74, width=19, height=10, anchor = {-242,-10}}}},
				{duration = dt, quads = {{x=60, y = 63, width=19, height=9, anchor = {-242,-10}}}},	
				{duration = dt, quads = {{x=60, y = 74, width=19, height=10, anchor = {-242,-10}}}},
				{duration = dt, quads = {{x=60, y = 86, width=17, height=10, anchor = {-243,-10}}}},
				{duration = dt, quads = {{x=60, y = 86, width=17, height=10, anchor = {-243,-10}}}},
				{duration = dt, quads = {{x=60, y = 86, width=17, height=10, anchor = {-243,-10}}}},
				{duration = dt, quads = {{x=60, y = 98, width=18, height=11, anchor = {-242,-10}}}},
				{duration = dt, quads = {{x=64, y = 111, width=15, height=13, anchor = {-245,-10}}}},
				{duration = dt, quads = {{x=66, y = 125, width=11, height=17, anchor = {-249,-10}}}},
				{duration = dt, quads = {{x=60, y = 144, width=12, height=17, anchor = {-248,-10}}}},
				{duration = dt, quads = {{x=85, y = 37, width=12, height=17, anchor = {-248,-10}}}},
			}
		},
		{
			name = "jump1",
			frames = {	
				{duration = dt, quads = {{x=39, y = 152, width=15, height=13, anchor = {-245,-40}}}},
				{duration = dt, quads = {{x=39, y = 152, width=15, height=13, anchor = {-245,-64}}}},
				{duration = dt, quads = {{x=39, y = 152, width=15, height=13, anchor = {-245,-94}}}},
				{duration = dt, quads = {{x=39, y = 152, width=15, height=13, anchor = {-245,-100}}}},
				{duration = dt, quads = {{x=39, y = 90, width=19, height=19, anchor = {-237,-82}}}},	
				{duration = dt, quads = {{x=39, y = 90, width=19, height=19, anchor = {-237,-64}}}},	
				{duration = dt, quads = {{x=39, y = 90, width=19, height=19, anchor = {-237,-40}}}},	
				{duration = dt, quads = {{x=39, y = 90, width=19, height=19, anchor = {-237,-10}}}}
			}
		},
		{
			name = "jump2",
			frames = {	
				{duration = dt, quads = {{x=39, y = 152, width=15, height=13, anchor = {-245,-40}}}},
				{duration = dt, quads = {{x=39, y = 152, width=15, height=13, anchor = {-245,-64}}}},
				{duration = dt, quads = {{x=39, y = 152, width=15, height=13, anchor = {-245,-82}}}},			
				{duration = dt, quads = {{x=39, y = 152, width=15, height=13, anchor = {-245,-94}}}},			
				{duration = dt, quads = {{x=39, y = 152, width=15, height=13, anchor = {-245,-100}}}},		
				{duration = dt, quads = {{x=66, y = 165, width=19, height=19, anchor = {-249,-98}}}},			
				{duration = dt, quads = {{x=66, y = 165, width=19, height=19, anchor = {-255,-94}}}},			
				{duration = dt, quads = {{x=66, y = 165, width=19, height=19, anchor = {-261,-86}}}},			
				{duration = dt, quads = {{x=66, y = 165, width=19, height=19, anchor = {-267,-74}}}},			
				{duration = dt, quads = {{x=66, y = 165, width=19, height=19, anchor = {-273,-58}}}},			
				{duration = dt, quads = {{x=66, y = 165, width=19, height=19, anchor = {-279,-38}}}},			
				{duration = dt, quads = {{x=3, y = 221, width=23, height=7, anchor = {-268,-34}}}},			
				{duration = dt, quads = {{x=39, y = 63, width=19, height=25, anchor = {-259,-27}}}},			
				{duration = dt, quads = {{x=39, y = 33, width=20, height=14, anchor = {-254,-23}}}},			
				{duration = dt, quads = {{x=39, y = 49, width=25, height=12, anchor = {-245,-15}}}},			
				{duration = dt, quads = {{x=39, y = 90, width=19, height=19, anchor = {-250,-17}}}},			
				{duration = dt, quads = {{x=39, y = 111, width=23, height=15, anchor = {-248,-14}}}},			
				{duration = dt, quads = {{x=39, y = 128, width=25, height=11, anchor = {-246,-13}}}},			
				{duration = dt, quads = {{x=39, y = 111, width=23, height=15, anchor = {-244,-12}}}},			
				{duration = dt, quads = {{x=39, y = 141, width=19, height=9, anchor = {-243,-11}}}}		
			}
		},
		{
			name = "nofish",
			frames = {	
				{duration = dt, quads = {{x=39, y = 152, width=15, height=13, anchor = {-245,-10}}}},
				{duration = dt, quads = {{x=88, y = 57, width=7, height=13, anchor = {-250,-10}}}},
				{duration = dt, quads = {{x=39, y = 152, width=15, height=13, anchor = {-245,-10}}}},
				{duration = dt, quads = {{x=39, y = 152, width=15, height=13, anchor = {-245,-10}}}},
				{duration = dt, quads = {{x=82, y = 72, width=15, height=13, anchor = {-245,-10}}}},
				{duration = dt, quads = {{x=84, y = 87, width=7, height=13, anchor = {-250,-10}}}},
				{duration = dt, quads = {{x=82, y = 72, width=15, height=13, anchor = {-245,-10}}}},
				{duration = dt, quads = {{x=28, y = 220, width=21, height=17, anchor = {-243,-10}}}},
				{duration = dt, quads = {{x=66, y = 165, width=19, height=19, anchor = {-247,-11}}}},
				{duration = dt, quads = {{x=51, y = 220, width=19, height=25, anchor = {-248,-10}}}},
				{duration = dt, quads = {{x=3, y = 233, width=20, height=14, anchor = {-250,-14}}}},
				{duration = dt, quads = {{x=51, y = 220, width=19, height=25, anchor = {-260,-20}}}},
				{duration = dt, quads = {{x=3, y = 233, width=20, height=14, anchor = {-264,-23}}}},
				{duration = dt, quads = {{x=24, y = 244, width=25, height=12, anchor = {-268,-24}}}},
				{duration = dt, quads = {{x=3, y = 233, width=20, height=14, anchor = {-272,-25}}}},
				{duration = dt, quads = {{x=51, y = 220, width=19, height=25, anchor = {-276,-25}}}},
				{duration = dt, quads = {{x=66, y = 165, width=19, height=19, anchor = {-280,-31}}}},
				{duration = dt, quads = {{x=51, y = 220, width=19, height=25, anchor = {-284,-27}}}},
				{duration = dt, quads = {{x=3, y = 233, width=20, height=14, anchor = {-288,-30}}}},
				{duration = dt, quads = {{x=24, y = 244, width=25, height=12, anchor = {-292,-32}}}},
				{duration = dt, quads = {{x=3, y = 233, width=20, height=14, anchor = {-296,-33}}}},
				{duration = dt, quads = {{x=51, y = 220, width=19, height=25, anchor = {-300,-32}}}},
				{duration = dt, quads = {{x=66, y = 165, width=19, height=19, anchor = {-304,-38}}}},
				{duration = dt, quads = {{x=51, y = 220, width=19, height=25, anchor = {-308,-34}}}},
				{duration = dt, quads = {{x=3, y = 233, width=20, height=14, anchor = {-312,-39}}}}
			}
		},	
	}
}