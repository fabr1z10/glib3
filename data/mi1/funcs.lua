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

function variables._actionInfo:toString ()
    local t = { self.verb.text }
	print (t)
    if (self.obj1 ~= nil) then
		o1 = objects[self.obj1]
        t[2] = o1.text
        if (self.obj2 ~= nil) then
            o2 = objects[self.obj2]
            t[3] = self.verb.prep
            t[4] = o2.text
        else
            if (self.selectSecond == true) then
               t[3] = self.verb.prep 
            end
        end 
    end
    return table.concat(t," ")
end

function changecolor (color, entity)
	print ("ASSO")	
    entity:setcolor(color[1], color[2], color[3], color[4])
end

function setverb(verb)
    variables._actionInfo.verb = verb
    variables._actionInfo.obj1 = nil
    variables._actionInfo.obj2 = nil
    variables._actionInfo.selectSecond = false
    updateVerb()
end

function updateVerb() 
    a = monkey.getEntity("currentaction")
    a:settext(variables._actionInfo:toString())    
end