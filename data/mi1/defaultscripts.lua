defaultactions = {}

local d = strings.defaultactions

defaultactions.open = { type = action.say, args = { actor="guybrush", lines={d[1]}}}
defaultactions.look = { { type = action.say, args = { actor="guybrush", lines={d[4]}}}}
defaultactions.use = { { type = action.say, args = { id=1, actor="guybrush", lines={d[2]} }} }
defaultactions.give = { { type = action.say, args = { id=1, actor="guybrush", lines={d[2]} }} }
defaultactions.pickup = { { type = action.say, args = { id=1, actor="guybrush", lines={d[5]} }}}
