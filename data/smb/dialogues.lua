
require ("dialogues/lookout")
require ("dialogues/pirates")
require ("dialogues/dog")
require ("dialogues/loom")
require ("dialogues/estevan")
require ("dialogues/mancomb")
require ("dialogues/citizen")
require ("dialogues/lowmoralfiber")
require ("dialogues/voodoolady")
require ("dialogues/storekeeper")
require ("dialogues/fettbros")

local d = strings.dialogues.lookout.text
local p = strings.dialogues.pirates.text
local dog = strings.dialogues.dog.text
local loom = strings.dialogues.loom_pirate.text
local est = strings.dialogues.estevan.text
local ms = strings.dialogues.mancomb.text
local ct = strings.dialogues.citizen.text
local lmf = strings.dialogues.lowmoralfiber.text
local v = strings.dialogues.voodoolady.text
local sk = strings.dialogues.storekeeper.text
local fb = strings.dialogues.fettbros.text

-- this is the basic dialogue handler
function onDialogueButtonClick(f) 
	-- clear dialogue 
	dialogue = monkey.getEntity("dialogue")
	dialogue:cleartext()
	-- set the button active to false
	--print ("Current status = " .. tostring(f.active))
	if (f.alwaysActive ~= true and type(f.active) ~= "function") then
    	f.active = false
	end
	--print ("Current status = " .. tostring(f.active))
	local s = f.click()
	--s:push { script = f.click() }
	--s = f.click()
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
	},
	mancomb = {
		[1] = {
			lines = {
				[1] = { text=ms[3], active=true, click = dialoguesMancomb.guybrush },
				[2] = { text=ms[4], active=true, click = dialoguesMancomb.crew },
				[3] = { text=ms[5], active=true, alwaysActive = true, click = dialoguesMancomb.charge },
				[4] = { text=ms[6], active=true, alwaysActive = true, click = dialoguesMancomb.leave },
				[5] = { text=ms[27], active=false, click = curry(dialoguesMancomb.governor, 27) },
				[6] = { text=ms[49], active=false, click = dialoguesMancomb.whatwasyourname },
			}
		},
		[2] = {
			lines = {
				[1] = {text=ms[12], active=true, click = dialoguesMancomb.ilikeguybrush },
				[2] = {text=ms[13], active=true, click = dialoguesMancomb.yourname },
				[3] = {text=ms[14], active=true, click = dialoguesMancomb.dumbname },
				[4] = {text=ms[15], active=true, click = dialoguesMancomb.insulted },
			}
		},
		[3] = {
			lines = {
				[1] = {text=ms[19], active=true, click = dialoguesMancomb.pirate },
				[2] = {text=ms[20], active=true, click = dialoguesMancomb.fortune },
				[3] = {text=ms[21], active=true, click = dialoguesMancomb.dontknow },
				[4] = {text=ms[22], active=true, click = dialoguesMancomb.noneofyourbusiness },
			}
		},
		[4] = {
				[1] = {text=ms[34], active=true, click = dialoguesMancomb.whynot },
				[2] = {text=ms[35], active=true, click = dialoguesMancomb.iamwelcome },
				[3] = {text=ms[36], active=true, click = dialoguesMancomb.gothere },
		},
		[5] = {
				[1] = {text=ms[42], active=true, click = dialoguesMancomb.pirateleaders },
				[2] = {text=ms[43], active=true, click = curry(dialoguesMancomb.governor, 43) },
				[3] = {text=ms[44], active=true, click = dialoguesMancomb.leave2 },
		},
		[6] = {
				[1] = {text=ms[54], active=true, click = dialoguesMancomb.howsthat},
				[2] = {text=ms[55], active=true, click = dialoguesMancomb.whoisthispirate},
				[3] = {text=ms[56], active=true, click = dialoguesMancomb.leave4 },
		},


	},
	citizen = {
		[1] = {
			lines = {
				[1] = { text = ct[2], active = true, click = curry(dialoguesCitizen.what, 2) },
				[2] = { text = ct[3], active = true, click = curry(dialoguesCitizen.what, 3) },
				[3] = { text = ct[4], active = true, click = dialoguesCitizen.code },
				[4] = { text = ct[5], active = true, click = dialoguesCitizen.dominique },

			}
		},
		[2] = {
			lines = {
				[1] = { text = ct[10], active = true, click = curry(dialoguesCitizen.wantmap, 10) },
				[2] = { text = ct[11], active = true, click = dialoguesCitizen.sven },
				[3] = { text = ct[12], active = true, click = curry(dialoguesCitizen.wantmap, 12) },
				[4] = { text = ct[13], active = true, click = dialoguesCitizen.somewhereelse },
			}	
		},
		[3] = {
			lines = {
				[1] = { text = ct[24], active = true, alwaysActive = true, click = dialoguesCitizen.nomoney },
				[2] = { text = ct[25], active = true, alwaysActive = true, click = dialoguesCitizen.nowant },
			}	
		}
	},
	lowmoralfiber = {
		[1] = {
			lines = {
				[1] = { text = lmf[1], active = true, click = curry(dialoguesLowmoralfiber.nicerat, 1) },
				[2] = { text = lmf[2], active = true , click = dialoguesLowmoralfiber.vermin},
				[3] = { text = lmf[3], active = true, click = dialoguesLowmoralfiber.sneaky },
				[4] = { text = lmf[4], active = true, click = dialoguesLowmoralfiber.areyoupirates },
				[5] = { text = lmf[5], active = true, click = curry(dialoguesLowmoralfiber.leave, 5) },
				[6] = { text = lmf[40], active = false, click = curry(dialoguesLowmoralfiber.intelligentrats, 40) },
				[7] = { text = lmf[67], active = false, click = curry(dialoguesLowmoralfiber.getminutes, 67) }
			}
		},
		[2] = {
			lines = {
				[1] = { text = lmf[7], active = true, click = curry(dialoguesLowmoralfiber.intelligentrats, 7) },
				[2] = { text = lmf[8], active = true, click = curry(dialoguesLowmoralfiber.intelligentrats, 8) },
				[3] = { text = lmf[9], active = true, click = dialoguesLowmoralfiber.winesauce },
				[4] = { text = lmf[10], active = true, click = curry(dialoguesLowmoralfiber.leave, 10) },
			}
		},
		[3] = {
			lines = {
				[1] = { text = lmf[17], active = true, click = curry(dialoguesLowmoralfiber.amazing, {17, 21}) },
				[2] = { text = lmf[18], active = true, click = curry(dialoguesLowmoralfiber.amazing, {18, 41}) },
				[3] = { text = lmf[19], active = true, click = curry(dialoguesLowmoralfiber.amazing, {19, 56}) },
				[4] = { text = lmf[20], active = true, click = curry(dialoguesLowmoralfiber.leave, 20) },
			}
		},
		[4] = {
			lines = {
				[1] = { text = lmf[31], active = true, click = dialoguesLowmoralfiber.nothanks },
				[2] = { text = lmf[32], active = true, click = dialoguesLowmoralfiber.onmyway },
				[3] = { text = lmf[33], active = true, click = curry(dialoguesLowmoralfiber.getminutes, 33) },

			}
		},
		[5] = {
			lines = {
				[1] = { text = lmf[48], active = true, click = dialoguesLowmoralfiber.keg },
				[2] = { text = lmf[49], active = true, click = curry(dialoguesLowmoralfiber.nicerat, 49) },
				[3] = { text = lmf[50], active = true, click = curry(dialoguesLowmoralfiber.leave, 50)},
				[4] = { text = lmf[51], active = true, click = dialoguesLowmoralfiber.pillage },

			}
		},
	},
	voodoolady = {
		[1] = {
			lines = {
				[1] = { text = v[2], active = true, click = dialoguesVoodooLady.myname },
				[2] = { text = v[3], active = true, click = dialoguesVoodooLady.future },
				[3] = { text = v[4], active = true, alwaysActive = true, click = dialoguesVoodooLady.leave},
				[4] = { text = v[28], active = false, click = dialoguesVoodooLady.changedmind },
			}
		},
		[2] = {
			lines = {
				[1] = { text = v[18], active = true, click = dialoguesVoodooLady.tricks },
				[2] = { text = v[19], active = true},
			}
		},
		[3] = {
			lines = {
				[1] = { text = v[25], active = true, click = dialoguesVoodooLady.yes },
				[2] = { text = v[26], active = true, click = dialoguesVoodooLady.no },
			}
		},
	},
	storekeeper = {
		[1] = {
			lines = {
			[1] = { text = sk[4], active = function() return inventory["sword"] ~= nil end, click = dialoguesStorekeeper.sword },
			[2] = { text = sk[5], active = function() return inventory["shovel"] ~= nil end, click = dialoguesStorekeeper.shovel },
			[3] = { text = sk[2], active = true, alwaysActive=true, click = dialoguesStorekeeper.leave }
			}
		},
		[2] = {
			lines = {
			[1] = { text = sk[13], active = true, alwaysActive = true, click = curry(dialoguesStorekeeper.iwantsword, 13) },
			[2] = { text = sk[14], active = true, alwaysActive = true, click = curry(dialoguesStorekeeper.iwantsword, 14) },
			[3] = { text = sk[15], active = true, alwaysActive = true, click = curry(dialoguesStorekeeper.nomoney, 15) },
			}
		},
		[3] = {
			lines = {
			[1] = { text = sk[18], active = true, alwaysActive = true, click = curry(dialoguesStorekeeper.nomoney, 18) },
			[2] = { text = sk[15], active = true, alwaysActive = true, click = curry(dialoguesStorekeeper.nomoney, 15) }
			}
		},
		[4] = {
			lines = {
			[1] = { text = sk[13], active = true, alwaysActive = true, click = curry(dialoguesStorekeeper.iwantshovel, 13) },
			[2] = { text = sk[14], active = true, alwaysActive = true, click = curry(dialoguesStorekeeper.iwantshovel, 14) },
			[3] = { text = sk[15], active = true, alwaysActive = true, click = curry(dialoguesStorekeeper.nomoneyshovel, 15) },
			}
		},
		[5] = {
			lines = {
			[1] = { text = sk[25], active = true, alwaysActive = true, click = curry(dialoguesStorekeeper.nomoneyshovel, 25) },
			[2] = { text = sk[15], active = true, alwaysActive = true, click = curry(dialoguesStorekeeper.nomoneyshovel, 15) }
			}
		},
	},
	fettbros = {
		[1] = {
			lines = {
			[1] = { text = fb[29], active=true, alwaysActive = true, click = curry(dialoguesFettBros.ahem, 29) },
			[2] = { text = fb[30], active=true, alwaysActive = true, click = curry(dialoguesFettBros.ahem, 30) },
			[3] = { text = fb[31], active=true, alwaysActive = true, click = curry(dialoguesFettBros.ahem, 31) },
			[4] = { text = fb[32], active=true, alwaysActive = true, click = curry(dialoguesFettBros.ahem, 32) },
			[5] = { text = fb[33], active=true, alwaysActive = true, click = curry(dialoguesFettBros.ahem, 33) },
			}
		},
		[2] = {
			lines = {
			[1] = { text = fb[61], active=true, alwaysActive = true, click = dialoguesFettBros.doit },
			[2] = { text = fb[62], active=true, alwaysActive = true, click = dialoguesFettBros.howmuch },
			[3] = { text = fb[63], active=true, alwaysActive = true, click = curry(dialoguesFettBros.noway, 63) },
			}
		},
		[3] = {
			lines = {
			[1] = { text = fb[65], active=true, click = dialoguesFettBros.ahem },
			[2] = { text = fb[66], active=true, alwaysActive = true, click = curry(dialoguesFettBros.noway, 66)  },
			}
		},
		[4] = {
			lines = {
			[1] = { text = fb[71], active=true, click = dialoguesFettBros.nohelmet },
			[2] = { text = fb[72], active=true, alwaysActive = true, click = dialoguesFettBros.ihavehelmet  },
			}
		}
	}
}

dialogues.lookout.init = function()
    -- reset to active at each init
    dialogues.lookout[2].lines[30].active = true

end