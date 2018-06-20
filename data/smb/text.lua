strings = {
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
        useprep = "with"
    },
    objects = {
        stairs = "stairs",
        path = "path",
        poster = "poster",
        door = "door",
        lookout = "lookout"
        
        
    },
    dialogues = {
        lookout = {
            text = {
            [1] = "I heard there was going to be a weenie roast here.",
            [2] = "I'm looking for fun. Seen any?",
            [3] = "What's green and hairy and has a thousand legs?",
            [4] = "Do you ever wonder if we're all just characters in a novel?",
            [5] = "Yikes!",
            [6] = "You almost scared me to death.",
            [7] = "I thought you were a--",
            [8] = "--never mind.",
            [9] = "What did you say your name was, again?",
            [10] = "I'm Guybrush Threepwood",
            [11] = "Call me Squinky.",
            [12] = "I'm over this way.",
            [13] = "Who are YOU?",
            [14] = "I'll just be off to seek my fortune now.",
            [15] = "Eh?",
            [16] = "Oh.",
            [17] = "I came to Mêlée™ Island because I want to be a pirate.",
            [18] = "Well, you picked the right place for it.",
            [19] = "Though perhaps the wrong time.",
            [20] = "Not to mention the wrong name.",
            [21] = "You have the silliest name I've heard in a long time.",
            [22] = "What the heck is wrong with \"Guybrush Threepwood\"?",
            [23] = "Nothing, if you want to sell shoes.",
            [24] = "You want to be a pirate, bou, take my advice:",
            [25] = "Change your name.",
            [26] = "Try something like \"Dreadbeard\" or \"Six-fingered Pete\".",
            [27] = "You just said you were Gibberish Driftwood, or something like that.",
            [28] = "GUYBRUSH THREEPwood.",
            [29] = "Sure, whatever.",
            [30] = "I'm the lookout of Mêlée™ Island.",
            [31] = "I watch the ocean for approaching storms and ships, and report them directly to the Governor.",
            [32] = "She doesn't like unexpected visitors.",
            [33] = "...especially not now.",
            [34] = "Why is the Governor worried about unexpected visitors?",
            [35] = "Actually, it's the EXPECTED visitors we're worried about.",
            [36] = "One pirate captain in particular...",
            [37] = "A dead one, but that doesn't make him any less dangerous.",
            [38] = "How did you get to be the lookout when you're obviously blind as a bat?",
            [39] = "Watch your tongue.",
            [40] = "I was hand-picked by Sheriff Shinetop!",
            [41] = "OK, Squinky.",
            [42] = "Good luck.",
            [43] = "Oh, it's you again, ",
            [44] = "Listen, I'm sort of busy right now.",
            [45] = "I'll talk to you later.",
            [46] = "Look out! Ha ha. Get it?",
            [47] = "That's THREEPWOOD.",
            [48] = "Actually, my name is Guybrush Threepwood.",
            [49] = "Oh, right."
            },
            names = { "Thranwook", "Thrumwink" }
        },
        cook = {
            [1] = "Hey!",
            [2] = "Don't go into the kitchen!",
			[3] = "You can't come back here!"
        }

        

    },
    defaultactions = {
        [1] = "It doesn't seem to open.",
        [2] = "That doesn't seem to work.",
        [3] = "I can't move it.",
        [4] = "I don't see anything special about it.",
        [5] = "I can't pick that up."

    },
    village1 = {
        [1] = "Re-elect Governor Marley.",
        [2] = "\"When there's only one candidate, there's only one choice.\""
    }
}

strings.dialogues.lookout.randomLookoutMsg = function() 
    return strings.dialogues.lookout.text[43] .. strings.dialogues.lookout.names[math.random(1, #strings.dialogues.lookout.names)] .. "."
end

    
    
    
