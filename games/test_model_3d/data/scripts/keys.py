import mopy.monkey as monkey
import example


anims = []
current = 0

def init(model):
    global anims, current
    m = monkey.engine.get_asset(model)
    anims = list(m['animations'].keys())
    current = 0


def on_key():
    global current
    current += 1
    if current >= len(anims):
        current = 0
    print('current anim: ' + anims[current])
    pippo = example.get('sprite')
    pippo.setAnim(anims[current])