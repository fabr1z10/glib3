import vars
import entity
import shapes as sh
import components as comp
import states
import platformer.states


def make_tiledata(tiledata):
    xmin = 0
    xmax = 0
    ymin = 0
    ymax = 0
    for t in tiledata.keys():
        xmin = min(xmin, t[0])
        xmax = max(xmax, t[0])
        ymin = min(ymin, t[1])
        ymax = max(ymax, t[1])
    width = xmax - xmin + 1
    height = ymax - ymin + 1
    tdata = []
    for iy in range(ymin, ymax + 1):
        for ix in range(xmin, xmax + 1):
            td = tiledata.get((ix, iy), None)
            if td:
                tdata.extend([td[0], td[1]])
            else:
                tdata.extend([-1])
    return (tdata, width, height)


def incline_platform(**kwargs):
    def f(*args):
        sheet_id = kwargs.get('sheet', 0)
        sheet = vars.tile_sheets[sheet_id]
        tl = kwargs.get('top_left')
        tiledata = dict()
        lup = args[3]
        ldown = args[4]
        dy = ldown-lup
        x0 = tl[0]
        y0 = tl[1]
        tiledata[(0, 0)] = (x0+3, y0)
        tiledata[(0, -1)] = (x0, y0+3)
        x=1
        y=1
        for i in range(1, lup):
            tiledata[(x, y)] = (x0 + 3, y0)
            tiledata[(x, y-1)] = (x0, y0 + 2)

            for j in range(0, 2*i-1):
                tiledata[(x, y-j-2)] = (x0+1, y0+1)
            tiledata[(x, y-2-(2*i-1))] = (x0+2,y0+3)
            x+=1
            y+=1
        y-=1
        for i in range(0, ldown):
            tiledata[(x,y)] = (x0+1, y0+3) if i == 0 else (x0+3, y0+3)
            for j in range(0, ldown-i-1):
                tiledata[(x, y-j-1)] = (x0+1, y0+1)
            x += 1
            y -= 1
            # tiledata[(x, y-2*i-1)] = (x0+2,y0+3)            # for j in range(0, 2*i-1):
            #     tiledata[(x, y-j-2)] = (x0+1, y0+1)
            # tiledata[(x, y-2*i-1)] = (x0+2,y0+3)
        tdata = make_tiledata(tiledata)
        pos = (args[0] * vars.tile_size, (args[1]-dy) * vars.tile_size, args[2])
        e = entity.Entity(pos=pos)
        e.add_component(comp.TiledGfx(
            tile_sheet=sheet['file'],
            sheet_size=sheet['sheet_size'],
            tile_data=tdata[0],
            width=tdata[1],
            height=tdata[2],
            size=vars.tile_size))
        e.add_component(comp.Collider(debug=True,
                                      flag=vars.flags.platform_passthrough,
                                      mask=0,
                                      tag=0,
                                      shape=sh.Line(a=[0,dy*vars.tile_size], b=[lup * vars.tile_size, (dy+lup)*vars.tile_size])))
        return e
    return f


