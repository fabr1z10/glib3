import scripts.actions.shared as a
import scumm.actions
import example
import entity
from script import Script
import actions
import status
import monkey
import vars

lookat_scummbar_fireplace = a.Actions.say(['$lines/3'])
def talkto_important_looking_pirates(a,b):
    example.get('ui').setActive(False)
    example.get('inventory').setActive(False)
    dial = example.get('dialogue')
    dial.setActive(True)
    start_node = 'root'
    dialogue = vars.dialogues['mancomb']
    node = dialogue['nodes'][start_node]
    lines = dialogue['lines']
    print ('*******')
    for l in node['lines']:
        line = monkey.engine.read(lines[l]['text'])
        dial.appendText(line)
        print(line)
    print ('*******')
    print ('suca')