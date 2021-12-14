#!/usr/bin/python3

import os
import argparse



parser = argparse.ArgumentParser(description = "Create a blank new game.")
parser.add_argument('file', metavar='file', help = 'the name of the game')

args = parser.parse_args()

filename = args.file

if os.path.isdir(filename):
    print('the directory ' + filename + ' already exists.')
    exit(1)
os.mkdir(filename)
os.mkdir(filename + '/assets')
os.mkdir(filename + '/data')
os.mkdir(filename + '/fonts')
os.mkdir(filename + '/gfx')
os.mkdir(filename + '/rooms')

open(filename + '/data/globals.py', 'a').close()
f = open(filename + '/data/__init__.py', 'w')
f.write('from .globals import *')
f.close()

f = open(filename+'/main.py', 'w')
f.write("from mopy.engine import Engine\n")
f.write("import data\n\n")
f.write("engine = Engine(data=data)\n")
f.close()
f = open(filename + '/main.yaml', 'w')
f.write('---\n')
f.write('  title: hello_world\n')
f.write('  lang: eng\n')
f.write('  device_size: [320, 240]\n')
f.write('  window_size: [640, 480]\n')
f.write('  start_room: hello_world\n')
f.write('  shaders:\n')
f.write('    - color\n')
f.write('    - unlit_textured\n')
f.write('    - text\n')

f.close()
f = open(filename + '/rooms/hello_world.yaml', 'w')
f.write('---\n')
f.write('  type: _basic\n')
f.write('  id: hello_world\n')
f.write('  cam:\n')
f.write('    - type: ortho\n')
f.write('      id: main\n')
f.write('      world_size: [320, 240]\n')
f.write('      cam_size: [320, 240]\n')
f.write('      bounds:\n')
f.write('        x: [0, 320]\n')
f.write('        y: [0, 240]\n')
f.write('        z: [0, 100]\n')
f.close()
