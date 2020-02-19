strings = {
	pieces_of_eight = function() 
		local n = variables.inventory["pieces_of_eight"]
		return ("I have " .. tostring(n) .. " pieces of eight.")
	end,
    ui = {
        open = "Open",
        close = "Close",
        push = "Push",
        pull = "Pull",
        walkto = "Walk to",
        pickup = "Pick up",
        talkto = "Talk to",
        give = "Give",
        use = "Use",
        lookat = "Look at",
        turnon = "Turn on",
        turnoff = "Turn off",
        giveprep = "to",
        useprep = "with",
		pause_message = "Game Paused. Press SPACE to Continue."
    },
    defaultactions = {
        [1] = "It doesn't seem to open.",
        [2] = "That doesn't seem to work.",
        [3] = "I can't move it.",
        [4] = "I don't see anything special about it.",
        [5] = "I can't pick that up."

    },

    objects = {
    	sign = 'sign',
    	path = 'path',
    	frontdoor = 'front door',
    	doormat = 'door mat',
    	key = 'key',
    	grating = 'grating',
    	bushes = 'bushes'
    },
    gate = {
    	[1] = 'WARNING!!',
    	[2] = 'Trespassers will be horribly mutilated.'
    }
}

    
    
    
