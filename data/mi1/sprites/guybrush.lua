local dt = 0.1
spritesheets["guybrush"] = {
	walk_east_1 = {x=4, y=1, width = 32, height=47, anchor={17, 0}  },
	walk_east_2 = {x = 39, y=1, width=17, height=47, anchor={13, 0}  },
	walk_east_3 = {x=60, y=1, width=19, height=47, anchor={12, 0}  },
	walk_east_4 = {x=83, y=1, width=31, height=47, anchor={16, 0} },
	walk_east_5 = {x=117, y=1, width=18, height=47, anchor={13, 0} },
	walk_east_6 = {x=141, y=1, width=19, height=47, anchor={12, 0} },
	walk_south_1 = {x=207, y=51, width=22, height=47, anchor={11, 0} },
	walk_south_2 = {x=231, y=51, width=21, height=47, anchor={11, 0} },
	walk_south_3 = {x=3, y=101, width=20, height=47, anchor={10, 0} },
	walk_south_4 = {x=25, y=101, width=22, height=47, anchor={12, 0} },
	walk_south_5 = {x=49, y=101, width=21, height=47, anchor={11, 0} },
	walk_south_6 = {x=72, y=101, width=20, height=47, anchor={11, 0} },
	walk_north_1 = {x=72, y=51, width=21, height=47, anchor={10, 0} },
	walk_north_2 = {x=95, y=51, width=21, height=47, anchor={10, 0} },
	walk_north_3 = {x=118, y=51, width=21, height=47, anchor={10, 0} },
	walk_north_4 = {x=139, y=51, width=21, height=47, anchor={10, 0} },
	walk_north_5 = {x=163, y=51, width=21, height=47, anchor={10, 0} },
	walk_north_6 = {x=186, y=51, width=19, height=47, anchor={8, 0} },
	idle_east = {x=2, y=51, width=19, height=47, anchor = {10, 0}},
	idle_south = {x=24, y=51, width=22, height=47, anchor = {12, 0}},
	idle_north = {x=49, y=51, width=20, height=47, anchor = {10, 0}},
	idle_body_south = {x=164, y=12, width=22, height=36, anchor= {12,0}},
	idle_body_east = {x=157, y=112, width=19, height=36, anchor= {10,0}},
	idle_body_north = {x=189, y=12, width=20, height=36, anchor= {10,0}},
	talk_head_south_1 = { x = 179, y = 129, width = 11, height = 13, anchor = {6, -34}},
	talk_head_south_2 = { x = 192, y = 129, width = 11, height = 13, anchor = {6, -34}},
	talk_head_south_3 = { x = 205, y = 129, width = 11, height = 13, anchor = {6, -34}},
	talk_head_south_4 = { x = 179, y = 143, width = 11, height = 13, anchor =  {6, -34}},
	talk_head_south_5 = { x = 192, y = 143, width = 11, height = 13, anchor = {6, -34}},
	talk_head_south_6 = { x = 205, y = 143, width = 11, height = 13, anchor = {6, -34}},
	talk_head_north_1 = { x = 220, y = 101, width = 11, height = 12, anchor = {6, -34}},
	talk_head_north_2 = { x = 233, y = 101, width = 11, height = 12, anchor = {6, -34}},
	talk_head_north_3 = { x = 220, y = 115, width = 11, height = 12, anchor = {6, -34}},
	talk_head_east_1 = { x = 179, y = 101, width = 11, height = 12, anchor = {7, -35}},
	talk_head_east_2 = { x = 192, y = 101, width = 11, height = 12, anchor = {7,-35}},
	talk_head_east_3 = { x = 205, y = 101, width = 11, height = 12, anchor = {7,-35}},
	talk_head_east_4 = { x = 179, y = 115, width = 11, height = 12, anchor = {7,-35}},
	talk_head_east_5 = { x = 192, y = 115, width = 11, height = 12, anchor = {7,-35}},
	talk_head_east_6 = { x = 205, y = 115, width = 11, height = 12, anchor = {7,-35}},
	operate_east = {x = 2, y = 150, width = 28, height = 45, anchor = {10, 0}},
	operate_south = {x = 125, y = 151, width = 18, height = 46, anchor = {12, 0}},
	operate_north = {x = 33, y = 150, width = 19, height = 45, anchor = {12, 0}},
	kneel_south = { x = 80, y = 163, width = 17, height = 33, anchor = {10, 0}},
	kneel_north = { x = 100, y = 163, width = 19, height = 33, anchor = {10, 0}},
	plank = {x = 57, y = 150, width = 21, height = 47, anchor = {10, 0}}



	-- idle_east_body = {},
	-- idle_east_head = {},
	-- idle_south_body = {},
	-- idle_south_head = {},
	-- idle_north_body = {},
	-- idle_north_head = {},


}
local s = spritesheets["guybrush"]
local file = "sprites/guybrush.png"

