# build 2d functions from dictionaries

from lib_py.shape import LinY, LinX, Const, Patch2D



def f2y (d: dict):
    p0 = d['p0']
    p1 = d['p1']
    return LinY(p0[0], p0[1], p1[0], p1[1])

def f2x (d: dict):
    p0 = d['p0']
    p1 = d['p1']
    return LinX(p0[0], p0[1], p1[0], p1[1])

def const (d: dict):
    return Const(d['value'])

def patch (d: dict):
    a = Patch2D()
    for f in d['func']:
        pos = f['pos']
        size = f['size']
        fu = f['f']
        from lib_py.builder.build import make_object
        f2d = make_object(fu)
        a.addFunc(pos[0], pos[1], size[0], size[1], f2d)
    return a


