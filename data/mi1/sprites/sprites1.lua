local dt = 0.1
local sheet = "sprites/sprites1.png"

spritesheets["sprites1"] = {
	arrow_up = {x=499, y=2, width = 12, height=20 },
	arrow_down = {x = 486, y=2, width=12, height=20 },
	arrow_up_focus = {x=499, y=23, width=12, height=20},
	arrow_down_focus = {x=486, y=23, width=12, height=20},
	low_moral_fiber_body_1 = { x = 1, y=1, width=31, height=30, anchor={13, 0} },
	low_moral_fiber_1_talk1 = {x=33, y=1, width=15, height=12, anchor ={8, 0}},
	low_moral_fiber_1_talk2 = {x=66, y=1, width=15, height=12, anchor ={7, 2} },
	low_moral_fiber_1_talk3 = {x=50, y=1, width=15, height=13, anchor ={7, 1}},
	low_moral_fiber_1_look_north = {x=83, y=1, width=14, height=12, anchor ={8, 0}},
	low_moral_fiber_1_rock1 = { x=33, y=15, width=34, height=39, anchor={17, 0}},
	low_moral_fiber_1_rock2 = { x=69, y=16, width=27, height=39, anchor={9, 0}},
	low_moral_fiber_2_body = {x=100, y=1, width=24, height=30, anchor={14, 0}},
	low_moral_fiber_2_head_east = {x=127, y=1, width=12, z=0.01, height=9, anchor ={7,0}},
	low_moral_fiber_2_head_s_1 = {x=141, y=1, width=10, z=0.01, height=9, anchor ={7,0}},
	low_moral_fiber_2_head_s_2 = {x=153, y=1, width=10, z=0.01, height=9, anchor ={7,0}},
	low_moral_fiber_2_laugh1 = {x=314, y=34, width=24, height=39, anchor = {14, 0}},
	low_moral_fiber_2_laugh2 = {x=340, y=35, width=25, height=38, anchor = {15, 0}},
	low_moral_fiber_2_laugh3 = {x=367, y=34, width=24, height=39, anchor = {14, 0}},
	low_moral_fiber_2_head_hit = {x=128, y=11, width=11, height=8, anchor={7,0}},
	cook_body_idle_right = {x=2,y=34,width=28,height=35, anchor={17, 0}},
	cook_head_idle_right = {x=36,y=57, width=11, height=16, anchor={7,0}},
	cook_head_talk1_right = {x=90,y=57, width=11, height=16, anchor={8,0}},
	cook_head_talk2_right = {x=50,y=57, width=12, height=18, anchor={7,2}},
	cook_head_talk3_right = {x=64,y=57, width=11, height=17, anchor={8,1}},
	cook_head_talk4_right = {x=77,y=57, width=11, height=17, anchor={8,1}},
	cook_head_talk5_right = {x=103,y=57, width=11, height=18, anchor={7,2}},
	cook_spit = {x=116, y=63, width=10, height=12},
	cook_idle_south = {x=39, y=77, width=31,height=48, anchor= {15,0}},
	cook_idle_north = {x=2, y=72, width=36,height=48, anchor= {17,0}},
	cook_walk_east1 = {x=72,y=77,width=25,height=48,anchor={13,0}},
	cook_walk_east2 = {x=99,y=78,width=31,height=47,anchor={17,0}},
	cook_walk_east3 = {x=132,y=76,width=20,height=49,anchor={12,0}},
	cook_walk_east4 = {x=154,y=76,width=28,height=49,anchor={16,0}},
	cook_walk_east5 = {x=184,y=77,width=26,height=48,anchor={16,0}},
	cook_walk_east6 = {x=212,y=77,width=22,height=48,anchor={13,0}},
	low_moral_fiber_3_body_idle = { x = 67, y = 127, width = 24, height = 37, anchor={14,0} },
	low_moral_fiber_3_body_open_jacket_1 = { x = 124, y = 127, width = 23, height = 37, anchor={13, 0} },
	low_moral_fiber_3_body_open_jacket_2 = { x = 149, y = 127, width = 24, height = 37, anchor={13, 0} },
	low_moral_fiber_3_body_punch_1 = { x = 190, y = 127, width = 23, height = 37, anchor={13, 0} },
	low_moral_fiber_3_body_punch_2 = { x = 213, y = 127, width = 30, height = 45, anchor={18, 0} },
	low_moral_fiber_3_body_punch_3 = { x = 244, y = 127, width = 32, height = 37, anchor={20, 0} },
	low_moral_fiber_3_head_idle_e = { x=93, y=127, width=13, height=15, anchor = {10, 0}},
	low_moral_fiber_3_head_talk_e_1 = { x=93, y=144, width=13, height=15, anchor = {10, 0}},
	low_moral_fiber_3_head_talk_e_2 = { x=108, y=127, width=13, height=15, anchor = {10, 0}},
	low_moral_fiber_3_head_talk_e_3 = { x=108, y=144, width=13, height=15, anchor = {10, 0}},
	low_moral_fiber_3_head_idle_s = { x=176, y=127, width=11, height=13, anchor = {6, 0}},
	low_moral_fiber_3_head_talk_s_1 = { x=175, y=142, width=13, height=14, anchor = {7, 0}},
	citizen_body_idle_south = {x=164, y=1, width=29, height=31, anchor = {15,0}},
	citizen_body_idle_east = {x=207, y=3, width=22, height=29, anchor = {17,0}},
	citizen_head_idle_south1 = {x=196, y=11, width=9, height=9, anchor = {5,0}},
	citizen_head_idle_south2 = {x=196, y=1, width=9, height=9, anchor = {5,0}},
	citizen_head_idle_east = {x=196, y=21, width=9, height=9, anchor = {5,0}},
	citizen_head_talk_1 = {x=231,y=1,width=9, height=9, anchor={5,0}},
	citizen_head_talk_2 = {x=231,y=11, width=9, height=9, anchor={5,0}},
	citizen_open_jacket_1 = {x=241, y=3, width=26, height=29, anchor = {20, 0 }},
	citizen_open_jacket_2 = {x=269, y=3, width=23, height=29, anchor = {17, 0 }},
	citizen_open_jacket_3 = {x=293, y=3, width=33, height=29, anchor = {25, 0}},
	citizen_open_jacket_4 = {x=328, y=3, width=38, height=29, anchor = {25, 0}},
	citizen_rollmap_1 = {x=165, y=34, width=29, height=29, anchor={17, 0}},
	citizen_rollmap_2 = {x=197, y=34, width=26, height=29, anchor={16, 0}},
	citizen_rollmap_3 = {x=226, y=34, width=26, height=29, anchor={16, 0}},
	citizen_rollmap_4 = {x=257, y=34, width=26, height=29, anchor={16, 0}},
	citizen_rollmap_5 = {x=286, y=34, width=25, height=29, anchor={16, 0}},
	rat_body_idle_1 = {x=69, y=166, width=13, height=12, anchor ={5,0}},
	rat_body_idle_2 = {x=84, y=168, width=13, height=10, anchor ={6,0}},
	rat_tail_1 = {x=99, y=168, width=5, height=4, anchor ={3,0}},
	rat_tail_2 = {x=99, y=175, width=6, height=2, anchor ={4,0}},
	door_village_scummbar_open = {x=3, y=126, width=31, height=52 },
	door_village_scummbar_close = {x=35, y=126, width=31, height=52 },
	door_village_voodoolady_open = {x=31, y=179, width=26, height=24 },
	door_village_voodoolady_close = {x=3, y=179, width=26, height=24 },
	fakedoor1_village_door_open = {x=76, y=179, width=16, height=29},
	fakedoor1_village_door_close = {x=58, y=179, width=16, height=29},
	fakedoor2_village_door_open = {x=13, y=204, width=8, height=14},
	fakedoor2_village_door_close = {x=3, y=204, width=8, height=14},
	door_scummbar_village_open = {x=472, y=2, width=38, height=47},
	door_scummbar_village_close = {x=472, y=50, width=38, height=47},
	door_scummbar_kitchen_open = {x=435, y=73, width=35, height=69},
	door_scummbar_kitchen_close = {x=435, y=2, width=35, height=69},
	door_kitchen_scummbar_open = {x=358, y=104, width=37, height=53},
	door_kitchen_scummbar_close = {x=397, y=104, width=37, height=53},
	door_kitchen_pier_open = {x=435, y=143, width=32, height=60},
	door_kitchen_pier_close = {x=469, y=143, width=32, height=60},
	mancomb_1 = {x=241, y=68, width=33, height=40},
	mancomb_2 = {x=277, y=68, width=36, height=39},
	estevan_1 = {x=318, y=76, width=35, height=27},
	estevan_2 = {x=355, y=76, width=39, height=27},
	estevan_3 = {x=396, y=76, width=37, height=27},
	seagull_fly_1 = {x=3, y = 220, width=20, height=14 },
	seagull_fly_2 = {x=3, y = 187+49, width=25, height=12},
	seagull_fly_3 = {x=3, y = 187+63, width=19, height=25},
	seagull_fly_4 = {x=3, y = 187+90, width=19, height=19},
	seagull_fly_5 = {x=3, y = 187+111, width=23, height=15},
	seagull_fly_6 = {x=3, y = 187+128, width=25, height=11},
	seagull_fly_7 = {x=3, y = 187+141, width=19, height=9},
	seagull_fly_8 = {x=47, y = 301, width=19, height=19},
	seagull_fly_9 = {x=46, y = 291, width=23, height=7},
	seagull_eat_1 = {x=3, y = 339, width=15, height=13},
	seagull_eat_2 = {x=25, y = 223, width=18, height=11},
	seagull_eat_3 = {x=30, y= 238, width=17, height=10},
	seagull_eat_4 = {x=24, y=250, width=19, height=9},
	seagull_eat_5 = {x=24, y=261, width=19, height=10},
	seagull_eat_6 = {x=24, y=273, width=17, height=10},
	seagull_eat_7 = {x=24, y=285, width=18, height=11},
	seagull_eat_8 = {x=28, y=298, width=15, height=13},
	seagull_eat_9 = {x=30, y=312, width=11, height=17},
	seagull_eat_10 = {x=30, y=331, width=12, height=17},
	seagull_eat_11 = {x=49, y=224, width=12, height=17},
	fish = {x=23, y=204, width=12, height=7},
	meat = {x=24, y=213, width=24, height=6},
	pot = {x=39, y=204, width=15, height=7},
	pot_o_stew_1 = {x=326, y=104, width=29, height=17},
	pot_o_stew_2 = {x=326, y=123, width=29, height=17},
	pot_o_stew_3 = {x=326, y=142, width=29, height=17},
	fireplace_1 = {x=334, y=160, width=32, height=26},
	fireplace_2 = {x=368, y=160, width=32, height=26},
	fireplace_3 = {x=402, y=160, width=32, height=26},
	kitchen_table = {x=394, y=46, width=33, height=26},
	plank_idle = {x=65,y=235,width=67,height=24},
	plank_pushed = {x=65,y=210,width=61,height=24},
	troll_arm_l_0 = {x=207, y=238, width=19, height=27, anchor ={7, 27}},
	troll_arm_l_1 = {x=275, y=236, z=0.1,width=13, height=28, anchor ={9, 28}},
	troll_arm_l_2 = {x=306, y=236, width=10, height=15, anchor ={4, 15}},

	troll_arm_rest_noclub = {x=227, y=238, width=9, height=18, anchor ={7, 18}},

	troll_body = {x=109,y=170,width=25,height=29, anchor={12,0}},

	troll_body_front = {x=283,y=110,width=41,height=33, anchor={19,0}},
	troll_body_front_2 = {x=138,y=239,width=29,height=30, anchor={15,0}},
	troll_head_idle = {x=150, y=167, width=20, z=0.1, height=15, anchor = {10, 0}},
	troll_head_talk_1 = {x=171,y=166, width=20, z=0.1, height=16, anchor = {10, 0}},
	troll_head_talk_2 = {x=151,y=183, width=20, z=0.1,height=16, anchor = {10, 0}},
	troll_head_talk_3 = {x=173,y=183, width=20, z=0.1,height=17, anchor = {10, 0}},
	troll_head_talk_4 = {x=194,y=166, width=19, z=0.1,height=17, anchor = {9, 0}},
	troll_head_side = {x=231, y=201, width=20, z=0.1,height=16, anchor = {10, 0}},
	troll_head_front = {x=231, y=220, width=20, z=0.1,height=15, anchor = {10, 0}},
	troll_body_pick_fish_1 = {x=131, y=203, width=27, height=34, anchor = {12,1}},
	troll_body_pick_fish_2 = {x=160, y=203, width=30, height=33, anchor ={13,0}},
	troll_body_pick_fish_3 = {x=192, y=203, width=37, height=33, anchor={24, 0}},
	troll_body_stand = {x = 295, y= 144, width = 29, height=34, anchor = {14, 0}},
	troll_arm_pick_fish_1 = {x=237, y=184, width=12, height=15, anchor={6,15}},
	troll_arm_pick_fish_2 = {x=196, y=185, width=16, height=14, anchor={5,14}},
	troll_arm_pick_fish_3 = {x=215, y=185, width=19, height=14, anchor={5,14}},
	troll_arm_pick_fish_4 = {x=251, y=181, width=16, height=20, anchor={7,20}},
	troll_fish = {x=216, y=174, z=0.1,width=14, height=8 },

	troll_arm_r_0 = {x=135, y=167, width=13, height=17, anchor = {11, 17}},
	troll_arm_r_1 = {x=262, y=236, width=11, height=18, anchor = {6, 18}},
	troll_arm_r_2 = {x=290, y=236, width=12, height=32, anchor = {10, 32}},

	troll_arm_1 = {x=332, y=187, width=22, height=32, anchor={22,32}},
	troll_arm_2 = {x=364, y=187, width=19, height=19, anchor={19,19}},
	troll_arm_3 = {x=364, y=208, width=21, height=12, anchor={21,12}},
	troll_arm_4 = {x=388, y=187, width=15, height=12, anchor={15,12}},
	troll_arm_5 = {x=390, y=201, width=10, height=13, anchor={10,13}},
	troll_arm_6 = {x=404, y=187, width=12, height=17, anchor={8,17}},
	troll_arm_7 = {x=386, y=231, width=12, height=16, anchor={10,16}},
	troll_arm_8 = {x=239, y=236, width=18, height=17, anchor={18,17}},

	troll_club_1 = {x=254, y=204, width=7, height=20, anchor = {4, 0}},
	troll_club_2 = {x=264, y=204, width=13, height=14, anchor = {7, 0}},
	troll_club_3 = {x=254, y=227, width=20, height=6, anchor = {10, 0}},
	troll_club_4 = {x=248, y=173, width=14, height=7, anchor = {7, 0}},
	troll_arm_head_1 = {x=279, y=181, width=26, height=20, anchor = {16, 5}},
	troll_arm_head_2 = {x=306, y=181, width=25, height=18, anchor = {15, 1}},
	troll_arm_head_3 = {x=279, y=203, width=25, height=17, anchor = {15, 1}},
	troll_head_1 = {x=306, y=200, width=20, height=14, anchor ={10,0}},
	troll_head_2 = {x=306, y=216, width=20, height=12, anchor ={10,0}},
	troll_head_3 = {x=279, y=221, width=20, height=12, anchor ={10,0}},
	troll_head_4 = {x=284, y=145, width=10, height=13, anchor ={5,0}},
	troll_head_5 = {x=284, y=159, width=9, height=13, anchor ={5,0}},
	troll_head_6 = {x=270, y=166, width=9, height=12, anchor={5,0}},
	troll_head_7 = {x=244, y=111, width=10, height=10, anchor={5,0}},
	troll_head_8 = {x=258, y=110, width=8, height=16, anchor={4,0}},
	troll_head_9 = {x=268, y=113, width=8, height=13, anchor={4,0}},
	troll_head_10 = {x=470, y=236, width=9, height=12, anchor={4,0}},
	troll_head_11 = {x=332, y=221, width=25, height=18, anchor={15,5}},
	
	troll_arm_fish_1= {x=417,y=187,width=14,height=21, anchor= {4,21}},
	troll_arm_fish_2= {x=403,y=206,width=17,height=17, anchor= {10,17}},
	troll_arm_fish_3= {x=423,y=210,width=16,height=15, anchor= {10,14}},
	troll_arm_fish_4= {x=364,y=223,width=16,height=14, anchor= {10,14}},
	troll_arm_fish_5= {x=403,y=224,width=17,height=16, anchor= {12,14}},
	troll_arm_fish_6= {x=441,y=204,width=20,height=26, anchor= {11,26}},
	troll_arm_fish_7= {x=462,y=204,width=15,height=29, anchor= {2,29}},
	troll_arm_fish_8= {x=478,y=204,width=10,height=31, anchor= {0,31}},
	troll_arm_fish_9= {x=490,y=204,width=14,height=29, anchor= {9,29}},
	troll_arm_fish_10= {x=386,y=215,width=16,height=14, anchor= {11,14}},
	troll_arm_fish_11= {x=423,y=227,width=12,height=20, anchor= {3,20}},
	troll_flyingfish_1 = {x=269, y=180, width=8, height=10, anchor={4,0}},
	troll_flyingfish_2 = {x=438, y=232, width=8, height=10, anchor={4,0}},
	troll_flyingfish_3 = {x=447, y=232, width=10, height=6, anchor={5,0}},
	troll_flyingfish_4 = {x=459, y=232, width=8, height=10, anchor={4,0}},









	















}

