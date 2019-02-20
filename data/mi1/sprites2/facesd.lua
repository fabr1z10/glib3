local dt = 0.1

require("sprites2/facess")

local s = spritesheets["faces"]

models["mancomb.mancomb"] = {
    sheet = "sprites2/faces.png",
    type = "sprite",
    ppu=1,
	animations = {
		{ name = "idle", frames = { { duration = dt, quads = {{ id = s.mancomb_default }}}}},
		{ name = "smile", frames = { { duration = dt, quads = {{ id = s.mancomb_smile }}}}}
	}
}
