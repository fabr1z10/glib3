require ('glib')
require ('script')
require ('action')


scumm = {}
scumm.func = {}
scumm.ifac = {}
scumm.factory = {}
scumm.script = {}
scumm.utils = {}
engine.items = {}
engine.state = {}

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

require ("s2/action")
require ("s2/items")
require ("s2/factories")
require ("s2/script")