local s = spritesheets["sprites1"]

models["arrow_up"] = {
    sheet = sheet,
    type = "sprite",
    ppu=1,
	animations = {
		{ name = "unselected", frames = { { duration = dt, quads = {{ id = s.arrow_up }}}}},
		{ name = "selected", frames = { { duration = dt, quads = {{ id = s.arrow_up_focus }}}}}
	}
}

models["arrow_down"] = {
    sheet = sheet,
    type = "sprite",
    ppu=1,
	animations = {
		{ name = "unselected", frames = { { duration = dt, quads = {{ id = s.arrow_down }}}}},
		{ name = "selected", frames = { { duration = dt, quads = {{ id = s.arrow_down_focus }}}}}
	}
}


models["low_moral_fiber_1"] = {
    sheet = sheet,
    type = "sprite",
    ppu=1,
	animations = {
		{
			name = "idle",
			frames = {
				{ duration = dt, quads = {{ id = s.low_moral_fiber_body_1 }, { id = s.low_moral_fiber_1_talk1, pos={1,28}}}}
			}
		},
		{
			name = "talk",
			frames = {
		 		{ duration = dt, quads = {{ id = s.low_moral_fiber_body_1 }, { id = s.low_moral_fiber_1_talk1, pos={1,28} }}},
		 		{ duration = dt, quads = {{ id = s.low_moral_fiber_body_1 }, { id = s.low_moral_fiber_1_talk2, pos={1,28} }}},
		 		{ duration = dt, quads = {{ id = s.low_moral_fiber_body_1 }, { id = s.low_moral_fiber_1_talk3, pos={1,28} }}},
		 	}
		},
		{
		 	name = "rock",
		 	frames = {
		 		{ duration = dt, quads = {{ id = s.low_moral_fiber_1_rock1 }}},
				{ duration = dt, quads = {{ id = s.low_moral_fiber_body_1 }, { id = s.low_moral_fiber_1_talk1, pos={1,28}}}},
		 		{ duration = dt, quads = {{ id = s.low_moral_fiber_1_rock2 }}},
				{ duration = dt, quads = {{ id = s.low_moral_fiber_body_1 }, { id = s.low_moral_fiber_1_talk1, pos={1,28}}}}
		 	}
		},
		{
		 	name = "looknorth",
		 	frames = {
		 		{ duration = dt, quads = {{ id = s.low_moral_fiber_body_1 }, { id = s.low_moral_fiber_1_look_north, pos={1,28} }}}
			}
		}
	}
}

