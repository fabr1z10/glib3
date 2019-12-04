local dt = 0.1
local sheet = "sprites/sprites1.png"
local sheet2 = "sprites/sprites2.png"
local layer_dz = 0.001

local s = {
	arrow_up = {x=116, y=395, width = 12, height=20 },
	arrow_down = {x = 103, y=395, width=12, height=20 },
	arrow_up_focus = {x=116, y=416, width=12, height=20},
	arrow_down_focus = {x=103, y=416, width=12, height=20},
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
	citizen_givemap_1 = {x=316,y=466,width=29,height=30, anchor={16,0}},
	citizen_givemap_2 = {x=346,y=466,width=37,height=30, anchor={16,0}},
	citizen_givemap_3 = {x=470,y=400,width=29,height=30, anchor={16,0}},	
	rat_body_idle_1 = {x=69, y=166, width=13, height=12, anchor ={5,0}},
	rat_body_idle_2 = {x=84, y=168, width=13, height=10, anchor ={6,0}},
	rat_tail_1 = {x=99, y=168, width=5, height=4, anchor ={3,0}},
	rat_tail_2 = {x=99, y=175, width=6, height=2, anchor ={4,0}},
	door_village_scummbar_open = {x=3, y=126, width=31, height=52 },
	door_village_scummbar_close = {x=35, y=126, width=31, height=52 },
	door_village_voodoolady_open = {x=31, y=179, width=26, height=24 },
	door_village_voodoolady_close = {x=3, y=179, width=26, height=24 },
	door_voodoolady_village_open = {x=36,y=55,width=33,height=58},
	door_voodoolady_village_close = {x=1,y=55,width=33,height=58},		
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
	loom_1 = {x = 221, y=457, width=29, height=38},
	important_looking_pirate_1_idle_1 = {x=319, y=410, width=35, height=55},
	important_looking_pirate_1_talk_1 = {x=394, y=409, width=35, height=56},
	important_looking_pirate_1_talk_2 = {x=431, y=411, width=35, height=54},
	important_looking_pirate_2_idle_1 = {x=2, y=1, width=34, height=53},
	important_looking_pirate_2_talk_1 = {x=39, y=1, width=34, height=56},
	important_looking_pirate_2_talk_2 = {x=75, y=1, width=35, height=52},
	important_looking_pirate_3_idle_1 = {x=113, y=1, width=35, height=52},
	important_looking_pirate_3_talk_1 = {x=150, y=1, width=31, height=52},
	important_looking_pirate_3_talk_2 = {x=183, y=2, width=32, height=51},
	important_looking_pirate_3_talk_3 = {x=217, y=1, width=31, height=52},
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
	-- troll quads
	troll_body = {x=109,y=170,width=25,height=29, anchor={12,0}},
	troll_body_2= {x=173,y=204,width=29,height=31, anchor={15,0}},
	troll_body_3= {x=295, y=145,width=28,height=34, anchor={14,0}},
	troll_arm_l_0 = {x=207, y=238, width=19, height=27, anchor ={7, 27}},
	troll_arm_l_1 = {x=275, y=236, z=0.1,width=13, height=28, anchor ={9, 28}},
	troll_arm_l_2 = {x=306, y=236, width=10, height=15, anchor ={4, 15}},
	troll_arm_l_3 = {x=156, y=203, width=16, height=14, anchor ={3, 14}},
	troll_arm_l_4 = {x=215, y=185, width=19, height=14, anchor= {5,14}},
	troll_arm_l_5 = {x=227, y=238, width=9, height=18, anchor= {7,18}},
	troll_arm_l_6 = {x=189, y=238, width=13, height=20, anchor= {2,20}},
	troll_arm_l_7 = {x=417,y=187,width=14,height=21, anchor= {4,21}},
	troll_arm_l_8 = {x=403,y=206,z=0.1,width=17,height=17, anchor= {10,17}},	
	troll_arm_l_9 = {x=423,y=210,z=0.1,width=16,height=15, anchor= {10,14}},
	troll_arm_l_10 = {x=364,y=223,z=0.1,width=16,height=14, anchor= {10,14}},
	troll_arm_l_11 = {x=403,y=224,z=0.1,width=17,height=16, anchor= {12,14}},
	troll_arm_l_12 = {x=441,y=204,z=0.1,width=20,height=26, anchor= {11,26}},
	troll_arm_l_13 = {x=462,y=204,z=0.1,width=15,height=29, anchor= {2,29}},
	troll_arm_l_14 = {x=478,y=204,z=0.1,width=10,height=31, anchor= {0,31}},
	troll_arm_l_15 = {x=490,y=204,z=0.1,width=14,height=29, anchor= {9,29}},
	troll_arm_l_16 = {x=386,y=215,z=0.1,width=16,height=14, anchor= {11,14}},
	troll_arm_l_17 = {x=423,y=227,z=0.1,width=12,height=20, anchor= {3,20}},
	troll_arm_r_0 = {x=135, y=167, width=13, height=17, anchor = {11, 17}},
	troll_arm_r_1 = {x=262, y=236, width=11, height=18, anchor = {6, 18}},
	troll_arm_r_2 = {x=290, y=236, width=12, height=32, anchor = {10, 32}},
	troll_arm_r_3 = {x=130, y=202, width=24, height=32, anchor = {22, 32}},
	troll_arm_r_4 = {x=204, y=205, width=12, height=30, anchor = {11, 30}},
	troll_arm_r_5 = {x=332, y=187, width=22, height=32, anchor={22,32}},
	troll_arm_r_6 = {x=364, y=187, width=19, height=19, anchor={18,19}},
	troll_arm_r_7 = {x=364, y=208, width=21, height=12, anchor={21,12}},
	troll_arm_r_8 = {x=388, y=187, width=15, height=12, anchor={15,12}},
	troll_arm_r_9 = {x=390, y=201, width=10, height=13, anchor={10,13}},
	troll_arm_r_10 = {x=404, y=187, width=12, z=0.1, height=17, anchor={8,17}},
	troll_arm_r_11 = {x=386, y=231, width=12, z=0.1, height=16, anchor={6, 7}},
	troll_arm_r_12 = {x=403, y=242, width=11, z=0.1, height=12, anchor={6, 6}},
	troll_arm_r_13 = {x=318, y=229, width=10, z=0.1, height=12, anchor={9, 12}},
	troll_arm_r_14 = {x=239, y=236, width=18, height=17, anchor={18,17}},
	troll_club_1 = {x=254, y=204, width=7, height=20, anchor = {4, 0}},
	troll_club_2 = {x=264, y=204, width=13, height=14, anchor = {7, 0}},
	troll_club_3 = {x=254, y=227, width=20, height=6, anchor = {10, 0}},
	troll_club_4 = {x=248, y=173, width=14, height=7, anchor = {7, 0}},
	troll_fish_1 = {x=269, y=180, width=8, height=10, anchor={4,0}},
	troll_fish_2 = {x=438, y=232, width=8, height=10, anchor={4,0}},
	troll_fish_3 = {x=447, y=232, width=10, height=6, anchor={5,0}},	
	troll_fish_4 = {x=459, y=232, width=8, height=10, anchor={4,0}},
	troll_body_front = {x=283,y=110,width=41,height=33, anchor={19,0}},
	troll_body_front_2 = {x=138,y=239,width=29,height=30, anchor={15,0}},
	troll_head_idle = {x=150, y=167, width=20, z=layer_dz, height=15, anchor = {10, 0}},
	troll_head_talk_1 = {x=171,y=166, width=20, z=0.1, height=16, anchor = {10, 0}},
	troll_head_talk_2 = {x=151,y=183, width=20, z=0.1,height=16, anchor = {10, 0}},
	troll_head_talk_3 = {x=173,y=183, width=20, z=0.1,height=17, anchor = {10, 0}},
	troll_head_talk_4 = {x=194,y=166, width=19, z=0.1,height=17, anchor = {9, 0}},
	troll_head_side = {x=231, y=201, width=20, z=0.1,height=16, anchor = {10, 0}},
	troll_head_front = {x=231, y=220, width=20, z=0.1,height=15, anchor = {10, 0}},
	troll_head_front_1 = {x=279, y=181, width=26, height=20, anchor = {16, 5}},
	troll_head_front_2 = {x=306, y=181, width=25, height=18, anchor = {15, 1}},
	troll_head_front_3 = {x=279, y=203, width=25, height=17, anchor = {15, 1}},	
	troll_head_front_4 = {x=306, y=200, width=20, height=14, anchor ={10,0}},
	troll_head_front_5 = {x=306, y=216, width=20, height=12, anchor ={10,0}},
	troll_head_front_6 = {x=279, y=221, width=20, height=12, anchor ={10,0}},
	troll_head_front_7 = {x=284, y=145, width=10, height=13, anchor ={5,0}},
	troll_head_front_8 = {x=284, y=159, width=9, height=13, anchor ={5,0}},
	troll_head_front_9 = {x=270, y=166, width=9, height=12, anchor={5,0}},
	troll_head_front_10 = {x=244, y=111, width=10, height=10, anchor={5,0}},
	troll_head_front_11 = {x=258, y=110, width=8, height=16, anchor={4,0}},
	troll_head_front_12 = {x=268, y=113, width=8, height=13, anchor={4,0}},
	troll_head_front_13 = {x=470, y=236, width=9, height=12, anchor={4,0}},
	troll_head_front_14 = {x=330, y=240, width=20, height=15, anchor={10,1}},
	troll_body_stand = {x = 295, y= 144, width = 29, height=34, anchor = {14, 0}},
	troll_fish = {x=216, y=174, z=0.1,width=14, height=8, anchor ={7,5} },
	-- fettuccini
	fettuccini_purple_idle_front = {x=137, y=271, width=27, height=45, anchor= {14,0}},
	fettuccini_purple_idle_side_body = {x=167, y=278, width=22, height=38, anchor= {13,0}},
	fettuccini_purple_idle_side_head = {x=170, y=261, width=11, height=12, anchor= {5,0}},
	fettuccini_purple_idle_back = {x=191, y=271, width=28, height=45, anchor= {14,0}},
	fettuccini_purple_talk_side_head_1 = {x=194, y=323, width=10, height=13, anchor= {5,0}},
	fettuccini_purple_talk_side_head_2 = {x=193, y=337, width=11, height=12, anchor= {5,0}},
	fettuccini_purple_talk_side_head_3 = {x=194, y=350, width=9, height=12, anchor= {5,0}},
	fettuccini_purple_walk_front_1 = {x=221, y=271, width=23, height=45, anchor={11,0}},
	fettuccini_purple_walk_front_2 = {x=246, y=270, width=24, height=46, anchor={11,0}},
	fettuccini_purple_walk_front_3 = {x=272, y=270, width=24, height=46, anchor={11,0}},
	fettuccini_purple_walk_front_4 = {x=298, y=271, width=23, height=45, anchor={11,0}},
	fettuccini_purple_walk_front_5 = {x=323, y=270, width=24, height=46, anchor={11,0}},
	fettuccini_purple_walk_front_6 = {x=349, y=271, width=24, height=45, anchor={11,0}},
	fettuccini_purple_walk_side_1 = {x=374, y=255, width=28, height=43, anchor={15,0}},
	fettuccini_purple_walk_side_2 = {x=404, y=256, width=24, height=42, anchor={15,0}},
	fettuccini_purple_walk_side_3 = {x=429, y=253, width=15, height=45, anchor={10,0}},
	fettuccini_purple_walk_side_4 = {x=446, y=255, width=26, height=43, anchor={15,0}},
	fettuccini_purple_walk_side_5 = {x=473, y=256, width=21, height=42, anchor={15,0}},
	fettuccini_purple_walk_side_6 = {x=496, y=253, width=15, height=45, anchor={10,0}},

	fettuccini_green_idle_front = {x=137, y=317, width=27, height=45, anchor= {14,0}},
	fettuccini_green_idle_side_body = {x=167, y=324, width=22, height=38, anchor= {13,0}},
	fettuccini_green_idle_side_head = {x=183, y=258, width=10, height=12, anchor= {5,0}},
	fettuccini_green_idle_back = {x=191, y=271, width=28, height=45, anchor= {14,0}},
	fettuccini_green_talk_side_head_1 = {x=206, y=324, width=10, height=12, anchor= {5,0}},
	fettuccini_green_talk_side_head_2 = {x=206, y=337, width=10, height=12, anchor= {5,0}},
	fettuccini_green_talk_side_head_3 = {x=206, y=350, width=10, height=12, anchor= {5,0}},
	fettuccini_green_walk_front_1 = {x=221, y=318, width=23, height=45, anchor={11,0}},
	fettuccini_green_walk_front_2 = {x=246, y=317, width=24, height=46, anchor={11,0}},
	fettuccini_green_walk_front_3 = {x=272, y=317, width=24, height=46, anchor={11,0}},
	fettuccini_green_walk_front_4 = {x=298, y=318, width=23, height=45, anchor={11,0}},
	fettuccini_green_walk_front_5 = {x=323, y=318, width=24, height=45, anchor={11,0}},
	fettuccini_green_walk_front_6 = {x=349, y=318, width=24, height=45, anchor={11,0}},
	fettuccini_green_walk_side_1 = {x=374, y=302, width=28, height=43, anchor={15,0}},
	fettuccini_green_walk_side_2 = {x=404, y=303, width=24, height=42, anchor={15,0}},
	fettuccini_green_walk_side_3 = {x=429, y=300, width=15, height=45, anchor={10,0}},
	fettuccini_green_walk_side_4 = {x=446, y=302, width=26, height=43, anchor={15,0}},
	fettuccini_green_walk_side_5 = {x=473, y=303, width=21, height=42, anchor={15,0}},
	fettuccini_green_walk_side_6 = {x=496, y=300, width=15, height=45, anchor={10,0}},

	circus_explosion_1 = {x=45, y=324, width=36, height=36},
	circus_explosion_2 = {x=87, y=300, width=48, height=41},
	circus_explosion_3 = {x=89, y=342, width=44, height=46},
	circus_explosion_4a = {x=2, y=354, width=46, height=50},
	circus_explosion_4b = {x=51, y=362, width=32, height=29},
	circus_explosion_5a = {x=1, y=406, width=51, height=48},
	circus_explosion_5b = {x=55, y=394, width=33, height=20},
	circus_explosion_6 = {x=2, y=457, width=48, height=43},
	circus_explosion_7 = {x=54, y=417, width=44, height=46},
	flying_guybrush_1 = {x = 53, y = 467, width = 20, height = 22},
	flying_guybrush_2 = {x = 74, y = 467, width = 26, height = 16},
	flying_guybrush_3 = {x = 74, y = 484, width = 26, height = 27},
	flying_guybrush_4 = {x = 103, y = 464, width = 37, height = 24},
	flying_guybrush_5 = {x = 103, y = 489, width=31, height=22},
	flying_guybrush_6 = {x = 143, y = 487, width = 25, height = 24},
	flying_guybrush_7 = {x = 144, y = 463, width = 22, height = 22},
	door_store_open = {x=479, y=347, width=31, height=51},
	door_store_closed = {x=446, y=347, width=31, height=51},
	door_village_store_open = {x=390, y=2, width=20, height=31},
	door_village_store_closed = {x=413, y=2, width=20, height=31},
	door_village_church_open = {x=398, y=347, width=22, height=34},
	door_village_church_closed = {x=422, y=347, width=22, height=34},


	sword = {x=99, y=49, width=30, height=6},
	shovel = {x=131, y=49, width = 8, height=25},
	sign = {x=370, y=2, width=16, height=10},
	bell = {x=370, y=15, width=8, height=5},

	storekeeper_idle_body_side = {x=137, y=365, width=28, height=42, anchor = {12, 0}},
	storekeeper_idle_head_side = {x=141, y=61, width=10, height=13, anchor = {6,0}},
	storekeeper_idle_south = {x=359, y=364, width=34, height=44, anchor ={19, 0}},
	storekeeper_talk_head_side_1 = {x=99, y=33, width=10, height=14, anchor = {6,0}},
	storekeeper_talk_head_side_2 = {x=111, y=34, width=10, height=13, anchor = {6,0}},
	storekeeper_talk_head_side_3 = {x=123, y=34, width=12, height=12, anchor = {6,0}},
	storekeeper_talk_head_side_4 = {x=137, y=33, width=11, height=15, anchor = {6,0}},
	storekeeper_talk_head_side_5 = {x=150, y=33, width=11, height=15, anchor = {6,0}},
	storekeeper_walk_south_1 = {x=167, y=364, width=34, height=43, anchor = {20, 0}},
	storekeeper_walk_south_2 = {x=202, y=364, width=29, height=43, anchor = {17, 0}},
	storekeeper_walk_south_3 = {x=233, y=366, width=28, height=41, anchor = {15, 0}},
	storekeeper_walk_south_4 = {x=263, y=365, width=29, height=42, anchor = {14, 0}},
	storekeeper_walk_south_5 = {x=294, y=365, width=30, height=42, anchor = {15, 0}},
	storekeeper_walk_south_6 = {x=326, y=366, width=31, height=41, anchor = {17, 0}},
	storekeeper_walk_east_1 = {x=134, y=408, width=30, height=45, anchor = {16, 0}},
	storekeeper_walk_east_2 = {x=166, y=410, width=26, height=44, anchor = {16, 0}},
	storekeeper_walk_east_3 = {x=194, y=408, width=27, height=46, anchor = {16, 0}},
	storekeeper_walk_east_4 = {x=223, y=409, width=26, height=45, anchor = {18, 0}},
	storekeeper_walk_east_5 = {x=251, y=411, width=25, height=43, anchor = {17, 0}},
	storekeeper_walk_east_6 = {x=279, y=409, width=37, height=45, anchor = {18, 0}},

	lookout_fire_1 = {x=409, y=479, width = 24, height=32},
	lookout_fire_2 = {x=435, y=479, width = 24, height=32},
	lookout_fire_3 = {x=461, y=479, width = 24, height=32},
	lookout_fire_4 = {x=487, y=479, width = 24, height=32},

	lookout_idle_body_side = {x=170, y=457, width=20, height=37, anchor={11, 0}},
	lookout_idle_body_front = {x=193, y=459, width=23, height=35, anchor={11, 0}},
	lookout_idle_head_side = {x=173, y=495, width=11, height=13, anchor={5, 0}},
	lookout_talk_head_side_1 = {x=197, y=496, width=11, height=14, anchor={5, 0}},
	lookout_talk_head_side_2 = {x=210, y=496, width=11, height=13, anchor={5, 0}},
	lookout_idle_head_front = {x=186, y=495, width=9, height=14, anchor={5, 0}},
	lookout_talk_head_front_1 = {x=223, y=496, width=9, height=15, anchor={5, 0}},
	lookout_talk_head_front_2 = {x=234, y=496, width=9, height=13, anchor={5, 0}},

	troll_head_11 = {x=332, y=221, width=25, height=18, anchor={15,5}},	
	voodoolady_trunk = {x=71,y=56,width=81,height=24},
	rubber_chicken = {x=472,y=98,width=27,height=20},
	voodoolady_baskets = {x=71,y=81,width=79,height=35},
	voodoolady_basket = {x=473,y=121,width=23,height=20},
	otis_walk_e_1 = {x=1,y=115,width=17,height=44,anchor={11,0}},
	otis_walk_e_2 = {x=19,y=114,width=19,height=45,anchor={12,0}},
	otis_walk_e_3 = {x=39,y=115,width=32,height=44,anchor={17,0}},
	otis_walk_e_4 = {x=72,y=116,width=16,height=43,anchor={10,0}},
	otis_walk_e_5 = {x=1,y=160,width=19,height=45,anchor={12,0}},
	otis_walk_e_6 = {x=21,y=161,width=32,height=44,anchor={17,0}},
	otis_walk_n_1 = {x=1,y=209,width=19,height=43,anchor={9,0}},
	otis_walk_n_2 = {x=21,y=207,width=20,height=45,anchor={11,0}},
	otis_walk_n_3 = {x=42,y=207,width=19,height=45,anchor={11,0}},
	otis_walk_n_4 = {x=62,y=208,width=19,height=44,anchor={9,0}},
	otis_walk_n_5 = {x=82,y=207,width=20,height=45,anchor={9,0}},
	otis_walk_n_6 = {x=103,y=207,width=19,height=45,anchor={8,0}},
	otis_walk_s_1 = {x=55,y=161,width=22,height=44,anchor={11,0}},
	otis_walk_s_2 = {x=78,y=161,width=20,height=44,anchor={9,0}},
	otis_walk_s_3 = {x=99,y=161,width=20,height=44,anchor={9,0}},
	otis_walk_s_4 = {x=120,y=161,width=22,height=44,anchor={11,0}},
	otis_walk_s_5 = {x=143,y=161,width=21,height=44,anchor={11,0}},
	otis_walk_s_6 = {x=165,y=161,width=20,height=44,anchor={11,0}},
	otis_idle_body_e = {x=111,y=124,width=22,height=35,anchor={12,0}},
	otis_idle_body_s = {x=111,y=124,width=22,height=35,anchor={12,0}},
	otis_idle_body_n = {x=90,y=123,width=19,height=36,anchor={10,0}},
	otis_idle_legs = {x=136,y=136,width=17,height=23,anchor={7, 0}},
	otis_idle_head_e = {x=137,y=123,width=11,height=10,anchor={6,0}},
	otis_idle_head_s = {x=151,y=123,width=9,height=12,anchor={6,0}},
	swordmaster_sign_1 = {x=395,y=382,width=26,height=25},
	swordmaster_sign_2 = {x=422,y=383,width=21,height=25},
	trunk_bridge_closed = {x=252,y=1,width=77,height=38},
	trunk_bridge_open = {x=252,y=41,width=77,height=38},
	swordmaster_tiny_1 = {x=484,y=465,width=8,height=12,anchor={4,0}},
	swordmaster_tiny_2 = {x=494,y=465,width=8,height=12,anchor={4,0}},
	swordmaster_tiny_3 = {x=504,y=465,width=5,height=12,anchor={3,0}},


	
	
	
	
	
	
	
	
	
	
	









	















}

