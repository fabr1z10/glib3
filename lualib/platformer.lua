require ("glib")
require ("script")
require ("action")
require ("factory")

glib.assert (engine.lang, "missing engine.lang!!!", 1)

glib.assert (engine.start_room, "engine.start_room", 1)

engine.state.game = {
}


-- load text


io.write ("loading strings ...")
require ("text/" .. engine.lang .."/text")
io.write ("done!\n")

io.write  ("loading sprites ...")
glib.load_folder("sprites")
io.write ("done! loaded " .. tostring(glib.tablelength(engine.assets.models)) .. " models.\n")
--print (tostring(engine.assets.models["low_moral_fiber_1"].animations[1].frames[1].quads[2]["id"].x))


glib.load_all("items")
glib.load_all("dialogue")

