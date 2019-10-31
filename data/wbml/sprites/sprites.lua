local models = engine.assets.models

local s = {
	-- wonderboy in monsterland
	wbml_idle_1 = {x=1,y=1,width=22,height=24,anchor={12,0}},
	wbml_walk_1 = {x=24,y=1,width=22,height=24,anchor={12, 0}},
	wbml_walk_2 = {x=47,y=1,width=23,height=24,anchor={12, 0}},
	wbml_walk_3 = {x=71,y=1,width=22,height=24,anchor={12, 0}},
	wbml_walk_4 = {x=94,y=1,width=22,height=24,anchor={12, 0}},
	wbml_jump_1 = {x=117,y=1,width=21,height=22, anchor={11,0}},
	wbml_attack_1 = {x=139,y=1,width=18,height=24,anchor={11,0}},
	wbml_attack_2 = {x=158,y=1,width=26,height=24,anchor={13,0}},
}

local dt=0.1

local wbml = {-8, 0, 8, 24}

models["wbml"] = {
	sheet ="s1.png",
	type = "boxed_sprite",
	ppu=1,
	--thickness = 1,
	animations = {
		{ name="idle", box=wbml, frames = { 
			{duration=dt, quads = {{ id = s.wbml_idle_1}} }
		}},
		{ name="walk", box=wbml, frames = { 
			{duration=dt, quads = {{ id = s.wbml_walk_1}} },
			{duration=dt, quads = {{ id = s.wbml_walk_2}} },
			{duration=dt, quads = {{ id = s.wbml_idle_1}} },
			{duration=dt, quads = {{ id = s.wbml_walk_3}} },
			{duration=dt, quads = {{ id = s.wbml_walk_4}} },
			{duration=dt, quads = {{ id = s.wbml_idle_1}} },
		}},
		{ name="jumpup", box=wbml, frames = { 
			{duration=dt, quads = {{ id = s.wbml_jump_1}} }
		}},		
		{ name="jumpdown", box=wbml, frames = { 
			{duration=dt, quads = {{ id = s.wbml_jump_1}} }
		}},		
		{ name="attack", box=wbml, frames = { 
			{duration=dt, quads = {{ id = s.wbml_attack_1}} },
			{duration=2*dt, quads = {{ id = s.wbml_attack_2}}, attack ={6,10,18,15} },
			{duration=2*dt, quads = {{ id = s.wbml_attack_1}} }
		}},	
	}
}