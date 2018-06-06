function defaultWalk(script)
   return script 
end

function defaultLook (script)
    table.insert (script.actions,
    {
        id = #script.actions,
        type = "say",
        actor = "player",
        color = {255,0,0,255},
        message = {"ciao cazzo!", "te lo dico an!e?"}
    })
 --    {
 --        id = #script.actions,
 --        type = "showmessage",
	-- 	actor = "player",
 --        font ="monkey",
 --        size = 8,
 --        color = {255,0,0,255},
 --        outlinecolor = {0,0,0,255},
	-- 	message = "ciao cazzo!"
	-- })
end