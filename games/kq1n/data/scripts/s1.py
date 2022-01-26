from mopy.actions import Msg
from mopy.script import Script
import mopy
from mopy.entity import TextAlignment
from mopy.scumm.actionlib import sierra_enable_controls
from mopy.scumm.scriptlib import sierra_msg


def look_001_moat(it, en): return sierra_msg('$msg/1')
def look_001_portcullis(it, en): return sierra_msg('$msg/3')
def look_001_urns(it, en): return sierra_msg('$msg/4')
def look_01(a, b): return sierra_msg('$msg/2')


def add_shade(player, entity, x, y):
    player.setColor((0.4, 0.4, 0.4, 1), (0, 0, 0, 0))


def rm_shade(player, entity, x, y):
    player.setColor((1.0, 1.0, 1.0, 1.0), (0, 0, 0, 0))