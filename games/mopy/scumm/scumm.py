import mopy.engine as eng
import mopy.shader as shader
import os
import example
import yaml
import sys


def init(data, scripts):
    print(' === initializing scumm')
    engine = eng.Engine(data=data, scripts=scripts)
    engine.libs.append('scumm')

    print (' === adding shaders... ', end = '')
    engine.add_shader(shader.ShaderType.unlit_textured)
    #engine.add_shader(shader.ShaderType.unlit_color)
    #engine.add_shader(shader.ShaderType.text)
    print ('OK.')

    items_dir = example.dir + '/items'
    dialogue_dir = example.dir + '/dialogues'

    engine.data.items = dict()
    engine.data.dialogues = dict()
    engine.data.items_in_room = dict()

    if os.path.isdir(items_dir):
        print (' === items directory found. Loading items ...', end='')
        for filename in os.listdir(items_dir):
            with open(items_dir+ '/' +filename) as f:
                engine.data.items.update(yaml.load(f, Loader=yaml.FullLoader))
        print ('OK. (' + str(len(engine.data.items)) + ')')
    else:
        print (' === no items found.')

    if os.path.isdir(dialogue_dir):
        print (' === dialogues directory found. Loading dialogues ...', end='')
        for filename in os.listdir(dialogue_dir):
            with open(dialogue_dir+ '/' +filename) as f:
                engine.data.dialogues.update(yaml.load(f, Loader=yaml.FullLoader))
        print ('OK. (' + str(len(engine.data.dialogues)) + ')')
    else:
        print (' === no dialogues found.')
    # initialize room <-> items map
    print (' === setting room -> item map... ', end='')
    for k, v in engine.data.items.items():
        if 'room' in v:
            if v['room'] not in engine.data.items_in_room:
                engine.data.items_in_room[v['room']] = set()
            engine.data.items_in_room[v['room']].add(k)
    print ('OK.')
    return engine