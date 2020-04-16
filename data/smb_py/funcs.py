from lib_py.entity import Entity
import lib_py.components as compo
import lib_py.shape as sh
import smb_py.vars as vars

def makePlatform(img : str, x:float, y:float, width : int, height: int):
    a = Entity()
    a.addComponent (compo.Gfx(image = img, repeat = [width, height]))
    a.addComponent (compo.Collider(flag = vars.flags.platform, mask = vars.flags.player, tag = 1, 
        shape = sh.Rect(width = width * vars.tileSize, height = height * vars.tileSize)))
    a.pos = [x * vars.tileSize, y * vars.tileSize]
    return a