factory.model.create_simple { id="voodoolady.trunk", sheet=sheet2, frame = s.voodoolady_trunk }
factory.model.create_simple { id="rubber.chicken", sheet=sheet, frame = s.rubber_chicken }
factory.model.create_simple { id="voodoolady.baskets", sheet=sheet2, frame = s.voodoolady_baskets }
factory.model.create_simple { id="voodoolady.basket", sheet=sheet, frame = s.voodoolady_basket }
--local s = spritesheets["sprites1"]

engine.assets.models["arrow_up"] = {
    sheet = sheet,
    type = "sprite",
    ppu=1,
	animations = {
		{ name = "unselected", frames = { { duration = dt, quads = {{ id = s.arrow_up }}}}},
		{ name = "selected", frames = { { duration = dt, quads = {{ id = s.arrow_up_focus }}}}}
	}
}

engine.assets.models["arrow_down"] = {
    sheet = sheet,
    type = "sprite",
    ppu=1,
	animations = {
		{ name = "unselected", frames = { { duration = dt, quads = {{ id = s.arrow_down }}}}},
		{ name = "selected", frames = { { duration = dt, quads = {{ id = s.arrow_down_focus }}}}}
	}
}


engine.assets.models["low_moral_fiber_1"] = {
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

engine.assets.models["low_moral_fiber_2"] = {
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



engine.assets.models["cook"] = {
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

-- engine.assets.models["citizen.body"] = {
--     sheet = sheet,
--     type = "sprite",
--     ppu=1,
-- 	animations = {
-- 		{ name = "idle_s", frames = { { duration = dt, quads = {{ id = s.citizen_body_idle_south }}}}},
-- 		{ name = "idle_e", frames = { { duration = dt, quads = {{ id = s.citizen_body_idle_east }}}}},
-- 		{ name = "open_jacket", loop=false, frames = {
-- 			{ duration = dt, quads = {{ id = s.citizen_body_idle_east }}},
-- 			{ duration = dt, quads = {{ id = s.citizen_open_jacket_1 }}},
-- 			{ duration = dt, quads = {{ id = s.citizen_open_jacket_2 }}},
-- 			{ duration = dt, quads = {{ id = s.citizen_open_jacket_3 }}},
-- 			{ duration = dt, quads = {{ id = s.citizen_open_jacket_4 }}},
-- 		}},
-- 		{ name = "rollmap", loop=false, frames = {
-- 			{ duration = dt, quads = {{ id = s.citizen_body_idle_east }}},
-- 			{ duration = dt, quads = {{ id = s.citizen_rollmap_1 }}},
-- 			{ duration = dt, quads = {{ id = s.citizen_rollmap_2 }}},
-- 			{ duration = dt, quads = {{ id = s.citizen_rollmap_3 }}},
-- 			{ duration = dt, quads = {{ id = s.citizen_rollmap_4 }}},
-- 			{ duration = dt, quads = {{ id = s.citizen_rollmap_5 }}},
-- 		}},

-- 	}
-- }

-- engine.assets.models["citizen.head"] = {
--     sheet = sheet,
--     type = "sprite",
--     ppu=1,
-- 	animations = {
-- 		{ name = "idle_s", frames = { 
-- 			{ duration = dt, quads = {{ id = s.citizen_head_idle_south1 }}},
-- 			{ duration = dt, quads = {{ id = s.citizen_head_idle_south2 }}},
-- 			{ duration = dt, quads = {{ id = s.citizen_head_idle_south1 }}},
-- 			{ duration = dt, quads = {{ id = s.citizen_head_idle_south2, flipx=true }}}
-- 		}},
-- 		{ name = "idle_e", frames = { 
-- 			{ duration = dt, quads = {{ id = s.citizen_head_idle_south2 }}},
-- 			{ duration = dt, quads = {{ id = s.citizen_head_idle_east }}},
-- 			{ duration = dt, quads = {{ id = s.citizen_head_idle_south2 }}},
-- 			{ duration = dt, quads = {{ id = s.citizen_head_idle_south1 }}}
-- 		}},
-- 		{ name = "talk", frames = { 
-- 			{ duration = dt, quads = {{ id = s.citizen_head_talk_1 }}},
-- 			{ duration = dt, quads = {{ id = s.citizen_head_talk_2 }}},
-- 			{ duration = dt, quads = {{ id = s.citizen_head_idle_east }}},
-- 		}},

-- 	}
-- }

local citizen_head = {0, 26, 0}
local citizen_head_1 = {-2, 26, 0}

engine.assets.models["citizen"] = {
	sheet = sheet,
	type = "sprite",
	ppu=1,
	animations = {
		{ 
			name = "idle_s",
			frames = {
				{ duration = dt, quads = { {id=s.citizen_body_idle_south}, {id = s.citizen_head_idle_south1, pos = citizen_head}}},
				{ duration = dt, quads = { {id=s.citizen_body_idle_south}, {id = s.citizen_head_idle_south2, pos = citizen_head}}},
				{ duration = dt, quads = { {id=s.citizen_body_idle_south}, {id = s.citizen_head_idle_south1, pos = citizen_head}}},
				{ duration = dt, quads = { {id=s.citizen_body_idle_south}, {id = s.citizen_head_idle_south2, flipx=true, pos = citizen_head}}},
			}
		},
		{ 
			name = "talk_s",
			frames = {
				{ duration = dt, quads = { {id=s.citizen_body_idle_south}, {id = s.citizen_head_talk_1, pos = citizen_head}}},
				{ duration = dt, quads = { {id=s.citizen_body_idle_south}, {id = s.citizen_head_talk_2, pos = citizen_head}}},
				{ duration = dt, quads = { {id=s.citizen_body_idle_south}, {id = s.citizen_head_idle_south1, pos = citizen_head}}},
			}
		},		
		{
			name = "idle_e",
			frames = {
				{ duration = dt, quads = { {id=s.citizen_body_idle_east}, {id = s.citizen_head_idle_south2, pos = citizen_head_1}}},
				{ duration = dt, quads = { {id=s.citizen_body_idle_east}, {id = s.citizen_head_idle_east, pos = citizen_head_1}}},
				{ duration = dt, quads = { {id=s.citizen_body_idle_east}, {id = s.citizen_head_idle_south2, pos = citizen_head_1}}},
				{ duration = dt, quads = { {id=s.citizen_body_idle_east}, {id = s.citizen_head_idle_south1, pos = citizen_head_1}}},
			}
		},
		{
			name = "idle_e_1",
			frames = {
				{ duration = dt, quads = { {id=s.citizen_open_jacket_4}, {id = s.citizen_head_idle_south2, pos = citizen_head_1}}},
				{ duration = dt, quads = { {id=s.citizen_open_jacket_4}, {id = s.citizen_head_idle_east, pos = citizen_head_1}}},
				{ duration = dt, quads = { {id=s.citizen_open_jacket_4}, {id = s.citizen_head_idle_south2, pos = citizen_head_1}}},
				{ duration = dt, quads = { {id=s.citizen_open_jacket_4}, {id = s.citizen_head_idle_south1, pos = citizen_head_1}}},
			}
		},
		{
			name = "idle_e_2",
			frames = {
				{ duration = dt, quads = { {id=s.citizen_rollmap_5}, {id = s.citizen_head_idle_south2, pos = citizen_head_1}}},
				{ duration = dt, quads = { {id=s.citizen_rollmap_5}, {id = s.citizen_head_idle_east, pos = citizen_head_1}}},
				{ duration = dt, quads = { {id=s.citizen_rollmap_5}, {id = s.citizen_head_idle_south2, pos = citizen_head_1}}},
				{ duration = dt, quads = { {id=s.citizen_rollmap_5}, {id = s.citizen_head_idle_south1, pos = citizen_head_1}}},
			}
		},
		{
			name = "talk_e",
			frames = {
				{ duration = dt, quads = { {id=s.citizen_body_idle_east}, {id = s.citizen_head_talk_1, pos = citizen_head_1}}},
				{ duration = dt, quads = { {id=s.citizen_body_idle_east}, {id = s.citizen_head_talk_2, pos = citizen_head_1}}},
				{ duration = dt, quads = { {id=s.citizen_body_idle_east}, {id = s.citizen_head_idle_east, pos = citizen_head_1}}},
			}
		},
		{
			name = "talk_e_1",
			frames = {
				{ duration = dt, quads = { {id=s.citizen_open_jacket_4}, {id = s.citizen_head_talk_1, pos = citizen_head_1}}},
				{ duration = dt, quads = { {id=s.citizen_open_jacket_4}, {id = s.citizen_head_talk_2, pos = citizen_head_1}}},
				{ duration = dt, quads = { {id=s.citizen_open_jacket_4}, {id = s.citizen_head_idle_east, pos = citizen_head_1}}},
			}
		},	
		{
			name = "talk_e_2",
			frames = {
				{ duration = dt, quads = { {id=s.citizen_rollmap_5}, {id = s.citizen_head_talk_1, pos = citizen_head_1}}},
				{ duration = dt, quads = { {id=s.citizen_rollmap_5}, {id = s.citizen_head_talk_2, pos = citizen_head_1}}},
				{ duration = dt, quads = { {id=s.citizen_rollmap_5}, {id = s.citizen_head_idle_east, pos = citizen_head_1}}},
			}
		},	
		{
			name="open_jacket",
			loop = false,
			frames = {
				{ duration = dt, quads = { {id=s.citizen_body_idle_east}, {id = s.citizen_head_idle_east, pos = citizen_head_1}}},				
				{ duration = dt, quads = { {id=s.citizen_open_jacket_1}, {id = s.citizen_head_idle_east, pos = citizen_head_1}}},
				{ duration = dt, quads = { {id=s.citizen_open_jacket_2}, {id = s.citizen_head_idle_east, pos = citizen_head_1}}},
				{ duration = dt, quads = { {id=s.citizen_open_jacket_3}, {id = s.citizen_head_idle_east, pos = citizen_head_1}}},
				{ duration = dt, quads = { {id=s.citizen_open_jacket_4}, {id = s.citizen_head_idle_east, pos = citizen_head_1}}},
			}
		},
		{
			name="rollmap",
			loop = false,
			frames = {
				{ duration = dt, quads = { {id=s.citizen_body_idle_east}, {id = s.citizen_head_idle_east, pos = citizen_head_1}}},				
				{ duration = dt, quads = { {id=s.citizen_rollmap_1}, {id = s.citizen_head_idle_east, pos = citizen_head_1}}},
				{ duration = dt, quads = { {id=s.citizen_rollmap_2}, {id = s.citizen_head_idle_east, pos = citizen_head_1}}},
				{ duration = dt, quads = { {id=s.citizen_rollmap_3}, {id = s.citizen_head_idle_east, pos = citizen_head_1}}},
				{ duration = dt, quads = { {id=s.citizen_rollmap_4}, {id = s.citizen_head_idle_east, pos = citizen_head_1}}},
				{ duration = dt, quads = { {id=s.citizen_rollmap_5}, {id = s.citizen_head_idle_east, pos = citizen_head_1}}},
			}
		},
		{
			name = "givemap",
			loop = false,
			frames = {
				{ duration = dt, quads = { {id=s.citizen_givemap_1}, {id = s.citizen_head_idle_east, pos = citizen_head_1}}},				
				{ duration = dt, quads = { {id=s.citizen_givemap_2}, {id = s.citizen_head_idle_east, pos = citizen_head_1}}},
				{ duration = dt, quads = { {id=s.citizen_givemap_3}, {id = s.citizen_head_idle_east, pos = citizen_head_1}}},
				{ duration = dt, quads = { {id=s.citizen_body_idle_east}, {id = s.citizen_head_idle_east, pos = citizen_head_1}}},
			}

		}

	}
}

engine.assets.models["door_village_scummbar"] = {
    sheet = sheet,
    type = "sprite",
    ppu=1,
	animations = {
		{ name = "open", frames = { { duration = dt, quads = {{ id = s.door_village_scummbar_open }}}}},
		{ name = "close", frames = { { duration = dt, quads = {{ id = s.door_village_scummbar_close }}}}}
	}
}

engine.assets.models["door_village_voodoolady"] = {
    sheet = sheet,
    type = "sprite",
    ppu=1,
	animations = {
		{ name = "open", frames = { { duration = dt, quads = {{ id = s.door_village_voodoolady_open }}}}},
		{ name = "close", frames = { { duration = dt, quads = {{ id = s.door_village_voodoolady_close }}}}}
	}
}

engine.assets.models["door_voodoolady"] = {
    sheet = sheet2,
    type = "sprite",
    ppu=1,
	animations = {
		{ name = "open", frames = { { duration = dt, quads = {{ id = s.door_voodoolady_village_open }}}}},
		{ name = "close", frames = { { duration = dt, quads = {{ id = s.door_voodoolady_village_close }}}}}
	}
}

engine.assets.models["fakedoor_village_1"] = {
    sheet = sheet,
    type = "sprite",
    ppu=1,
	animations = {
		{ name = "open", frames = { { duration = dt, quads = {{ id = s.fakedoor1_village_door_open }}}}},
		{ name = "close", frames = { { duration = dt, quads = {{ id = s.fakedoor1_village_door_close }}}}}
	}
}

engine.assets.models["fakedoor_village_2"] = {
    sheet = sheet,
    type = "sprite",
    ppu=1,
	animations = {
		{ name = "open", frames = { { duration = dt, quads = {{ id = s.fakedoor2_village_door_open }}}}},
		{ name = "close", frames = { { duration = dt, quads = {{ id = s.fakedoor2_village_door_close }}}}}
	}
}

engine.assets.models["lmf3.body"] = {
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

engine.assets.models["lmf3.head"] = {
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

local lmf3_head = {-3,34,0}
local lmf3_head_1 = {-4,34,0}
engine.assets.models["low_moral_fiber_3"] = {
	sheet = sheet,
	type = "sprite",
	ppu = 1,
	animations = {
		{
			name="idle_e",
			frames = {
				{ duration = dt, quads = { {id=s.low_moral_fiber_3_body_idle}, {id=s.low_moral_fiber_3_head_idle_e, pos=lmf3_head}}}

			}
		},
		{
			name="idle_s",
			frames = {
				{ duration = dt, quads = { {id=s.low_moral_fiber_3_body_idle}, {id=s.low_moral_fiber_3_head_idle_s, pos=lmf3_head_1}}}

			}
		},
		{
			name="talk_e",
			frames = {
				{ duration = dt, quads = { {id=s.low_moral_fiber_3_body_idle}, {id=s.low_moral_fiber_3_head_talk_e_1, pos=lmf3_head}}},
				{ duration = dt, quads = { {id=s.low_moral_fiber_3_body_idle}, {id=s.low_moral_fiber_3_head_talk_e_2, pos=lmf3_head}}},
				{ duration = dt, quads = { {id=s.low_moral_fiber_3_body_idle}, {id=s.low_moral_fiber_3_head_talk_e_3, pos=lmf3_head}}},
			}
		},
		{
			name="talk_e_1",
			frames = {
				{ duration = dt, quads = { {id=s.low_moral_fiber_3_body_open_jacket_2}, {id=s.low_moral_fiber_3_head_talk_e_1, pos=lmf3_head}}},
				{ duration = dt, quads = { {id=s.low_moral_fiber_3_body_open_jacket_2}, {id=s.low_moral_fiber_3_head_talk_e_2, pos=lmf3_head}}},
				{ duration = dt, quads = { {id=s.low_moral_fiber_3_body_open_jacket_2}, {id=s.low_moral_fiber_3_head_talk_e_3, pos=lmf3_head}}},
			}
		},
		{
			name="talk_s",
			frames = {
				{ duration = dt, quads = { {id=s.low_moral_fiber_3_body_idle}, {id=s.low_moral_fiber_3_head_idle_s, pos=lmf3_head_1}}},
				{ duration = dt, quads = { {id=s.low_moral_fiber_3_body_idle}, {id=s.low_moral_fiber_3_head_talk_s_1, pos=lmf3_head_1}}}

			}
		},
		{
			name ="punch",
			loop = false,
			frames = {
				{ duration = dt, quads = { {id=s.low_moral_fiber_3_body_idle}, {id=s.low_moral_fiber_3_head_idle_s, pos=lmf3_head_1}}},
				{ duration = dt, quads = { {id=s.low_moral_fiber_3_body_punch_1}, {id=s.low_moral_fiber_3_head_idle_s, pos=lmf3_head_1}}},
				{ duration = 2*dt, quads = { {id=s.low_moral_fiber_3_body_punch_2}, {id=s.low_moral_fiber_3_head_idle_s, pos=lmf3_head_1}}},
				{ duration = dt, quads = { {id=s.low_moral_fiber_3_body_punch_3}, {id=s.low_moral_fiber_3_head_idle_s, pos=lmf3_head_1}}}
			}
		},
		{
			name="open_jacket",
			loop = false,
			frames = {
				{ duration = dt, quads = { {id=s.low_moral_fiber_3_body_idle}, {id=s.low_moral_fiber_3_head_idle_e, pos=lmf3_head}}},
				{ duration = dt, quads = { {id=s.low_moral_fiber_3_body_open_jacket_1}, {id=s.low_moral_fiber_3_head_idle_e, pos=lmf3_head}}},
				{ duration = dt, quads = { {id=s.low_moral_fiber_3_body_open_jacket_2}, {id=s.low_moral_fiber_3_head_idle_e, pos=lmf3_head}}}
			}			

		}

	}

 --    type = "model",
	-- components = {
	-- 	{ name="body", mesh="lmf3.body"},
	-- 	{ name="head", mesh="lmf3.head"},
	-- },
	-- animations = {
	-- 	{ name = "idle_e", anims = { {name="body", anim="idle_e"}, {name="head", anim="idle_e", pos={-3,34,0} }}},
	-- 	{ name = "idle_s", anims = { {name="body", anim="idle_e"}, {name="head", anim="idle_s", pos={-4,34,0} }}},
	-- 	{ name = "talk_s", anims = { {name="body", anim="idle_e"}, {name="head", anim="talk_s", pos={-4,34,0} }}},
	-- 	{ name = "talk_e", anims = { {name="body", anim="idle_e"}, {name="head", anim="talk_e", pos={-4,34,0} }}},
	-- 	{ name = "punch", loop = false, anims = { {name="body", anim="punch" }, {name="head", anim="talk_s", pos ={-4,34,0} }}},
	-- 	{ name = "h_talk_s", anims = { {name="head", anim="talk_s", pos={-4,34,0} }}},
	-- 	{ name = "h_talk_e", anims = { {name="head", anim="talk_e", pos={-4,34,0} }}},		-- { name = "talk_start", anims = { {name="head", anim="talk", pos ={-1,25,0} }}},
	-- 	-- { name = "talk_end", anims = { {name="head", anim="idle_e", pos ={-1,25,0} }}},
	-- 	{ name = "open_jacket", loop = false, anims = { { name="body", anim="open_jacket" }}},
	-- 	-- { name = "rollmap", anims = { { name="body", anim="rollmap" }}}

	-- }
}


engine.assets.models["village2.rat"] = {
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

engine.assets.models["door_scummbar_village"] = {
    sheet = sheet,
    type = "sprite",
    ppu=1,
	animations = {
		{ name = "open", frames = { { duration = dt, quads = {{ id = s.door_scummbar_village_open }}}}},
		{ name = "close", frames = { { duration = dt, quads = {{ id = s.door_scummbar_village_close }}}}}
	}
}

engine.assets.models["door_scummbar_kitchen"] = {
    sheet = sheet,
    type = "sprite",
    ppu=1,
	animations = {
		{ name = "open", frames = { { duration = dt, quads = {{ id = s.door_scummbar_kitchen_open }}}}},
		{ name = "close", frames = { { duration = dt, quads = {{ id = s.door_scummbar_kitchen_close }}}}}
	}
}

engine.assets.models["door_kitchen_scummbar"] = {
    sheet = sheet,
    type = "sprite",
    ppu=1,
	animations = {
		{ name = "open", frames = { { duration = dt, quads = {{ id = s.door_kitchen_scummbar_open }}}}},
		{ name = "close", frames = { { duration = dt, quads = {{ id = s.door_kitchen_scummbar_close }}}}}
	}
}

engine.assets.models["door_kitchen_pier"] = {
    sheet = sheet,
    type = "sprite",
    ppu=1,
	animations = {
		{ name = "open", frames = { { duration = dt, quads = {{ id = s.door_kitchen_pier_open }}}}},
		{ name = "close", frames = { { duration = dt, quads = {{ id = s.door_kitchen_pier_close }}}}}
	}
}

engine.assets.models["scummbar.mancomb"] = {
    sheet = sheet,
    type = "sprite",
    ppu=1,
	animations = {
		{ name = "idle_1", frames = { { duration = dt, quads = {{ id = s.mancomb_1 }}}}},
		{ name = "idle_2", frames = { { duration = dt, quads = {{ id = s.mancomb_2 }}}}}
	}
}

engine.assets.models["scummbar.estevan"] = {
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

engine.assets.models["scummbar.loompirate"] = {
    sheet = sheet,
    type = "sprite",
    ppu=1,
	animations = {
		{ name = "idle_1", frames = { { duration = dt, quads = {{ id = s.loom_1 }}}}},
		-- { name = "idle_2", frames = { 
		-- 	{ duration = dt, quads = {{ id = s.estevan_2 }}},
		-- 	{ duration = dt, quads = {{ id = s.estevan_3 }}}
		-- }}

	}
}

engine.assets.models["scummbar.ilp1"] = {
    sheet = sheet,
    type = "sprite",
    ppu=1,
	animations = {
		{ name = "idle_e", frames = { { duration = dt, quads = {{ id = s.important_looking_pirate_1_idle_1 }}}}},
		{ name = "talk_e", frames = { 
			{ duration = dt, quads = {{ id = s.important_looking_pirate_1_talk_1 }}},
			{ duration = dt, quads = {{ id = s.important_looking_pirate_1_talk_2 }}}
		}
		},
	}
}

engine.assets.models["scummbar.ilp2"] = {
    sheet = sheet2,
    type = "sprite",
    ppu=1,
	animations = {
		{ name = "idle_e", frames = { { duration = dt, quads = {{ id = s.important_looking_pirate_2_idle_1 }}}}},
		{ name = "talk_e", frames = { 
			{ duration = dt, quads = {{ id = s.important_looking_pirate_2_talk_1 }}},
			{ duration = dt, quads = {{ id = s.important_looking_pirate_2_talk_2 }}}
		}
		},
	}
}

engine.assets.models["scummbar.ilp3"] = {
    sheet = sheet2,
    type = "sprite",
    ppu=1,
	animations = {
		{ name = "idle_e", frames = { { duration = dt, quads = {{ id = s.important_looking_pirate_3_idle_1 }}}}},
		{ name = "talk_e", frames = { 
			{ duration = dt, quads = {{ id = s.important_looking_pirate_3_talk_1 }}},
			{ duration = dt, quads = {{ id = s.important_looking_pirate_3_talk_2 }}},
			{ duration = dt, quads = {{ id = s.important_looking_pirate_3_talk_3 }}},

		}
		},
	}
}


engine.assets.models["kitchen.seagull"] = {
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

engine.assets.models["kitchen.plank"] = {
    sheet = sheet,
    type = "sprite",
    ppu=1,
	animations = {
		{ name = "idle", frames = { { duration = dt, quads = {{ id = s.plank_idle }}}}},
		{ name = "pushed", frames = { { duration = dt, quads = {{ id = s.plank_pushed }}}}}
	}
}

engine.assets.models["kitchen.meat"] = {
    sheet = sheet,
    type = "sprite",
    ppu=1,
	animations = {
		{ name = "idle", frames = { { duration = dt, quads = {{ id = s.meat }}}}},
	}
}

engine.assets.models["kitchen.pot"] = {
    sheet = sheet,
    type = "sprite",
    ppu=1,
	animations = {
		{ name = "idle", frames = { { duration = dt, quads = {{ id = s.pot }}}}},
	}
}

engine.assets.models["kitchen.fish"] = {
    sheet = sheet,
    type = "sprite",
    ppu=1,
	animations = {
		{ name = "idle", frames = { { duration = dt, quads = {{ id = s.fish }}}}},
	}
}

engine.assets.models["kitchen.potostew"] = {
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

engine.assets.models["scummbar.fireplace"] = {
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

engine.assets.models["kitchen.table"] = {
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
	head_flip = {6, 26},
	arm_right = {-2, 32},
	arm_left = {11, 27},
	head_2 = {2,26},
	arm_left_2 = {8, 30},
	arm_right_2 = {-8, 32},

}
local f1 = function(body, head, arm_left, arm_right, dur) 
	return { duration = dur or dt, quads = {
		{ id = body }, 
		{ id = head, flipx = flipx or false, pos = troll_info.head },
		{ id = arm_left, pos = troll_info.arm_left},
		{ id = arm_right, pos = troll_info.arm_right, z=0.1}
	}}
end

local f1a = function(arm_right, club, pos_club, dur) 
	local f = { duration = dur or dt, quads = {
		{ id = s.troll_body }, 
		{ id = s.troll_head_idle, flipx = true, pos = troll_info.head_flip },
		{ id = s.troll_arm_l_5, pos = troll_info.arm_left},
		{ id = arm_right, pos = troll_info.arm_right, z=0.1},
		--{ id = club, pos = pos_club }
	}}
	if (club ~= nil) then
		table.insert(f.quads, {id=club, pos=pos_club})
	end
	return f
end



local f2 = function(body, head, arm_left, arm_right, fish, fish_pos, dur) 
	return { duration = dur or dt, quads = {
		{ id = body }, 
		{ id = head, pos = troll_info.head },
		{ id = arm_left, pos = troll_info.arm_left},
		{ id = arm_right, pos = troll_info.arm_right, z=0.1},
		{ id = fish, pos = fish_pos }
	}}
end
local f3 = function(head, arm_left, arm_right, fish, fliphead, dur) 
	local f = { duration = dur or dt, quads = {
		{ id = s.troll_body_2 }, 
		{ id = head, flipx = fliphead, pos = troll_info.head_2 },
		{ id = arm_left, pos = troll_info.arm_left_2},
		{ id = arm_right, pos = troll_info.arm_right_2, z=0.1}
	}}
	if (fish ~= nil) then
		table.insert(f.quads, {id = fish.id, pos = fish.pos})
	end
	return f
end
local f4 = function(head, arm_left, arm_right, club, fish, dur) 
	local f = { duration = dur or dt, quads = {
		{ id = s.troll_body_3 }, 
		{ id = head, pos = {0,31} },
		{ id = arm_left, pos = {5, 35}},
	}}
	if (arm_right) then
		table.insert(f.quads, { id = arm_right, pos = {-7, 34}})
	end
	if (club ~= nil) then
		table.insert(f.quads, {id = club.id, pos = club.pos})
	else
		table.insert(f.quads, {id = s.troll_club_4, pos = {-50, 1}})
	end
	if (fish ~= nil) then
		table.insert(f.quads, {id = fish.id, pos = fish.pos})
	end
	return f
end


engine.assets.models["bridge.troll"] = {
    sheet = sheet,
    type = "sprite",
    ppu=1,
	animations = {
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
			f1(s.troll_body, s.troll_head_talk_1, s.troll_arm_l_2, s.troll_arm_r_2),
			f1(s.troll_body, s.troll_head_talk_3, s.troll_arm_l_3, s.troll_arm_r_3),
			f1(s.troll_body, s.troll_head_talk_4, s.troll_arm_l_4, s.troll_arm_r_3),
			f2(s.troll_body, s.troll_head_talk_1, s.troll_arm_l_4, s.troll_arm_r_3, s.troll_fish, {21, 17}),
			f2(s.troll_body, s.troll_head_talk_2, s.troll_arm_l_3, s.troll_arm_r_3, s.troll_fish, {19, 17}),
			f2(s.troll_body, s.troll_head_talk_4, s.troll_arm_l_2, s.troll_arm_r_3, s.troll_fish, {15, 15}),
			f2(s.troll_body, s.troll_head_talk_1, s.troll_arm_l_5, s.troll_arm_r_3, s.troll_fish, {14, 13}),
		}},
		{ name = "idle_fish", frames = { 
			f2(s.troll_body, s.troll_head_idle, s.troll_arm_l_5, s.troll_arm_r_3, s.troll_fish, {14, 13})
		}},
		{ name = "talk_fish", frames = { 
			f2(s.troll_body, s.troll_head_talk_2, s.troll_arm_l_5, s.troll_arm_r_3, s.troll_fish, {14, 13}),
			f2(s.troll_body, s.troll_head_talk_1, s.troll_arm_l_5, s.troll_arm_r_3, s.troll_fish, {14, 13}),
			f2(s.troll_body, s.troll_head_talk_3, s.troll_arm_l_5, s.troll_arm_r_3, s.troll_fish, {14, 13}),
			f2(s.troll_body, s.troll_head_talk_1, s.troll_arm_l_5, s.troll_arm_r_3, s.troll_fish, {14, 13}),
			f2(s.troll_body, s.troll_head_talk_4, s.troll_arm_l_5, s.troll_arm_r_3, s.troll_fish, {14, 13}),
			f2(s.troll_body, s.troll_head_talk_1, s.troll_arm_l_5, s.troll_arm_r_3, s.troll_fish, {14, 13}),
			f2(s.troll_body, s.troll_head_talk_2, s.troll_arm_l_5, s.troll_arm_r_3, s.troll_fish, {14, 13}),
			f2(s.troll_body, s.troll_head_talk_4, s.troll_arm_l_5, s.troll_arm_r_3, s.troll_fish, {14, 13}),
		}},
		{ name = "fish_cutscene", loop=false, frames = { 
			f3(s.troll_head_idle, s.troll_arm_l_6, s.troll_arm_r_4, { id=s.troll_fish, pos={14, 13}}, false),
			f3(s.troll_head_front, s.troll_arm_l_6, s.troll_arm_r_4, { id=s.troll_fish, pos={14, 13}}, false),
			f3(s.troll_head_idle, s.troll_arm_l_6, s.troll_arm_r_4, { id=s.troll_fish, pos={14, 13}}, true),
			f3(s.troll_head_side, s.troll_arm_l_6, s.troll_arm_r_4, { id=s.troll_fish, pos={14, 13}}, true),
			f3(s.troll_head_front, s.troll_arm_l_6, s.troll_arm_r_4, { id=s.troll_fish, pos={14, 13}}, false),
			f3(s.troll_head_idle, s.troll_arm_l_6, s.troll_arm_r_4, { id=s.troll_fish, pos={14, 13}}, false),
			f3(s.troll_head_side, s.troll_arm_l_6, s.troll_arm_r_4, { id=s.troll_fish, pos={14, 13}}, false),
			f3(s.troll_head_front, s.troll_arm_l_6, s.troll_arm_r_4, { id=s.troll_fish, pos={14, 13}}, false),
			f3(s.troll_head_idle, s.troll_arm_l_6, s.troll_arm_r_4, { id=s.troll_fish, pos={14, 13}}, true),
			f3(s.troll_head_side, s.troll_arm_l_6, s.troll_arm_r_4, { id=s.troll_fish, pos={14, 13}}, true),
			f3(s.troll_head_front, s.troll_arm_l_6, s.troll_arm_r_4, { id=s.troll_fish, pos={14, 13}}, false),
			f4(s.troll_head_front, s.troll_arm_l_7, s.troll_arm_r_5, nil),
			f4(s.troll_head_front, s.troll_arm_l_7, s.troll_arm_r_6, {id = s.troll_club_1, pos = {-29, 0}}, nil),
			f4(s.troll_head_front, s.troll_arm_l_7, s.troll_arm_r_7, {id = s.troll_club_2, pos = {-38, 1}}, nil),
			f4(s.troll_head_front, s.troll_arm_l_7, s.troll_arm_r_8, {id = s.troll_club_3, pos = {-45, 1}}, nil),
			f4(s.troll_head_front, s.troll_arm_l_7, s.troll_arm_r_9, {id = s.troll_club_4, pos = {-50, 1}}, nil),
			f4(s.troll_head_front_1, s.troll_arm_l_7, nil, nil, nil),
			f4(s.troll_head_front_2, s.troll_arm_l_7, nil, nil, nil),
			f4(s.troll_head_front_3, s.troll_arm_l_7, nil, nil, nil),
			f4(s.troll_head_front_4, s.troll_arm_l_7, s.troll_arm_r_9, nil, nil),
			f4(s.troll_head_front_5, s.troll_arm_l_7, s.troll_arm_r_10, nil, nil),
			f4(s.troll_head_front_6, s.troll_arm_l_7, s.troll_arm_r_10, nil, nil),	
			f4(s.troll_head_front_7, s.troll_arm_l_8, s.troll_arm_r_10, nil, nil),	
			f4(s.troll_head_front_7, s.troll_arm_l_9, s.troll_arm_r_10, nil, nil),	
			f4(s.troll_head_front_9, s.troll_arm_l_10, s.troll_arm_r_10, nil, nil),	
			f4(s.troll_head_front_8, s.troll_arm_l_11, s.troll_arm_r_10, nil, nil),	
			f4(s.troll_head_front_9, s.troll_arm_l_12, s.troll_arm_r_10, nil, nil),	
			f4(s.troll_head_front_8, s.troll_arm_l_13, s.troll_arm_r_10, nil, nil),	
			f4(s.troll_head_front_9, s.troll_arm_l_14, s.troll_arm_r_10, nil, nil),	
			f4(s.troll_head_front_8, s.troll_arm_l_15, s.troll_arm_r_10, nil, nil),	
			f4(s.troll_head_front_9, s.troll_arm_l_16, s.troll_arm_r_10, nil, {id = s.troll_fish_1, pos = {-6,37}}),	
			f4(s.troll_head_front_8, s.troll_arm_l_17, s.troll_arm_r_10, nil, {id = s.troll_fish_2, pos = {-11,51}}),	
			f4(s.troll_head_front_9, s.troll_arm_l_17, s.troll_arm_r_10, nil, {id = s.troll_fish_3, pos = {-9,57}}),	
			f4(s.troll_head_front_10, s.troll_arm_l_17, s.troll_arm_r_10, nil, {id = s.troll_fish_4, pos = {-2,49}}),	
			f4(s.troll_head_front_11, s.troll_arm_l_17, s.troll_arm_r_10, nil, nil),	
			f4(s.troll_head_front_12, s.troll_arm_l_17, s.troll_arm_r_10, nil, nil),	
			f4(s.troll_head_front_13, s.troll_arm_l_17, s.troll_arm_r_10, nil, nil),	
			f4(s.troll_head_front_9, s.troll_arm_l_17, s.troll_arm_r_10, nil, nil),	
			f4(s.troll_head_front_8, s.troll_arm_l_17, s.troll_arm_r_10, nil, nil),	
			f4(s.troll_head_front_9, s.troll_arm_l_17, s.troll_arm_r_10, nil, nil),	
			f4(s.troll_head_front_8, s.troll_arm_l_17, s.troll_arm_r_10, nil, nil),	
			f4(s.troll_head_front_9, s.troll_arm_l_17, s.troll_arm_r_10, nil, nil),	
			f4(s.troll_head_front_8, s.troll_arm_l_17, s.troll_arm_r_10, nil, nil),	
			f4(s.troll_head_front_6, s.troll_arm_l_17, s.troll_arm_r_11, nil, nil),	
			f4(s.troll_head_front_2, s.troll_arm_l_17, s.troll_arm_r_12, nil, nil),	
			f4(s.troll_head_front_14, s.troll_arm_l_17, s.troll_arm_r_13, nil, nil),	
			f4(s.troll_head_front, s.troll_arm_l_17, s.troll_arm_r_10, nil, nil),	
			f3(s.troll_head_front, s.troll_arm_l_5, s.troll_arm_r_0, nil, false),
			f1(s.troll_body, s.troll_head_idle, s.troll_arm_l_5, s.troll_arm_r_0),
			f1(s.troll_body, s.troll_head_front, s.troll_arm_l_5, s.troll_arm_r_0),
			f1a(s.troll_arm_r_0, s.troll_club_4, {-50, 1}),
			f1a(s.troll_arm_r_14, s.troll_club_3, {-45,1}),
			f1a(s.troll_arm_r_14, s.troll_club_2, {-38,1}),
			f1a(s.troll_arm_r_14, s.troll_club_1, {-29,0}),
			f1a(s.troll_arm_r_5, nil, nil),
			f1(s.troll_body, s.troll_head_front, s.troll_arm_l_5, s.troll_arm_r_2),
			f1(s.troll_body, s.troll_head_idle, s.troll_arm_l_1, s.troll_arm_r_1),
			f1(s.troll_body, s.troll_head_idle, s.troll_arm_l_0, s.troll_arm_r_0)
		}},

		
	}

}


engine.assets.models["fettuccini.purple"] = {
    sheet = sheet,
    type = "sprite",
    ppu=1,
	animations = {
		{ name = "idle_s", frames = { { duration = dt, quads = {{ id = s.fettuccini_purple_idle_front }}}}},
		{ name = "idle_e", frames = { { duration = dt, quads = {{ id = s.fettuccini_purple_idle_side_body}, {id = s.fettuccini_purple_idle_side_head, pos={0, 33}}}}}},
		{ name = "idle_n", frames = { { duration = dt, quads = {{ id = s.fettuccini_purple_idle_back}}}}},
		{ name = "talk_e", frames = { 
			{ duration = dt, quads = {{ id = s.fettuccini_purple_idle_side_body}, {id = s.fettuccini_purple_idle_side_head, pos={0, 33}}}},
			{ duration = dt, quads = {{ id = s.fettuccini_purple_idle_side_body}, {id = s.fettuccini_purple_talk_side_head_1, pos={0, 33}}}},
			{ duration = dt, quads = {{ id = s.fettuccini_purple_idle_side_body}, {id = s.fettuccini_purple_talk_side_head_2, pos={0, 33}}}},
			{ duration = dt, quads = {{ id = s.fettuccini_purple_idle_side_body}, {id = s.fettuccini_purple_talk_side_head_3, pos={0, 33}}}},
		}},
		{ name = "talk_n", frames = { { duration = dt, quads = {{ id = s.fettuccini_purple_idle_back}}}}},
		{ name = "walk_e", frames = { 
			{ duration = dt, quads = {{ id = s.fettuccini_purple_walk_side_1}}},
			{ duration = dt, quads = {{ id = s.fettuccini_purple_walk_side_2}}},
			{ duration = dt, quads = {{ id = s.fettuccini_purple_walk_side_3}}},
			{ duration = dt, quads = {{ id = s.fettuccini_purple_walk_side_4}}},
			{ duration = dt, quads = {{ id = s.fettuccini_purple_walk_side_5}}},
			{ duration = dt, quads = {{ id = s.fettuccini_purple_walk_side_6}}},
		}},
		{ name = "walk_n", frames = { { duration = dt, quads = {{ id = s.fettuccini_purple_idle_back}}}}},

	}
}

engine.assets.models["fettuccini.green"] = {
    sheet = sheet,
    type = "sprite",
    ppu=1,
	animations = {
		{ name = "idle_s", frames = { { duration = dt, quads = {{ id = s.fettuccini_green_idle_front }}}}},
		{ name = "idle_e", frames = { { duration = dt, quads = {{ id = s.fettuccini_green_idle_side_body}, {id = s.fettuccini_green_idle_side_head, pos={0, 33}}}}}},
		{ name = "idle_n", frames = { { duration = dt, quads = {{ id = s.fettuccini_green_idle_back}}}}},
		{ name = "talk_e", frames = { 
			{ duration = dt, quads = {{ id = s.fettuccini_green_idle_side_body}, {id = s.fettuccini_green_idle_side_head, pos={0, 33}}}},
			{ duration = dt, quads = {{ id = s.fettuccini_green_idle_side_body}, {id = s.fettuccini_green_talk_side_head_1, pos={0, 33}}}},
			{ duration = dt, quads = {{ id = s.fettuccini_green_idle_side_body}, {id = s.fettuccini_green_talk_side_head_2, pos={0, 33}}}},
			{ duration = dt, quads = {{ id = s.fettuccini_green_idle_side_body}, {id = s.fettuccini_green_talk_side_head_3, pos={0, 33}}}},
		}},
		{ name = "walk_e", frames = { 
			{ duration = dt, quads = {{ id = s.fettuccini_green_walk_side_1}}},
			{ duration = dt, quads = {{ id = s.fettuccini_green_walk_side_2}}},
			{ duration = dt, quads = {{ id = s.fettuccini_green_walk_side_3}}},
			{ duration = dt, quads = {{ id = s.fettuccini_green_walk_side_4}}},
			{ duration = dt, quads = {{ id = s.fettuccini_green_walk_side_5}}},
			{ duration = dt, quads = {{ id = s.fettuccini_green_walk_side_6}}},
		}},
		{ name = "walk_n", frames = { { duration = dt, quads = {{ id = s.fettuccini_green_idle_back}}}}},
	}
}

engine.assets.models["circus.explosion"] = {
    sheet = sheet,
    type = "sprite",
    ppu=1,
	animations = {
		{ name = "default", frames = { 
			{ duration = dt, quads = {{ id = s.circus_explosion_1, pos = {244, 43}}}},
			{ duration = dt, quads = {{ id = s.circus_explosion_2, pos = {244, 40}}}},
			{ duration = dt, quads = {{ id = s.circus_explosion_3, pos = {244, 38}}}},
			{ duration = dt, quads = {{ id = s.circus_explosion_4a, pos = {244, 40}}, { id = s.circus_explosion_4b, pos = {201,72}}}},
			{ duration = dt, quads = {{ id = s.circus_explosion_5a, pos = {244, 36}}, { id = s.circus_explosion_4b, pos = {200,78}}}},
			{ duration = dt, quads = {{ id = s.circus_explosion_6, pos = {244, 35}}}},
			{ duration = dt, quads = {{ id = s.circus_explosion_7, pos = {244, 34}}}},
		}},
	}
}

engine.assets.models["circus.flyingguy"] = {
    sheet = sheet,
    type = "sprite",
    ppu=1,
	animations = {
		{ name = "default", loop = false, frames = { 
			{ duration = dt, quads = {{ id = s.flying_guybrush_1, pos = {213, 75}}}},
			{ duration = dt, quads = {{ id = s.flying_guybrush_2, pos = {190, 89}}}},
			{ duration = dt, quads = {{ id = s.flying_guybrush_3, pos = {169, 96}}}},
			{ duration = dt, quads = {{ id = s.flying_guybrush_4, pos = {148, 100}}}},
			{ duration = dt, quads = {{ id = s.flying_guybrush_5, pos = {133, 98}}}},
			{ duration = dt, quads = {{ id = s.flying_guybrush_6, pos = {111, 92}}}},
			{ duration = dt, quads = {{ id = s.flying_guybrush_7, pos = {93, 89}}}},
			{ duration = dt, quads = {{ id = s.flying_guybrush_7, pos = {93, 84}}}},
			{ duration = dt, quads = {{ id = s.flying_guybrush_7, pos = {93, 82}}}},
			{ duration = dt, quads = {{ id = s.flying_guybrush_7, pos = {93, 70}}}},
			{ duration = dt, quads = {{ id = s.flying_guybrush_7, pos = {93, 65}}}},
			{ duration = dt, quads = {{ id = s.flying_guybrush_7, pos = {93, 60}}}},
			{ duration = dt, quads = {{ id = s.flying_guybrush_7, pos = {93, 55}}}},
			{ duration = dt, quads = {{ id = s.flying_guybrush_7, pos = {93, 50}}}},
			{ duration = dt, quads = {{ id = s.flying_guybrush_7, pos = {93, 45}}}},
			{ duration = dt, quads = {{ id = s.flying_guybrush_7, pos = {93, 40}}}},
			{ duration = dt, quads = {{ id = s.flying_guybrush_7, pos = {93, 35}}}},
			{ duration = dt, quads = {{ id = s.flying_guybrush_7, pos = {93, 29}}}},
		}},
	}
}

engine.assets.models["shop.door"] = {
    sheet = sheet,
    type = "sprite",
    ppu=1,
	animations = {
		{ name = "open", frames = { { duration = dt, quads = {{ id = s.door_store_open }}}}},
		{ name = "close", frames = { { duration = dt, quads = {{ id = s.door_store_closed }}}}}
	}
}

engine.assets.models["village3.shop_door"] = {
    sheet = sheet,
    type = "sprite",
    ppu=1,
	animations = {
		{ name = "open", frames = { { duration = dt, quads = {{ id = s.door_village_store_open }}}}},
		{ name = "close", frames = { { duration = dt, quads = {{ id = s.door_village_store_closed }}}}}
	}
}

engine.assets.models["village3.church_door"] = {
    sheet = sheet,
    type = "sprite",
    ppu=1,
	animations = {
		{ name = "open", frames = { { duration = dt, quads = {{ id = s.door_village_church_open }}}}},
		{ name = "close", frames = { { duration = dt, quads = {{ id = s.door_village_church_closed }}}}}
	}
}

engine.assets.models["shop.sword"] = { sheet = sheet, type = "sprite", ppu=1, animations = {{ name = "idle", frames = { { duration = dt, quads = {{ id = s.sword }}}}}}}
engine.assets.models["shop.shovel"] = { sheet = sheet, type = "sprite", ppu=1, animations = {{ name = "idle", frames = { { duration = dt, quads = {{ id = s.shovel }}}}}}}
engine.assets.models["shop.sign"] = { sheet = sheet, type = "sprite", ppu=1, animations = {{ name = "idle", frames = { { duration = dt, quads = {{ id = s.sign }}}}}}}
engine.assets.models["shop.bell"] = { sheet = sheet, type = "sprite", ppu=1, animations = {{ name = "idle", frames = { { duration = dt, quads = {{ id = s.bell }}}}}}}



engine.assets.models["shop.shopkeeper"] = {
    sheet = sheet,
    type = "sprite",
    ppu=1,
	animations = {
		{ name = "idle_s", frames = { { duration = dt, quads = {{ id = s.storekeeper_idle_south }}}}},
		{ name = "idle_e", frames = { { duration = dt, quads = {{ id = s.storekeeper_idle_body_side}, {id = s.storekeeper_idle_head_side, pos={9, 30}}}}}},
		--{ name = "idle_n", frames = { { duration = dt, quads = {{ id = s.fettuccini_purple_idle_back}}}}},
		{ name = "talk_e", frames = { 
			{ duration = dt, quads = {{ id = s.storekeeper_idle_body_side}, {id = s.storekeeper_talk_head_side_1, pos={9,30}}}},
			{ duration = dt, quads = {{ id = s.storekeeper_idle_body_side}, {id = s.storekeeper_talk_head_side_2, pos={9,30}}}},
			{ duration = dt, quads = {{ id = s.storekeeper_idle_body_side}, {id = s.storekeeper_talk_head_side_3, pos={9,30}}}},
			{ duration = dt, quads = {{ id = s.storekeeper_idle_body_side}, {id = s.storekeeper_talk_head_side_4, pos={9,30}}}},
			{ duration = dt, quads = {{ id = s.storekeeper_idle_body_side}, {id = s.storekeeper_talk_head_side_5, pos={9,30}}}},
			{ duration = dt, quads = {{ id = s.storekeeper_idle_body_side}, {id = s.storekeeper_idle_head_side, pos={9,30}}}},
		}},
		-- { name = "talk_n", frames = { { duration = dt, quads = {{ id = s.fettuccini_purple_idle_back}}}}},
		{ name = "walk_e", frames = { 
			{ duration = dt, quads = {{ id = s.storekeeper_walk_east_1}}},
			{ duration = dt, quads = {{ id = s.storekeeper_walk_east_2}}},
			{ duration = dt, quads = {{ id = s.storekeeper_walk_east_3}}},
			{ duration = dt, quads = {{ id = s.storekeeper_walk_east_4}}},
			{ duration = dt, quads = {{ id = s.storekeeper_walk_east_5}}},
			{ duration = dt, quads = {{ id = s.storekeeper_walk_east_6}}},
		}},
		{ name = "walk_s", frames = { 
			{ duration = dt, quads = {{ id = s.storekeeper_walk_south_1}}},
			{ duration = dt, quads = {{ id = s.storekeeper_walk_south_2}}},
			{ duration = dt, quads = {{ id = s.storekeeper_walk_south_3}}},
			{ duration = dt, quads = {{ id = s.storekeeper_walk_south_4}}},
			{ duration = dt, quads = {{ id = s.storekeeper_walk_south_5}}},
			{ duration = dt, quads = {{ id = s.storekeeper_walk_south_6}}},
		}},
		{ name = "walk_n", frames = { 
			{ duration = dt, quads = {{ id = s.storekeeper_walk_south_1}}},
			{ duration = dt, quads = {{ id = s.storekeeper_walk_south_2}}},
			{ duration = dt, quads = {{ id = s.storekeeper_walk_south_3}}},
			{ duration = dt, quads = {{ id = s.storekeeper_walk_south_4}}},
			{ duration = dt, quads = {{ id = s.storekeeper_walk_south_5}}},
			{ duration = dt, quads = {{ id = s.storekeeper_walk_south_6}}},
		}},

		-- { name = "walk_n", frames = { { duration = dt, quads = {{ id = s.fettuccini_purple_idle_back}}}}},

	}
}

engine.assets.models["lookout.fire"] = {
    sheet = sheet,
    type = "sprite",
    ppu=1,
	animations = {
		{ name = "default", frames = { 
			{ duration = dt, quads = {{ id = s.lookout_fire_1}}},
			{ duration = dt, quads = {{ id = s.lookout_fire_2}}},
			{ duration = dt, quads = {{ id = s.lookout_fire_3}}},
			{ duration = dt, quads = {{ id = s.lookout_fire_4}}}
		}},
	}
}

engine.assets.models["swordmaster.sign"] = {
    sheet = sheet,
    type = "sprite",
    ppu=1,
	animations = {
		{ name = "default", frames = { 
			{ duration = dt, quads = {{ id = s.swordmaster_sign_1}}},
		}},
		{ name = "activated", frames = { 
			{ duration = dt, quads = {{ id = s.swordmaster_sign_2}}},
		}},
	}
}

engine.assets.models["trunk.bridge"] = {
    sheet = sheet2,
    type = "sprite",
    ppu=1,
	animations = {
		{ name = "closed", frames = { 
			{ duration = dt, quads = {{ id = s.trunk_bridge_closed}}},
		}},
		{ name = "open", frames = { 
			{ duration = dt, quads = {{ id = s.trunk_bridge_open}}},
		}},
	}
}

engine.assets.models["lookout.lookout"] = {
    sheet = sheet,
    type = "sprite",
    ppu=1,
	animations = {
		{ name = "idle_s", frames = { { duration = dt, quads = {{ id = s.lookout_idle_body_front}, { id = s.lookout_idle_head_front, pos ={0,31}}}}}},
		{ name = "idle_e", frames = { { duration = dt, quads = {{ id = s.lookout_idle_body_side}, {id = s.lookout_idle_head_side, pos={2, 31}}}}}},
		---{ name = "idle_n", frames = { { duration = dt, quads = {{ id = s.fettuccini_purple_idle_back}}}}},
		{ name = "talk_e", frames = { 
			{ duration = dt, quads = {{ id = s.lookout_idle_body_side}, {id = s.lookout_idle_head_side, pos={0, 31}}}},
			{ duration = dt, quads = {{ id = s.lookout_idle_body_side}, {id = s.lookout_talk_head_side_1, pos={0, 31}}}},
			{ duration = dt, quads = {{ id = s.lookout_idle_body_side}, {id = s.lookout_talk_head_side_2, pos={0, 31}}}},
			{ duration = dt, quads = {{ id = s.lookout_idle_body_side}, {id = s.lookout_talk_head_side_1, pos={0, 31}}}},
		}},
		{ name = "talk_s", frames = { 
			{ duration = dt, quads = {{ id = s.lookout_idle_body_front}, {id = s.lookout_idle_head_front, pos={0, 31}}}},
			{ duration = dt, quads = {{ id = s.lookout_idle_body_front}, {id = s.lookout_talk_head_front_1, pos={0, 31}}}},
			{ duration = dt, quads = {{ id = s.lookout_idle_body_front}, {id = s.lookout_talk_head_front_2, pos={0, 31}}}},
			{ duration = dt, quads = {{ id = s.lookout_idle_body_front}, {id = s.lookout_talk_head_front_1, pos={0, 31}}}},
		}},
		--{ name = "talk_n", frames = { { duration = dt, quads = {{ id = s.fettuccini_purple_idle_back}}}}},
		-- { name = "walk_e", frames = { 
		-- 	{ duration = dt, quads = {{ id = s.fettuccini_purple_walk_side_1}}},
		-- 	{ duration = dt, quads = {{ id = s.fettuccini_purple_walk_side_2}}},
		-- 	{ duration = dt, quads = {{ id = s.fettuccini_purple_walk_side_3}}},
		-- 	{ duration = dt, quads = {{ id = s.fettuccini_purple_walk_side_4}}},
		-- 	{ duration = dt, quads = {{ id = s.fettuccini_purple_walk_side_5}}},
		-- 	{ duration = dt, quads = {{ id = s.fettuccini_purple_walk_side_6}}},
		-- }},
		{ name = "walk_n", frames = { { duration = dt, quads = {{ id = s.fettuccini_purple_idle_back}}}}},

	}
}

engine.assets.models["otis"] = {
    sheet = sheet2,
    type = "sprite",
    ppu=1,
	animations = {
		{ name = "idle_e", frames = { { duration = dt, quads = { 
			{ id = s.otis_idle_body_e }, 
			{ id = s.otis_idle_head_e, pos = {1,34,0} }}}}},
		{ name = "idle_n", frames = { { duration = dt, quads = { { id = s.otis_idle_body_e }, { id = s.otis_idle_head_e }}}}},
		{ name = "idle_s", frames = { { duration = dt, quads = {{ id = s.otis_idle_body_s }, { id=s.otis_idle_head_s }}}}},
		{ name = "walk_e", frames = { 
			{ duration = dt, quads = {{ id = s.otis_walk_e_1 }}},
			{ duration = dt, quads = {{ id = s.otis_walk_e_2 }}},
			{ duration = dt, quads = {{ id = s.otis_walk_e_3 }}},
			{ duration = dt, quads = {{ id = s.otis_walk_e_4 }}},
			{ duration = dt, quads = {{ id = s.otis_walk_e_5 }}},
			{ duration = dt, quads = {{ id = s.otis_walk_e_6 }}}
		}},
		{ name = "walk_n", frames = { 
			{ duration = dt, quads = {{ id = s.otis_walk_n_1 }}},
			{ duration = dt, quads = {{ id = s.otis_walk_n_2 }}},
			{ duration = dt, quads = {{ id = s.otis_walk_n_3 }}},
			{ duration = dt, quads = {{ id = s.otis_walk_n_4 }}},
			{ duration = dt, quads = {{ id = s.otis_walk_n_5 }}},
			{ duration = dt, quads = {{ id = s.otis_walk_n_6 }}}
		}},
		{ name = "walk_s", frames = { 
			{ duration = dt, quads = {{ id = s.otis_walk_s_1 }}},
			{ duration = dt, quads = {{ id = s.otis_walk_s_2 }}},
			{ duration = dt, quads = {{ id = s.otis_walk_s_3 }}},
			{ duration = dt, quads = {{ id = s.otis_walk_s_4 }}},
			{ duration = dt, quads = {{ id = s.otis_walk_s_5 }}},
			{ duration = dt, quads = {{ id = s.otis_walk_s_6 }}}
		}},


	}
}

engine.assets.models["swordmaster.smtiny"] = {
    sheet = sheet,
    type = "sprite",
    ppu=1,
	animations = {
		{ name = "idle", frames = { 
			{ duration = dt, quads = {{ id = s.swordmaster_tiny_1 }}},
			{ duration = dt, quads = {{ id = s.swordmaster_tiny_2 }}},
			{ duration = dt, quads = {{ id = s.swordmaster_tiny_3 }}},
		}},
	}
}
