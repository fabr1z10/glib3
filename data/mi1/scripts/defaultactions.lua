script.defaultactions = {}

local d = strings.defaultactions

script.defaultactions.look = ms { 
	{action = action.say, args = { id=1, actor="guybrush", lines={d[4]} }}
}

print("pollo")
