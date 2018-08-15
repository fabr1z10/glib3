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
        useprep = "with",
		pause_message = "Game Paused. Press SPACE to Continue."
    },
    objects = {
        stairs = "stairs",
        path = "path",
        poster = "poster",
        door = "door",
        lookout = "lookout",
		cliffside = "cliffside",
		meat = "hunk of meat",
		pot = "pot",
		fish = "fish",
		potostew = "pot o'stew",
		meatstew = "meat in stew",
        stewedmeat = "stewed meat",
		barrel = "barrel",
		kitchen_table = "table",
		fireplace = "fireplace",
		ilp = "important-looking pirates",
		dog = "dog",
		pirate = "pirate",
		pirates = "pirates",
		archway = "archway",
		citizen = "Citizen of M�l�e",
		lowmoralfiber = "Men of Low Moral Fiber (pirates)",
		pieceofeight = "piece of eight",
		piecesofeight = "pieces of eight",
		minutes = "minutes",
		baskets = "baskets",
		basket = "basket",
		chicken = "chicken",
		chickens = "chickens",
		statue = "statue",
		knickknacks = "voodoo knickknacks",
		couch = "couch",
        trunk = "trunk",
		rubberchicken = "rubber chicken",
		bones = "bones",
		chalice = "chalice",
		sword = "sword",
		storekeeper="storekeeper",
        shovel = "shovel"
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
            [17] = "I came to M�l�e� Island because I want to be a pirate.",
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
            [30] = "I'm the lookout of M�l�e� Island.",
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
            [49] = "Oh, right.",
			[50] = "I am not sure, but I think he may be asleep."
            },
            names = { "Thranwook", "Thrumwink" }
        },
        cook = {
            [1] = "Hey!",
            [2] = "Don't go into the kitchen!",
			[3] = "You can't come back here!"
        },
		pirates = {
			text = {
			[1] = "What be ye wantin', boy?",
			[2] = "I mean to kill you all!",
			[3] = "I want to be a pirate.",
			[4] = "I want to be a fireman.",
			[5] = "Get lost, boy, you bother us.",
			[6] = "So what?",
			[7] = "Why bother us?",
			[8] = "Hey, don't forget we're short on help because of this whole LeChuck thing.",
			[9] = "So?",
			[10] = "So, no pirates means no swag, and no swag means no grog, and we're getting dangerously low on grog...",
			[11] = "Hmm...",
			[12] = "Do you have any special skills?",
			[13] = "I can hold my breath for ten minutes!",
			[14] = "Well...",
			[15] = "All right, but you don't become a pirate just by ASKING.",
			[16] = "You'll have to go through...",
			[17] = "The three trials!",
			[18] = "Er...",
			[19] = "What three trials are those?",
			[20] = "There are three trials every pirate must pass.",
			[21] = "You must master the sword", 
			[22] = "...and the art of thievery...",
			[23] = "...and the quest.",
			[24] = "The what?",
			[25] = "Treasure huntin', ya sea urchin!",
			[26] = "Right.",
			[27] = "You must prove yourself in each of these three areas:",
			[28] = "swordplay, thievery, and, er, treasure huntery;",
			[29] = "then return with proof that you've done it.",
			[30] = "And then ye must drink grog with us!!",
			[31] = "GROG!!!",
			[32] = "Tell me more about mastering the sword.",
			[33] = "Tell me more about mastering the art of thievery.",
			[34] = "Tell me more about treasure hunting.",
			[35] = "You're a bunch of foul-smelling, grog-swilling pigs!",
			[36] = "What's in that grog stuff, anyway?",
			[37] = "I'll just be running along now.",
			[38] = "Leave us to our grog.",
			[39] = "Come back later and tell us how ye're doing.",
			[40] = "Well, if it isn't the boy who wants to be a pirate.",
			[41] = "How do you fare on your quests?",
			[42] = "First, get ye a sword.",
			[43] = "You must seek out and defeat the Sword Master.",
			[44] = "Someone in town can probably direct you.",
			[45] = "Oh!",
			[46] = "You'll want to find someone to train you first.",
			[47] = "Ha ha.",
			[48] = "Imagine trying to take on the Sword Master without any training!",
			[49] = "Har har har",
			[50] = "Tell me again about mastering the sword.",
			[51] = "And get yourself trained first.",
			[52] = "We want you to procure a small item for us...",
			[53] = "The Idol of Many Hands...",
			[54] = "...in the Governor's mansion!",
			[55] = "The Governor keeps the Idol o' Many Hands in a display case in the mansion outside of town.",
			[56] = "You'll have to get past the guards, naturally.",
			[57] = "The tricky part will be getting past the dogs outside.",
			[58] = "They're a particularly vicious breed...",
			[59] = "...you might be able to drug them or something.",
			[60] = "Tell me again about pilfering the idol.",
			[61] = "Legend has it that there's a treasure buried here on the island...",
			[62] = "All you must do is find the Legendary Lost Treasure of M�l�e Island� and bring it back here.",
			[63] = "Should I have a map or something?",
			[64] = "You can hardly expect to find a treasure without a map!",
			[65] = "...and don't forget:",
			[66] = "X marks the spot!",
			[67] = "Tell me again about the Lost Treasure.",
			[68] = "To be a pirate ye must also be a foul-smelling, grog-swilling pig.",
			[69] = "Grog is a secret mixture which contains one or more of the following:",
			[70] = "kerosene",
			[71] = "propylene glycol",
			[72] = "artificial sweeteners",
			[73] = "sulphuric acid",
			[74] = "rum", 
			[75] = "acetone",
			[76] = "red dye #2",
			[77] = "scumm",
			[78] = "axle grease",
			[79] = "battery acid",
			[80] = "and/or pepperoni",
			[81] = "As you can probably imagine, it's one of the most caustic, volatile substances known to man.",
			[82] = "The stuff eats right through these mugs and the cook is losing a fortune replacing them."
			}
		},
		dog = {
			text = {
			[1] = "Grrrrr.",
			[2] = "Woof.",
			[3] = "Arf.",
			[4] = "Ruff.",
			[5] = "Grrrrrr.",
			[6] = "GRRRRRRRRRR!!!",
			[7] = "WOOF?",
			[8] = "Aruff roof!",
			[9] = "Woof-woof arf woof...",
			[10] = "...warroof, M�l�e Island�!",
			[11] = "...a-roof wuf:",
			[12] = "...LeChuck!",
			[13] = "Grrrrrrr!",
			[14] = "Worf.",
			[15] = "A-ROOF!",
			[16] = "Wuf, 'LeChuck?'",
			[17] = "Yip! Yip! Yip!",
			[18] = "Worf, worf.",
			[19] = "A-roof?",
			[20] = "Ruff.",
			[21] = "Worf woof woof ruff-ruff...",
			[22] = "Wor-roof wuf?",
			[23] = "Ruff arf-arf, bow-ruff...",
			[24] = "...Governor Marley!",
			[25] = "A-OOOOOOO! A-OOOOOOO!",
			[26] = "(ruff ruff ruff)",
			[27] = "Bow-roo wuf rowwf--",
			[28] = "--Arrooof--",
			[29] = "--LeChuck!",
			[30] = "GRRRRRRRRR!",
			[31] = "Arf, oof-oof, Monkey Island�!",
			[32] = "*sniff* *sniff*",
			[33] = "Woof ARF!",
			[34] = "...arf?",
			[35] = "Ruff, a-roof arf!",
			}
		},
		loom_pirate = {
			text = {
			[1] = "Aye.",
			[2] = "Aye, yourself.",
			[3] = "Nice hat.",
			[4] = "So, tell me about LOOM.",
			[5] = "Nice talking to you.",
			[6] = "You mean the latest masterpiece of fantasy storytelling from Lucasfilm's� Brian Moriarty�?",
			[7] = "Why it's an extraordinary adventure with an interface of magic...",
			[8] = "...stunning, high-resolution, 3D landscapes...",
			[9] = "...sophisticated score and musical effects.",
			[10] = "Not to mention the detailed animation and special effects,",
			[11] = "elegant point 'n' click control of characters, objects, and magic spells.",
			[12] = "Beat the rush!",
			[13] = "Go out and buy Loom� today!",
			[14] = "Geeze, what an obvious sales pitch.",
			[15] = "Sorry, but on some topics I just get carried away.",
			[16] = "No thanks. I can't stand salesmen."
			}
		},
		estevan = {
			text = {
			[1] = "What are you looking at me for?",
			[2] = "I'd like to introduce myself... my name's Guybrush.",
			[3] = "Excuse me, but I'm looking for the dart board.",
			[4] = "Where can I get a drink?",
			[5] = "Sorry to bother you. Bye.",
			[6] = "What now?",
			[7] = "Right.",
			[8] = "Yeah, so what?",
			[9] = "What happened to your eye?",
			[10] = "Dart board?",
			[11] = "We don't have one anymore.",
			[12] = "There was a horrible accident",
			[13] = "Drinking and darts don't mix.",
			[14] = "A drink?",
			[15] = "You could wait for the cook to notice you...",
			[16] = "...but that could take all day.",
			[17] = "Just find a mug and sneak into the kitchen.",
			[18] = "That's what we all do.",
			[19] = "Well, I was putting in my contact lens when--",
			[20] = "Hey, wait a second!",
			[21] = "That's none of your business!"
			}
		},
		mancomb = {
			text = {
			[1] = "Ahoy there, stranger.",
			[2] = "New in town?",
			[3] = "My name's Guybrush Threepwood. I'm new in town.",
			[4] = "Are you a pirate? Can I be on your crew?",
			[5] = "Who's in charge here?",
			[6] = "Nice talking to you.",
			[7] = "Have fun on M�l�e Island�.",
			[8] = "Hey, nice to see you again.",
			[9] = "Guybrush Threepwood?",
			[10] = "Ha ha ha!!!",
			[11] = "That's the stupidest name I've ever heard!",
			[12] = "I don't know... I kind of like 'Guybrush'",
			[13] = "Well, what's YOUR name?",
			[14] = "Yeah, it's pretty dumb, isn't it?",
			[15] = "I'm insulted. Goodbye.",
			[16] = "But it's not even a name!",
			[17] = "My name is Mancomb Seepgood",
			[18] = "So what brings you to M�l�e Island� anyway?",
			[19] = "I want to be a pirate!",
			[20] = "I've come seeking my fortune.",
			[21] = "I really don't know.",
			[22] = "None of your business. Goodbye.",
			[23] = "Oh really?",
			[24] = "You should go talk to the important-looking pirates in the next room.",
			[25] = "They're pretty much in charge around here.",
			[26] = "They can tell you where to go and what to do.",
			[27] = "Where can I find the Governor?",
			[28] = "Oh, you Have, have you?",
			[29] = "Well, I am a pirate.",
			[30] = "But, alas, I'm not a captain.",
			[31] = "Governor Marley?",
			[32] = "Her mansion is on the other side of town.",
			[33] = "But pirates aren't as welcome around her place as they used to be.",
			[34] = "Why not?",
			[35] = "I'm welcome everywhere I go.",
			[36] = "I think I'll go there right now. Bye.",
			[37] = "Okay, but watch out for those guard dogs!",
			[38] = "My grog is going flat, so you'll have to excuse me.",
			[39] = "I don't want to come between a pirate and his grog.",
			[40] = "Well, this island has a governor...",
			[41] = "...but we pirates have our own leaders.",
			[42] = "I want to talk to the leaders of the pirates.",
			[43] = "Where can I find the Governor of the island?",
			[44] = "That's nice. Goodbye.",
			[45] = "That's okay.",
			[46] = "Mine is Mancomb Seepgood.",
			[47] = "Sorry to see you go away mad.",
			[48] = "Don't be a stranger.",
			[49] = "So, what was your name, anyway?",
			[50] = "Well, it sure wasn't for the sunshine.",
			[51] = "I think you need some guidance.",
			[52] = "Well, the last time she had a pirate over for dinner, he fell in love with her.",
			[53] = "It's made things rather uncomfortable for everybody.",
			[54] = "How's that?",
			[55] = "Who is this pirate?",
			[56] = "That's too bad. Well, see you later.",
			[57] = "Well, excuse me Mr. Secretive.",
			[58] = "It was none other than the fearsome pirate LeChuck.",
			[59] = "Well, there's a whole big story about what happened next...",
			[60] = "But I don't believe a word of it.",
			[61] = "Estevan over there at the other table might tell you about it.",
			[62] = "He takes the whole thing seriously.",
			[63] = "Very seriously.",
			[64] = "Whatever you say.",
			[65] = "Just watch out for those guard dogs!"
			}
		},
		citizen = {
			text = {	
			[1] = "Excuse me, but do you have a cousin named Sven?",
			[2] = "What?",
			[3] = "No, I don't",
			[4] = "What is that? Some sort of code?",
			[5] = "No, but I once had a barber named Dominique.",
			[6] = "Never mind.",
			[7] = "Good night.",
			[8] = "Excuse me, but do--",
			[9] = "Oh, it's only you again.",
			[10] = "I just want a map",
			[11] = "My cousin Sven sends his regards.",
			[12] = "Could you tell me that code again?",
			[13] = "Never mind. I can get a map somewhere else.",
			[14] = "Wanna bet?",
			[15] = "Now get lost.",
			[16] = "Of course it's a code, you idiot.",
			[17] = "Close enough.",
			[18] = "Let's talk business.",
			[19] = "You want to buy a map to the Legendary Lost Treasure of M�l�e Island�?",
			[20] = "Only one in existence.",
			[21] = "Rare.",
			[22] = "Very rare.",
			[23] = "Only 100 pieces of eight...",
			[24] = "No thanks. I don't have enough money.",
			[25] = "No thanks. I don't want it.",
			[26] = "Well then, buzz off kid, it's bad for business.",
			[27] = "Come back for the map to the Legenrary Lost Treasure of M�l�e Island�, eh?",
			[28] = "I hope you brought enough moneyt this time.",
			[29] = "Shhhhhhh!",
			[30] = "Pipe down, will ya?",
			[31] = "That ugly sheriff might be around here.",
			[32] = "Now, then...",
			[33] = "I see.",
			[34] = "Not enough money, eh?",
			[35] = "Come back when you're serious about treasure hunting, kid."

			}
		},
		lowmoralfiber = {
			text = {
			[1] = "Hey, nice rat!",
			[2] = "How can you stand to be near this vermin?",
			[3] = "Do you guys know the sneaky-looking man on the opposite corner?",
			[4] = "Say, are you guys pirates?",
			[5] = "I'll just be running along, now.",
			[6] = "Do you like rats?",
			[7] = "Yes, I love rats!",
			[8] = "No, I can't stand them.",
			[9] = "Yes, especially in a light wine sauce",
			[10] = "I can't talk about it right now. Got to go.",
			[11] = "They're very intelligent creatures!",
			[12] = "Ha ha ha ha!!",
			[13] = "More intelligent than HIM!",
			[14] = "Why, there's a story around these parts that a bunch of rats actually crewed a ship here from fabled Monkey Island�.",
			[15] = "No, that's not right.",
			[16] = "It was actually a group of monkeys.",
			[17] = "That's amazing!",
			[18] = "That's difficult to believe.",
			[19] = "No way could a bunch of stupid monkeys crew a ship!",
			[20] = "Excuse me, I must be going.",
			[21] = "But true.",
			[22] = "When they arrived, they sold the ship for a pretty penny.",
			[23] = "Only time I've seen anyone get the better of ol'Stan in a deal.",
			[24] = "I thought it was rats...",
			[25] = "Wanna buy a map, eh?",
			[26] = "OUR maps are top quality, not like the birdcage liners you get from that clown across the street.",
			[27] = "No, just kidding.",
			[28] = "These are actually copies of the minutes of the last meeting of the M�l�e Island� PTA.",
			[29] = "Can't even GIVE them away.",
			[30] = "Want one?",
			[31] = "No, thanks.",
			[32] = "No, I must be on my way.",
			[33] = "No, but I'll take one if you give me two pieces of eight.",
			[34] = "Oh, they are not so bad.",
			[35] = "-- squeak --",
			[36] = "Sounds like this guy don't like rats!",
			[37] = "Let's saut� him now!",
			[38] = "I think you'd best leave, boy.",
			[39] = "Ha ha ha ha ha hoo hoo ha ha ha",
			[40] = "I apologize for what I said about rats.",
			[41] = "But it's true.",
			[42] = "OK, that's fair.",
			[43] = "No, we're a wandering circus troupe.",
			[44] = "But this rat scared away the elephant.",
			[45] = "Of course we're pirates!",
			[46] = "You can't buy clothes like these off the rack!",
			[47] = "What do you want?",
			[48] = "What's in the keg?",
			[49] = "Where'd you get that rat?",
			[50] = "Nothing. See you later.",
			[51] = "How come you're on this street corner and not on a ship, looting, pillaging, sacking, that sort of thing?",
			[52] = "Rum.",
			[53] = "Jam.",
			[54] = "Er... rum and jam.",
			[55] = "It's an old pirate favorite, everybody knows that.",
			[56] = "Actually, they were chimps, and they WEREN'T stupid.",
			[57] = "AIEEE!!! Get away!!!",
			[58] = "Well, pirating hasn't been panning out so well for us...",
			[59] = "There are some UNNATURALLY talented pirates in the area right now...",
			[60] = "...operating out of Monkey Island�.",
			[61] = "So we've been pursuing alternate means of self-support.",
			[62] = "We're trying to start up a circus.",
			[63] = "It was working out well, until the rat scared off the elephant.",
			[64] = "Now you've depressed us.",
			[65] = "Go home.",
			[66] = "See? Told you so.",
			[67] = "I'll take those minutes if you give me two pieces of eight."

			}
		},
		voodoolady = {
			text = {
			[1] = "What may I help you with, son?",
			[2] = "My name is Guybrush Threepwood and I'm a mighty pirate.",
			[3] = "Can you read palms? Am I going to be rich?",
			[4] = "Neat place you got here. Guess I'll be on my way.",
			[5] = "I can tell, you grow tired.",
			[6] = "Go, please.",
			[7] = "Yes?",
			[8] = "Wait...",
			[9] = "...don't say anything.",
			[10] = "I can sense your name is...",
			[11] = "...is...",
			[12] = "...Guybrush...",
			[13] = "...Guybrush Nosehair.",
			[14] = "No...",
			[15] = "...Threepwood",
			[16] = "Guybrush Threepwood.",
			[17] = "Am I not right?",
			[18] = "Wow! That was amazing. Do you know any other tricks?",
			[19] = "Lucky guess.",
			[20] = "I do not deal in tricks.",
			[21] = "What I know is the truth.",
			[22] = "So...",
			[23] = "...my mindreading skills tells me it is your future you are interested in.",
			[24] = "Are you certain this is something you really wish to know?",
			[25] = "Yes! Tell me everything that's going to happen to me.",
			[26] = "No! Don't tell me a thing. Life should be unexpected and exciting.",
			[27] = "Suit yourself.",
			[28] = "I've changed my mind about knowing the future... spill it.",
			[29] = "I am getting a vision...",
			[30] = "... I see you taking a voyage, a long voyage.",
			[31] = "I see you captaining a ship.",
			[32] = "Yeah!",
			[33] = "I see...",
			[34] = "What?",
			[35] = "See what?",
			[36] = "I see a giant monkey.",
			[37] = "Yikes!",
			[38] = "I see you inside the giant monkey.",
			[39] = "Gross.",
			[40] = "Wait...",
			[41] = "...it is all becoming clear.",
			[42] = "Your journey will have many parts.",
			[43] = "You will see things better left unseen.",
			[44] = "You will hear things better left unheard.",
			[45] = "You will learn things better left unlearned.",
			[46] = "What kind of things?",
			[47] = "I hate surprises.",
			[48] = "NO!",
			[49] = "The time is not right to know.",
			[50] = "When you know your purpose, come see me...",
			[51] = "...I will let you know then."
			}
		},
		storekeeper = {
			text = {
			[1] = "Waddya want?",
			[2] = "I think I'd just like to browse for now.",
			[3] = "Whatever.",
			[4] = "About this sword...",
			[5] = "About this shovel...",
			[6] = "Okay, but don't put your lips on anything.",
			[7] = "Hey, this ain't no boutique.",
			[8] = "Don't take all day.",
			[9] = "Okay.",
			[10] = "Wake me up if you need anything.",
			[11] = "Be my guest, fancy pants.",
			[12] = "What about it?",
			[13] = "I want it.",
			[14] = "How much is it?",
			[15] = "I don't want it.",
			[16] = "That's 100 pieces of eight.",
			[17] = "Take it or leave it.",
			[18] = "I don't have enough money.",
			[19] = "Figures.",
			[20] = "How else do you want to waste my time?",
			[21] = "I already told you, it's 100 pieces of eight.",
			[22] = "Did you bring enough money this time?",
			[23] = "Another would-be treasure hunter, eh?",
			[24] = "That'll cost you 75 pieces of eight.",
			[25] = "75 pieces of eight? I don't have that much.",
			[26] = "Then you'd better go put it back.",
			[27] = "Is there something here maybe that you CAN afford?",
			[28] = "Same price as the last time you asked me:",
			[29] = "75 pieces of eight.",
			[30] = "Maybe you'd like to pay for that?"
			}
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
    },
	kitchen = {
		[1] = "It's some sort of meat or meatlike substance...",
		[2] = "Someone cooked a headcheese in this.",
		[3] = "I think it's a herring.",
		[4] = "I think that bird will peck my hand off...",
		[5] = "It's boiling hot.",
		[6] = "I think it's full of that foul stuff pirates drink.",
		[7] = "Ouch!",
		[8] = "Got it!",
		[9] = "Hmm. Stewed meat."
	},
	scummbar = {
		[1] = "Cozy.",
		[2] = "I don't want to bother them.",
		[3] = "They're busy listening to the guy on the left.",
		[4] = "I don't think it's wise to wake a sleeping pirate."
	},
	village2 = {
		[1] = "What are YOU looking at?",
		[2] = "There sure are a lot of spelling errors.",
		[3] = "I have",
	},
	voodoolady = {
		[1] = "Actually, I'm not THAT curious to find out what's inside.",
		[2] = "Probably poisonous snakes.",
		[3] = "No thanks, I'd rather not touch any of this creepy voodoo stuff.",
		[4] = "Gee, I wonder what's in these baskets.",
		[5] = "Hmmm... I think I hear slithering inside.",
		[6] = "No thanks. Something would probably jump out and bite me.",
		[7] = "Poor chickens...",
		[8] = "I'd better not. They're probably being saved for a pagan ritual, and I wouldn't want to spoil it.",
		[9] = "Kind of an emaciated Charles Atlas.",
		[10] = "Let's see, there's a jar of bat drippings...",
		[11] = "...a box that says, \"Assorted Scales\"...",
		[12] = "...a shaker full of monkey flakes...",
		[13] = "...and some cat knuckles",
		[14] = "Cat knuckles?!?",
		[15] = "How barbaric!",
		[16] = "No thanks. I can never fall asleep in strange places.",
		[17] = "Looks comfortable, in a spooky sort of way.",
		[18] = "Probably got a body in it.",
		[19] = "Hmmm...",
		[20] = "A rubber chicken with a pulley in the middle...",
		[21] = "What possible use could that have?",
		[22] = "Maybe no one will miss just this one thing...",
		[23] = "Poor little thing...",
		[24] = "Whatever it was.",
		[25] = "Now, THIS is the cup of a carpenter."
	},
	shop = {
		[1] = "Ahoy there, fancy pants.",
		[2] = "Let's go, fancy-pants!",
		[3] = "What do you think this is? A museum?",
		[4] = "I don't have all day.",
		[5] = "Got a good deal on swords right now...",
		[5] = "\"SLASHMASTER� -- When you want a sword as sharp as your wit.\"",
		[6] = "\"DIGMASTER� -- The only shovel for serious treasure-hunting enthusiasts.\""
		
	}
}

strings.dialogues.lookout.randomLookoutMsg = function() 
    return strings.dialogues.lookout.text[43] .. strings.dialogues.lookout.names[math.random(1, #strings.dialogues.lookout.names)] .. "."
end

strings.piecesofeightmsg = function() 
    return strings.village2[3] .. " " .. tostring(inventory["pieceofeight"].qty) .. " " .. strings.objects.piecesofeight
end
    
    
    
