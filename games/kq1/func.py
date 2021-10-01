import script
import scumm.actions
import example
import status

def walkto(x, y):
    s = script.Script(uid='_main')
    s.add_action(scumm.actions.Walk(pos=[x, y], tag='player'))
    example.play(s)

def toggle_cursor(x,y):
    status.current_action += 1
    if status.current_action >= len(status.actions):
        status.current_action = 0
    if status.actions[status.current_action] == -1:
        status.current_action = 0
    example.get('cursor').setAnim(status.actions[status.current_action])
