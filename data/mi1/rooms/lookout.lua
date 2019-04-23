roomDefinition = {
	width = 320,
	height = 144,
	startTable = {
		village1 = { pos = items["lookout.stairs"].hotspot.walk_to, dir="north"},
		meleemap = { pos = items["lookout.path"].hotspot.walk_to, dir = "east"},
	},
	defaultroom = "meleemap",
	depth = { type="linear_y", values= {0, 1, 144, 0} },
}

room = scumm.factory.basic_room (roomDefinition)

local walkarea = scumm.factory.object { id = "lookout.walkarea" }

table.insert (walkarea.children, scumm.factory.object {
	id="guybrush",
	pos={160, 32, 0}, 
	tag="player", 
	dir = "east",
	--follow = (roomDefinition.width > 320enableScroll),
		-- 		--collide = args.collide
})
table.insert (walkarea.children, scumm.factory.object { id = "lookout.fire" })
table.insert (walkarea.children, scumm.factory.object { id = "lookout.lookout" })


room:add( {
	{ pos = {0,0,-3}, components = { { type="gfx", image="gfx/lookout_1.png" }}},
    { pos = {81, 16, 3}, components = { { type="gfx", image="gfx/lookout_2.png" }}},
    { pos = {294, 33, 3}, components = { { type="gfx", image ="gfx/lookout_3.png" }}},
    { pos = {226, 0, 3}, components = { { type="gfx", image="gfx/lookout_4.png" }}},

    walkarea
 	-- scumm.factory.walkarea {
		-- tag = "walkarea",
		-- shape = { type = "poly", outline = {203,51,315,62,315,40,293,40,260,10,260,0,260,-20,234,-20,234,0,234,10,221,26,152,33,152,51}},
		-- children = {
		-- 	scumm.factory.object { id = "lookout.fire" },
		-- 	scumm.factory.object { id = "lookout.lookout" },


		-- }
 	-- },
	-- scumm.factory.object { id = "lookout.stairs" },
	-- scumm.factory.object { id = "lookout.path" },
})

local entry_cutscene = function() 
	local actions = {
		{ type = scumm.action.walkto, args = {tag="player", pos = {240, 30}}}
	}
	local s = script.make(actions)
	s.name = "_walk"
	monkey.play(s)
end

--table.insert(room.initstuff, entry_cutscene)