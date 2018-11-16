room = {

engines = {
	{ type = "hotspotmanager" },
	{ type = "scheduler" }
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
		}
	},
	{
		tag = "main",
		camera = {
			tag = "maincam",
			type="ortho",
			size = {320, 56},
			bounds = {0, 0, 320, 56},
			viewport = {0, 0, 320, 56}
		},
		children = {
			{
		    	tag = "currentaction",
		    	pos={160,48,0},
				components = {
		    		{ type="text", id = "ciao", font="ui", align = "bottom", color = config.ui_currentaction_color}
				}
		    },
			items.verbbutton.create {pos={2, 40}, verb = config.verbs.open},
			items.verbbutton.create {pos={2, 32}, verb = config.verbs.close},
			items.verbbutton.create {pos={2, 24}, verb = config.verbs.push},
			items.verbbutton.create {pos={2, 16}, verb = config.verbs.pull},
			items.verbbutton.create {pos={48, 40}, verb = config.verbs.walk},
			items.verbbutton.create {pos={48, 32}, verb = config.verbs.pick},
			items.verbbutton.create {pos={48, 24}, verb = config.verbs.talk},
			items.verbbutton.create {pos={48, 16}, verb = config.verbs.give},
			items.verbbutton.create {pos={100, 40}, verb = config.verbs.use},
			items.verbbutton.create {pos={100, 32}, verb = config.verbs.look},
			items.verbbutton.create {pos={100, 24}, verb = config.verbs.turnon},
			items.verbbutton.create {pos={100, 16}, verb = config.verbs.turnoff},
			{
				tag="inventory",
				pos = {150, 0, 0},
				components = {
					{ 
						type="textview",
						width = 170.0,
						height = 48.0,
		                --viewport = {150, 0, 170, 48},
		                size = 8,
						lines = 6,
						deltax = 26,
						factory = items.inventorybutton.create
					}
				}
			}

			--items.button.create { pos ={2, 40}, font="ui", text="Open", align="bottomleft", color = config.ui_unselected_color, size = 8, priority = 1,
		--		onenter = curry2(changecolor, config.ui_selected_color), onleave = curry2(changecolor, config.ui_unselected_color) }
			--items.button.create { pos ={0,0}, font="ui", text="ciao", size = 8, priority = 1, align="bottomleft"},
			--items.button.create { pos ={320,0}, font="ui", text="ciao", size = 8, priority = 1, align="bottomright"},
			--items.button.create { pos ={320,56}, font="ui", text="ciao", size = 8, priority = 1, align="topright"},

		}
	}

}


}

function room.afterstartup() 
	setverb (config.verbs.walk)

	local c = monkey.getEntity("inventory")
	c:addtext("ciao")
	c:addtext("come")
	c:addtext("stai")
	c:addtext("alleelelel")
	c:addtext("stronzo")
	c:addtext("duro")
	c:addtext("anvedi")


	--monkey.addEntity(items.inventorybutton.create ("ciao",100), c)
end


