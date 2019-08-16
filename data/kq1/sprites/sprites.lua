local models = engine.assets.models

local s = {
	-- wonderboy in monsterland
	graham_walk_e_1 = {x=106,y=1,width=13,height=32,anchor={4,0}},
	graham_walk_e_2 = {x=119,y=1,width=10,height=32,anchor={4,0}},
	graham_walk_e_3 = {x=130,y=2,width=12,height=31,anchor={6,0}},
	graham_walk_e_4 = {x=143,y=2,width=12,height=31,anchor={6,0}},
	graham_walk_e_5 = {x=156,y=1,width=10,height=32,anchor={4,0}},
	graham_walk_e_6 = {x=167,y=2,width=12,height=31,anchor={6,0}},

	graham_walk_n_1 = {x=106,y=35,width=10,height=32,anchor={5,0}},
	graham_walk_n_2 = {x=118,y=36,width=10,height=31,anchor={5,0}},
	graham_walk_n_3 = {x=130,y=36,width=10,height=31,anchor={5,0}},
	graham_walk_n_4 = {x=142,y=35,width=10,height=32,anchor={5,0}},
	graham_walk_n_5 = {x=154,y=36,width=10,height=31,anchor={5,0}},
	graham_walk_n_6 = {x=166,y=36,width=10,height=31,anchor={5,0}},

	graham_walk_s_1 = {x=106,y=69,width=10,height=31,anchor={5,0}},
	graham_walk_s_2 = {x=118,y=68,width=10,height=32,anchor={5,0}},
	graham_walk_s_3 = {x=130,y=69,width=10,height=31,anchor={5,0}},
	graham_walk_s_4 = {x=142,y=69,width=10,height=31,anchor={5,0}},
	graham_walk_s_5 = {x=154,y=68,width=10,height=32,anchor={5,0}},
	graham_walk_s_6 = {x=166,y=69,width=10,height=31,anchor={5,0}},

	graham_idle_e_1 = {x=106,y=1,width=13,height=32,anchor={4,0}},
	graham_idle_n_1 = {x=106,y=35,width=10,height=32,anchor={5,0}},
	graham_idle_s_1 = {x=106,y=69,width=10,height=31,anchor={5,0}},

	-- cursor
	cursor_use = { x=1, y=53, width=15, height=16, anchor = {9,8}},
	cursor_talk = { x=17, y=53, width=16, height=16, anchor = {8,8}},
	cursor_walk = { x=34, y=53, width=11, height=16, anchor = {6,8}},
	cursor_look = { x=46, y=53, width=12, height=9, anchor ={6,4}},

	graham_drown_1 = {x=181,y=2,width=37,height=10, anchor={15,0}},
	graham_drown_2 = {x=182,y=13,width=38,height=15, anchor={17,0}},
	graham_drown_3 = {x=182,y=29,width=38,height=15, anchor={17,0}},
	graham_drown_4 = {x=182,y=45,width=30,height=12, anchor={15,0}},
	graham_drown_5 = {x=182,y=58, width=32,height=10, anchor={15,0},},
	graham_drown_6 = {x=182,y=69,width=38,height=12, anchor={17,0},},
	graham_drown_7 = {x=182,y=82,width=32,height=12, anchor={15,0}},
	graham_drown_8 = {x=182,y=95,width=34,height=11, anchor={15,0}},
	graham_drown_9 = {x=182,y=107,width=38,height=11, anchor={15, 0}},

	purple_flag_1 = {x=1,y=1,width=24,height=9},
	purple_flag_2 = {x=1,y=11,width=22,height=9},
	purple_flag_3 = {x=1,y=21,width=20,height=9},
	purple_flag_4 = {x=1,y=31,width=22,height=9},
	purple_flag_5 = {x=1,y=41,width=22,height=9},

	yellow_flag_1 = {x=26,y=1,width=24,height=9},
	yellow_flag_2 = {x=26,y=11,width=22,height=9},
	yellow_flag_3 = {x=26,y=21,width=22,height=9},
	yellow_flag_4 = {x=26,y=31,width=22,height=9},
	yellow_flag_5 = {x=26,y=41,width=24,height=9},

	cyan_flag_1 = {x=51,y=1,width=22,height=9},
	cyan_flag_2 = {x=51,y=11,width=22,height=9},
	cyan_flag_3 = {x=51,y=21,width=22,height=9},
	cyan_flag_4 = {x=51,y=31,width=22,height=9},
	cyan_flag_5 = {x=52,y=41,width=24,height=9},

	alligator_1 = {x=75, y=23, width = 26, height=4, anchor={15,0}},
	alligator_2 = {x=75, y=1, width = 26, height=8, anchor={15,0}},
	alligator_3 = {x=75, y=11, width = 24, height=11, anchor={15,0}},

	castle_door_closed = {x=45, y=123,width=42,height=50},
	castle_door_open_1 = {x=89, y=123,width=42,height=50},
	castle_door_open_2 = {x=1,y=123,width=42,height=50}
}

local dt=0.1

local wbml = {-8, 0, 8, 24}

models["castle_door"] = {
	sheet="sprites.png",
	type="sprite",
	ppu=1,
	animations = {
		{
			name="closed",
			frames = {
				{ duration = dt, quads = {{id=s.castle_door_closed}}}
			}
		},
		{
			name="open",
			loop=false,
			frames = {
				{ duration = dt, quads = {{id=s.castle_door_open_1}}},
				{ duration = dt, quads = {{id=s.castle_door_open_2}}},
			}
		},

	}
}

