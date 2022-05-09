### default actions
import mopy
import example
from mopy.script import Script
from mopy.actions import Walk, Turn, Say
import mopy.scumm.scriptlib as sl

def init():
    pass

def walkto_(id, e):
    return sl.walk_to(id)


def lookat_(item_id, entity):
    return sl.walk_and_say(item_id, ['$defaultactions/4'])

def open_(item_id, entity):
    return sl.walk_and_say(item_id, ['$defaultactions/1'])

def close_(item_id, entity):
    return sl.walk_and_say(item_id, ['$defaultactions/2'])

def push_(item_id, entity):
    return sl.walk_and_say(item_id, ['$defaultactions/3'])

def pickup_(item_id, entity):
    return sl.walk_and_say(item_id, ['$defaultactions/5'])

pull_ = push_
talkto_ = close_
turnon_ = close_
turnoff_ = close_
