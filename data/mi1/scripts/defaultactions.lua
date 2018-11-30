script.defaultactions = {}

local d = strings.defaultactions

script.defaultactions.look = ms { 
	{ action.say, { id=1, actor="guybrush", lines={d[4]} }}
}

print("pollo")
