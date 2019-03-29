config.defaultactions = {}

local d = config.defaultactions

d.open = { type = action.say, args = { actor="guybrush", lines={d[1]}}}
d.look = { { type = action.say, args = { actor="guybrush", lines={d[4]}}}}
d.use = { { type = action.say, args = { id=1, actor="guybrush", lines={d[2]} }} }
d.give = { { type = action.say, args = { id=1, actor="guybrush", lines={d[2]} }} }
d.pickup = { { type = action.say, args = { id=1, actor="guybrush", lines={d[5]} }}}

mi = {}

mi.checkfunds = function(n) 
	local p8 = variables.inventory["pieces_of_eight"]
	if (p8 == nil) then return false end
	return (p8 >= n)
end