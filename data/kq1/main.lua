package.path = '/home/fabrizio/glib3/lualib/?.lua;' .. package.path

engine = {
    shaders = { "unlit_textured", "unlit_color", "text" },
    device_size = { 320, 200 },
    window_size = { 640, 400 },
    title = "King's quest I",
    collision = true,
    collision_size={40, 40},
    assets = {
        fonts = {
            ui = {file  = "./fonts/sierra1.ttf" },
        },
        models = {},
        animations = {}
    },
    lang="eng",
    start_room ="001",
    config = {
        default_verb = "walk",
        current_verb = "walk"
    }
}

require("scumm")

engine.config.verbs = {
    walk = { code="walk", next="look", anim="walk" },
    look = { code="look", next="use", anim="look" },
    use = { code="use", next="talk", anim="use" },
    talk = { code="talk", anim="talk", next=function() 
        if (engine.config.verbs.item.code == "") then 
            return "walk" 
        else 
            return "item" 
        end 
    end
    },
    item = { code = "", next="walk"}
}
-- require("script")
-- require("sprites")
 require("funcs")
-- require("strings")

-- variables = {
--     _room = "001",
--     _previousroom = "start",
-- 	status = 0,
-- 	pause = false,
-- 	callbackAfterPause = nil
-- }

