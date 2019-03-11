local dt = 0.1

spritesheets["faces"] = {
	mancomb_default = {x=80, y=0, width=78, height=78},
	mancomb_smile = {x=0, y=0, width=78, height=78},




}



local s = spritesheets["faces"]

models["mancomb.mancomb"] = {
    sheet = "sprites/faces.png",
    type = "sprite",
    ppu=1,
	animations = {
		{ name = "idle", frames = { { duration = dt, quads = {{ id = s.mancomb_default }}}}},
		{ name = "smile", frames = { { duration = dt, quads = {{ id = s.mancomb_smile }}}}}
	}
}
