script.defaultactions = {}


script.defaultactions.look = function()
	return say {actor =items.guybrush, lines = {strings.defaultactions[4]} }
end