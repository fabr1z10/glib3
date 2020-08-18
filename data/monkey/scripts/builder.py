from lib_py.script import Script
from lib_py.scumm.actions import Say, StartDialogue
from lib_py.actions import ChangeRoom, Animate, Msg
from lib_py.scumm.helper import gt, gd, gv, sv
from lib_py.scumm.scumm import Data, State
from lib_py.engine import data

# this is for dialogue room, specialize for each room
def make_dialogue_2 (pos_player, pos_other, other_id, dialogueLines):
    def f(dialogue):
        def g():
            s = Script()
            color_player = Data.items[State.player]['text_color']
            color_other = Data.items[other_id]['text_color']
            for item in dialogue:
                tag = item[0]            
                pos = pos_player if tag == 'player' else pos_other
                color = color_player if tag =='player' else color_other
                for line in item[1:]:
                    print ('adding action msg ' + str(pos) + '  ' + dialogueLines[line])
                    s.addAction (Msg(text=dialogueLines[line], font='monkey', pos=pos, color = color))
            return s
        return g
    return f

make_dialogue_mancomb = make_dialogue_2( (200, 100, 1), (50, 100, 1), 'mancomb',data['strings']['dialogues']['mancomb'])


def make_dialogue(dialogueId, dialogue):
    def f():
        s = Script()
        for item in dialogue:
            print ('tag = ' + item[0])
            ist = [dialogueId[a] for a in item[1:]]
            print ('tag = ' + str(ist))

            s.addAction (Say(lines=ist, tag=item[0], font='monkey'))
        return s
    return f

def goto(room, pos, dir = None, node = 'walkarea' ):
    def f():
        s = Script()
        if pos is not None:
            Data.putItem (State.player, room, gv(pos), node)
            if dir is not None:
                Data.items[State.player]['dir'] = dir
        s = Script()
        s.addAction (ChangeRoom(room = room))
        return s
    return f