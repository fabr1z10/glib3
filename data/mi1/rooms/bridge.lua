roomDefinition = {
	width = 320,
	height = 144,
	startTable = {
		meleemap = { pos = items["bridge.path"].hotspot.walk_to, dir = "east"}
	},
	defaultroom = "meleemap",
	depth = { type="linear_y", values= {0, 1, 144, 0} },	
	collide=true
}

room = scumm.factory.basic_room(roomDefinition)


room:add({
	{ pos = {0, 0, -3}, components = { { type="gfx", image="gfx/bridge.png" }}},
	--{ pos = {0, 0, 2}, components = { { type="gfx", image="gfx/bridge2.png" }}},
	scumm.factory.walkarea { shape = { type = "poly", outline = {0,14,80,21, 201, 55, 229, 55,136, 0,0,0}}},
	scumm.factory.object { id="bridge.path"},
	
})

local gotoTroll = function()
	local d = strings.dialogues.troll
	local actions = {	
	 	{ ref = 1, type = action.suspend_script, args = {script="_troll"}},
	 	{ type = action.kill_script, after={1}, args = {script="_walk"}},
	 	{ ref = 2, type = scumm.action.walkto, after={1}, args = {tag="player", obj="bridge.troll"}},
	 	{ type = scumm.action.say, after={1}, args = { actor="bridge.troll", lines = {d[2], d[3]}, animstart="talk", animend="idle"}},
	 	{ type = scumm.action.start_dialogue, args = {dialogue="troll"}},
	 	{ type = scumm.action.turn, after={2}, args={tag="player", dir="east"}}
	}
	local s = script.make(actions)
	monkey.play(s)

end

-- additional items to add if troll has not been fed yets
if (variables.troll_fed == false) then
	room:add( {scumm.factory.object { id="bridge.troll"}})
	room:add( {scumm.factory.trap { pos ={95, 0, 0}, tag="troll_sensor", width=10, height = 144, onenter = gotoTroll }})
end





-- if (variables.troll_in) then

-- end

local troll = function() 
	if (variables.troll_fed == false) then
		
		local d = strings.dialogues.troll
		local actions = {
			{ ref = 1, type = action.delay, args = {sec = 5}},
			{ type = scumm.action.say, args = {actor="bridge.troll", lines = {d[1]}, animstart="talk", animend="idle"}}
		}
		local s = script.make(actions, 1)
		s.name = "_troll"
		monkey.play(s)
	end
end




function room.afterstartup() 
	
	for k, v in ipairs(room.initstuff) do
		v()
	end
	if (variables.troll_fed==false) then troll() end
	-- local s = script:new("_troll")
	-- s.actions = {
	-- 	action.say { id=1, actor="bridge.troll", lines = {d[1]}, animstart="talk", animend="idle" },
	-- 	action.delay { id=2, sec=5},
	-- }
	-- s.loop = 1
	-- monkey.play(s)

end


