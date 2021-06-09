from . import shared as a
import scumm.actions
import example
import entity
from script import Script
import actions
import status
import monkey
import vars

# one-object actions


def init_frontdoor():
    b = example.get('key')
    if b.valid:
        if example.get('doormat').anim == 'closed':
            b.setActive(False)


def pickup_bushes(item_id, entity):
    s = a.Scripts.walk(item_id)
    s.add_action(actions.RemoveEntity(tag=item_id))
    example.play(s)


def setMat(state):
    def f():
        example.get('doormat').setAnim(state)
        vars.items['doormat']['anim'] = state
        b = example.get('key')
        if b.valid:
            b.setActive(state[0] == 'o')
    return f

def openDoor(item_id, state):
    def f():
        example.get(item_id).setAnim(state)
        vars.items[item_id]['anim']=state
    return f

def pull_doormat(item_id, entity):
    s = a.Scripts.walk(item_id)
    if example.get(item_id).anim == 'closed':
        s.add_action(actions.CallFunc(f=setMat('open')))
    example.play(s)

def use_key_front_door(item_id, entity):
    s = a.Scripts.walk(entity)
    s.add_action(actions.CallFunc(f=openDoor(entity, 'open')))
    status.front_door_open = True
    example.play(s)

def open_front_door(item_id, entity):
    if not status.front_door_open:
        a.Actions.say(['$lines/4'])(item_id, entity)
    else:
        s = a.Scripts.walk(item_id)
        s.add_action(actions.CallFunc(f=openDoor(item_id, 'open')))
        example.play(s)

def close_front_door(item_id, entity):
    s = a.Scripts.walk(item_id)
    s.add_action(actions.CallFunc(f=openDoor(item_id, 'closed')))
    example.play(s)

def walkto_front_door(item_id, entity):
    if example.get(item_id).anim == 'open':
        a.Actions.goto_room('entry', [0, 0], 'e')(item_id, entity)
    else:
        s = a.Scripts.walk(item_id)
        example.play(s)

def push_doormat(item_id, entity):
    s = a.Scripts.walk(item_id)
    if example.get(item_id).anim == 'open':
        s.add_action(actions.CallFunc(f=setMat('closed')))
    example.play(s)


open_grating = a.Actions.say(['$lines/3'])
read_doorbell = a.Actions.say(['$lines/5','$lines/6','$lines/7'])
pickup_key = a.Actions.pickup()