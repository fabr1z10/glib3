from lib_py.script import Script
from lib_py.scumm.functions import d3
from lib_py.actions import Animate, Delay,RunScript
from lib_py.scumm.actions import Say
import mi1_py.variables as vars
import lib_py.engine as engine
import example

sl = engine.data['strings']['dialogues']['citizen']

def citi_01():
    vars.knows_map = 1
    return d3 (sl, 
        ['citizen', 'a:talk_e', ('_', 18), 'A:open_jacket', 'a:talk_e_1', ('_', 19), 'a:idle_e_1', 'd:2', 'Ab:open_jacket',
         'a:talk_e', ('_',20), 'a:idle_e', 'A:rollmap', 'a:talk_e_2', ('_', 21, 22), 'Ab:rollmap', 'a:talk_e',
         ('_', 23), 'a:idle_e'])()

def citi1():
    s = Script()
    s.addAction(RunScript(d3 (sl, ['player', ('a',5)], ['citizen', 'a:talk_e', ('_', 17), 'a:idle_e'])()))
    s.addAction(RunScript(citi_01()))
    return s

def citi2(n):
    def f():
        s = Script()
        s.addAction(RunScript(d3 (sl, ['player', ('a', n)], ['citizen', 'a:talk_e', ('_', 29, 30, 31, 32), 'a:idle_e'])()))
        s.addAction(RunScript(citi_01()))
        return s
    return f

def citi3():
    s = Script()
    s.addAction(RunScript(d3 (sl, ['player', ('a',11)], ['citizen', 'a:talk_e', ('_', 33), 'a:idle_e'])()))
    s.addAction(RunScript(citi_01()))
    return s
