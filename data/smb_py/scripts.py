import example
from lib_py.script import Script
from lib_py.actions import Delay,SetState,Move,CallFunc, ChangeRoom
from lib_py.entity import Sprite
from lib_py.components import SmartCollider, Info
import smb_py.vars as vars

def cippo():
    print ('ciappo')
    example.get('w1').setActive(False)
    s = Script()
    s.addAction (SetState(tag='player', state='pipe'))
    s.addAction (Move(tag='player', speed=50, by=[0,64]))
    s.addAction (SetState(tag='player', state='walk'))
    example.play(s)


def pickupCoin(p,k,x,y):
    example.remove(k.id())
    vars.coins += 1
    example.get('coin_label').setText ('{:02d}'.format(vars.coins))

def pipe_out(p : example.Wrap1,k,x,y):
    p.setState ('demo', {'left':0})
    addInfo = k.getInfo()['info']
    s = Script()
    from smb_py.funcs import gotoWorld
    s.addAction(Delay(sec=0.5))
    s.addAction (CallFunc (gotoWorld(addInfo['world'], addInfo['pos'])))
    example.play(s)

def winSlide(p:example.Wrap1,k,x,y):
    example.remove(k.id())
    p.setState('slide',{})
    s = Script()
    p.vy = 0
    s.addAction (Move(speed=50, to=[p.x, 48], tag='player'))   
    s.addAction (SetState (tag='player', state='demo', args={'left': 0}))
    example.play(s) 

def gotoNext(p:example.Wrap1,k: example.Wrap1,x,y):
    #print (k.getInfo())
    addInfo = k.getInfo()['info']
    #print('world is ' + ['world'])
    example.remove(k.id())
    p.setActive(False)
    s = Script()
    from smb_py.funcs import gotoWorld
    s.addAction(Delay(sec=0.5))
    s.addAction (CallFunc (gotoWorld(addInfo['world'], addInfo['pos'])))
    example.play(s)
