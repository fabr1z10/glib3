import mopy



# global
gl = None



def init_shortcuts():
    global gl
    print('ciao')
    gl = mopy.monkey.engine.data.globals
    gl = 33
    print(gl)
    #scripts = mopy.monkey.engine.data.scripts