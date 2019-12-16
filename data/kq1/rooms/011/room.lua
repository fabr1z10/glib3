local items = engine.items

roomDefinition = {
	width = 316,
	height = 166,
	startTable = {
		['010'] = { walkarea = "011.walkarea", pos = {8, 20}, dir="east"},
	},
	defaultroom = "010",
	walkareas = { "011.walkarea" },
	font_size = 8,
	playerid="graham",
	collide=true,
}

room = scumm.factory.sci_room (roomDefinition)

room:add ( "main",
	{ 
		{ pos = {0,0,-3}, components = { { type="gfx", image="011_bg_0.png" }}},   
	}
)


function chase ()
	local acts = {

		{ ac}

	}
end

function init_script()
	local actions = {
		{ type = action.delay, args = { sec=2}},
		{ type = action.kill_script, args = {script="_walk"}},
		{ type = action.set_state, args ={tag="player",state="idle"}},
		{ type = action.callfunc, args = {func = function() engine.state.scumm.play =false end }},
		{ type = action.kq.showmessage, args = { msg = strings.room011[1] }},
		{ type = action.create_object, args = { parent="011.walkarea",factory=scumm.factory.object,
			args = {
				id="fairy",
				pos = {158,20,0},
				dir = "west",
			}}
		},
		{
			type = action.callfunc, args = { func = function() 
				local p = monkey.getEntity("player")	
				local a = {
					{ type = scumm.action.walkto, args = {tag="fairy", pos = {p.x < 160 and p.x+32 or p.x-32, p.y}}},
					{ type = action.delay, args = { sec=2}},
					{ type = action.kq.showmessage, args = { msg = strings.room011[2] }},					
					{ type = action.remove_object, args = { tag="fairy"}},
					{ type = action.callfunc, args = {func = function() engine.state.scumm.play = true end }},
				}
		 		local s2 = script.make(a)
		 		s2.name="ciccio"
		 		monkey.play(s2)
		 	end
		 	}
		}
		-- {
		-- 	type = action.repeat_forever, args = { func = function()
		-- 		local p = monkey.getEntity("player")
		-- 		local a ={
		-- 			{ type = scumm.action.walkto, args = { tag="fairy", pos = {p.x,p.y}}},
		-- 		}
		-- 		local s2 = script.make(a)
		-- 		s2.name="ciccio"
		-- 		monkey.play(s2)
		-- 	end,
		-- 	interval=1
		-- }}

	}
	local s1 = script.make(actions,1)
 	monkey.play(s1)
end


table.insert(room.initstuff, init_script)