models["low_moral_fiber_2"] = {
    sheet = sheet,
    type = "sprite",
    ppu=1,
	animations = {
		{
			name = "idle",
			frames = {
				{ duration = dt, quads = {{ id = s.low_moral_fiber_2_body }, { id = s.low_moral_fiber_2_head_east, pos={0,28}}}}
			}
		},
		{
			name = "idle_s",
			frames = {
				{ duration = dt, quads = {{ id = s.low_moral_fiber_2_body }, { id = s.low_moral_fiber_2_head_s_1, pos={0,28}}}},
				{ duration = dt, quads = {{ id = s.low_moral_fiber_2_body }, { id = s.low_moral_fiber_2_head_s_2, pos={0,28}}}}
			}
		},
		{
			name = "laugh",
			frames = {
				{ duration = dt, quads = {{ id = s.low_moral_fiber_2_laugh1 }}},
				{ duration = dt, quads = {{ id = s.low_moral_fiber_2_laugh2 }}},
				{ duration = dt, quads = {{ id = s.low_moral_fiber_2_laugh3 }}},
			}
		},
		{
			name = "hit",
			frames = {
				{ duration = dt, quads = {{ id = s.low_moral_fiber_2_body }, { id = s.low_moral_fiber_2_head_hit, pos={0,29}}}}
			}
		},
	}
}



models["cook"] = {
    sheet = sheet,
    type = "sprite",
    ppu=1,
	animations = {
		{ name = "idle_e", frames = { { duration = dt, quads = {{ id = s.cook_body_idle_right }, { id = s.cook_head_idle_right, pos={-1,32}}}}}},
		{ name = "idle_n", frames = {{ duration = dt, quads = {{ id = s.cook_idle_north }}}}},
		{ name = "idle_s", frames = {{ duration = dt, quads = {{ id = s.cook_idle_south }}}}},
		{
			name = "talk_e",
			frames = {
		 		{ duration = dt, quads = {{ id = s.cook_body_idle_right }, { id = s.cook_head_talk1_right, pos={-1,32} }}},
		 		{ duration = dt, quads = {{ id = s.cook_body_idle_right }, { id = s.cook_head_talk2_right, pos={-1,32} }}},
		 		{ duration = dt, quads = {{ id = s.cook_body_idle_right }, { id = s.cook_head_talk3_right, pos={-1,32} }}},
		 		{ duration = dt, quads = {{ id = s.cook_body_idle_right }, { id = s.cook_head_talk4_right, pos={-1,32} }}},
		 		{ duration = dt, quads = {{ id = s.cook_body_idle_right }, { id = s.cook_head_talk5_right, pos={-1,32} }}},
		 	}
		},
		{
			name = "walk_e",
			frames = {
		 		{ duration = dt, quads = {{ id = s.cook_walk_east1 }}},
		 		{ duration = dt, quads = {{ id = s.cook_walk_east2 }}},
		 		{ duration = dt, quads = {{ id = s.cook_walk_east3 }}},
		 		{ duration = dt, quads = {{ id = s.cook_walk_east4 }}},
		 		{ duration = dt, quads = {{ id = s.cook_walk_east5 }}},
		 		{ duration = dt, quads = {{ id = s.cook_walk_east6 }}},
		 	}
		},
		{
			name = "walk_n",
			frames = {
		 		{ duration = dt, quads = {{ id = s.cook_idle_north }}}
		 	}
		},
		{
			name = "walk_s",
			frames = {
		 		{ duration = dt, quads = {{ id = s.cook_idle_south }}}
		 	}
		},

	}
}

models["citizen.body"] = {
    sheet = sheet,
    type = "sprite",
    ppu=1,
	animations = {
		{ name = "idle_s", frames = { { duration = dt, quads = {{ id = s.citizen_body_idle_south }}}}},
		{ name = "idle_e", frames = { { duration = dt, quads = {{ id = s.citizen_body_idle_east }}}}},
		{ name = "open_jacket", loop=false, frames = {
			{ duration = dt, quads = {{ id = s.citizen_body_idle_east }}},
			{ duration = dt, quads = {{ id = s.citizen_open_jacket_1 }}},
			{ duration = dt, quads = {{ id = s.citizen_open_jacket_2 }}},
			{ duration = dt, quads = {{ id = s.citizen_open_jacket_3 }}},
			{ duration = dt, quads = {{ id = s.citizen_open_jacket_4 }}},
		}},
		{ name = "rollmap", loop=false, frames = {
			{ duration = dt, quads = {{ id = s.citizen_body_idle_east }}},
			{ duration = dt, quads = {{ id = s.citizen_rollmap_1 }}},
			{ duration = dt, quads = {{ id = s.citizen_rollmap_2 }}},
			{ duration = dt, quads = {{ id = s.citizen_rollmap_3 }}},
			{ duration = dt, quads = {{ id = s.citizen_rollmap_4 }}},
			{ duration = dt, quads = {{ id = s.citizen_rollmap_5 }}},
		}},

	}
}

