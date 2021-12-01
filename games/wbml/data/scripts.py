import data
from mopy.script import Script
import mopy.actions as act
import example


def init(desc):
    data.globals.start_positions = desc['start_positions']


def setup():
    print('merfda')


def set_warp(player, warp, x, y):
    data.globals.active_warp = warp.getInfo()['warp_to']
    print('setting warp')


def clear_warp(player, warp, x, y):
    data.globals.active_warp = None
    print('clearing warp')


def enter_door(x):
    if data.globals.active_warp:
        s = Script()
        s.add_action(act.SetState(tag='player', state='knock'))
        s.add_action(act.Delay(sec=2))
        s.add_action(act.ChangeRoom(room=data.globals.active_warp))
        example.play(s)