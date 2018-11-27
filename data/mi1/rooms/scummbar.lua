require("template/room1")

local roomInfo = {
	width = 640,
	height = 144,
	startTable = {
		village1 = { pos = items.scummbar.door_out.walk_to, facing = "east"},
	},
	defaultroom = "village1",
	--depth = { type="linear_y", values= {0, 1, 144, 0} },
	--scale = { type="linear_y", values= {0, 0.8, 144, 0.2}}
}

room = generateBasicRoom (roomInfo)

room:add_asset(sprites.door_scummbar_village)
room:add_asset(sprites.mancomb)

room:add( {
	{ pos = {0, 0,-3}, components = { { type="gfx", image="gfx/scummbar_1.png" }}},
	factory.object.create { object = items.scummbar.door_out },
	factory.object.create { object = items.scummbar.mancomb },
	factory.walkarea.create {
   		shape = { 
	    	type = "poly", 
	        outline = {32,16,70,24,128,19,251,18,311,10,321,10,345,32,467,41,492,50,514,40,565,40,580,35,629,6,626,0,256,0,200,16,149,0,90,0,85,10},
	        holes = {
	        	{374,6,505,6,505,28,374,28}
	        }
	    }
	}

})


function room.afterstartup() 
	for k, v in ipairs(room.initstuff) do
		v()
	end
	
	local mancomb_script = script:new()
	mancomb_script.actions = {
		[1] = { type="delay_dynamic", func = function() return (1 + math.random() * 4) end },
		[2] = { type="animate", actor="mancomb", anim="drink", loop=1, after={1}},
		[3] = { type="animate", actor="mancomb", anim="idle", after={2} },
	}
	mancomb_script.loop = 1
	monkey.play(mancomb_script)


end