models["citizen.head"] = {
    sheet = sheet,
    type = "sprite",
    ppu=1,
	animations = {
		{ name = "idle_s", frames = { 
			{ duration = dt, quads = {{ id = s.citizen_head_idle_south1 }}},
			{ duration = dt, quads = {{ id = s.citizen_head_idle_south2 }}},
			{ duration = dt, quads = {{ id = s.citizen_head_idle_south1 }}},
			{ duration = dt, quads = {{ id = s.citizen_head_idle_south2, flipx=true }}}
		}},
		{ name = "idle_e", frames = { 
			{ duration = dt, quads = {{ id = s.citizen_head_idle_south2 }}},
			{ duration = dt, quads = {{ id = s.citizen_head_idle_east }}},
			{ duration = dt, quads = {{ id = s.citizen_head_idle_south2 }}},
			{ duration = dt, quads = {{ id = s.citizen_head_idle_south1 }}}
		}},
		{ name = "talk", frames = { 
			{ duration = dt, quads = {{ id = s.citizen_head_talk_1 }}},
			{ duration = dt, quads = {{ id = s.citizen_head_talk_2 }}},
			{ duration = dt, quads = {{ id = s.citizen_head_idle_east }}},
		}},

	}
}

models["citizen"] = {
    type = "model",
	components = {
		{ name="body", mesh="citizen.body"},
		{ name="head", mesh="citizen.head"},
	},
	animations = {
		{ name = "idle_s", anims = { {name="body", anim="idle_s"}, {name="head", anim="idle_s", pos={0,25,0} }}},
		{ name = "idle_e", anims = { {name="body", anim="idle_e"}, {name="head", anim="idle_e", pos={-1,25,0} }}},
		{ name = "talk_start", anims = { {name="head", anim="talk", pos ={-1,25,0} }}},
		{ name = "talk_end", anims = { {name="head", anim="idle_e", pos ={-1,25,0} }}},
		{ name = "open_jacket", anims = { { name="body", anim="open_jacket" }}},
		{ name = "rollmap", anims = { { name="body", anim="rollmap" }}}

	}
}

models["door_village_scummbar"] = {
    sheet = sheet,
    type = "sprite",
    ppu=1,
	animations = {
		{ name = "open", frames = { { duration = dt, quads = {{ id = s.door_village_scummbar_open }}}}},
		{ name = "close", frames = { { duration = dt, quads = {{ id = s.door_village_scummbar_close }}}}}
	}
}

models["door_village_voodoolady"] = {
    sheet = sheet,
    type = "sprite",
    ppu=1,
	animations = {
		{ name = "open", frames = { { duration = dt, quads = {{ id = s.door_village_voodoolady_open }}}}},
		{ name = "close", frames = { { duration = dt, quads = {{ id = s.door_village_voodoolady_close }}}}}
	}
}

models["fakedoor_village_1"] = {
    sheet = sheet,
    type = "sprite",
    ppu=1,
	animations = {
		{ name = "open", frames = { { duration = dt, quads = {{ id = s.fakedoor1_village_door_open }}}}},
		{ name = "close", frames = { { duration = dt, quads = {{ id = s.fakedoor1_village_door_close }}}}}
	}
}

models["fakedoor_village_2"] = {
    sheet = sheet,
    type = "sprite",
    ppu=1,
	animations = {
		{ name = "open", frames = { { duration = dt, quads = {{ id = s.fakedoor2_village_door_open }}}}},
		{ name = "close", frames = { { duration = dt, quads = {{ id = s.fakedoor2_village_door_close }}}}}
	}
}

models["lmf3.body"] = {
    sheet = sheet,
    type = "sprite",
    ppu=1,
	animations = {
		{ name = "idle_e", frames = { { duration = dt, quads = {{ id = s.low_moral_fiber_3_body_idle }}}}},

		{ name = "open_jacket", loop=false, frames = {
			{ duration = dt, quads = {{ id = s.low_moral_fiber_3_body_idle }}},
			{ duration = dt, quads = {{ id = s.low_moral_fiber_3_body_open_jacket_1 }}},
			{ duration = dt, quads = {{ id = s.low_moral_fiber_3_body_open_jacket_2 }}},
		}},
		{ name = "punch", loop=false, frames = {
			{ duration = dt, quads = {{ id = s.low_moral_fiber_3_body_idle }}},
			{ duration = dt, quads = {{ id = s.low_moral_fiber_3_body_punch_1 }}},
			{ duration = 2*dt, quads = {{ id = s.low_moral_fiber_3_body_punch_2 }}},
			{ duration = dt, quads = {{ id = s.low_moral_fiber_3_body_punch_3 }}},
		}},
	}
}

models["lmf3.head"] = {
    sheet = sheet,
    type = "sprite",
    ppu=1,
	animations = {
		{ name = "idle_s", frames = { {duration = dt, quads = {{ id = s.low_moral_fiber_3_head_idle_s }}}}},
		{ name = "idle_e", frames = { { duration = dt, quads = {{ id = s.low_moral_fiber_3_head_idle_e }}}}},
		{ name = "talk_e", frames = { 
			{ duration = dt, quads = {{ id = s.low_moral_fiber_3_head_talk_e_1 }}},
			{ duration = dt, quads = {{ id = s.low_moral_fiber_3_head_talk_e_2 }}},
			{ duration = dt, quads = {{ id = s.low_moral_fiber_3_head_talk_e_3 }}},
		}},
		{ name = "talk_s", frames = { 
			{ duration = dt, quads = {{ id = s.low_moral_fiber_3_head_idle_s }}},
			{ duration = dt, quads = {{ id = s.low_moral_fiber_3_head_talk_s_1 }}}
		}},

	}
}

models["lmf3"] = {
    type = "model",
	components = {
		{ name="body", mesh="lmf3.body"},
		{ name="head", mesh="lmf3.head"},
	},
	animations = {
		{ name = "idle_e", anims = { {name="body", anim="idle_e"}, {name="head", anim="idle_e", pos={-3,34,0} }}},
		{ name = "idle_s", anims = { {name="body", anim="idle_e"}, {name="head", anim="idle_s", pos={-4,34,0} }}},
		{ name = "talk_s", anims = { {name="body", anim="idle_e"}, {name="head", anim="talk_s", pos={-4,34,0} }}},
		{ name = "talk_e", anims = { {name="body", anim="idle_e"}, {name="head", anim="talk_e", pos={-4,34,0} }}},
		{ name = "punch", loop = false, anims = { {name="body", anim="punch" }, {name="head", anim="talk_s", pos ={-4,34,0} }}},
		{ name = "h_talk_s", anims = { {name="head", anim="talk_s", pos={-4,34,0} }}},
		{ name = "h_talk_e", anims = { {name="head", anim="talk_e", pos={-4,34,0} }}},		-- { name = "talk_start", anims = { {name="head", anim="talk", pos ={-1,25,0} }}},
		-- { name = "talk_end", anims = { {name="head", anim="idle_e", pos ={-1,25,0} }}},
		{ name = "open_jacket", loop = false, anims = { { name="body", anim="open_jacket" }}},
		-- { name = "rollmap", anims = { { name="body", anim="rollmap" }}}

	}
}


models["village2.rat"] = {
    sheet = sheet,
    type = "sprite",
    ppu=1,
	animations = {
		{ name = "idle", frames = { 
			{ duration = dt, quads = {{ id = s.rat_body_idle_1 }, {id = s.rat_tail_1, pos = {-6,0} }}},
			{ duration = dt, quads = {{ id = s.rat_body_idle_1 }, {id = s.rat_tail_2, pos = {-6,0} }}},
			{ duration = dt, quads = {{ id = s.rat_body_idle_2 }, {id = s.rat_tail_2, pos = {-6,0} }}},
		}},
	}
}

models["door_scummbar_village"] = {
    sheet = sheet,
    type = "sprite",
    ppu=1,
	animations = {
		{ name = "open", frames = { { duration = dt, quads = {{ id = s.door_scummbar_village_open }}}}},
		{ name = "close", frames = { { duration = dt, quads = {{ id = s.door_scummbar_village_close }}}}}
	}
}

models["door_scummbar_kitchen"] = {
    sheet = sheet,
    type = "sprite",
    ppu=1,
	animations = {
		{ name = "open", frames = { { duration = dt, quads = {{ id = s.door_scummbar_kitchen_open }}}}},
		{ name = "close", frames = { { duration = dt, quads = {{ id = s.door_scummbar_kitchen_close }}}}}
	}
}

