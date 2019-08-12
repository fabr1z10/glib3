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
	cursor_look = { x=46, y=53, width=12, height=9, anchor ={6,4}}

}

local dt=0.1

local wbml = {-8, 0, 8, 24}

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