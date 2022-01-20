import example
import yaml
import os
import mopy.font as font
import mopy.monkey as monkey
import sys
import mopy.factories.scumm
import mopy.factories.basicroom
import mopy.factories.items
import copy
import operator
from collections import defaultdict
import mopy.scumm

def scumm_init(engine):
    engine.add_room_factory('scumm.room', mopy.factories.scumm.default_room)
    engine.add_item_factory('scumm.bg', mopy.factories.scumm.bg)
    engine.add_item_factory('scumm.walkarea', mopy.factories.scumm.walkarea)
    engine.data.items = {}
    engine.data.dialogues= {}
    engine.data.r2i = defaultdict(list)
    engine.data.i2r = {}
    root_dir = example.dir + '/items'
    dial_dir = example.dir + '/dialogues'
    n = len(root_dir) + 1

    for subdir, dirs, files in os.walk(root_dir):
        for f in files:
            filepath = subdir + os.sep + f
            prefix = filepath[n:-5].replace('/', '.') + '.'
            with open(filepath) as fi:
                if filepath[-4:] == 'yaml':
                    print(filepath)
                    cip = yaml.load(fi, Loader=yaml.FullLoader)
                    if cip:
                        for key, value in cip.items():
                            item_id = prefix + key
                            engine.data.items[item_id] = value
                            room = value.get('room')
                            if room:
                                engine.data.r2i[room].append(item_id)
                                engine.data.i2r[item_id] = room
    for subdir, dirs, files in os.walk(dial_dir):
        for f in files:
            filepath = subdir + os.sep + f
            prefix = filepath[n:-5].replace('/', '.') + '.'
            with open(filepath) as fi:
                if filepath[-4:] == 'yaml':
                    cip = yaml.load(fi, Loader=yaml.FullLoader)
                    if cip:
                        for key, value in cip.items():
                            engine.data.dialogues[key] = value
                            print('loaded dialogue: ' + key)
    mopy.scumm.gl = engine.data.globals
    print(' i am here ' + str(mopy.scumm.gl))

initializers = {
    'scumm': scumm_init
}

