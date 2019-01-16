require("template/room1")

local roomInfo = {
	width = 320,
	height = 144,
	startTable = {
		meleemap = { pos = items["bridge.path"].walk_to, facing = "east"}
	},
	defaultroom = "meleemap",
	depth = { type="linear_y", values= {0, 1, 144, 0} },	
	collide=true
}

room = generateBasicRoom (roomInfo)

room:add_asset(sprites["bridge.troll.body"])
room:add_asset(sprites["bridge.troll.head"])

room:add({
	{ pos = {0, 0, -3}, components = { { type="gfx", image="gfx/bridge.png" }}},
	{ pos = {0, 0, 2}, components = { { type="gfx", image="gfx/bridge2.png" }}},
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
	{
		pos = {134, 20, 0},
		flipx = true,
		children = {
			{
				name = "body",
				pos = {0, 0, 0},
				components = {
					{ type = "gfx", model = "bridge.troll.body", anim="idle", framehandlers = { { type="pos"}  } }
				},
				children = {
					{
						tag="bridge.troll",
						name="head",
						pos = {0,0,0},
						components = {
							{ type="gfx", model="bridge.troll.head", anim="idle" }
						}
					}
				}

			}
		},
		components = {
			{ type="depth", depth = roomInfo.depth, scale = roomInfo.scale }
		}		

	}
 	--factory.object.create { object = "bridge.troll"},
	-- factory.trap.create { pos ={90, 0, 0}, tag="bridge_sensor", width=10, height = 144, onenter = 
	--   	function()			
	-- 		local s = script:new()
	-- 	 	s.actions = {	
	-- 			action.kill_script { id=1, script="_walk" },
	-- 			action.walkto {id=2, actor="guybrush", objid = "bridge.troll"},
	-- 			action.turn { id=3, actor="guybrush", dir = items["bridge.troll"].face}
	-- 		}
	-- 		local s1 = items["bridge.troll"].talk_script()
	-- 		s:push {script=s1}
	-- 		monkey.play(s)
	--   	end
	-- }

})


function room.afterstartup() 
	for k, v in ipairs(room.initstuff) do
		v()
	end
	local d = strings.dialogues.troll
	local s = script:new("_troll")
	s.actions = {
		action.say { id=1, actor="bridge.troll", lines = {d[1]}, animstart="talk", animend="idle" },
		action.delay { id=2, sec=5},
	}
	s.loop = 1
	monkey.play(s)
end


