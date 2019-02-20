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

models["low_moral_fiber_2"] = {
    sheet = "sprites2/sprites1.png",
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

models["door_village_voodoolady"] = {
    sheet = "sprites2/sprites1.png",
    type = "sprite",
    ppu=1,
	animations = {
		{ name = "open", frames = { { duration = dt, quads = {{ id = s.door_village_voodoolady_open }}}}},
		{ name = "close", frames = { { duration = dt, quads = {{ id = s.door_village_voodoolady_close }}}}}
	}
}

models["fakedoor_village_1"] = {
    sheet = "sprites2/sprites1.png",
    type = "sprite",
    ppu=1,
	animations = {
		{ name = "open", frames = { { duration = dt, quads = {{ id = s.fakedoor1_village_door_open }}}}},
		{ name = "close", frames = { { duration = dt, quads = {{ id = s.fakedoor1_village_door_close }}}}}
	}
}

models["fakedoor_village_2"] = {
    sheet = "sprites2/sprites1.png",
    type = "sprite",
    ppu=1,
	animations = {
		{ name = "open", frames = { { duration = dt, quads = {{ id = s.fakedoor2_village_door_open }}}}},
		{ name = "close", frames = { { duration = dt, quads = {{ id = s.fakedoor2_village_door_close }}}}}
	}
}

models["lmf3.body"] = {
    sheet = "sprites2/sprites1.png",
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
    sheet = "sprites2/sprites1.png",
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
    sheet = "sprites2/sprites1.png",
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
    sheet = "sprites2/sprites1.png",
    type = "sprite",
    ppu=1,
	animations = {
		{ name = "open", frames = { { duration = dt, quads = {{ id = s.door_scummbar_village_open }}}}},
		{ name = "close", frames = { { duration = dt, quads = {{ id = s.door_scummbar_village_close }}}}}
	}
}

models["door_scummbar_kitchen"] = {
    sheet = "sprites2/sprites1.png",
    type = "sprite",
    ppu=1,
	animations = {
		{ name = "open", frames = { { duration = dt, quads = {{ id = s.door_scummbar_kitchen_open }}}}},
		{ name = "close", frames = { { duration = dt, quads = {{ id = s.door_scummbar_kitchen_close }}}}}
	}
}

models["scummbar.mancomb"] = {
    sheet = "sprites2/sprites1.png",
    type = "sprite",
    ppu=1,
	animations = {
		{ name = "idle_1", frames = { { duration = dt, quads = {{ id = s.mancomb_1 }}}}},
		{ name = "idle_2", frames = { { duration = dt, quads = {{ id = s.mancomb_2 }}}}}
	}
}