local items = engine.items


roomDefinition = {
	width = 316,
	height = 166,
	startTable = {
		['002'] = { walkarea = "001.walkarea", pos = {10, 15}, dir="east"},
--		meleemap = { walkarea = "lookout.walkarea", pos = items["lookout.path"].hotspot.walk_to, dir = "east"},
	},
	defaultroom = "002",
	walkareas = { "001.walkarea", "001.moat"},
	font_size = 8,
	playerid="graham",
	
}

room = scumm.factory.sci_room (roomDefinition)

room:add ( "main",
	{ 
		{ pos = {0,0,-3}, components = { { type="gfx", image="bg001.png" }}},
		scumm.factory.item_sci { id="castle" },
		scumm.factory.item_sci { id="001.bridge" },
		scumm.factory.item_sci { id="001.moat.item" },
 		scumm.factory.item_sci { id="purple_flag"},
		scumm.factory.item_sci { id="yellow_flag"},
		scumm.factory.item_sci { id="cyan_flag"},
		scumm.factory.item_sci { id="flags"},
		makeRoomChange { x=0, y=10, width=1, height=10, room ="002"},
		{ 
			pos = {0,0,0},
			components = {
				{ type = "collider", flag = 32, mask = 1, tag=10, 
 						shape = { type="line", A = {0,8.1}, B = {228, 8.1}}
 				},
 				{ type = "info", func = function() 
 					local p = monkey.getEntity("player")
 					local actions = {
 						{ type = scumm.action.enableplay, args = {value=false}},
 						{ type = action.move, args = {tag="player", to = {p.x, 0}, imm=true}},
 						{ type = action.set_state, args = { tag="player",state="drown"}},
						{ type = action.kill_script, args = {script = "alli1"}},
						{ ref = 1, type = action.kill_script, args = {script = "alli2"}},
						{ ref = 2, after = {1}, type = scumm.action.walktoitem, args = { tag = "alli1", item = "player", offset={-20,0} }},
						{ ref = 3, after = {1}, type = scumm.action.walktoitem, args = { tag = "alli2", item ="player", offset={20,0 }}},
 						{ after = {2,3}, type = action.delay, args = {sec = 2}},
						{ type = action.kq.showmessage, args = {msg=strings.room001[3]}},
						{ type = action.remove_object, args = {tag ="player"}},
 						{ type = action.delay, args = {sec = 2}},
						{ type = action.kq.showmessage, args = {msg=strings.global[1]}},
						{ type = action.restart_game}
						--{ type = action.callfunc, args = { func = function() displayBox(strings.room001[3]) end }}
					}		
 					local s = script.make(actions)
 					monkey.play(s)
 					--displayBox("ciaociao") 
 				end }
 			 }
 		}
	}
)

room:add ( "001.walkarea", { 
	scumm.factory.item_sci { id="001.tree" },
})	

room:add ( "001.moat", { 
	scumm.factory.item_sci { id="001.alligator_1" },
	scumm.factory.item_sci { id="001.alligator_2" },
})	
-- 
function move_alligator(name)
	local actions = {
		{ ref=1, type = scumm.action.walkto, args = { tag =name, pos = {200, 10} }},
		{ type = scumm.action.walkto, args = { tag =name, pos = {10, 10} }},
	}
	local s1 = script.make(actions,1)
	s1.name=name
 	monkey.play(s1)
end


table.insert(room.initstuff, glib.curry(move_alligator, "alli1"))
table.insert(room.initstuff, glib.curry(move_alligator, "alli2"))

