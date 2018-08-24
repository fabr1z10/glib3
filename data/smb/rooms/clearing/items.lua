local function gotoCircus() 
	if (variables.cannondone == true) then
		return _say { character="guybrush", lines= { strings.circus[1] }}
	else
		return changeRoom("circus")
	end
end


objects["clearing_path"] = {
	text = strings.objects.path,
	pos = {490, 24},
	dir = "east",
	walk = curry(changeRoom, "meleemap")
}

objects["circus_tent"] = {
	text = strings.objects.circustent,
	pos = {82, 69},
	dir = "north",
	walk = gotoCircus -- function() if (variables.cannondone == false) then curry(changeRoom, "circus")
}

