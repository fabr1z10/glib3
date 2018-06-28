
require ("dialogues/lookout")

local d = strings.dialogues.lookout.text

-- this is the basic dialogue
function pippo(f) 
-- clear dialogue 
dialogue = monkey.getEntity("dialogue")
dialogue:clear()
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
				[6] = { text = d[10], active = true },
				[7] = { text = d[11], active = true },
            	--[8] = { text = d[12], active = true },
				--[9] = { text = d[13], active = true },
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
    	}
    }

dialogues.lookout.init = function()
    -- reset to active at each init
    dialogues.lookout[2].lines[30].active = true

end