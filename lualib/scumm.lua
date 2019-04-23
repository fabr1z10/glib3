require ("glib")
require ("script")
require ("action")
require ("factory")

glib.assert (config.default_verb, "config.default_verb", 1)

-- Initialize key scumm variables
variables._room = config.start_room
variables._previousRoom = ""
variables._actionInfo = {
	verb = nil,
    obj1 = nil,
    obj2 = nil,
    selectSecond = false
}

scumm = {}
require ("scumm/ui")
require ("scumm/action")
require ("scumm/factory")