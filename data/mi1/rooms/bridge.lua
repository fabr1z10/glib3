require("template/room1")

local roomInfo = {
	width = 320,
	height = 144,
	startTable = {
		meleemap = { pos = items["bridge.path"].walk_to, facing = "east"}
	},
	defaultroom = "meleemap",
	depth = { type="linear_y", values= {0, 1, 144, 0} }
}

room = generateBasicRoom (roomInfo)

room:add_asset(sprites["bridge.troll"])

room:add({
	{ pos = {0, 0, -3}, components = { { type="gfx", image="gfx/bridge.png" }}},
	{
		pos = {0,0,0},
		components = {
      		{ 
				type ="walkarea",
				priority = 0,
       			target = "player",
				shape = { type = "poly", outline = {0,14,80,21, 201, 55, 229, 55,136, 0,0,0}},
			}
      	}
	},
 	factory.object.create { object = "bridge.troll"},

})


function room.afterstartup() 
	for k, v in ipairs(room.initstuff) do
		v()
	end
	local d = strings.dialogues.troll
	local s = script:new("_troll")
	s.actions = {
		action.say { id=1, actor="bridge.troll", lines = {d[1]}, animstart="idle", animend="idle" },
		action.delay { id=2, sec=5},
	}
	s.loop = 1
	monkey.play(s)
end


