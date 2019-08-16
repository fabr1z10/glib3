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
    start_room ="002",
    config = {
        walk = "walksci",
        default_verb = "walk",
        play = true,
        --current_verb = "walk",
        pause = false,
        msgid =-1
    },
    extension = {
        action = "actio2n"
    }
}
 require("funcs")
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

 --quire("actio2n")
-- require("strings")

-- variables = {
--     _room = "001",
--     _previousroom = "start",
-- 	status = 0,
-- 	pause = false,
-- 	callbackAfterPause = nil
-- }

