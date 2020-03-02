require ('glib')
require ('script')
require ('action')

engine.shaders = { "unlit_textured", "unlit_color", "text" }


scumm = {}
scumm.func = {}
scumm.ifac = {}
scumm.factory = {}
scumm.script = {}
scumm.utils = {}
scumm.func = {}
engine.items = {}
engine.dialogues = {}
--engine.state = {}

scumm.state = {
	actionInfo = {
		verb = "",			-- key into engine.c
		obj1 = nil,
		obj2 = nil,
		selectSecond = false
	},
	walk_enabled = true,
	inventory = {},
	play = true,
	game_paused = false,
	lmboverride = nil
}

require ("scumm/action")
require ("scumm/items")
require ("scumm/factories")
require ("scumm/utils")
require ("scumm/func")
require ("scumm/script")