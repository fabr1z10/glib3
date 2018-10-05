

characters = {

	beast = {
		info = {	
			sprite = "beast",
			energy = 3,
			bodymetrics = {
				y = {
					body = 40,
					head = 62,
					legs = 0,
					arm = 60
				},
				width = {
					body = 18,
					head = 8,
					legs = 15
				},
				height = {
					body = 22,
					head = 8,
					legs = 40		
				}
			}
		},
		-- body metrics
		shadowsize ={20,5},
		colliders = {
			{ name = "head", info = {type="head"} },
			{ name = "body", info = {type="body", sprite="character_2", parts = { { anim="head", cr = 1 }, {anim="legs", cr = 0} }}  },
			{ name = "legs", info = {type="legs"} }
		},
		states = {
			{ id = "idle", type="basic", anim = "idle", colliders = { "body" } },
			{ id = "walk", type="walkcollision", anim = "walk", colliders = { "body" }, speed=50, width = 1, height = 1, horizontal_rays = 1, vertical_rays = 2},
			{ id = "ishit", type="basic", anim="idle", colliders= {} },
			{ id = "punch", type="hit",  anim = "punch", colliders = { "body" }, frame = 2, mask = 2, shape = {type="rect", width = 10, height = 10 }, offset = {32, 52}, func = ciao},
			{ id = "kick", type="hit",  anim = "kick", colliders = { "body" }, frame = 2, mask = 2, shape ={type="rect", width = 18, height = 8}, offset = {38, 19}, func = ciao},
			{ id = "cr", type="hit",  anim = "cr", colliders = { "body" }, frame = 1, mask = 4, shape = {type="rect", width = 10, height = 10 }, offset = {10, 0}, func = ciao2},

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
	},
	bred = {
		info = {
			sprite = "bred", 
			energy = 1,
			bodymetrics = {
				y = {
					body = 49,
					head = 76,
					legs = 0,
					arm = 50
				},
				width = {
					body = 16,
					head = 12,
					legs = 16
				},
				height = {
					body = 26,
					head = 12,
					legs = 49		
				}
			},
			scale = 0.6
		},
		shadowsize ={20,5},
		colliders = {
			{ name = "head", info = {type="head", parts = { { anim="body", cr=0, crscale=0.3 }, { anim="legs", cr=0 } }}},
			{ name = "body", info = {type="body", parts = { { anim="head", cr=1, crscale=0.4 }, { anim="legs", cr=0 } }}},
			{ name = "legs", info = {type="legs", parts = { { anim="head", cr=1, crscale=0.4 }, { anim="body", cr=0 } }}}
		},
		states = {
			{ id = "idle", type="basic", anim = "idle", colliders = { "head", "body", "legs" } },
			{ id = "walk", type="aiwalk", anim = "walk", target="player", colliders = {"head", "body", "legs"  }, speed=20, width = 1, height = 1, horizontal_rays = 1, vertical_rays = 2},
			{ id = "ishit", type="basic", anim="idle", colliders= {} },
			{ id = "punch", type="hit",  anim = "punch", colliders = { "head", "body", "legs"  }, frame = 2, mask = 2, shape = {type="rect", width = 10, height = 10 }, offset = {32, 52}, func = ciao},
		},
		initialstate ="idle",
		transitionmatrix = {
			{ current = "idle", next="punch", prob = 0.01 }
		},

	}



}
