-- creates a boxed message
-- input:
-- text ... the text to display
-- font --- the font
scumm.factory.message = function(args)
		
	return {
		type ="boxedmessage",
		pos = args.pos,
		-- components = {
		-- 	{ type="text", font=args.font, id=args.message, size=args.size, color= {255,255,255,255}, maxwidth=100}
		-- }
		font = args.font,
		message= args.message,
		size = args.size,
		maxwidth = args.maxwidth,
		color = args.color,
		bgcolor = args.bgcolor,
		padding = args.padding,
		border = args.border,
		corner = args.corner
	}

end