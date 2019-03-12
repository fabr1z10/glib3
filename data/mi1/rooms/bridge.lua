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
	--factory.scumm.object { id="bridge.path"},
	scumm.factory.object { id="bridge.troll"}
})

local gotoTroll = function()
	local d = strings.dialogues.troll
	local actions = {	
		{ ref = 1, type = action.suspend_script, args = {script="_troll"}},
		{ type = action.kill_script, after={1}, args = {script="_walk"}},
		{ ref = 2, type = action.walkto, after={1},args = {actor="guybrush", obj="bridge.troll"}},
		{ type = action.say, after={1}, args = { actor="bridge.troll", lines = {d[2], d[3]}, animstart="talk", animend="idle"}},
		{ type = action.start_dialogue, args = {dialogue="troll"}},
		{ type = action.turn, after={2}, args={actor="guybrush", dir="east"}}
	}
	local s = ms2(actions)
	monkey.play(s)

end

-- if (variables.troll_in) then
--  	room:add( { factory.scumm.trap { pos ={95, 0, 0}, tag="troll_sensor", width=10, height = 144, onenter = gotoTroll }})
-- end

local troll = function() 
	local d = strings.dialogues.troll
	local actions = {
		{ ref = 1, type = action.delay, args = {sec = 5}},
		{ type = scumm.action.say, args = {actor="bridge.troll", lines = {d[1]}, animstart="talk", animend="idle"}}
	}
	local s = script.make(actions, 1)
	s.name = "_troll"
	monkey.play(s)
end




function room.afterstartup() 
	
	for k, v in ipairs(room.initstuff) do
		v()
	end
	troll()
	-- local s = script:new("_troll")
	-- s.actions = {
	-- 	action.say { id=1, actor="bridge.troll", lines = {d[1]}, animstart="talk", animend="idle" },
	-- 	action.delay { id=2, sec=5},
	-- }
	-- s.loop = 1
	-- monkey.play(s)

end


