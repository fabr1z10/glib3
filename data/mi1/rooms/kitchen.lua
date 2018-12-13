require("template/room1")

local roomInfo = {
	width = 320,
	height = 144,
	startTable = {
		scummbar = { pos = items["kitchen.door"].walk_to, facing = "east"},
	},
	defaultroom = "scummbar",
	depth = { type="linear_y", values= {0, 1, 144, 0} },
	collide = true
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

					-- local s = script:new()
					-- s.actions = {
					-- 	action.remove_object {id=1, tag="seagull_sensor"},
					-- 	action.create_object {id=2, name="kitchen.seagull"},
					-- 	action.animate_once {id=3, actor="kitchen.seagull", anim="flying"},
					-- 	action.animate {id=4, actor="kitchen.seagull", anim="eating"},
					-- 	action.set_variable {id=5, var="can_pickup_fish", value=false}
					-- }
					-- monkey.play(s)
			 end}
		}
	}
)

room:add_asset(sprites.kitchen_table)
room:add_asset(sprites.door_kitchen)
room:add_asset(sprites.door_kitchen_pier)
room:add_asset(sprites.potostew)
room:add_asset(sprites.kitchen_pot)
room:add_asset(sprites.kitchen_meat)
room:add_asset(sprites.kitchen_fish)
room:add_asset(sprites.seagull)
room:add_asset(sprites.plank)

room:add( {
	{ pos = {0, 0,-3}, components = { { type="gfx", image="gfx/kitchen.png" }}},
	factory.object.create { object = "kitchen.door" },
	factory.object.create { object = "kitchen.door_pier" },
	factory.object.create { object = "kitchen.table" },
	factory.object.create { object = "kitchen.potostew" },
	factory.object.create { object = "kitchen.pot" },
	factory.object.create { object = "kitchen.meat" },
	factory.object.create { object = "kitchen.fish" },
	factory.object.create { object = "kitchen.plank" },
	factory.walkarea.create {
    	shape = { type = "poly", outline = {40,16,59,21,155,21,180,18,192,18,294,18,307,12,199,9,207,0,160,0,149,11,112,11,100,0,40,0}},
		blockedlines = {
			{ A = {194, 0}, B = {194, 144}, active =true },
			{ A = {206, 0}, B = {206, 144}, active =true },
		},
	},

	factory.hotspot.create { pos = {290,5,0}, width=20, height=10, onclick = function()
		if (variables.door_kitchen_pier == 1) then
			local s = script:new("_walk")
			s.actions = {
				action.walkto{id=1, actor="guybrush", pos={292,8} },
				action.turn {id=2, actor="guybrush", dir="south" },
				{ id=3, type="callfunc", func = function ()
					local s = script:new()
					s.actions = {
						action.animate_once{id=1,actor="guybrush", anim="plank"},
						action.animate{id=2, actor="guybrush", anim="idle_front"},
						action.animate_once{id=3, actor="kitchen.plank", anim="pushed"}
					}
					if (variables.seagull_flying == false) then
						variables.seagull_flying = true
						local s1 = script:new()
						s1.actions = {
							{ id=1, type="noop" },
							action.animate_once {id=2, actor="kitchen.seagull", anim="jump" .. tostring(variables.seagull_jump)},
							action.animate {id=3, actor="kitchen.plank", anim="default", after={1} },
							{ id = 4, type = "callfunc", after={2}, func = function() 
								-- see if fish has been taken
								local s2 = script:new()
								if (variables.inventory["kitchen.fish"] == nil) then
									s2.actions = {
										action.animate {id=1, actor="kitchen.seagull", anim="eating" },
										action.set_variable {id=2, var="seagull_jump", value = (variables.seagull_jump==1) and 2 or 1 },
										action.set_variable {id=3, var="seagull_flying", value = false }
									}
								else 
									s2.actions = {
										action.animate_once {id=1, actor="kitchen.seagull", anim="nofish" },
										action.set_variable {id=2, var="fish_taken", value = true },
										action.remove_object {id =3, name="kitchen.seagull", after={1}}
									}								
								end
								monkey.play(s2)
							end }

						}
						s:push { script = s1, at="end"}
					else
						local s1 = script:new()
						s1.actions = {
							action.animate {id=1, actor="kitchen.plank", anim="default" },
						}
						s:push { script = s1, at="end"}
					end
					monkey.play(s)
				end }

			}
			monkey.play(s)
		end
	end }
})

if (variables.fish_taken == false) then
	room:add( {
		factory.trap.create { pos ={100,10,0}, tag="seagull_sensor", width=10, height = 10, onenter = 
			function()			
				local s = script:new()
				s.actions = {
					action.remove_object {id=1, tag="seagull_sensor"},
					action.create_object {id=2, name="kitchen.seagull"},
					action.animate_once {id=3, actor="kitchen.seagull", anim="flying"},
					action.animate {id=4, actor="kitchen.seagull", anim="eating"},
				 	action.set_variable {id=5, var="can_pickup_fish", value=false}
				}
				monkey.play(s)
			end
		}})
end

function room.afterstartup() 
	for k, v in ipairs(room.initstuff) do
		v()
	end
end


