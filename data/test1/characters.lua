

characters = {

	beast = {
		sprite = "beast",
		-- body metrics
		shadowsize ={20,5},
		colliders = {
			{ width = 20, height = 60, offset = {-10, 0}, name = "body" }
		},
		states = {
			{ id = "idle", type="basic", anim = "idle", colliders = { "body" } },
			{ id = "walk", type="walkcollision", anim = "walk", colliders = { "body" }, speed=50, width = 1, height = 1, horizontal_rays = 1, vertical_rays = 2},
			{ id = "ishit", type="basic", anim="idle", colliders= {} },
			{ id = "punch", type="hit",  anim = "punch", colliders = { "body" }, frame = 2, mask = 2, shape = {type="rect", width = 10, height = 10 }, offset = {32, 52}, func = ciao},
			{ id = "kick", type="hit",  anim = "kick", colliders = { "body" }, frame = 2, mask = 2, shape ={type="rect", width = 18, height = 8}, offset = {38, 19}, func = ciao}
		},
		initialstate = "idle",
		keys = {
			{ current = "idle", key =  263, next="walk" },
			{ current = "idle", key =  264, next="walk" },
			{ current = "idle", key =  265, next="walk" },
			{ current = "idle", key =  262, next="walk" },
			{ current = "idle", key =  65, next="punch" },
			{ current = "idle", key =  83, next="kick" },
			{ current = "idle", key =  84, next="cr" },

			{ current = "walk", key =  65, next="punch" },
			{ current = "walk", key =  83, next="kick" },
			{ current = "walk", key =  84, next="cr" }
		},
		collisionType = "clear",
		info = {	
			energy = 3,
			killscale = 1
		}
	},
	bred = {
		sprite = "character_2", 
		shadowsize ={20,5},
		scale = 0.7,
		colliders = {
			{ width = 20, height = 60, offset = {-10, 0}, name = "body" }
		},
		states = {
			{ id = "idle", type="basic", anim = "idle", colliders = { "body" } },
			{ id = "walk", type="aiwalk", anim = "walk", target="player", colliders = { "body" }, speed=50, width = 1, height = 1, horizontal_rays = 1, vertical_rays = 2},
			{ id = "ishit", type="basic", anim="idle", colliders= {} },
			{ id = "punch", type="hit",  anim = "punch", colliders = { "body" }, frame = 2, mask = 2, shape = {type="rect", width = 10, height = 10 }, offset = {32, 52}, func = ciao},
		},
		initialstate ="idle",
		transitionmatrix = {
			{ current = "idle", next="punch", prob = 0.01 }
		},
		--collisionType = "clear",
		collisionType = "headBodyLegs",
		info = {
			energy = 2,
			killscale = 1
		}
	}



}
