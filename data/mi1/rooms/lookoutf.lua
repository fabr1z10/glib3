function say2(args)
return { type="say", actor=args.actor.tag, lines = args.lines, offset = args.actor.text_offset, color = args.actor.text_color, after = args.after }
end
function ciaooo() 
	print ("IIIDIDIDI")
	local s = script:new()
	s.actions = {
		[1] = say2 { actor = objects.guybrush, lines= {strings.dialogues.lookout.text[1] }},
		[2] = say2 { actor = obj.lookout, lines = {strings.dialogues.lookout.text[2]}, after= {1} }
	}
	print ("DIDIDIDIDI!!!")
	return s
end


