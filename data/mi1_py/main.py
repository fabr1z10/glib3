import sys

sys.path.append('../data')

import lib_py.scumm as scumm
import lib_py.engine as engine

import settings
import text.eng.text as text
import example

example.what.prova()

e = engine.Engine(deviceSize=[320,200], windowSize=[640,400], uiHeight = 56, startRoom='lookout')

e.addShader (engine.ShaderType.unlit_textured)
e.addShader (engine.ShaderType.unlit_color)
e.addShader (engine.ShaderType.text)

e.strings = text.strings

# add verbs and verb sets
scumm.ScummConfig.addVerb (scumm.Verb (id = 'open', text=e.strings['ui']['open'], items=1))


# add fonts
e.addFont (engine.assets.Font('ui', './fonts/monkeysmall.ttf'))

# add spritemodels

e.config['verbs'] = {
    'open': scumm.Verb (text = e.strings['ui']['open'], items = 1),
    'close': scumm.Verb (text = e.strings['ui']['close'], items = 1),
    'push': scumm.Verb (text = e.strings['ui']['push'], items = 1),
    'pull': scumm.Verb (text = e.strings['ui']['pull'], items = 1),
    'walkto': scumm.Verb (text = e.strings['ui']['walkto'], items = 1),
    'pickup': scumm.Verb (text = e.strings['ui']['pickup'], items = 1),
    'talkto': scumm.Verb (text = e.strings['ui']['talkto'], items = 1),
    'give': scumm.Verb (text = e.strings['ui']['close'], items = 2),
}

e.config['verbset'] = [
    [ ['open', 'close', 'push', 'pull', 'walkto', 'pickup', 'talkto', 'give'], 'walkto' ]
]


settings.monkey = e


settings.monkey.title = 'The secret of Monkey Island'

# load rooms
import rooms.lookout
