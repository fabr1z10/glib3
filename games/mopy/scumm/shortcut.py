import mopy



# global
gl = None



def init_shortcuts():
    global gl
    gl = mopy.monkey.engine.data.globals
    gl = 33
    print(gl)
    #scripts = mopy.monkey.engine.data.scripts


def get_item(item_id):
    items = mopy.monkey.engine.data.items
    print(items[item_id])
    return mopy.monkey.engine.repl_vars(items[item_id])