models["guybrush"] = {
    sheet = file,
    type = "sprite",
    ppu=1,
	animations = {
		{ name = "idle_e", frames = { { duration = dt, quads = {{ id = s.idle_east }}}}},
		{ name = "idle_n", frames = { { duration = dt, quads = {{ id = s.idle_north }}}}},
		{ name = "idle_s", frames = { { duration = dt, quads = {{ id = s.idle_south }}}}},
		{ name = "walk_e", frames = { 
			{ duration = dt, quads = {{ id = s.walk_east_1 }}},
			{ duration = dt, quads = {{ id = s.walk_east_2 }}},
			{ duration = dt, quads = {{ id = s.walk_east_3 }}},
			{ duration = dt, quads = {{ id = s.walk_east_4 }}},
			{ duration = dt, quads = {{ id = s.walk_east_5 }}},
			{ duration = dt, quads = {{ id = s.walk_east_6 }}}
		}},
		{ name = "walk_n", frames = { 
			{ duration = dt, quads = {{ id = s.walk_north_1 }}},
			{ duration = dt, quads = {{ id = s.walk_north_2 }}},
			{ duration = dt, quads = {{ id = s.walk_north_3 }}},
			{ duration = dt, quads = {{ id = s.walk_north_4 }}},
			{ duration = dt, quads = {{ id = s.walk_north_5 }}},
			{ duration = dt, quads = {{ id = s.walk_north_6 }}}
		}},
		{ name = "walk_s", frames = { 
			{ duration = dt, quads = {{ id = s.walk_south_1 }}},
			{ duration = dt, quads = {{ id = s.walk_south_2 }}},
			{ duration = dt, quads = {{ id = s.walk_south_3 }}},
			{ duration = dt, quads = {{ id = s.walk_south_4 }}},
			{ duration = dt, quads = {{ id = s.walk_south_5 }}},
			{ duration = dt, quads = {{ id = s.walk_south_6 }}}
		}},
		{ name = "talk_s", frames = { 
			{ duration = dt, quads = {{ id = s.idle_body_south }, { id = s.talk_head_south_1 }}},
			{ duration = dt, quads = {{ id = s.idle_body_south }, { id = s.talk_head_south_2 }}},
			{ duration = dt, quads = {{ id = s.idle_body_south }, { id = s.talk_head_south_1 }}},
			{ duration = dt, quads = {{ id = s.idle_body_south }, { id = s.talk_head_south_2 }}},
			{ duration = dt, quads = {{ id = s.idle_body_south }, { id = s.talk_head_south_3 }}},
			{ duration = dt, quads = {{ id = s.idle_body_south }, { id = s.talk_head_south_4 }}},
			{ duration = dt, quads = {{ id = s.idle_body_south }, { id = s.talk_head_south_2 }}},
			{ duration = dt, quads = {{ id = s.idle_body_south }, { id = s.talk_head_south_5 }}},
			{ duration = dt, quads = {{ id = s.idle_body_south }, { id = s.talk_head_south_6 }}},
			{ duration = dt, quads = {{ id = s.idle_body_south }, { id = s.talk_head_south_5 }}},
			{ duration = dt, quads = {{ id = s.idle_body_south }, { id = s.talk_head_south_1 }}},
			{ duration = dt, quads = {{ id = s.idle_body_south }, { id = s.talk_head_south_2 }}},
			{ duration = dt, quads = {{ id = s.idle_body_south }, { id = s.talk_head_south_6 }}},
		}},
		{ name = "talk_n", frames = { 
			{ duration = dt, quads = {{ id = s.idle_body_north }, { id = s.talk_head_north_1 }}},
			{ duration = dt, quads = {{ id = s.idle_body_north }, { id = s.talk_head_north_2 }}},
			{ duration = dt, quads = {{ id = s.idle_body_north }, { id = s.talk_head_north_1 }}},
			{ duration = dt, quads = {{ id = s.idle_body_north }, { id = s.talk_head_north_2 }}},
			{ duration = dt, quads = {{ id = s.idle_body_north }, { id = s.talk_head_north_3 }}},
		}},
		{ name = "talk_e", frames = { 
			{ duration = dt, quads = {{ id = s.idle_body_east }, { id = s.talk_head_east_1 }}},
			{ duration = dt, quads = {{ id = s.idle_body_east }, { id = s.talk_head_east_2 }}},
			{ duration = dt, quads = {{ id = s.idle_body_east }, { id = s.talk_head_east_3 }}},
			{ duration = dt, quads = {{ id = s.idle_body_east }, { id = s.talk_head_east_4 }}},
			{ duration = dt, quads = {{ id = s.idle_body_east }, { id = s.talk_head_east_2 }}},
			{ duration = dt, quads = {{ id = s.idle_body_east }, { id = s.talk_head_east_1 }}},
			{ duration = dt, quads = {{ id = s.idle_body_east }, { id = s.talk_head_east_5 }}},
			{ duration = dt, quads = {{ id = s.idle_body_east }, { id = s.talk_head_east_6 }}},
			{ duration = dt, quads = {{ id = s.idle_body_east }, { id = s.talk_head_east_1 }}},
			{ duration = dt, quads = {{ id = s.idle_body_east }, { id = s.talk_head_east_5 }}},
			{ duration = dt, quads = {{ id = s.idle_body_east }, { id = s.talk_head_east_1 }}},
			{ duration = dt, quads = {{ id = s.idle_body_east }, { id = s.talk_head_east_3 }}},
		}},
		{ name = "plank", frames = { { duration = dt, quads = {{ id = s.plank }}}}},
		{ name = "operate_e", frames = { { duration = dt, quads = {{ id = s.operate_east }}}}},
		{ name = "operate_n", frames = { { duration = dt, quads = {{ id = s.operate_north }}}}},
		{ name = "operate_s", frames = { { duration = dt, quads = {{ id = s.operate_south }}}}},
		--{ name = "kneel_e", frames = { { duration = dt, quads = {{ id = s.kneel_east }}}}},
		{ name = "kneel_n", frames = { { duration = dt, quads = {{ id = s.kneel_north }}}}},
		{ name = "kneel_s", frames = { { duration = dt, quads = {{ id = s.kneel_south }}}}},



	}
}

