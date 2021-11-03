import example
import yaml
import os
import mopy.font as font
import mopy.monkey as monkey
import sys
import mopy.factories.basicroom
import mopy.factories.items

class Engine:
    def __init__(self, data = None, scripts = None):
        sys.path.append(example.dir)
        self.data = data
        self.scripts = scripts
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
            print (' === loading strings ...', end='')
            self.load_strings()
            print (' OK.')
            # read game variables, and functions
            for file in a.get('fonts', []):
                self.add_font(file['id'], file['file'])
            for shader in a.get('shaders', []):
                self.add_shader(shader)
        # loading assets
        self.load_assets()

        self.add_room_factory('_basic', mopy.factories.basicroom.BasicRoom.make)

        self.add_item_factory('_model3d', mopy.factories.items.model3d)
        self.add_item_factory('_entity', mopy.factories.items.entity)


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
        for subdir, dirs, files in os.walk(root_dir):
            for f in files:
                filepath = subdir + os.sep + f
                with open(filepath) as fi:
                    cip = yaml.load(fi, Loader=yaml.FullLoader)
                    if cip:
                        self.assets.update(cip)
        print(self.assets)
        #exit(1)
        # dirs = [
        #     ('sprites', 'models'),
        #     ('animations', 'skeletal_animations'),
        #     ('skeletalmodels', 'models'),
        #     ('mesh', 'mesh')
        # ]
        # print ('loading assetz.....')
        # for d in dirs:
        #     directory = example.dir + '/assets/' + d[0]
        #     #print('checking directory ' + directory)
        #     if os.path.exists(directory):
        #         #print ('exists')
        #         files = os.listdir(directory)
        #         for fi in files:
        #             if os.path.isdir(directory + fi):
        #                 continue
        #             with open(directory + '/' + fi) as f:
        #                 models = yaml.load(f, Loader=yaml.FullLoader)
        #                 for key, value in models.items():
        #                     tp = value['type']
        #                     #print ('AAAA ' + key + ' ' + str(value))
        #                     self.assets[d[1]][key] = value
        # print('done!')
        # exit(1)

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
            print('CANE=' + str(id))
            if id[0] == '@':
                cc = self.data
                d = id[1:].split('/')
                print(d)
                for b in d[:-1]:
                    cc = getattr(cc, b)
                print ('current value = ' + str(getattr(cc, d[-1])))
                print ('ccc = ' + str(d[-1]))
                setattr(cc, d[-1], value)
                print ('current value = ' + str(getattr(cc, d[-1])))



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


