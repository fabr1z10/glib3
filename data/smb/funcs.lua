function curry(f, arg)
    return function()
       return f(arg) 
    end 
end

function curry2(f, arg)
    return function(x)
       f(arg, x) 
    end 
end

require ("factoryactions")
require ("rooms/scummbar/actions")
require ("rooms/kitchen/actions")
require ("items")
require ("factoryobjects")
require ("uifuncs")


function curry2_1(f, arg1, arg2)
    return function(x)
       f(arg1, arg2, x) 
    end 
end




function createWalkToPosition (position, script, f)
    table.insert (script.actions,
    {
        id = #script.actions,
		    walkarea = "walkarea",
		    actor = "player",
        type = "walkto",
		    pos = position
	  }

  )
end

require ("characters")



