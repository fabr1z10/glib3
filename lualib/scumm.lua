require ("glib")
require ("script")
require ("action")
require ("factory")

glib.assert (engine.lang, "missing engine.lang!!!", 1)
glib.assert (engine.config.default_verb, "engine.config.default_verb", 1)
glib.assert (engine.start_room, "engine.start_room", 1)

engine.state.scumm = {
	actionInfo = {
		verb = "",			-- key into engine.c
		obj1 = nil,
		obj2 = nil,
		selectSecond = false
	},
	walk_enabled = true,
	inventory = {},
	play = true
}

engine.state.scumm.has = function(id)
	return (engine.state.scumm.inventory[id] ~= nil)
end

engine.state.scumm.has_at_least = function(id, n)
	return (engine.state.scumm.inventory[id] ~= nil and engine.state.scumm.inventory[id] >= n)
end

engine.state.scumm.remove_from_inventory = function(id, n)
	local a = engine.state.scumm.inventory[id]
	if (a~= nil) then
		if (a > n) then
			engine.state.scumm.inventory[id] = a-n
		else
			engine.state.scumm.inventory[id] = nil
		end
	end
end 

if (engine.items == nil) then engine.items = {} end
if (engine.dialogues == nil) then engine.dialogues = {} end
scumm = {}
require ("scumm/ui")
require ("scumm/action")
if (engine.extension ~= nil and engine.extension.action ~= nil) then
	require (engine.extension.action)
end
require("factories/factory")
require ("scumm/factory")
	

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

