items = {}

require ("items/button")
require ("items/player")
require ("items/object")


objects= {
	lookout = {
		stairs = {
			text = strings.objects.stairs,
			pos = {250, 0, 0}, 
			size = {10, 10},
			actions = {
				walk = curry(changeRoom, "village1")
			}
		}
		
    

	}


}