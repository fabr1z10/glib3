
require ("dialogues/lookout")
require ("dialogues/pirates")
require ("dialogues/dog")
require ("dialogues/loom")
require ("dialogues/estevan")

local d = strings.dialogues.lookout.text
local p = strings.dialogues.pirates.text
local dog = strings.dialogues.dog.text
local loom = strings.dialogues.loom_pirate.text
local est = strings.dialogues.estevan.text

-- this is the basic dialogue
function pippo(f) 
-- clear dialogue 
dialogue = monkey.getEntity("dialogue")
dialogue:cleartext()
-- set the button active to false
print ("Current status = " .. tostring(f.active))
if (f.alwaysActive ~= true) then
    f.active = false
end
print ("Current status = " .. tostring(f.active))
s = f.click()
monkey.play(s)
end

dialogues = {
    lookout = {
        [1] = {
            lines = {
                [1] = { text = d[1], active = true, alwaysActive = true, click = curry(dialoguesLookout.start, 1) },
                [2] = { text = d[2], active = true, alwaysActive = true, click = curry(dialoguesLookout.start, 2) },
                [3] = { text = d[3], active = true, alwaysActive = true, click = curry(dialoguesLookout.start, 3) },
                [4] = { text = d[4], active = true, alwaysActive = true, click = curry(dialoguesLookout.start, 4) },
                [5] = { text = d[46], active = false, alwaysActive = true, click = curry(dialoguesLookout.start, 46) },
				-- [6] = { text = d[10], active = true },
				-- [7] = { text = d[11], active = true },
    --         	[8] = { text = d[12], active = true },
				-- [9] = { text = d[13], active = true },
			}
        },
        [2] = {
        	lines = {
                [10] = { text = d[10], active = true, click = dialoguesLookout.iamguybrush },
                [11] = { text = d[22], active = false, click = dialoguesLookout.whatiswrong },
                [12] = { text = d[47], active = false, click = dialoguesLookout.thatsthreep },
                [20] = { text = d[11], active = true,click = dialoguesLookout.squinky},
                [30] = { text = d[12], active = true, click = dialoguesLookout.iamhere },
                [40] = { text = d[13], active = true, click = dialoguesLookout.whoareu },
                [41] = { text = d[34], active = false, click = dialoguesLookout.govworried },
                [42] = { text = d[38], active = false, click = dialoguesLookout.bat },
                [100] = { text = d[14], active = true, alwaysActive = true, click = dialoguesLookout.goodbye }
            }
        },
        [3] = {
            lines = {}
        }
    },
    pirates = {
		[1] = {
			lines = {
				[1] = { text = p[2], active = true, alwaysActive = true, click = curry(dialoguesPirates.getlost, 2) },
				[2] = { text = p[3], active = true, alwaysActive = true, click = dialoguesPirates.iwanttobeapirate },
				[3] = { text = p[4], active = true, alwaysActive = true, click = curry(dialoguesPirates.getlost, 4) },
				[4] = { text = p[32], active = false, click = dialoguesPirates.masteringSword },
				[5] = { text = p[33], active = false, click = dialoguesPirates.masteringThievery },
				[6] = { text = p[34], active = false, click = dialoguesPirates.treasureHunting },	
				[7] = { text = p[35], active = false, click = dialoguesPirates.pigs },	
				[8] = { text = p[36], active = false, click = dialoguesPirates.grog },	
				[9] = { text = p[37], active = false, click = dialoguesPirates.leave },	
				[10] = { text = p[50], active = false, alwaysActive =true, click = dialoguesPirates.masteringSwordAgain },
				[11] = { text = p[60], active = false, alwaysActive =true, click = dialoguesPirates.masteringThieveryAgain },
				[12] = { text = p[67], active = false, alwaysActive =true, click = dialoguesPirates.treasureHuntingAgain },
			}
		}
	},
	dog = {
		[1] = {
			lines = {
				[1] = {text=dog[2], active =true, alwaysActive = true, click = dialoguesDog.woof },
				[2] = {text=dog[3], active =true, alwaysActive = true, click = dialoguesDog.arf },
				[3] = {text=dog[4], active =true, alwaysActive = true, clcik = dialoguesDog.ruff },
				[4] = {text=dog[5], active =true, click = dialoguesDog.grrr },
			}
		},
		[2] = {
			lines = {
				[5] = {text=dog[14], active=true, click = dialoguesDog.worf},
				[6] = {text=dog[15], active=true, click = dialoguesDog.aroof},
				[7] = {text=dog[16], active=true, click = dialoguesDog.lechuck},
				[8] = {text=dog[17], active=true, click = dialoguesDog.yip},

			}
		}
	},
	loom_pirate = {
		[1] = {
			lines = {
				[1] = { text=loom[2], active=true, click = dialoguesLoom.aye },
				[2] = { text=loom[3], active=true, click = dialoguesLoom.hat },
				[3] = { text=loom[4], active=true, click = dialoguesLoom.loom },
				[4] = { text=loom[5], active=true, alwaysActive = true, click = dialoguesLoom.leave },
				[5] = { text=loom[14], active=false, click = dialoguesLoom.pitch}
			}
		}
	},
	estevan = {
		[1] = {
			lines = {
				[1] = { text=est[2], active=true, click = dialoguesEstevan.iamguybrush },
				[2] = { text=est[3], active=true, click = dialoguesEstevan.darts },
				[3] = { text=est[4], active=true, click = dialoguesEstevan.drink },
				[4] = { text=est[5], active=true, alwaysActive = true, click = dialoguesEstevan.leave },
				[5] = {text =est[9], active=false, click = dialoguesEstevan.eye}
			}
		
		}
	}
}

dialogues.lookout.init = function()
    -- reset to active at each init
    dialogues.lookout[2].lines[30].active = true

end