script.defaultactions = {}

local d = strings.defaultactions

script.defaultactions.look = ms { 
	{ action.say, { id=1, actor="guybrush", lines={d[4]} }},

}

script.defaultactions.use = ms {
	{ action.say, { id=1, actor="guybrush", lines={d[2]} }},		
}

script.defaultactions.give = ms {
	{ action.say, { id=1, actor="guybrush", lines={d[2]} }},		
}

script.defaultactions.pickup = ms { 
	{ action.say, { id=1, actor="guybrush", lines={d[5]} }},

}