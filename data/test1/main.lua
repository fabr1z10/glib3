engine = {
    device_size = { 800, 600 },
    window_size = { 800, 600 },
    title = "The secret of Monkey Island",
	shaders = { "unlit_textured", "unlit_color", "text" }
}

-- fonts = {
--     ui = {file  = "./fonts/monkeysmall.ttf" },
--     monkey = {file  = "./fonts/MonkeyIsland-1990.ttf"}
-- }

-- global_assets = {
-- 	fonts = { "ui", "monkey" }
-- }

require ("script")
require ("funcs2")
-- -- this stuff will change at gametime
variables = {
    _room = "test1",

}
