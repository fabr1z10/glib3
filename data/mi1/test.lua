test = {}


test.bridge = function() 
	variables._room = "bridge"
	--variables.inventory["pieces_of_eight"] = 999
	variables.inventory["kitchen.fish"] = 1
end

test.meleemap = function() 
	--variables.inventory["kitchen.fish"] = 1
	variables._room = "meleemap"
end

test.circus = function() 
	variables._room = "clearing"
	variables.inventory["kitchen.pot"] = 1
end

test.shop = function() 
	variables._room = "shop"
	variables.door_shop = 1
end

test.shop2 = function() 
	variables._room = "shop"
	variables.inventory["shop.sword"] = 1
	variables.sword_paid = true
	variables.door_shop = 1
end

test.village2 = function() 
	variables._room = "village2"
	
end