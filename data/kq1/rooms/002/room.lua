local items = engine.items

roomDefinition = {
	width = 316,
	height = 166,
	startTable = {
		['001'] = { walkarea = "002.walkarea", pos = {313, 16}, dir="west" },
		['003'] = { walkarea = "002.walkarea", pos = {227, 46}, dir="south" },
		['009'] = { walkarea = "002.walkarea", pos = {100, 100}, dir="south" } 
	},
	defaultroom = "001",
	walkareas = { "002.walkarea" },
	font_size = 8,
	playerid="graham",
	collide=true
}

room = scumm.factory.sci_room (roomDefinition)

room:add ( "main",
	{ 
		{ pos = {0,0,-3}, components = { { type="gfx", image="bg003.png" }}},
 		scumm.factory.item_sci { id="002.purple_flag"},
		scumm.factory.item_sci { id="002.yellow_flag"},
		scumm.factory.item_sci { id="002.cyan_flag"},		
		scumm.factory.item_sci { id="002.door"},
		scumm.factory.item_sci { id="002.flags"},
		scumm.factory.item_sci { id="002.lion1"},
		scumm.factory.item_sci { id="002.lion2"},
		makeRoomChange { x=315, y=10, width=1, height=10, room ="001"},
		makeRoomChange { x=0, y=0, width=1, height=128, room ="006"},

	}
)

room:add ( "002.walkarea", { 
 	--{ pos = {8, 44, 0}, components = { { type="gfx", image="002_bg_1.png" }}},
	scumm.factory.item_sci { id="002.tree" },

})	


function init_script()
	local pr = engine.state.previousRoom or roomDefinition.defaultroom
	if (pr == "003") then
		local actions = {
			{ type = action.animate, args = { tag="002.door", anim="open", fwd=false, sync = true}},
			{ type = action.animate, args = {tag = "002.door", anim="closed"}}
		}
		local s1 = script.make(actions,1)
	 	monkey.play(s1)
	end
end


table.insert(room.initstuff, init_script)
