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