models["purple_flag"] = { 
	sheet ="sprites.png",
	type = "sprite",
	ppu=1,
	animations = {
		{ 
			name="default",
			frames = {
				{ duration = dt, quads = {{id=s.purple_flag_1}}},
				{ duration = dt, quads = {{id=s.purple_flag_2}}},
				{ duration = dt, quads = {{id=s.purple_flag_3}}},
				{ duration = dt, quads = {{id=s.purple_flag_4}}},
				{ duration = dt, quads = {{id=s.purple_flag_5}}},				
			}

		}
	}
}

models["yellow_flag"] = { 
	sheet ="sprites.png",
	type = "sprite",
	ppu=1,
	animations = {
		{ 
			name="default",
			frames = {
				{ duration = dt, quads = {{id=s.yellow_flag_1}}},
				{ duration = dt, quads = {{id=s.yellow_flag_2}}},
				{ duration = dt, quads = {{id=s.yellow_flag_3}}},
				{ duration = dt, quads = {{id=s.yellow_flag_4}}},
				{ duration = dt, quads = {{id=s.yellow_flag_5}}},				
			}

		}
	}
}

models["cyan_flag"] = { 
	sheet ="sprites.png",
	type = "sprite",
	ppu=1,
	animations = {
		{ 
			name="default",
			frames = {
				{ duration = dt, quads = {{id=s.cyan_flag_1}}},
				{ duration = dt, quads = {{id=s.cyan_flag_2}}},
				{ duration = dt, quads = {{id=s.cyan_flag_3}}},
				{ duration = dt, quads = {{id=s.cyan_flag_4}}},
				{ duration = dt, quads = {{id=s.cyan_flag_5}}},				
			}

		}
	}
}

models["alligator"] = { 
	sheet ="sprites.png",
	type = "sprite",
	ppu=1,
	animations = {
		{ 
			name="walk",
			frames = {
				{ duration = 5*dt, quads = {{id=s.alligator_1}}},
				{ duration = dt, quads = {{id=s.alligator_2}}},
				{ duration = dt, quads = {{id=s.alligator_3}}},
				{ duration = dt, quads = {{id=s.alligator_2}}},
			}
		},
		{ 
			name="idle",
			frames = {
				{ duration = 5*dt, quads = {{id=s.alligator_1}}},
				{ duration = dt, quads = {{id=s.alligator_2}}},
				{ duration = dt, quads = {{id=s.alligator_3}}},
				{ duration = dt, quads = {{id=s.alligator_2}}},
			}
		},
	}
}


models["graham"] = {
	sheet ="sprites.png",
	type = "boxed_sprite",
	ppu=1,
	animations = {
		{ name="idle_e", box=wbml, frames = { 
			{duration=dt, quads = {{ id = s.graham_idle_e_1}} }
		}},
		{ name="idle_n", box=wbml, frames = { 
			{duration=dt, quads = {{ id = s.graham_idle_n_1}} }
		}},
		{ name="idle_s", box=wbml, frames = { 
			{duration=dt, quads = {{ id = s.graham_idle_s_1}} }
		}},			
		{ name="walk_e", box=wbml, frames = { 
			{duration=dt, quads = {{ id = s.graham_walk_e_1}} },
			{duration=dt, quads = {{ id = s.graham_walk_e_2}} },
			{duration=dt, quads = {{ id = s.graham_walk_e_3}} },
			{duration=dt, quads = {{ id = s.graham_walk_e_4}} },
			{duration=dt, quads = {{ id = s.graham_walk_e_5}} },
			{duration=dt, quads = {{ id = s.graham_walk_e_6}} },
		}},
		{ name="walk_n", box=wbml, frames = { 
			{duration=dt, quads = {{ id = s.graham_walk_n_1}} },
			{duration=dt, quads = {{ id = s.graham_walk_n_2}} },
			{duration=dt, quads = {{ id = s.graham_walk_n_3}} },
			{duration=dt, quads = {{ id = s.graham_walk_n_4}} },
			{duration=dt, quads = {{ id = s.graham_walk_n_5}} },
			{duration=dt, quads = {{ id = s.graham_walk_n_6}} },
		}},
		{ name="walk_s", box=wbml, frames = { 
			{duration=dt, quads = {{ id = s.graham_walk_s_1}} },
			{duration=dt, quads = {{ id = s.graham_walk_s_2}} },
			{duration=dt, quads = {{ id = s.graham_walk_s_3}} },
			{duration=dt, quads = {{ id = s.graham_walk_s_4}} },
			{duration=dt, quads = {{ id = s.graham_walk_s_5}} },
			{duration=dt, quads = {{ id = s.graham_walk_s_6}} },
		}},
		{ name="drown", box=wbml, frames = {
			{duration=dt, quads = {{ id = s.graham_drown_1}} },
			{duration=dt, quads = {{ id = s.graham_drown_2}} },
			{duration=dt, quads = {{ id = s.graham_drown_3}} },
			{duration=dt, quads = {{ id = s.graham_drown_4}} },
			{duration=dt, quads = {{ id = s.graham_drown_5}} },
			{duration=dt, quads = {{ id = s.graham_drown_6}} },
			{duration=dt, quads = {{ id = s.graham_drown_7}} },
			{duration=dt, quads = {{ id = s.graham_drown_8}} },
			{duration=dt, quads = {{ id = s.graham_drown_9}} },
		}}
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
		{ name="talk", frames = { {duration=dt, quads = {{ id = s.cursor_talk}}}}}
	}

}