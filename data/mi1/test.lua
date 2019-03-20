test = {}


test.bridge = function() 
	variables._room = "bridge"
	variables.inventory["pieces_of_eight"] = 999
	variables.inventory["kitchen.fish"] = 1
end

test.meleemap = function() 
	variables.inventory["kitchen.fish"] = 1
	variables._room = "meleemap"
end