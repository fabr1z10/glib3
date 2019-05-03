engine.config.defaultactions = {}

local d = engine.config.defaultactions
local s = strings.defaultactions

d.open = { type = action.say, args = { actor="guybrush", lines={s[1]}}}
d.look = { { type = scumm.action.say, args = { actor="guybrush", lines={s[4]}}}}
d.use = { { type = action.say, args = { id=1, actor="guybrush", lines={s[2]} }} }
d.give = { { type = action.say, args = { id=1, actor="guybrush", lines={s[2]} }} }
d.pickup = { { type = action.say, args = { id=1, actor="guybrush", lines={s[5]} }}}

mi = {}

mi.checkfunds = function(n) 
	local p8 = variables.inventory["pieces_of_eight"]
	if (p8 == nil) then return false end
	return (p8 >= n)
end

mi.addStorekeeper = function(args) 
	-- pos: where it goes
	-- walkto: where it walks to (might be more than once)
	if (variables.chasing_shopkeeper == true) then
		local actions = {
			{ type = action.create_object, args = { factory = scumm.factory.object, args = { id="village3.shopkeeper", pos = args.pos }}}
		}
		for _, v in ipairs(args.walkto) do
			table.insert(actions, { type = scumm.action.walkto, args ={tag="village3.shopkeeper", pos = v }})
		end
		table.insert (actions, { type = action.activate, args = {tag="village3.shopkeeper", value=false}})
		table.insert (actions, { type = action.delay, args = {sec=10}})
		table.insert (actions, { type = action.set_variable, args = {var="chasing_shopkeeper", value=false}})
		local s = script.make(actions)
		monkey.play(s)
	end


end