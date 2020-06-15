from lib_py.scumm.scumm import State
from lib_py.scumm.entity import Item, CharItem
import lib_py.scumm.scripts as ssc
from lib_py.scumm.functions import d3
import lib_py.engine as engine
import mi1_py.variables as var
from lib_py.script import Script
from lib_py.actions import RunScript,Animate,SetActive,Scroll,Move,Delay
from lib_py.scumm.actions import EnableControls, Turn

st = engine.data['strings']