models["door_kitchen_scummbar"] = {
    sheet = sheet,
    type = "sprite",
    ppu=1,
	animations = {
		{ name = "open", frames = { { duration = dt, quads = {{ id = s.door_kitchen_scummbar_open }}}}},
		{ name = "close", frames = { { duration = dt, quads = {{ id = s.door_kitchen_scummbar_close }}}}}
	}
}

models["door_kitchen_pier"] = {
    sheet = sheet,
    type = "sprite",
    ppu=1,
	animations = {
		{ name = "open", frames = { { duration = dt, quads = {{ id = s.door_kitchen_pier_open }}}}},
		{ name = "close", frames = { { duration = dt, quads = {{ id = s.door_kitchen_pier_close }}}}}
	}
}

models["scummbar.mancomb"] = {
    sheet = sheet,
    type = "sprite",
    ppu=1,
	animations = {
		{ name = "idle_1", frames = { { duration = dt, quads = {{ id = s.mancomb_1 }}}}},
		{ name = "idle_2", frames = { { duration = dt, quads = {{ id = s.mancomb_2 }}}}}
	}
}

models["scummbar.estevan"] = {
    sheet = sheet,
    type = "sprite",
    ppu=1,
	animations = {
		{ name = "idle_1", frames = { { duration = dt, quads = {{ id = s.estevan_1 }}}}},
		{ name = "idle_2", frames = { 
			{ duration = dt, quads = {{ id = s.estevan_2 }}},
			{ duration = dt, quads = {{ id = s.estevan_3 }}}
		}}

	}
}


models["kitchen.seagull"] = {
    sheet = sheet,
    type = "sprite",
    ppu=1,
	animations = {
		{ name = "fly", frames = { 
			{ duration = dt, quads = {{ id = s.seagull_fly_1, pos = {307, 37} }}},
			{ duration = dt, quads = {{ id = s.seagull_fly_2, pos = {295, 35} }}},
			{ duration = dt, quads = {{ id = s.seagull_fly_1, pos = {292, 33} }}},
			{ duration = dt, quads = {{ id = s.seagull_fly_3, pos = {285, 29} }}},
			{ duration = dt, quads = {{ id = s.seagull_fly_4, pos = {277, 32} }}},
			{ duration = dt, quads = {{ id = s.seagull_fly_3, pos = {269, 22} }}},
			{ duration = dt, quads = {{ id = s.seagull_fly_1, pos = {260, 25} }}},
			{ duration = dt, quads = {{ id = s.seagull_fly_2, pos = {247, 23} }}},
			{ duration = dt, quads = {{ id = s.seagull_fly_1, pos = {244, 21} }}},
			{ duration = dt, quads = {{ id = s.seagull_fly_4, pos = {245, 23} }}},
			{ duration = dt, quads = {{ id = s.seagull_fly_4, pos = {250, 17} }}},
			{ duration = dt, quads = {{ id = s.seagull_fly_5, pos = {248, 14} }}},
			{ duration = dt, quads = {{ id = s.seagull_fly_6, pos = {246, 13} }}},
			{ duration = dt, quads = {{ id = s.seagull_fly_5, pos = {243, 12} }}},
			{ duration = dt, quads = {{ id = s.seagull_fly_7, pos = {243, 10} }}},
		}},
		{ name = "eat", frames = { 
			{ duration = dt, quads = {{ id = s.seagull_eat_1, pos = {245, 10} }}},
			{ duration = dt, quads = {{ id = s.seagull_eat_2, pos = {242, 10} }}},
			{ duration = dt, quads = {{ id = s.seagull_eat_3, pos = {243, 10} }}},
			{ duration = dt, quads = {{ id = s.seagull_eat_4, pos = {242, 10} }}},
			{ duration = dt, quads = {{ id = s.seagull_eat_5, pos = {242, 10} }}},
			{ duration = 3*dt, quads = {{ id = s.seagull_eat_6, pos = {243, 10} }}},
			{ duration = dt, quads = {{ id = s.seagull_eat_7, pos = {242, 10} }}},
			{ duration = dt, quads = {{ id = s.seagull_eat_8, pos = {245, 10} }}},
			{ duration = dt, quads = {{ id = s.seagull_eat_9, pos = {249, 10} }}},
			{ duration = dt, quads = {{ id = s.seagull_eat_10, pos = {248, 10} }}},
			{ duration = dt, quads = {{ id = s.seagull_eat_11, pos = {248, 10} }}},
		}},
		{ name = "jump1", frames = { 
			{ duration = dt, quads = {{ id = s.seagull_eat_1, pos = {245, 40} }}},
			{ duration = dt, quads = {{ id = s.seagull_eat_1, pos = {245, 64} }}},
			{ duration = dt, quads = {{ id = s.seagull_eat_1, pos = {245, 94} }}},
			{ duration = dt, quads = {{ id = s.seagull_eat_1, pos = {245, 100} }}},
			{ duration = dt, quads = {{ id = s.seagull_fly_4, pos = {237, 82} }}},
			{ duration = dt, quads = {{ id = s.seagull_fly_4, pos = {237, 64} }}},
			{ duration = dt, quads = {{ id = s.seagull_fly_4, pos = {237, 40} }}},
			{ duration = dt, quads = {{ id = s.seagull_fly_4, pos = {237, 10} }}},
		}},
		{ name = "jump2", frames = {
			{duration = dt, quads = {{id = s.seagull_eat_1, pos = {245, 40}}}},
			{duration = dt, quads = {{id = s.seagull_eat_1, pos = {245, 64}}}},
			{duration = dt, quads = {{id = s.seagull_eat_1, pos = {245, 94}}}},
			{duration = dt, quads = {{id = s.seagull_eat_1, pos = {245, 100}}}},
			{duration = dt, quads = {{id = s.seagull_fly_8, pos = {249, 98}}}},
			{duration = dt, quads = {{id = s.seagull_fly_8, pos = {255, 94}}}},
			{duration = dt, quads = {{id = s.seagull_fly_8, pos = {261, 86}}}},
			{duration = dt, quads = {{id = s.seagull_fly_8, pos = {267, 74}}}},
			{duration = dt, quads = {{id = s.seagull_fly_8, pos = {273, 58}}}},
			{duration = dt, quads = {{id = s.seagull_fly_8, pos = {279, 38}}}},
			{duration = dt, quads = {{id = s.seagull_fly_9, pos = {268, 34}}}},
			{duration = dt, quads = {{id = s.seagull_fly_3, pos = {259, 27}}}},
			{duration = dt, quads = {{id = s.seagull_fly_1, pos = {254, 23}}}},
			{duration = dt, quads = {{id = s.seagull_fly_2, pos = {245, 15}}}},
			{duration = dt, quads = {{id = s.seagull_fly_4, pos = {250, 17}}}},
			{duration = dt, quads = {{id = s.seagull_fly_5, pos = {248, 14}}}},
			{duration = dt, quads = {{id = s.seagull_fly_6, pos = {246, 13}}}},
			{duration = dt, quads = {{id = s.seagull_fly_5, pos = {244, 12}}}},
			{duration = dt, quads = {{id = s.seagull_fly_7, pos = {243, 11}}}},
		}}


	}
}

models["kitchen.plank"] = {
    sheet = sheet,
    type = "sprite",
    ppu=1,
	animations = {
		{ name = "idle", frames = { { duration = dt, quads = {{ id = s.plank_idle }}}}},
		{ name = "pushed", frames = { { duration = dt, quads = {{ id = s.plank_pushed }}}}}
	}
}

models["kitchen.meat"] = {
    sheet = sheet,
    type = "sprite",
    ppu=1,
	animations = {
		{ name = "idle", frames = { { duration = dt, quads = {{ id = s.meat }}}}},
	}
}

models["kitchen.pot"] = {
    sheet = sheet,
    type = "sprite",
    ppu=1,
	animations = {
		{ name = "idle", frames = { { duration = dt, quads = {{ id = s.pot }}}}},
	}
}

models["kitchen.fish"] = {
    sheet = sheet,
    type = "sprite",
    ppu=1,
	animations = {
		{ name = "idle", frames = { { duration = dt, quads = {{ id = s.fish }}}}},
	}
}

