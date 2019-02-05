local dt = 0.1

require("sprites2/guybrushs")

local s = spritesheets["guybrush"]
local file = "sprites2/guybrush.png"

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

	}
}

