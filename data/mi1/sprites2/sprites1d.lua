local dt = 0.1

require("sprites2/sprites1s")

local s = spritesheets["sprites1"]

models["arrow_up"] = {
    sheet = "sprites2/sprites1.png",
    type = "sprite",
    ppu=1,
	animations = {
		{ name = "unselected", frames = { { duration = dt, quads = {{ id = s.arrow_up }}}}},
		{ name = "selected", frames = { { duration = dt, quads = {{ id = s.arrow_up_focus }}}}}
	}
}

models["arrow_down"] = {
    sheet = "sprites2/sprites1.png",
    type = "sprite",
    ppu=1,
	animations = {
		{ name = "unselected", frames = { { duration = dt, quads = {{ id = s.arrow_down }}}}},
		{ name = "selected", frames = { { duration = dt, quads = {{ id = s.arrow_down_focus }}}}}
	}
}


models["low_moral_fiber_1"] = {
    sheet = "sprites2/sprites1.png",
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



models["cook"] = {
    sheet = "sprites2/sprites1.png",
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
	}
}

models["citizen.body"] = {
    sheet = "sprites2/sprites1.png",
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
    sheet = "sprites2/sprites1.png",
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
    sheet = "sprites2/sprites1.png",
    type = "sprite",
    ppu=1,
	animations = {
		{ name = "open", frames = { { duration = dt, quads = {{ id = s.door_village_scummbar_open }}}}},
		{ name = "close", frames = { { duration = dt, quads = {{ id = s.door_village_scummbar_close }}}}}
	}
}
