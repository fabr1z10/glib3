
require ("dialogues/lookout")

-- this is the basic dialogue
function pippo(f) 
-- clear dialogue 
dialogue = monkey.getEntity("dialogue")
dialogue:clear()
s = f.callback()
monkey.play(s)
end

dialogues = {
    lookout = {
        [1] = {
            lines = {
                [1] = { text = strings.dialogues.lookout[1], nodenext = 2, active = true, click = curry(dialoguesLookout.start, 1) },
                [2] = { text = strings.dialogues.lookout[2], nodenext = 2, active = true, click = curry(dialoguesLookout.start, 2) },
                [3] = { text = strings.dialogues.lookout[3], nodenext = 2, active = true, click = curry(dialoguesLookout.start, 3) },
                [4] = { text = strings.dialogues.lookout[4], nodenext = 2, active = true, click = curry(dialoguesLookout.start, 4) }
            }
        }
    }
}