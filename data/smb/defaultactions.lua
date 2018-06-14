

function defaultWalk(script)
   return script 
end


function defaultopen(script) 
    say (characters.guybrush, {strings.defaultactions[1]}, script)
end

function defaultclose(script) 
    say (characters.guybrush, {strings.defaultactions[2]}, script)
end


function defaultLook (script)
    say (characters.guybrush, {strings.defaultactions[4]}, script)
end

function defaultmove (script)
    say (characters.guybrush, {strings.defaultactions[3]}, script)
end

function defaultpickup (script)
    say (characters.guybrush, {strings.defaultactions[5]}, script)
end