import example
import yaml
import sys

from lib_py.scumm.entity import WalkArea, BackgroundItem
from lib_py.shape import Polygon, LinY
from lib_py.scumm.scumm import Data
from lib_py.scumm.builder.item import buildItem

def makeRoom (roomid: str):
    filename = example.dir +'/rooms/'+ roomid+ '.yaml'
    from lib_py.scumm.room import RoomUI
    try:
        with open(filename) as f:
            room = yaml.load(f, Loader=yaml.FullLoader)
            r = RoomUI(id= room['id'], width = room['width'], height = room['height'])
            # add walkareas
            if 'bg' in room:
                for bg in room['bg']:
                    image = bg['image']
                    pos = bg.get('pos', [0,0,0])
                    r.add (BackgroundItem(image = image, pos = pos), 'main')
            if 'walkareas' in room:
                for wa in room['walkareas']:                        
                    shape = None
                    if wa['type'] == 'poly':
                        shape = Polygon(outline = wa['outline'])     
                    d = wa.get('depth', None)
                    depth = None
                    if d == 'auto':
                        depth = LinY (0,1,room['height'],0)
                    r.add (WalkArea(tag = 'walkarea', shape = shape, depth = depth), 'main')
            if roomid in Data.locator:
                for key, value in Data.locator[roomid].items():
                    print ('found item: ' + key)
                    d = Data.items[key]
                    node = d.get('node', 'main')
                    e = buildItem (key)
                    r.add(e, node)
            return r
    except EnvironmentError as error:
        print (error)
        sys.exit(1)