models["kitchen.potostew"] = {
    sheet = sheet,
    type = "sprite",
    ppu=1,
	animations = {
		{ name = "idle", frames = { 
			{ duration = dt, quads = {{ id = s.pot_o_stew_1 }}},
			{ duration = dt, quads = {{ id = s.pot_o_stew_2 }}},
			{ duration = dt, quads = {{ id = s.pot_o_stew_3 }}},
		}},
	}
}

models["scummbar.fireplace"] = {
    sheet = sheet,
    type = "sprite",
    ppu=1,
	animations = {
		{ name = "idle", frames = { 
			{ duration = dt, quads = {{ id = s.fireplace_1 }}},
			{ duration = dt, quads = {{ id = s.fireplace_2 }}},
			{ duration = dt, quads = {{ id = s.fireplace_3 }}},
		}},
	}
}

models["kitchen.table"] = {
    sheet = sheet,
    type = "sprite",
    ppu=1,
	animations = {
		{ name = "idle", frames = { { duration = dt, quads = {{ id = s.kitchen_table }}}}},
	}
}

local troll_delta1 = {5,35}
local troll_info = {
	head = {8, 26},
	arm_right = {-2, 32},
	arm_left = {11, 27}

}
local f1 = function(body, head, arm_left, arm_right, dur) 
	return { duration = dur or dt, quads = {
		{ id = body }, 
		{ id = head, pos = troll_info.head },
		{ id = arm_left, pos = troll_info.arm_left},
		{ id = arm_right, pos = troll_info.arm_right, z=0.1}
	}}
