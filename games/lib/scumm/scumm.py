import engine as eng
import shader
import os
import example
import yaml

def init_scumm(vars, status):
    print (' === initializing scumm')
    engine = eng.Engine()
    engine.libs.append('scumm')
    engine.vars = status
    print (' === adding shaders... ', end = '')
    engine.add_shader(shader.ShaderType.unlit_textured)
    engine.add_shader(shader.ShaderType.unlit_color)
    engine.add_shader(shader.ShaderType.text)
    print ('OK.')
    items_dir = example.dir + '/items'
    dialogue_dir = example.dir + '/dialogues'
    vars.items = dict()
    vars.dialogues = dict()
    vars.items_in_room = dict()

    if os.path.isdir(items_dir):
        print (' === items directory found. Loading items ...', end='')
        for filename in os.listdir(items_dir):
            with open(items_dir+ '/' +filename) as f:
                vars.items.update(yaml.load(f, Loader=yaml.FullLoader))
        print ('OK. (' + str(len(vars.items)) + ')')
    else:
        print (' === no items found.')

    if os.path.isdir(dialogue_dir):
        print (' === dialogues directory found. Loading dialogues ...', end='')
        for filename in os.listdir(dialogue_dir):
            with open(dialogue_dir+ '/' +filename) as f:
                vars.dialogues.update(yaml.load(f, Loader=yaml.FullLoader))
        print ('OK. (' + str(len(vars.dialogues)) + ')')
    else:
        print (' === no dialogues found.')
    # initialize room <-> items map
    print (' === setting room -> item map... ', end='')
    for k, v in vars.items.items():
        if 'room' in v:
            if v['room'] not in vars.items_in_room:
                vars.items_in_room[v['room']] = set()
            vars.items_in_room[v['room']].add(k)
    print ('OK.')
    return engine