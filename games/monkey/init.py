import vars
import monkey
import status
import func

def outside_circus():
    func.set_item_pos('guybrush', 'clearing', (83, 58), 's')
    vars.inventory['pot'] = 1
    monkey.engine.room = 'clearing'


def start():
    func.set_item_pos('guybrush', 'lookout', (240, 42), 'w')
    monkey.engine.room = 'lookout'


def scummbar():
    func.set_item_pos('guybrush', 'scummbar', (0, 0), 'w')
    monkey.engine.room = 'scummbar'

def store():
    func.set_item_pos('guybrush', 'store', status.pos.store_entry , 'e')
    monkey.engine.room = 'store'