end
models["bridge.troll"] = {
    sheet = sheet,
    type = "sprite",
    ppu=1,
	animations = {
		-- { name = "idle", frames = { { duration = dt, quads = { 
		-- 	{ id = s.troll_body }, 
		-- 	{ id = s.troll_head_idle, pos = troll_info.head },
		-- 	{ id = s.troll_arm_l_0, pos = troll_info.arm_left},
		-- 	{ id = s.troll_arm_r_0, pos = troll_info.arm_right, z=0.1}
		-- }}}},
		{ name = "idle", frames = { f1(s.troll_body, s.troll_head_idle, s.troll_arm_l_0, s.troll_arm_r_0) }},
		{ name = "talk", frames = { 
			f1(s.troll_body, s.troll_head_talk_1, s.troll_arm_l_0, s.troll_arm_r_0),
			f1(s.troll_body, s.troll_head_talk_2, s.troll_arm_l_0, s.troll_arm_r_0),
			f1(s.troll_body, s.troll_head_talk_1, s.troll_arm_l_0, s.troll_arm_r_0),
			f1(s.troll_body, s.troll_head_talk_3, s.troll_arm_l_0, s.troll_arm_r_0),
			f1(s.troll_body, s.troll_head_talk_4, s.troll_arm_l_0, s.troll_arm_r_0),
			f1(s.troll_body, s.troll_head_talk_1, s.troll_arm_l_0, s.troll_arm_r_0),
			f1(s.troll_body, s.troll_head_talk_2, s.troll_arm_l_0, s.troll_arm_r_0),
			f1(s.troll_body, s.troll_head_talk_4, s.troll_arm_l_0, s.troll_arm_r_0)
		}}, 
		{ name = "pickup_fish", loop=false, frames = {
			f1(s.troll_body, s.troll_head_talk_1, s.troll_arm_l_0, s.troll_arm_r_0),
			f1(s.troll_body, s.troll_head_talk_2, s.troll_arm_l_1, s.troll_arm_r_1),
			f1(s.troll_body, s.troll_head_talk_1, s.troll_arm_l_2, s.troll_arm_r_2, 4000),

			-- { duration = dt, quads = { { id = s.troll_body }, {id = s.troll_head_talk_1, pos={8,26} }, { id = s.troll_arm_l_0, pos = {11, 27}}}},
			-- { duration = dt, quads = { { id = s.troll_body_pick_fish_1 }, {id = s.troll_head_talk_2, pos={8,26} }}},
			-- { duration = dt, quads = { { id = s.troll_body_pick_fish_2 }, {id = s.troll_head_talk_1, pos={8,26} }}},
			-- { duration = dt, quads = { { id = s.troll_body_pick_fish_3 }, {id = s.troll_arm_pick_fish_1, pos={11,26}}, {id = s.troll_head_talk_3, pos={8,26} }}},
			-- { duration = dt, quads = { { id = s.troll_body_pick_fish_3 }, {id = s.troll_arm_pick_fish_2, pos={11,26}}, {id = s.troll_head_talk_4, pos={8,26} }}},
			-- { duration = dt, quads = { { id = s.troll_body_pick_fish_3 }, {id = s.troll_arm_pick_fish_3, pos={11,26}}, {id = s.troll_head_talk_4, pos={8,26} }}},
			-- { duration = 2*dt, quads = { { id = s.troll_body_pick_fish_3 }, {id = s.troll_arm_pick_fish_3, pos={11,26}}, 
			-- 	{ id = s.troll_fish, pos ={12, 11}},{id = s.troll_head_talk_4, pos={7,26} }}},
			-- { duration = dt, quads = { { id = s.troll_body_pick_fish_3 }, {id = s.troll_arm_pick_fish_2, pos={11,26}}, 
			-- 	{ id = s.troll_fish, pos ={10, 9}},{id = s.troll_head_talk_4, pos={7,26} }}},
			-- { duration = dt, quads = { { id = s.troll_body_pick_fish_3 }, {id = s.troll_arm_pick_fish_1, pos={11,26}}, 
			-- 	{ id = s.troll_fish, pos ={9, 8}},{id = s.troll_head_talk_4, pos={7,26} }}},
			-- { duration = dt, quads = { { id = s.troll_body_pick_fish_3 }, {id = s.troll_arm_pick_fish_4, pos={9,26}}, {id = s.troll_head_idle, pos={8,26} }}},
		}},
		{ name = "idle_fish", frames = { { duration = dt, quads = { 
			{ id = s.troll_body_pick_fish_3 }, {id = s.troll_arm_pick_fish_4, pos={9,26}}, {id = s.troll_head_idle, pos={8,26}}}}}},
		{ name = "talk_fish", frames = { 
			{ duration = dt, quads = { { id = s.troll_body_pick_fish_3 }, {id = s.troll_arm_pick_fish_4, pos={9,26}}, {id = s.troll_head_talk_1, pos={8,26} }}},
			{ duration = dt, quads = { { id = s.troll_body_pick_fish_3 }, {id = s.troll_arm_pick_fish_4, pos={9,26}}, {id = s.troll_head_talk_2, pos={8,26} }}},
			{ duration = dt, quads = { { id = s.troll_body_pick_fish_3 }, {id = s.troll_arm_pick_fish_4, pos={9,26}}, {id = s.troll_head_talk_1, pos={8,26} }}},
			{ duration = dt, quads = { { id = s.troll_body_pick_fish_3 }, {id = s.troll_arm_pick_fish_4, pos={9,26}}, {id = s.troll_head_talk_3, pos={8,26} }}},
			{ duration = dt, quads = { { id = s.troll_body_pick_fish_3 }, {id = s.troll_arm_pick_fish_4, pos={9,26}}, {id = s.troll_head_talk_4, pos={7,26} }}},
			{ duration = dt, quads = { { id = s.troll_body_pick_fish_3 }, {id = s.troll_arm_pick_fish_4, pos={9,26}}, {id = s.troll_head_talk_1, pos={8,26} }}},
			{ duration = dt, quads = { { id = s.troll_body_pick_fish_3 }, {id = s.troll_arm_pick_fish_4, pos={9,26}}, {id = s.troll_head_talk_2, pos={8,26} }}},
			{ duration = dt, quads = { { id = s.troll_body_pick_fish_3 }, {id = s.troll_arm_pick_fish_4, pos={9,26}}, {id = s.troll_head_talk_4, pos={7,26} }}},
		}},
		{ name = "fish_cutscene", frames = { 
			{ duration = 5*dt, quads = { { id = s.troll_body_pick_fish_3 }, {id = s.troll_arm_pick_fish_4, pos={9,26}}, {id = s.troll_head_side, pos={6,26} }}},
			{ duration = dt, quads = { { id = s.troll_body_front }, {id = s.troll_head_front, pos={0,27} }}},
			{ duration = dt, quads = { { id = s.troll_body_front }, {id = s.troll_head_idle, flipx=true, pos={-2,27} }}},
			{ duration = dt, quads = { { id = s.troll_body_front }, {id = s.troll_head_side, flipx=true, pos={-2,27} }}},
			{ duration = dt, quads = { { id = s.troll_body_front }, {id = s.troll_head_idle, flipx=true, pos={-2,27} }}},
			{ duration = dt, quads = { { id = s.troll_body_front }, {id = s.troll_head_front, pos={0,27} }}},
			{ duration = dt, quads = { { id = s.troll_body_front }, {id = s.troll_head_idle, pos={2,27} }}},
			{ duration = dt, quads = { { id = s.troll_body_front }, {id = s.troll_head_side, pos={2,27} }}},
			{ duration = dt, quads = { { id = s.troll_body_front }, {id = s.troll_head_idle, pos={2,27} }}},
			{ duration = 2*dt, quads = { { id = s.troll_body_front }, {id = s.troll_head_front, pos={0,27} }}},
			{ duration = dt, quads = { 
				{ id = s.troll_body_stand }, 
				{ id = s.troll_arm_fish_1, pos = troll_delta1 }, 
				{ id = s.troll_head_front, pos={0,31}},
				{ id = s.troll_arm_1, pos = {-7, 34}}
			}},
			{ duration = dt, quads = { 
				{ id = s.troll_body_stand }, 
				{ id = s.troll_arm_fish_1, pos = troll_delta1 }, 
				{ id = s.troll_head_front, pos={0,31}},
				{ id = s.troll_arm_2, pos = {-6, 35}},
				{ id = s.troll_club_1, pos = {-29,0}}
			}},
			{ duration = dt, quads = { 
				{ id = s.troll_body_stand }, 
				{ id = s.troll_arm_fish_1, pos = troll_delta1 }, 
				{ id = s.troll_head_front, pos={0,31}},
				{ id = s.troll_arm_3, pos = {-7, 35}},
				{ id = s.troll_club_2, pos = {-38,-1}}
			}},
			{ duration = dt, quads = { 
				{ id = s.troll_body_stand }, 
				{ id = s.troll_arm_fish_1, pos = troll_delta1 }, 
				{ id = s.troll_head_front, pos={0,31}},
				{ id = s.troll_arm_4, pos = {-7, 35}},
				{ id = s.troll_club_3, pos = {-45,-1}}
			}},
			{ duration = dt, quads = { 
				{ id = s.troll_body_stand }, 
				{ id = s.troll_arm_fish_1, pos = troll_delta1 }, 
				{ id = s.troll_head_front, pos={0,31}},
				{ id = s.troll_arm_5, pos = {-7, 35}},
				{ id = s.troll_club_4, pos = {-50,-1}}
			}},
			{ duration = dt, quads = { 
				{ id = s.troll_body_stand }, 
				{ id = s.troll_arm_fish_1, pos = troll_delta1 }, 
				{ id = s.troll_arm_head_1, pos={0,30}},
				{ id = s.troll_club_4, pos = {-50,-1}}
			}},
			{ duration = dt, quads = { 
				{ id = s.troll_body_stand }, 
				{ id = s.troll_arm_fish_1, pos = troll_delta1 }, 
				{ id = s.troll_arm_head_2, pos={0,30}},
				{ id = s.troll_club_4, pos = {-50,-1}}
			}},
			{ duration = dt, quads = { 
				{ id = s.troll_body_stand }, 
				{ id = s.troll_arm_fish_1, pos = troll_delta1 }, 
				{ id = s.troll_arm_head_3, pos={0,31}},
				{ id = s.troll_club_4, pos = {-50,-1}}
			}},
			{ duration = dt, quads = { 
				{ id = s.troll_body_stand }, 
				{ id = s.troll_arm_fish_1, pos = troll_delta1 }, 
				{ id = s.troll_head_1, pos={0,31}},
				{ id = s.troll_arm_5, pos = {-7, 35}},
				{ id = s.troll_club_4, pos = {-50,-1}}
			}},
			{ duration = dt, quads = { 
				{ id = s.troll_body_stand }, 
				{ id = s.troll_arm_fish_1, pos = troll_delta1 }, 
				{ id = s.troll_head_2, pos={0,31}},
				{ id = s.troll_arm_6, pos = {-7, 35}, z=0.1},
				{ id = s.troll_club_4, pos = {-50,-1}}
			}},
			{ duration = dt, quads = { 
				{ id = s.troll_body_stand }, 
				{ id = s.troll_arm_fish_1, pos = troll_delta1 }, 
				{ id = s.troll_head_3, pos={0,31}},
				{ id = s.troll_arm_6, pos = {-7, 35},z=0.1},
				{ id = s.troll_club_4, pos = {-50,-1}}
			}},
			{ duration = dt, quads = { 
				{ id = s.troll_body_stand }, 
				{ id = s.troll_arm_fish_2, pos = troll_delta1, z = 0.1 }, 
				{ id = s.troll_head_4, pos={0,30}},
				{ id = s.troll_arm_6, pos = {-7, 35},z=0.1},
				{ id = s.troll_club_4, pos = {-50,-1}}
			}},
			{ duration = dt, quads = { 
				{ id = s.troll_body_stand }, 
				{ id = s.troll_arm_fish_3, pos = troll_delta1, z = 0.1 }, 
				{ id = s.troll_head_4, pos={0,30}},
				{ id = s.troll_arm_6, pos = {-7, 35},z=0.1},
				{ id = s.troll_club_4, pos = {-50,-1}}
			}},
			{ duration = dt, quads = { 
				{ id = s.troll_body_stand }, 
				{ id = s.troll_arm_fish_4, pos = troll_delta1, z = 0.1 }, 
				{ id = s.troll_head_4, pos={0,30}},
				{ id = s.troll_arm_6, pos = {-7, 35},z=0.1},
				{ id = s.troll_club_4, pos = {-50,-1}}
			}},
			{ duration = dt, quads = { 
				{ id = s.troll_body_stand }, 
				{ id = s.troll_arm_fish_5, pos = troll_delta1, z = 0.1 }, 
				{ id = s.troll_head_5, pos={0,30}},
				{ id = s.troll_arm_6, pos = {-7, 35},z=0.1},
				{ id = s.troll_club_4, pos = {-50,-1}}
			}},
			{ duration = dt, quads = { 
				{ id = s.troll_body_stand }, 
				{ id = s.troll_arm_fish_6, pos = troll_delta1, z = 0.1 }, 
				{ id = s.troll_head_6, pos={0,30}},
				{ id = s.troll_arm_6, pos = {-7, 35},z=0.1},
				{ id = s.troll_club_4, pos = {-50,-1}}
			}},
			{ duration = dt, quads = { 
				{ id = s.troll_body_stand }, 
				{ id = s.troll_arm_fish_7, pos = troll_delta1, z = 0.1 }, 
				{ id = s.troll_head_5, pos={0,30}},
				{ id = s.troll_arm_6, pos = {-7, 35},z=0.1},
				{ id = s.troll_club_4, pos = {-50,-1}}
			}},
			{ duration = dt, quads = { 
				{ id = s.troll_body_stand }, 
				{ id = s.troll_arm_fish_8, pos = troll_delta1, z = 0.1 }, 
				{ id = s.troll_head_6, pos={0,30}},
				{ id = s.troll_arm_6, pos = {-7, 35},z=0.1},
				{ id = s.troll_club_4, pos = {-50,-1}}
			}},
			{ duration = dt, quads = { 
				{ id = s.troll_body_stand }, 
				{ id = s.troll_arm_fish_9, pos = troll_delta1, z = 0.1 }, 
				{ id = s.troll_head_5, pos={0,30}},
				{ id = s.troll_arm_6, pos = {-7, 35},z=0.1},
				{ id = s.troll_club_4, pos = {-50,-1}}
			}},
			{ duration = dt, quads = { 
				{ id = s.troll_body_stand }, 
				{ id = s.troll_arm_fish_10, pos = troll_delta1, z = 0.1 }, 
				{ id = s.troll_head_6, pos={0,30}},
				{ id = s.troll_arm_6, pos = {-7, 35},z=0.1},
				{ id = s.troll_club_4, pos = {-50,-1}},
				{ id = s.troll_flyingfish_1, pos ={-6, 37} }
			}},
			{ duration = dt, quads = { 
				{ id = s.troll_body_stand }, 
				{ id = s.troll_arm_fish_11, pos = troll_delta1, z = 0.1 }, 
				{ id = s.troll_head_5, pos={0,30}},
				{ id = s.troll_arm_6, pos = {-7, 35},z=0.1},
				{ id = s.troll_club_4, pos = {-50,-1}},
				{ id = s.troll_flyingfish_2, pos ={-11, 51} }
			}},
			{ duration = dt, quads = { 
				{ id = s.troll_body_stand }, 
				{ id = s.troll_arm_fish_11, pos = troll_delta1, z = 0.1 }, 
				{ id = s.troll_head_6, pos={0,30}},
				{ id = s.troll_arm_6, pos = {-7, 35},z=0.1},
				{ id = s.troll_club_4, pos = {-50,-1}},
				{ id = s.troll_flyingfish_3, pos ={-9, 57} }
			}},
			{ duration = dt, quads = { 
				{ id = s.troll_body_stand }, 
				{ id = s.troll_arm_fish_11, pos = troll_delta1, z = 0.1 }, 
				{ id = s.troll_head_7, pos={0,30}},
				{ id = s.troll_arm_6, pos = {-7, 35},z=0.1},
				{ id = s.troll_club_4, pos = {-50,-1}},
				{ id = s.troll_flyingfish_4, pos ={-2, 49} }
			}},
			{ duration = dt, quads = { 
				{ id = s.troll_body_stand }, 
				{ id = s.troll_arm_fish_11, pos = troll_delta1, z = 0.1 }, 
				{ id = s.troll_head_8, pos={0,30}},
				{ id = s.troll_arm_6, pos = {-7, 35},z=0.1},
				{ id = s.troll_club_4, pos = {-50,-1}},
			}},
			{ duration = dt, quads = { 
				{ id = s.troll_body_stand }, 
				{ id = s.troll_arm_fish_11, pos = troll_delta1, z = 0.1 }, 
				{ id = s.troll_head_9, pos={0,30}},
				{ id = s.troll_arm_6, pos = {-7, 35},z=0.1},
				{ id = s.troll_club_4, pos = {-50,-1}},
			}},
			{ duration = dt, quads = { 
				{ id = s.troll_body_stand }, 
				{ id = s.troll_arm_fish_11, pos = troll_delta1, z = 0.1 }, 
				{ id = s.troll_head_5, pos={0,30}},
				{ id = s.troll_arm_6, pos = {-7, 35},z=0.1},
				{ id = s.troll_club_4, pos = {-50,-1}},
			}},
			{ duration = dt, quads = { 
				{ id = s.troll_body_stand }, 
				{ id = s.troll_arm_fish_11, pos = troll_delta1, z = 0.1 }, 
				{ id = s.troll_head_6, pos={0,30}},
				{ id = s.troll_arm_6, pos = {-7, 35},z=0.1},
				{ id = s.troll_club_4, pos = {-50,-1}},
			}},
			{ duration = dt, quads = { 
				{ id = s.troll_body_stand }, 
				{ id = s.troll_arm_fish_11, pos = troll_delta1, z = 0.1 }, 
				{ id = s.troll_head_5, pos={0,30}},
				{ id = s.troll_arm_6, pos = {-7, 35},z=0.1},
				{ id = s.troll_club_4, pos = {-50,-1}},
			}},
			{ duration = dt, quads = { 
				{ id = s.troll_body_stand }, 
				{ id = s.troll_arm_fish_11, pos = troll_delta1, z = 0.1 }, 
				{ id = s.troll_head_6, pos={0,30}},
				{ id = s.troll_arm_6, pos = {-7, 35},z=0.1},
				{ id = s.troll_club_4, pos = {-50,-1}},
			}},
			{ duration = dt, quads = { 
				{ id = s.troll_body_stand }, 
				{ id = s.troll_arm_fish_11, pos = troll_delta1, z = 0.1 }, 
				{ id = s.troll_head_5, pos={0,30}},
				{ id = s.troll_arm_6, pos = {-7, 35},z=0.1},
				{ id = s.troll_club_4, pos = {-50,-1}},
			}},
			{ duration = dt, quads = { 
				{ id = s.troll_body_stand }, 
				{ id = s.troll_arm_fish_11, pos = troll_delta1, z = 0.1 }, 
				{ id = s.troll_head_6, pos={0,30}},
				{ id = s.troll_arm_6, pos = {-7, 35},z=0.1},
				{ id = s.troll_club_4, pos = {-50,-1}},
			}},
			{ duration = dt, quads = { 
				{ id = s.troll_body_stand }, 
				{ id = s.troll_arm_fish_11, pos = troll_delta1, z = 0.1 }, 
				{ id = s.troll_head_3, pos={0,31}},
				{ id = s.troll_arm_7, pos = {-5, 37},z=0.1},
				{ id = s.troll_club_4, pos = {-50,-1}},
			}},
			{ duration = dt, quads = { 
				{ id = s.troll_body_stand }, 
				{ id = s.troll_arm_fish_11, pos = troll_delta1, z = 0.1 }, 
				{ id = s.troll_head_11, pos={0,31}},
				{ id = s.troll_club_4, pos = {-50,-1}},
			}},
			{ duration = dt, quads = { 
				{ id = s.troll_body_stand }, 
				{ id = s.troll_arm_fish_11, pos = troll_delta1, z = 0.1 }, 
				{ id = s.troll_arm_head_2, pos={0,30}},
				{ id = s.troll_club_4, pos = {-50,-1}},
			}},
			{ duration = dt, quads = { 
				{ id = s.troll_body_stand }, 
				{ id = s.troll_arm_fish_11, pos = troll_delta1, z = 0.1 }, 
				{ id = s.troll_arm_head_1, pos={0,30}},
				{ id = s.troll_club_4, pos = {-50,-1}},
			}},
			{ duration = dt, quads = { 
				{ id = s.troll_body_stand }, 
				{ id = s.troll_arm_fish_11, pos = troll_delta1, z = 0.1 }, 
				{ id = s.troll_head_front, pos={0,30}},
				{ id = s.troll_arm_6, pos = {-7, 35},z=0.1},
				{ id = s.troll_club_4, pos = {-50,-1}},
			}},
			{ duration = dt, quads = { 
				{ id = s.troll_body_front_2 }, 
				{ id = s.troll_head_front, pos={0,27}},
				{ id = s.troll_club_4, pos = {-50,-1}},
			}},
			{ duration = dt, quads = { 
				{ id = s.troll_body }, 
				{ id = s.troll_head_idle, pos={8,26} },
				{ id = s.troll_arm_rest_noclub, pos = {11, 27}},
				{ id = s.troll_club_4, pos = {-50,-1}},
			}},
			{ duration = dt, quads = { 
				{ id = s.troll_body }, 
				{ id = s.troll_head_front, pos={6,26} },
				{ id = s.troll_arm_rest_noclub, pos = {11, 27}},
				{ id = s.troll_club_4, pos = {-50,-1}},
			}},
			{ duration = 50*dt, quads = { 
				{ id = s.troll_body }, 
				{ id = s.troll_head_idle, pos={2,26}, flipx = true },
				{ id = s.troll_arm_rest_noclub, pos = {11, 27}},
				{ id = s.troll_club_4, pos = {-50,-1}},
			}}

			-- { duration = dt, quads = { { id = s.troll_body_front }, {id = s.troll_head_front, pos={0,27} }}},
			-- { duration = dt, quads = { { id = s.troll_body_front }, {id = s.troll_head_idle, flipx=true, pos={-2,27} }}},
			-- { duration = dt, quads = { { id = s.troll_body_front }, {id = s.troll_head_side, flipx=true, pos={-2,27} }}},
			-- { duration = dt, quads = { { id = s.troll_body_front }, {id = s.troll_head_idle, flipx=true, pos={-2,27} }}},
			-- { duration = dt, quads = { { id = s.troll_body_front }, {id = s.troll_head_front, pos={0,27} }}},
			-- { duration = dt, quads = { { id = s.troll_body_front }, {id = s.troll_head_idle, pos={2,27} }}},
			-- { duration = dt, quads = { { id = s.troll_body_front }, {id = s.troll_head_side, pos={2,27} }}},
			-- { duration = dt, quads = { { id = s.troll_body_front }, {id = s.troll_head_idle, pos={2,27} }}},
			-- { duration = dt, quads = { { id = s.troll_body_front }, {id = s.troll_head_front, pos={0,27} }}},
		}},

		
	}

}
