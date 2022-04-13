import data
import example
from mopy.script import Script
import mopy.actions as act

def format_score(score):
    return '{:06d}'.format(score)


def add_score(n):
    data.globals.score += n
    example.get('label_score').setText(format_score(data.globals.score))

def init(desc):
    if 'time' in desc:
        data.globals.time = desc['time']
        data.globals.display_name = desc['display_name']
    data.globals.start_positions = desc['start_positions']







def setup():
    example.get('label_time').setText(str(data.globals.time))
    print(data.globals.display_name)
    example.get('label_world').setText(data.globals.display_name)
    #sp = data.globals.start_positions[data.globals.start_position]
    #script = sp.get('script')
    #if script:
    #    script()