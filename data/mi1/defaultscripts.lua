script.defaultactions = {}

local d = strings.defaultactions

script.defaultactions.look = { { type = action.say, args = { actor="guybrush", lines={d[4]}}}}
script.defaultactions.use = { { type = action.say, args = { id=1, actor="guybrush", lines={d[2]} }} }
script.defaultactions.give = { { type = action.say, args = { id=1, actor="guybrush", lines={d[2]} }} }
script.defaultactions.pickup = { { type = action.say, args = { id=1, actor="guybrush", lines={d[5]} }}}
