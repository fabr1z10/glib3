script.defaultactions = {}

local d = strings.defaultactions

script.defaultactions.look = curry (make_script, { action.say { id=1, actor=items.guybrush, lines = {d[4]} }})


