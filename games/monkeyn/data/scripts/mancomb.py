import mopy.scumm.scriptlib as sl
import mopy.scumm.actionlib as al
import mopy.actions as actions
from mopy.script import Script
import mopy
import example
from mopy.util import rgb

def _a(x):
    return '$dialogues/mancomb/' + str(x)

guy_color = (1, 1, 1, 1)
mancomb_color = rgb(255, 85, 85)
guy_pos = (609, 120)
mancomb_pos = (0, 120)
mw = 200.0

def guy_msg(line):
    return actions.Msg(text=_a(line), outline=True, outline_color=(0,0,0,1), thickness=0.5, pos=guy_pos, color=guy_color, max_width=mw)

def mcb_msg(line):
    return actions.Msg(text=_a(line), outline=True, outline_color=(0,0,0,1), thickness=0.5, pos=mancomb_pos, color=mancomb_color,max_width=mw)

def on_init_mancomb():
    s = Script()
    s.add_action(al.start_dialogue('mancomb', False))
    example.play(s)

def on_exit_mancomb():
    s = sl.change_room('scummbar', pos=(120, 20), dir='n')
    return s

def mancomb_0(args):
    s = Script()
    s.add_action(guy_msg('imguy'))
    s.add_action(mcb_msg('9'))
    s.add_action(actions.Animate(anim='smile', tag='mancomb'))
    s.add_action(mcb_msg('10'))
    s.add_action(mcb_msg('11'))
    return s

def mancomb_1(args):
    s = Script()
    s.add_action(guy_msg('rupirate'))
    s.add_action(mcb_msg('29'))
    s.add_action(mcb_msg('30'))
    s.add_action(mcb_msg('24'))
    s.add_action(mcb_msg('25'))
    s.add_action(mcb_msg('26'))
    return s

def mancomb_2(args):
    s = Script()
    s.add_action(guy_msg('charge'))
    s.add_action(mcb_msg('40'))
    s.add_action(mcb_msg('41'))
    return s

def mancomb_3(args):
    s = Script()
    s.add_action(guy_msg('bye'))
    s.add_action(mcb_msg('7'))
    return s


def mancomb_4(args):
    s = Script()
    s.add_action(guy_msg(args[0]))
    s.add_action(mcb_msg('17'))
    s.add_action(mcb_msg('18'))
    return s

def mancomb_19(args):
    s = Script()
    s.add_action(guy_msg('19'))
    s.add_action(mcb_msg('23'))
    s.add_action(mcb_msg('24'))
    s.add_action(mcb_msg('25'))
    s.add_action(mcb_msg('26'))
    return s

def mancomb_20(args):
    s = Script()
    s.add_action(guy_msg('20'))
    s.add_action(mcb_msg('28'))
    s.add_action(mcb_msg('24'))
    s.add_action(mcb_msg('25'))
    s.add_action(mcb_msg('26'))
    return s

def mancomb_21(args):
    s = Script()
    s.add_action(guy_msg('21'))
    s.add_action(mcb_msg('50'))
    s.add_action(mcb_msg('51'))
    s.add_action(mcb_msg('24'))
    s.add_action(mcb_msg('25'))
    s.add_action(mcb_msg('26'))
    return s

def mancomb_22(args):
    s = Script()
    s.add_action(guy_msg('22'))
    s.add_action(mcb_msg('47'))
    s.add_action(mcb_msg('48'))
    return s

def mancomb_17(args):
    s = Script()
    s.add_action(guy_msg('dumb'))
    s.add_action(mcb_msg('45'))
    s.add_action(mcb_msg('46'))
    s.add_action(mcb_msg('18'))
    return s

def mancomb_5(args):
    s = Script()
    s.add_action(guy_msg('leaders'))
    s.add_action(mcb_msg('24'))
    s.add_action(mcb_msg('25'))
    s.add_action(mcb_msg('26'))
    return s

def mancomb_6(args):
    s = Script()
    s.add_action(guy_msg('guvnor2'))
    s.add_action(mcb_msg('31'))
    s.add_action(mcb_msg('32'))
    s.add_action(mcb_msg('33'))
    return s

def mancomb_7(args):
    s = Script()
    s.add_action(guy_msg('nice'))
    s.add_action(mcb_msg('bye'))
    s.add_action(mcb_msg('7'))
    return s


def mancomb_8(args):
    s = Script()
    s.add_action(guy_msg('guvnor'))
    s.add_action(mcb_msg('31'))
    s.add_action(mcb_msg('32'))
    s.add_action(mcb_msg('33'))
    return s

def mancomb_9(args):
    s = Script()
    s.add_action(guy_msg('whynot'))
    s.add_action(mcb_msg('52'))
    s.add_action(mcb_msg('53'))
    return s

def mancomb_10(args):
    s = Script()
    s.add_action(guy_msg('welcome'))
    s.add_action(mcb_msg('64'))
    s.add_action(mcb_msg('65'))
    return s

def mancomb_11(args):
    s = Script()
    s.add_action(guy_msg('welcome'))
    s.add_action(mcb_msg('37'))
    s.add_action(mcb_msg('bye'))
    s.add_action(mcb_msg('7'))
    return s

def mancomb_12(args):
    s = Script()
    s.add_action(guy_msg('howsthat'))
    s.add_action(mcb_msg('59'))
    s.add_action(mcb_msg('60'))
    s.add_action(mcb_msg('61'))
    s.add_action(mcb_msg('62'))
    s.add_action(mcb_msg('63'))
    return s

def mancomb_13(args):
    s = Script()
    s.add_action(guy_msg('whois'))
    s.add_action(mcb_msg('58'))
    s.add_action(mcb_msg('59'))
    s.add_action(mcb_msg('60'))
    s.add_action(mcb_msg('61'))
    s.add_action(mcb_msg('62'))
    s.add_action(mcb_msg('63'))
    return s

def mancomb_14(args):
    s = Script()
    s.add_action(guy_msg('toobad'))
    s.add_action(mcb_msg('bye'))
    s.add_action(mcb_msg('7'))
    return s

def mancomb_15(args):
    s = Script()
    s.add_action(guy_msg('ilikeguy'))
    s.add_action(actions.Animate(anim='idle', tag='mancomb'))

    s.add_action(mcb_msg('16'))
    return s
