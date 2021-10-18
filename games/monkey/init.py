import vars
import monkey
import status
import func

def outside_circus():
    func.set_item_pos('guybrush', 'clearing', (83, 58), 's')
    vars.inventory['pot'] = 1
    monkey.engine.room = 'clearing'


def start():
    func.set_item_pos('guybrush', 'forest6', (240, 42), 'w')
    monkey.engine.room = 'forest6'

def village():
    func.set_item_pos('guybrush', 'village2', (240, 42), 'w')
    monkey.engine.room = 'village2'

def kitchen():
    func.set_item_pos('guybrush', 'kitchen', (0,0), 'w')
    monkey.engine.room = 'kitchen'

def scummbar():
    func.set_item_pos('guybrush', 'scummbar', (0, 0), 'w')
    monkey.engine.room = 'scummbar'

def store():
    func.set_item_pos('guybrush', 'store', status.pos.store_entry , 'e')
    vars.inventory['pieces_of_eight'] = 478

    monkey.engine.room = 'store'
