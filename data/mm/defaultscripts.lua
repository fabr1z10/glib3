engine.config.defaultactions = {}

local d = engine.config.defaultactions
local s = strings.defaultactions

d.open = { type = action.say, args = { actor="guybrush", lines={s[1]}}}
d.look = { { type = scumm.action.say, args = { actor="guybrush", lines={s[1]}}}}
d.use = { { type = action.say, args = { id=1, actor="guybrush", lines={s[1]} }} }
d.give = { { type = action.say, args = { id=1, actor="guybrush", lines={s[1]} }} }
d.pickup = { { type = action.say, args = { id=1, actor="guybrush", lines={s[1]} }}}

