local models = engine.assets.models

local s = {
	-- larry
	larry_idle_front_1 = {x=96,y=44,width=19,height=47, anchor={11,0}},
	larry_idle_front_2 = {x=117,y=45,width=19,height=47, anchor={11,0}},
	larry_idle_front_3 = {x=137,y=44,width=20,height=47, anchor={12,0}},

	larry_idle_side_1 = {x=261,y=93,width=18,height=47, anchor={11,0}},
	larry_idle_side_2 = {x=280,y=94,width=19,height=46, anchor={12,0}},
	larry_idle_side_3 = {x=300,y=93,width=17,height=47, anchor={12,0}},

	larry_idle_back_1 = {x=241,y=94,width=19,height=46,anchor={10,0}},

	larry_walk_front_1 = {x=96, y=142, width=26, height=46, anchor={12,0}},
	larry_walk_front_2 = {x=123, y=143, width=25, height=45	, anchor={10,0}},
	larry_walk_front_3 = {x=149, y=144, width=22, height=44, anchor={11,0}},
	larry_walk_front_4 = {x=172, y=142, width=26, height=46, anchor={15,0}},
	larry_walk_front_5 = {x=199, y=143, width=25, height=45, anchor={15,0}},
	larry_walk_front_6 = {x=225, y=144, width=22, height=44, anchor={12,0}},

	larry_walk_side_1 = {x=159,y=47,width=23,height=44,anchor={13, 0}},
	larry_walk_side_2 = {x=183,y=46,width=21,height=45,anchor={11, 0}},
	larry_walk_side_3 = {x=205,y=46,width=17,height=45,anchor={11, 0}},
	larry_walk_side_4 = {x=223,y=46,width=19,height=45,anchor={11, 0}},
	larry_walk_side_5 = {x=243,y=47,width=21,height=44,anchor={14, 0}},
	larry_walk_side_6 = {x=265,y=46,width=17,height=45,anchor={11, 0}},
	larry_walk_side_7 = {x=283,y=46,width=17,height=45,anchor={11, 0}},
	larry_walk_side_8 = {x=301,y=46,width=19,height=45,anchor={11, 0}},

	larry_walk_back_1 = {x=96, y=92, width=25, height=48, anchor={14,0}},
	larry_walk_back_2 = {x=122, y=94, width=23, height=46, anchor={13,0}},
	larry_walk_back_3 = {x=146, y=96, width=21, height=44, anchor={11,0}},
	larry_walk_back_4 = {x=168, y=92, width=24, height=48, anchor={12,0}},
	larry_walk_back_5 = {x=193, y=96, width=25, height=44, anchor={12,0}},
	larry_walk_back_6 = {x=219, y=94, width=21, height=46, anchor={11,0}},

	-- cursor
	cursor_use = { x=196, y=16, width=16, height=14, anchor = {8,8}},
	cursor_talk = { x=181, y=1, width=16, height=14, anchor = {8,9}},
	cursor_walk = { x=181, y=16, width=14, height=16, anchor = {7,9}},
	cursor_look = { x=198, y=1, width=16, height=14, anchor ={8,8}},
	cursor_zipper = {x=215, y=1, width=13, height=12, anchor={7,7}},

	leftys_sign_1_1 = {x=1,y=1,width=44,height=42},
	leftys_sign_1_2 = {x=46,y=1,width=44,height=42},
	leftys_sign_1_3 = {x=91,y=1,width=44,height=42},
	leftys_sign_1_4 = {x=136,y=1,width=44,height=42},

	leftys_sign_2_1 = {x=1,y=44,width=18,height=70},
	leftys_sign_2_2 = {x=20,y=44,width=18,height=70},
	leftys_sign_2_3 = {x=39,y=44,width=18,height=70},
	leftys_sign_2_4 = {x=58,y=44,width=18,height=70},
	leftys_sign_2_5 = {x=77,y=44,width=18,height=70},

	lefty_door_closed = {x=45,y=172,width=43,height=56},
	lefty_door_open_1 = {x=1,y=115,width=43,height=56},
	lefty_door_open_2 = {x=45,y=115,width=43,height=56},
	lefty_door_open_3 = {x=1,y=172,width=43,height=56},


}

local dt=0.1

local wbml = {-8, 0, 8, 24}

