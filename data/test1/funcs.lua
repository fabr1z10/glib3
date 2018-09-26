function curry(f, arg)
    return function()
       return f(arg) 
    end 
end

function createObject (obj) 
    parent = monkey.getEntity("main")
    monkey.addEntity (obj, parent)
end