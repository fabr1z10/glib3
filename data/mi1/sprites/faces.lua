local dt = 0.1

local s = {
	mancomb_default = {x=80, y=0, width=78, height=78},
	mancomb_smile = {x=0, y=0, width=78, height=78},
	estevan_default = {x=268, y=79, width=92, height=94},
	loom_default = {x=319,y=1,width=78,height=70},
	loom_smile = {x=239,y=1,width=78,height=70}

}



engine.assets.models["mancomb.mancomb"] = {
    sheet = "faces.png",
    type = "sprite.model",
    ppu=1,
	animations = {
		{ name = "idle", frames = { { duration = dt, quads = {{ id = s.mancomb_default }}}}},
		{ name = "smile", frames = { { duration = dt, quads = {{ id = s.mancomb_smile }}}}}
	}
}

engine.assets.models["estevan.estevan"] = {
    sheet = "faces.png",
    type = "sprite.model",
    ppu=1,
	animations = {
		{ name = "idle", frames = { { duration = dt, quads = {{ id = s.estevan_default }}}}},

	}
}

engine.assets.models["loompirate.loompirate"] = {
    sheet = "faces.png",
    type = "sprite.model",
    ppu=1,
	animations = {
		{ name = "idle", frames = { { duration = dt, quads = {{ id = s.loom_default }}}}},
		{ name = "smile", frames = { { duration = dt, quads = {{ id = s.loom_smile }}}}}
	}
}