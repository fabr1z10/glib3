
from lib_py.builder.functions import *
fmap = {
    'func.linear.x': f2x,
    'func.linear.y': f2y,
    'func.const': const,
    'func.patch2d': patch
}


def make_object (d: dict):
    tp = d['type']
    if tp not in fmap:
        raise BaseException('Don''t know how to build object of type: ' + tp)
    return fmap[tp](d) 