def platform(**kwargs):
    def f(*args):
        sheet_id = kwargs.get('sheet', 0)
        sheet = vars.tile_sheets[sheet_id]
        tl = kwargs.get('top_left')
        extend_down = args[3]
        pos = (args[0] * vars.tile_size, (args[1]) * vars.tile_size, args[2])
        x0 = tl[0]
        y0 = tl[1]
        data = args[4:]
        tiledata = dict()
        xmap = dict()
        cd = None
        x = 0
        y = 0
        cpoints = []
        cpoints.append( (0, 0))
        left_border = False
        right_border=False
        for i in data:
            if i[-1] == 'S':
                tiledata[(x, y)] = (x0+3, y0+1)
                left_border = True
                x += 1
                cpoints.append((x,y))
                cd = 'R'
            elif i[-1] == 'E':
                tiledata[(x, y)] = (x0+4, y0+1)
                right_border= True
                x += 1
                cpoints.append((x,y))
            elif i[-1] == 'R':
                n = int(i[:-1])
                if cd == 'U':
                    y -= 1
                    tiledata[(x, y)] = (x0, y0)
                    x += 1
                    n -= 1
                elif cd == '/':
                    y -= 1
                elif cd == 'D':
                    tiledata[(x, y)] = (x0+2, y0+2)
                    x += 1
                elif cd == '\\':
                    x-=1
                    tiledata[(x, y)] = (x0+2, y0+2)
                    x+=1
                for j in range(0, n):
                    tiledata[(x, y)] = (x0+1, y0)
                    x += 1
                cpoints.append((x,y))
                cd = i[-1]
            elif i[-1] == 'U':
                if cd == 'R':
                    tiledata[(x, y)] = (x0, y0+2)
                    y += 1
                elif cd=='/':
                    y -=1
                    tiledata[(x, y)] = (x0, y0+2)
                # joint up
                n = int(i[:-1])
                for j in range(0, n):
                    tiledata[(x, y)] = (x0, y0+1)
                    y += 1
                cpoints.append((x,y-1))
                cd = 'U'
            elif i[-1] == 'D':
                n = int(i[:-1])
                if cd == 'R':
                    x -= 1
                    tiledata[(x, y)] = (x0+2, y0)
                    y -= 1
                    n -= 1
                for j in range(0, n):
                    tiledata[(x, y)] = (x0+2, y0+1)
                    y -= 1
                cpoints.append((x+1,y))
                cd = 'D'
            elif i[-1] == '/':
                # slope up
                n = int(i[:-1])
                if cd == 'R':
                    tiledata[(x, y)] = (x0, y0+2)
                    y += 1
                for i in range(0, n):
                    tiledata[(x, y)] = (x0+3, y0)
                    if i < n-1:
                        tiledata[(x+1, y)] = (x0, y0+2)
                    x+=1
                    y+=1
                cpoints.append((x,y-1))
                cd = '/'
            elif i[-1] == '\\':
                # slope down
                n = int(i[:-1])
                if cd == 'D':
                    tiledata[(x, y)] = (x0+2, y0+2)
                    x += 1
                for i in range(0, n):
                    tiledata[(x, y)] = (x0+4, y0)
                    if i < n-1:
                        tiledata[(x, y-1)] = (x0+2, y0+2)
                    x+=1
                    y-=1
                cpoints.append((x,y))
                cd = '\\'
        print(cpoints)
        xmin = 0
        xmax = 0
        ymin = 0
        ymax = 0

        for t in tiledata.keys():
            xmin = min(xmin, t[0])
            xmax = max(xmax, t[0])
            ymin = min(ymin, t[1])
            ymax = max(ymax, t[1])
        ymin -= extend_down
        width = xmax - xmin + 1
        height = ymax - ymin + 1
        for ix in range(xmin ,xmax+1):
            for iy in range(ymin, ymax+1):
                if (ix, iy) in tiledata:
                    break
                if ix == 0 and left_border:
                    tiledata[(ix, iy)] = (x0+3, y0+2)
                elif ix == xmax and right_border:
                    tiledata[(ix, iy)] = (x0+4, y0+2)
                else:
                    tiledata[(ix, iy)] = (x0+1, y0+1)
        tdata = []
        for iy in range(ymin, ymax + 1):
            for ix in range(xmin ,xmax+1):
                td = tiledata.get((ix, iy), None)
                if td:
                    tdata.extend([td[0], td[1]])
                else:
                    tdata.extend([-1])
        pos = (args[0] * vars.tile_size, (args[1] - 1 - abs(ymin)) * vars.tile_size, args[2])
        e = entity.Entity(pos=pos)
        e.add_component(comp.TiledGfx(
            tile_sheet=sheet['file'],
            sheet_size=sheet['sheet_size'],
            tile_data=tdata,
            width=width,
            height=height,
            size=vars.tile_size))
        for i in range(1, len(cpoints)):
            a = entity.Entity()
            a.add_component(comp.Collider(debug=True,flag=vars.flags.platform_passthrough, mask=0, tag=0,
                                          shape=sh.Line(a=[cpoints[i-1][0]*vars.tile_size, (cpoints[i-1][1] + 1+abs(ymin))*vars.tile_size],
                                                        b=[cpoints[i][0]*vars.tile_size, (cpoints[i][1] + 1+abs(ymin))*vars.tile_size])))
            e.add(a)
        return e
    return f


def player(**kwargs):
    def f(*args):
        pos = (args[0] * vars.tile_size, args[1] * vars.tile_size, args[2])
        current_state = vars.states[vars.state]
        model = current_state['model']
        speed = current_state['speed']
        p = entity.Sprite(model=model, pos=pos, tag='player')
        p.add_component(comp.SmartCollider(flag=vars.flags.player, mask=vars.flags.foe | vars.flags.foe_attack, tag=vars.tags.player))
        p.add_component(comp.Controller2D(mask_up=vars.flags.platform, mask_down=vars.flags.platform | vars.flags.platform_passthrough,
                                          max_climb_angle=80, max_descend_angle=80, size=current_state['size'], debug=True))
        p.add_component(comp.Dynamics2D(gravity=vars.gravity))
        sm = comp.StateMachine(initial_state='walk')
        sm.states.append(states.SimpleState(uid='dead', anim='dead'))
        sm.states.append(platformer.states.WalkSide(uid='walk', speed=speed, acceleration=0.05, jump_speed=vars.jump_velocity, flip_horizontal=True))
                                                    # keys=[
                                                    #     [90,  states.StateCallback(func.fire)],
                                                    #     [264, states.StateCallback(func.enter_pipe)],
                                                    # ]))
        sm.states.append(platformer.states.Jump(uid='jump', speed=speed, acceleration=0.10, flip_horizontal=True,
                                                anim_up='jump_up', anim_down='jump_down'))
                                                #keys=[
                                                #    [90, states.StateCallback(func.firej)],
                                                #]))
        sm.states.append(platformer.states.FoeWalk(uid='demo', anim='walk', speed=speed, acceleration=0.05,
                                                   flip_horizontal=True, flip_when_platform_ends=False, left=1,
                                                   flip_on_wall=False))
        sm.states.append(states.SimpleState(uid='pipe', anim='pipe'))
        #sm.states.append(states.SimpleState(uid='slide', anim='slide'))

        p.add_component(sm)
        p.add_component(comp.KeyInput())
        p.add_component(comp.Follow())
        return p
    return f