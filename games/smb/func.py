# functions
import vars
import example
import entity

def toggle_pause():
    if vars.paused:
        example.get('main').enableUpdate(True)
        example.removeByTag('shader')
    else:
        example.get('main').enableUpdate(False)
        a = entity.Entity(pos=(0, 0, 1), tag='shader')
        a.add_component()
        a.addComponent (compo.ShapeGfxColor(shape = sh.Rect(256, 256), fill = sh.SolidFill(r=0, g=0, b=0, a=64)))
        example.get('diag').add(a)
    vars.paused = not vars.paused


def restart():
    vars.invincibility = False
    vars.currentWarp = -1
    example.restart()
