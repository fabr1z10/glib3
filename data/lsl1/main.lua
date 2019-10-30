package.path = '/home/fabrizio/glib3/lualib/?.lua;' .. package.path

engine = {
    shaders = { "unlit_textured", "unlit_color", "text" },
    device_size = { 320, 200 },
    window_size = { 640, 400 },
    title = "Leisure Suit Larry",
    collision = true,
    collision_size={40, 40},
    assets = {
        fonts = {
            ui = {file  = "./fonts/sierra-sci-font-000.ttf" },
        },
        models = {},
        animations = {}
    },
    lang="eng",
    start_room ="lefty",
    config = {
		style = "sci",
        walk = "walksci",           -- depends on scumm/sci
        turn = "turnsci",           -- depends on scumm/sci
        default_verb = "walk",
        play = true,
        --current_verb = "walk",
        pause = false,
        msgid =-1
    },
    extension = {
        action = "lsl"
    }
}
--require("funcs")
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
    item = { code = "", anim = "", next="walk"}
}
engine.config.verb = "walk"

-- engine.state.scumm.items = {
--     dagger = { text = strings.items[1], code="look", anim ="dagger"}

-- }

variables = {
    talked_to_king = 0,
    rock_moved = 0,
    dagger_taken = 0,

}