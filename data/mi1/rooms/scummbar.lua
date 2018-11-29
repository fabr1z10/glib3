require("template/room1")

local roomInfo = {
	width = 640,
	height = 144,
	startTable = {
		village1 = { pos = items.scummbar.door_out.walk_to, facing = "east"},
		mancomb = { pos = items.scummbar.mancomb.walk_to, facing = "north"},
		estevan = { pos = items.scummbar.estevan.walk_to, facing = "south"},

	},
	defaultroom = "village1",
	depth = { type="linear_y", values= {0, 1, 144, 0} },
	--depth = { type="linear_y", values= {0, 1, 144, 0} },
	--scale = { type="linear_y", values= {0, 0.8, 144, 0.2}}
}

room = generateBasicRoom (roomInfo)

room:add_asset(sprites.door_scummbar_village)
room:add_asset(sprites.mancomb)
room:add_asset(sprites.estevan)

room:add( {
	{ pos = {0, 0,-3}, components = { { type="gfx", image="gfx/scummbar_1.png" }}},
	{ pos = {157, 0, 0.99}, components = { { type="gfx", image="gfx/scummbar_3.png" }}},
	{ pos = {20, 0, 0.99}, components = { { type="gfx", image="gfx/scummbar_4.png" }}},
	{ pos = {374, 20, 0.95}, components = { { type="gfx", image="gfx/scummbar_2.png" }}},
	factory.object.create { object = items.scummbar.door_out },
	factory.object.create { object = items.scummbar.mancomb },
	factory.object.create { object = items.scummbar.estevan },
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


function run_background_script(actor, anim) 
	local mancomb_script = script:new()
	mancomb_script.actions = {
		action.random_delay { id=1, min=1, max=4 },
		action.animate_once { id=2, actor = actor, anim = anim },
		action.animate { id=3, actor = actor, anim = "idle" },
	}
	mancomb_script.loop = 1
	print ("CANE BESTIA")
	monkey.play(mancomb_script)
end

function room.afterstartup() 
	for k, v in ipairs(room.initstuff) do
		v()
	end
	
	run_background_script ("mancomb", "drink")
	run_background_script ("estevan", "drink")


end


