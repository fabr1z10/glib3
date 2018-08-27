local dt = 0.1

-- begin room
room = {

assets = {
    makeGuybrush(),
    makeArrowUp(),
    makeArrowDown(),
},
scene = {
	{
		tag = "main",
		camera = {
			tag = "maincam",
			type="ortho",
			size = {320, 144},
			bounds = {0, 0, 320, 144},
			viewport = {0, 56, 320, 144}
		},
		children = {}
	},
	makescummui1(),
	{
		tag = "diag",
		camera = {
			tag = "maincam",
			type="ortho",
			size = {320, 200},
			bounds = {0, 0, 320, 200},
			viewport = {0, 0, 320, 200}
		},
		children = {}
	}
}
}
-- end room

function room.init()
	variables._actionInfo:reset()
	-- add possible previous rooms here
	local defaultRoom = ""
	local fromData = {
        --village2 = { playerpos = objects.village3_archway.pos, anim = "idle_right", flip = true },
		--shop = { playerpos = objects.door_village_shop.pos, anim="idle_front", flip=false }
    }
    
-- add player
	local d = fromData[variables._previousroom]
	if (d == nil) then
		d = fromData[defaultRoom]
	end

    table.insert (room.scene[1].children, {
        tag = objects.guybrush.tag,
        pos = d.playerpos,
        gfx = { model = "guybrush", anim = d.anim, flip = d.flip },
        follow = { cam="maincam" },
        scaling = {}
    })
end

function room.afterstartup() 
	refreshInventory()
end