# data is a module that contain game variables, configuration and scripts
class Engine:
    def __init__(self, data=None):
        sys.path.append(example.dir)
        self.data = data
        example.init(example.what)
        monkey.engine = self
        with open(example.dir + '/main.yaml') as f:
            a = yaml.load(f, Loader=yaml.FullLoader)
            self.lang = a['lang']
            self.device_size = tuple(a['device_size'])
            self.window_size = tuple(a['window_size'])
            self.tick_multiplier = a.get('tick_multiplier', 1.0)
            self.room = a['start_room']
            self.title = a['title']
            print(' === loading strings ...', end='')
            self.load_strings()
            print(' OK.')
            # read game variables, and functions
            for file in a.get('fonts', []):
                self.add_font(file['id'], file['file'])
            for shader in a.get('shaders', []):
                self.add_shader(shader)
        # loading assets
        self.load_assets()
        game_type = a.get('type', 'default')
        print('the game type is ' + game_type)
        if game_type != 'default':
            initializers[game_type](self)

        self.add_room_factory('_basic', mopy.factories.basicroom.BasicRoom.make)

        self.add_item_factory('_model3d', mopy.factories.items.model3d)
        self.add_item_factory('_entity', mopy.factories.items.entity)
        self.add_item_factory('_text', mopy.factories.items.text)
        self.add_item_factory('_fps_counter', mopy.factories.items.fps_counter)
        self.add_item_factory('_player2D', mopy.factories.items.player2D)
        self.add_item_factory('_player3D', mopy.factories.items.player3D)
        self.add_item_factory('_rect', mopy.factories.items.rect_platform)
        self.add_item_factory('_line', mopy.factories.items.line_platform)
        self.add_item_factory('_poly', mopy.factories.items.poly_platform)
        self.add_item_factory('_prism_3d', mopy.factories.items.rect_platform_3d)
        self.add_item_factory('_box_3d', mopy.factories.items.box_platform_3d)
        self.add_item_factory('_directional_light', mopy.factories.items.dir_light)

    @staticmethod
    def open_data_file(filename):
        with open(example.dir + '/' + filename) as f:
            a = yaml.load(f, Loader=yaml.FullLoader)
            return a

    def add_shader(self, shader):
        self.shaders.append(shader)

    def add_font(self, uid, file):
        self.assets['fonts'][uid] = font.Font(uid, file)

    def load_assets(self):
        root_dir = example.dir + '/assets'
        n = len(root_dir) + 1
        for subdir, dirs, files in os.walk(root_dir):
            for f in files:
                filepath = subdir + os.sep + f
                prefix = filepath[n:-5].replace('/', '.') + '.'
                with open(filepath) as fi:
                    if filepath[-4:] == 'yaml':
                        print(filepath)
                        cip = yaml.load(fi, Loader=yaml.FullLoader)
                        if cip:
                            for key, value in cip.items():
                                print (prefix + " " + key)
                                self.assets[prefix + key] = value
        # for key, value in self.assets.items():
        #     print(key + ':')

    def load_strings(self):
        directory = example.dir + '/text/' + self.lang;
        if os.path.exists(directory):
            with open(directory + '/text.yaml', encoding='utf8') as f:
                self.assets['strings'] = yaml.load(f, Loader=yaml.FullLoader)

    def create_room(self):
        print('Hey, creating room: ' + self.room)
        filename = example.dir + '/rooms/' + self.room + '.yaml'
        try:
            with open(filename) as f:
                room = yaml.load(f, Loader=yaml.FullLoader)
                rt = room['type']
                if 'on_start' in room:
                    getattr(self.scripts, room['on_start'])()
                # check if a factory exists for this room type
                factory = self.factories['rooms'].get(rt, None)
                if factory is None:
                    print('Unable to find factory for room type: ' + rt)
                    exit(1)
                return factory(room)
        except EnvironmentError as error:
            print(error)
            exit(1)

    def set(self, id, value):
        if isinstance(id, str):
            cc = self.data
            d = id.split('.')
            for b in d[:-1]:
                cc = getattr(cc, b)
            print('current value = ' + str(getattr(cc, d[-1])))
            setattr(cc, d[-1], value)
            print('current value = ' + str(getattr(cc, d[-1])))

    # read a string
    def read(self, value):
        if isinstance(value, str):
            if value[0] == '@':
                c = value[1]
                if c == '@':
                    return value[1:]
                else:
                    # get a variable
                    cc = self.data
                    for b in value[1:].split('/'):
                        cc = getattr(cc, b)
                    # if the value is a function, call it
                    if callable(cc):
                        return cc()
                    else:
                        return cc
            elif value[0] == '$':
                c = value[1]
                if c == '$':
                    return value[1:]
                else:
                    # get a string
                    cc = self.assets['strings']
                    for b in value[1:].split('/'):
                        cc = cc[int(b) if b.isdigit() else b]
                    return cc
        return value

    def add_room_factory(self, uid: str, f: callable):
        self.factories['rooms'][uid] = f

    def add_item_factory(self, uid: str, f: callable):
        self.factories['items'][uid] = f

    def get_room_factory(self, uid: str):
        return self.factories['rooms'].get(uid, None)

    def get_item_factory(self, uid: str):
        return self.factories['items'].get(uid, None)

    def get_sprite_model(self, uid: str):
        print ('HALLLO')
        exit(1)

    def get_next_tag(self):
        tag = '__' + str(self.taggen)
        self.taggen += 1
        return tag

    def _repl(self, a, index, value, args):
        if isinstance(value, str):
            if value[0] == '#' and value[1] != '#':
                a[index] = args[int(value[1:])]
            elif value[0] == '@' and value[1] != '@':
                print(' *** reading variable: ' + value[1:])
                a[index] = operator.attrgetter(value[1:])(monkey.engine.data)
                print(str(a[index]) + ' is da valu')
            elif value[0] == '$' and value[1] != '$':
                print(' *** reading str: ' + value[1:])
                # get a string
                cc = self.assets['strings']
                for b in value[1:].split('/'):
                    cc = cc[int(b) if b.isdigit() else b]
                print (' *** valuf is ' + cc)
                a[index] = cc




    def replace(self, a, args):
        if isinstance(a, dict):
            for k, v in a.items():
                if isinstance(v, dict) or isinstance(v, list):
                    self.replace(v, args)
                else:
                    self._repl(a, k, v, args)
                    # print(v)
                    # if isinstance(v, str) and v[0] == '@':
                    #     print(args)
                    #     a[k] = args[int(v[1:])]
        elif isinstance(a, list):
            for i in range(0, len(a)):
                if isinstance(a[i], dict) or isinstance(a[i], list):
                    self.replace(a[i], args)
                else:
                    self._repl(a, i, a[i], args)
                    #if isinstance(a[i], str) and a[i][0] == '@':
                    #    a[i] = args[int(a[i][1:])]


    def repl_vars(self, dict, args=None):
        b = copy.deepcopy(dict)
        self.replace(b, args)
        return b

    def get_asset(self, id, args=None):
        if not args:
            return self.repl_vars(self.assets[id])
        else:
            b = copy.deepcopy(self.assets[id])
            self.replace(b, args)
            return b

    scripts = None
    shaders = []
    libs = []
    device_size = []
    window_size = []
    frame_time = 0.1
    title = ''
    room = ''
    previous_room = ''
    lang = ''
    taggen = 0
    #vars = {}
    models = {}
    assets = {}

    factories = {
        'rooms': {},
        'items': {}
    }