models["larry"] = {
	sheet ="sprites.png",
	type = "boxed_sprite",
	ppu=1,
	animations = {
		{ name="idle_e", box=wbml, frames = { 
			{duration=5*dt, quads = {{ id = s.larry_idle_side_1}} },
			{duration=5*dt, quads = {{ id = s.larry_idle_side_2}} },
			{duration=5*dt, quads = {{ id = s.larry_idle_side_1}} },
			{duration=5*dt, quads = {{ id = s.larry_idle_side_3}} },
		}},
		{ name="idle_n", box=wbml, frames = { 
			{duration=dt, quads = {{ id = s.larry_idle_back_1 }} }
		}},
		{ name="idle_s", box=wbml, frames = { 
			{duration=5*dt, quads = {{ id = s.larry_idle_front_1 }} },
			{duration=5*dt, quads = {{ id = s.larry_idle_front_2 }} },
			{duration=5*dt, quads = {{ id = s.larry_idle_front_1 }} },
			{duration=5*dt, quads = {{ id = s.larry_idle_front_3 }} },
		}},			
		{ name="walk_e", box=wbml, frames = { 
			{duration=dt, quads = {{ id = s.larry_walk_side_1}} },
			{duration=dt, quads = {{ id = s.larry_walk_side_2}} },
			{duration=dt, quads = {{ id = s.larry_walk_side_3}} },
			{duration=dt, quads = {{ id = s.larry_walk_side_4}} },
			{duration=dt, quads = {{ id = s.larry_walk_side_5}} },
			{duration=dt, quads = {{ id = s.larry_walk_side_6}} },
			{duration=dt, quads = {{ id = s.larry_walk_side_7}} },
			{duration=dt, quads = {{ id = s.larry_walk_side_8}} },
		}},
		{ name="walk_n", box=wbml, frames = { 
			{duration=dt, quads = {{ id = s.larry_walk_back_1}} },
			{duration=dt, quads = {{ id = s.larry_walk_back_2}} },
			{duration=dt, quads = {{ id = s.larry_walk_back_3}} },
			{duration=dt, quads = {{ id = s.larry_walk_back_4}} },
			{duration=dt, quads = {{ id = s.larry_walk_back_5}} },
			{duration=dt, quads = {{ id = s.larry_walk_back_6}} },
		}},
		{ name="walk_s", box=wbml, frames = { 
			{duration=dt, quads = {{ id = s.larry_walk_front_1}} },
			{duration=dt, quads = {{ id = s.larry_walk_front_2}} },
			{duration=dt, quads = {{ id = s.larry_walk_front_3}} },
			{duration=dt, quads = {{ id = s.larry_walk_front_4}} },
			{duration=dt, quads = {{ id = s.larry_walk_front_5}} },
			{duration=dt, quads = {{ id = s.larry_walk_front_6}} },
		}},
	}
}

models["cursor"] = {
	sheet="sprites.png",
	type="sprite",
	ppu=1,
	animations = {
		{ name="walk", frames = { {duration=dt, quads = {{ id = s.cursor_walk}}}}},
		{ name="look", frames = { {duration=dt, quads = {{ id = s.cursor_look}}}}},
		{ name="use", frames = { {duration=dt, quads = {{ id = s.cursor_use}}}}},
		{ name="talk", frames = { {duration=dt, quads = {{ id = s.cursor_talk}}}}},
		{ name="zipper", frames = { {duration=dt, quads = {{ id = s.cursor_zipper}}}}},
	}
}

models["lefty.sign.1"] = {
	sheet="sprites.png",
	type="sprite",
	ppu=1,
	animations = {
		{ name="default", frames = { 
			{duration=dt, quads = {{ id = s.leftys_sign_1_1}}},
			{duration=dt, quads = {{ id = s.leftys_sign_1_2}}},
			{duration=dt, quads = {{ id = s.leftys_sign_1_3}}},
			{duration=dt, quads = {{ id = s.leftys_sign_1_4}}},
		},
	}}
}


models["lefty.sign.2"] = {
	sheet="sprites.png",
	type="sprite",
	ppu=1,
	animations = {
		{ name="default", frames = { 
			{duration=dt, quads = {{ id = s.leftys_sign_2_1}}},
			{duration=dt, quads = {{ id = s.leftys_sign_2_2}}},
			{duration=2*dt, quads = {{ id = s.leftys_sign_2_3}}},
			{duration=dt, quads = {{ id = s.leftys_sign_2_4}}},
			{duration=dt, quads = {{ id = s.leftys_sign_2_5}}},
		}
	}}
}

models["lefty.door"] = {
	sheet="sprites.png",
	type="sprite",
	ppu=1,
	animations = {
		{ name="closed", frames = { 
			{duration=dt, quads = {{ id = s.lefty_door_closed}}}
		}},
		{ name="open", loop=false, frames = { 
			{duration=dt, quads = {{ id = s.lefty_door_open_1}}},
			{duration=dt, quads = {{ id = s.lefty_door_open_2}}},
			{duration=dt, quads = {{ id = s.lefty_door_open_3}}},
		}},
	}
}