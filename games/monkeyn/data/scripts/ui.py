from mopy.script import Script


def walkto(x, y):
    s = Script(uid='_main')
    s.add_action(scumm.actions.Walk(pos=[x, y], tag='player'))
    example.play(s)