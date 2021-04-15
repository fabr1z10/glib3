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
        l = [monkey.engine.read(m + '40'), monkey.engine.read(m + '41')]
    s.add_action(scumm.actions.EnableUI(False))
    s.add_action(scumm.actions.Say(tag='important_looking_pirate_2', lines=l, font='monkey'))
    s.add_action(scumm.actions.StartDialogue('ilp'))
    example.play(s)


def talkto_scummbar_mancomb(aa,ba):
    s = a.Scripts.walk('scummbar_mancomb')
    # save player pos
    player = example.get('player')
    vars.items[vars.current_player]['pos'] = [player.x, player.y]
    vars.items[vars.current_player]['dir'] = 'n'
    s.add_action(actions.ChangeRoom('mancomb'))
    example.play(s)

lookat_scummbar_mancomb = talkto_scummbar_mancomb

def talkto_scummbar_estevan(aa,ba):
    s = a.Scripts.walk('scummbar_estevan')
    # save player pos
    player = example.get('player')
    vars.items[vars.current_player]['pos'] = [player.x, player.y]
    vars.items[vars.current_player]['dir'] = 's'
    s.add_action(actions.ChangeRoom('estevan'))
    example.play(s)

lookat_scummbar_estevan = talkto_scummbar_estevan


def pappo():
    s = Script()
    s.add_action(scumm.actions.EnableUI(False))
    l = ['$dialogues/mancomb/1', '$dialogues/mancomb/2']
    lines = [monkey.engine.read(x) for x in l]
    s.add_action(scumm.actions.Say(tag='mancomb', lines=lines, animate=False, font='monkey'))
    s.add_action(scumm.actions.StartDialogue('mancomb'))
    example.play(s)

def on_exit_mancomb():
    s = Script()
    s.add_action(actions.ChangeRoom('scummbar'))
    example.play(s)