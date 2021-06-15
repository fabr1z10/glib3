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


def init_basement():
    if not status.basement_light_on:
        a.toggle_light('basement_light_on', False)()
    example.get('circuit_breakers').setActive(vars.items['fuse_box']['anim']=='open')

def turnon_basement_light_switch(item_id, entity):
    s = a.Scripts.walk(item_id)
    s.add_action(actions.CallFunc(f=a.toggle_light('basement_light_on', True)))
    example.play(s)



def turnoff_basement_light_switch(item_id, entity):
    s = a.Scripts.walk(item_id)
    s.add_action(actions.CallFunc(f=a.toggle_light('basement_light_on', False)))
    example.play(s)

def activateBreakers(value):
    def f():
        example.get('circuit_breakers').setActive(value)
    return f

def open_fuse_box(item_id, entity):
    s = a.Scripts.walk(item_id)
    s.add_action(actions.CallFunc(f=a.openDoor(item_id, 'open')))
    s.add_action(actions.CallFunc(f=activateBreakers(True)))
    example.play(s)


def close_fuse_box(item_id, entity):
    s = a.Scripts.walk(item_id)
    s.add_action(actions.CallFunc(f=a.openDoor(item_id, 'closed')))
    s.add_action(actions.CallFunc(f=activateBreakers(True)))
    example.play(s)



walkto_path_basement_entry = a.Actions.goto_room('entry', [459, 21], 's')
read_furnace = a.Actions.say(['$lines/3'])
read_nuclear_reactor = a.Actions.say(['$lines/3'])
read_circuit_breakers = a.Actions.say(['$lines/12'])
read_slime = a.Actions.say(['$lines/13'])
pickup_slime = a.Actions.say(['$lines/13'])
pickup_silver_key = a.Actions.pickup()