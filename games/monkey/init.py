import vars
import monkey
import func

def outside_circus():
    func.set_item_pos('guybrush', 'clearing', (83, 58), 's')
    vars.inventory['pot'] = 1
    monkey.engine.room = 'clearing'


def start():
    func.set_item_pos('guybrush', 'lookout', (240, 42), 'w')
    monkey.engine.room = 'lookout'
