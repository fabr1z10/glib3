require ("glib")
require ("script")
require ("action")
require ("factory")

glib.assert (engine.lang, "missing engine.lang!!!", 1)
glib.assert (engine.config.default_verb, "engine.config.default_verb", 1)
glib.assert (engine.start_room, "engine.start_room", 1)

variables = {}
-- Initialize key scumm variables
variables._room = engine.start_room
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
-- load text


io.write ("loading strings ...")
require ("text/" .. engine.lang .."/text")
io.write ("done!\n")

io.write  ("loading sprites ...")
glib.load_folder("sprites")
io.write ("done! loaded " .. tostring(glib.tablelength(engine.assets.models)) .. " models.\n")
--print (tostring(engine.assets.models["low_moral_fiber_1"].animations[1].frames[1].quads[2]["id"].x))

io.write ("loading items ...")
glib.load_folder("items")
print ("done! loaded " .. tostring(glib.tablelength(engine.items)) .. " items.\n")


