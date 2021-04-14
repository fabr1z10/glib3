from . import shared as a

import scumm.actions
import example
import entity
from script import Script
import actions
import status
import monkey
import vars


lookat_scummbar_fireplace = a.Actions.say(['$lines/3'])


def talkto_important_looking_pirates(aa, ba):
    s = a.Scripts.walk('important_looking_pirates')

    m = '$dialogues/important_looking_pirates/'
    if status.pirates_know_guybrush == 0:
        l = [monkey.engine.read(m+'1')]
    else:
        l = [monkey.engine.read(m + '1')]
    s.add_action(scumm.actions.Say(tag='important_looking_pirate_2', lines=l, font='monkey'))
    s.add_action(scumm.actions.StartDialogue('ilp'))
    example.play(s)