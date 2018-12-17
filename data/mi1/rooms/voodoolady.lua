require("template/room1")

local roomInfo = {
	width = 496,
	height = 144,
	startTable = {
		village2 = { pos = items["voodoolady.door"].walk_to, facing = "east"},
	},
	defaultroom = "village2",
	enableScroll = false,
	collide = true,
	depth = { type="linear_y", values= {0, 1, 144, 0} }	
}

room = generateBasicRoom (roomInfo)
table.insert (room.engines, 
	{ 
		type = "collision", 
		size = {128, 128}, 
		response = {
			{ tag = {1, 2}, onenter=function(e,f) 

					local info = f:getinfo()
					if (info.onenter ~= nil) then
						info.onenter()
					end
			 end}
		}
	}
)

room:add_asset(sprites["voodoolady.door"])
room:add_asset(sprites["voodoolady.body"])
room:add_asset(sprites["voodoolady.voodoolady"])
room:add_asset(sprites["voodoolady.trunk"])

room:add( {
	{ 
		pos = {0, 0, 0},
		tag = "bg1",
		children = {
			{ pos = {0, 0,-3}, components = { { type="gfx", image="gfx/voodoolady1.png" }}},
			factory.object.create { object = "voodoolady.door" },
		}
	},
	factory.object.create{object="voodoolady.trunk"},
	{
		pos = {0, 0, 0},
		tag = "bg2",
		children = {
			{ pos = {258, 0, -2}, components = { {type="gfx", image="gfx/voodoolady2.png" }}},
			factory.object.create { object = "voodoolady.voodoolady_body" },
			factory.object.create { object = "voodoolady.voodoolady" },
		}
	},
	{
		pos = {0,0,0},
		components = {
 	  		{ 
				type ="walkarea",
	 			priority = 0,
      			target = "player",
	        	shape = { 
					type = "poly", 
					outline = {78,37,124,47,146,42,320,42,320,40,320,0,156,0,145,22},
	                holes = {
	                    {164,21,164,7,194,7,194,21}
	                }
				}
 	  		}
		}
	},
	factory.trap.create { pos ={265, 22, 0}, tag="seagull_sensor", width=25, height = 132, onenter = 
	 	function()			
			if (variables.talking_to_voodoolady == false) then
		 		variables.talking_to_voodoolady = true
				local n = 1
				if (variables.talked_to_voodoolady) then n = 7 end
				variables.talked_to_voodoolady = true
				local s = script:new()
		 		s.actions = {	
					action.disable_controls { id=1 },
					action.scroll { id =2, to = {336, 72}, speed=50},
					action.walkto {id=3, actor="guybrush", pos = {125+176, 36}, after={1}},
					action.activate {id = 4, tag="bg2", value=true, after={1}},
					action.activate {id = 5, tag="bg1", value=false, after={3}},
					action.activate {id = 6, name="voodoolady.voodoolady", value=not(variables.voodoolady_told_future), after={1}},
					action.activate {id = 7, name="voodoolady.voodoolady_body", value=not(variables.voodoolady_told_future), after={1}},
					variables.voodoolady_told_future 
					and action.noop {id=8, after={2}}
					or action.say {id = 8, actor="voodoolady.voodoolady", lines = {strings.dialogues.voodoolady[n]}, after={2}, animstart="talk", animend="idle" },
					action.start_dialogue {id=9, dialogue="voodoolady"}
				}
				monkey.play(s)
			end
	 	end
	}
})


function room.afterstartup() 
	monkey.getEntity("bg2"):setactive(false)
	for k, v in ipairs(room.initstuff) do
		v()
	end
end


