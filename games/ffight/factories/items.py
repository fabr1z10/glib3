import entity
import components as comp
import states
import platformer.states as pstates
import shapes3d as sh3d
import shapes as sh
import vars
import math
import func

sqrt2 = math.sqrt(2)


class WalkAreaInfo:
    def __init__(self, x0, elevation, z0, tex_height, y0):
        self.x0 = x0
        self.elevation = elevation
        self.z0 = z0
        self.tex_height = tex_height
        self.y0 = y0
        print ('z00 = ' + str(self.z0))

    def transform(self, pos):
        print('ciao '+str(self.y0))
        return [pos[0], self.elevation+0.012, self.z0 + (self.y0 - (self.tex_height - pos[1])) * sqrt2]




def transform(v):
    return v[0], v[1] - v[2], v[2] * sqrt2


def static_bg(**kwargs):
    def f(*args):
        pos = (args[0], args[2]/math.sqrt(2), args[2])
        e = entity.Entity(pos=pos)
        e.add_component(comp.Gfx(image=args[3]))
        return e
    return f


def t1(y, y_goto):
    # get the origin of walkarea
    wa = vars.walk_areas[y_goto[0]]
    wo0 = wa[0]
    wz0 = wa[1]
    print('figa ' + str(wz0) + ' ' + str(y_goto[2]))
    return [y, y_goto[1], wo0[1], (y_goto[2] - wz0) * sqrt2]


def hotspot(**kwargs):
    def f(*args):

        ym = kwargs.get('y_min')
        y0 = kwargs.get('y_min_goto')
        wa : WalkAreaInfo = vars.walk_areas[y0[0]]
        ymg = wa.transform(y0[1:])
        print ('y m goto = '+ str(ymg))

        yM = kwargs.get('y_max')
        y1 = kwargs.get('y_max_goto')
        wa : WalkAreaInfo = vars.walk_areas[y1[0]]
        yMg = wa.transform(y1[1:])
        print ('y M goto = '+ str(yMg))

        x0 = args[0]
        depth_y = args[2] * math.sqrt(2.0)
        y0 = args[1] - args[2]
        z0 = -depth_y
        pos = (x0, y0, z0)
        e = entity.Entity(pos=pos)
        e.add_component(comp.Collider(debug=True, shape=sh3d.AABB(size=(args[3], args[4], args[5])), flag=vars.flags.foe,
                                      mask=vars.flags.player, tag=vars.tags.hotspot))
        e.add_component(comp.Info(x=522, y_min=ym, y_max=yM, y_min_goto=ymg, y_max_goto=yMg))
        return e
    return f


def npc(**kwargs):
    def f(*args):
        pos = (args[0], args[1], args[2])
        model = kwargs.get('model')
        scale = kwargs.get('scale', 1.0)
        speed = kwargs.get('speed', 50)
        width = kwargs.get('width')
        energy = kwargs.get('energy', 2)

        p = entity.Sprite(model=model, pos=pos)
        #shadow = entity.Entity()
        #shadow.add_component(comp.ShadowRenderer(angle=20.0))
        #p.add(shadow)
        p.layer = 1
        p.scale = scale
        p.add_component(comp.Controller3D(
            mask_up=vars.flags.platform,
            mask_down=vars.flags.platform | vars.flags.platform_passthrough,
            size = [1, 1, 1],
            shift = [0, 0.5],
            max_climb_angle=80,
            max_descend_angle=80,
            debug=True))
        p.add_component(comp.Dynamics2D(gravity=vars.gravity))
        p.add_component(comp.SmartCollider(flag=vars.flags.foe, mask=vars.flags.player_attack,
                                           tag=vars.tags.foe, cast_tag=vars.tags.foe_attack, cast_mask=vars.flags.player, debug=True))
        #p.add_component(comp.Info(energy=energy, hp=hp_map, remain_stomp=remain_stomp_anim, dseq=dseq, tiny=False))
        sm = comp.StateMachine(initial_state='walk')

        sm.states.append(pstates.FoeChase3D(
            uid='walk',
            walk_anim='walk',
            idle_anim='idle',
            speed = speed,
            acceleration=0.05,
            attacks=[],
            prob_attack=0))
        #     prob_attack=prob_attack))
        #sm.states.append(platformer.states.IsHit(uid='ishit', anim='hit', acceleration=10, dist=4))
        #sm.states.append(states.SimpleState(uid='dead', anim='hit'))
        p.add_component(sm)

        return p
    return f

def character_player(**kwargs):
    def f(*args):
        pos = (args[0], args[1], args[2])
        scale = kwargs.get('scale', vars.player_scale)
        #char_info = vars.  xcharactersgft```<
        speed = vars.player_speed
        model = vars.player_model
        width = 10
        p = entity.Sprite(model=model, pos=pos, tag='player')
        # TODO shadow
        #shadow = entity.Entity()
        #shadow.add_component(comp.ShadowRenderer(angle=20.0))
        #p.add(shadow)
        #p.layer = 2
        #p.depth = 0x0207
        #p.scale = scale * vars.scale
        p.scale = scale
        p.add_component(comp.Controller3D(
             size = [1, 1, 1],
             shift = [0, 0.5],
             debug = True,
             mask_up=vars.flags.platform,
             mask_down=vars.flags.platform | vars.flags.platform_passthrough,
             max_climb_angle=80,
             max_descend_angle=80))
        p.add_component(comp.Dynamics2D(gravity=vars.gravity))
        p.add_component(comp.SmartCollider(flag=vars.flags.player, mask=vars.flags.foe_attack,
            tag=vars.tags.player, cast_tag=vars.tags.player_attack, cast_mask=vars.flags.foe, debug=True))
        sm = comp.StateMachine(initial_state='walk')
        sm.states.append(pstates.WalkSide3D(
            uid='walk',
            speed=speed,
            acceleration=0.05,
            jump_speed=vars.jump_velocity,
            animator=pstates.YAnimator(idle_up='idle_up', idle_down='idle', walk_up='walk_up', walk_down='walk'),
            keys=[
                [265, states.StateCallback(func.climb_bottom)],
                [264, states.StateCallback(func.climb_top)]],
            flip_horizontal=True))
        sm.states.append(pstates.Jump3D(
            uid='jump',
            speed=speed,
            acceleration=0.10,
            flip_horizontal=True,
            keys=[],
            anim_up='jump_up',
            anim_down='jump_down'))
        sm.states.append(pstates.Climb(uid='climb', speed=50, idle_anim='climb', climb_anim='climb'))
        p.add_component(sm)
        p.add_component(comp.KeyInput())
        p.add_component(comp.DynamicFollow(world_width=5216, cam_width=384, cam_height=224,
            origin=(0, 256),
            path=[
                3, 256, 2, 256, 3, 16, 2, 64, 3, 16, 2, 624, 0, 16, 2, 336, 3, 48, 2, 256, 3, 64,
                2, 48, 3, 64,  2, 96, 3, 32,  2, 608, 0, 128, 2, 16, 0, 96, 2, 64, 0, 112,  2, 192,
                0, 16, 2, 1536, 3, 16, 2, 320, 0, 32, 2, 16, 0, 16, 2, 16, 0, 48, 2, 144, 3, 160,
                2, 192, 3, 32,  2, 432,  0, 336, 1, 80, 0, 48, 1, 112, 0, 112, 1, 672, 3, 32, 1, 256,
                3, 96,  1, 2048, 3, 192, 1, 64, 0, 64, 1, 1984]))
        #p.add_component(comp.Follow(relpos=(0, 0, 5), z=1))
        return p
    return f


def walk_area(**kwargs):
    def f(*args):
        outline = kwargs.get('poly')
        depth = kwargs.get('depth')
        fy = kwargs.get('fy', 0)
        if fy > 0:
            outline = [fy - outline[i] if i % 2 == 1 else outline[i] for i in range(0, len(outline))]
            print(outline)
            #exit(1)

        height = kwargs.get('height', 1.0)
        depth_y = depth * math.sqrt(2.0)
        y0 = outline[1] - depth - height
        x0 = outline[0]
        z0 = -depth_y
        pos = (x0, y0, z0)
        top = (x0, y0 + height, z0)
        vars.walk_areas.append (WalkAreaInfo(x0, y0 + height, z0, fy, outline[1]))
        #print('PISUZIONA = ' + str(pos))
        color = kwargs.get('color', [1, 1, 1, 1])
        oline = []
        a0 = outline[1]
        for i in range(0, len(outline), 2):
            oline.append(outline[i] - x0)
            oline.append((outline[i+1] - a0) * math.sqrt(2.0))
        print(oline)
        e = entity.Entity(pos=pos)
        shape = sh3d.Prism(shape=sh.Poly(outline=oline), height=height, walls=kwargs.get('walls',[]))
        print(shape)
        e.add_component(comp.ShapeGfxColor(shape=shape, color=color))
        e.add_component(comp.Collider(shape=shape, flag=vars.flags.platform, mask=0, tag=vars.tags.platform))
        return e
    return f

def aabb3d(**kwargs):
    def f(*args):
        pos = (args[0], args[1], args[2])
        width = args[3]
        height = args[4]
        depth = args[5]
        offset = (0, 0, 0)
        if len(args) > 6:
            offset = (args[6], args[7], args[8])
        color = kwargs.get('color', [1, 1, 1, 1])
        e = entity.Entity(pos=pos)
        shape = sh3d.AABB(size=(width, height, depth), offset=offset)
        e.add_component(comp.ShapeGfxColor(shape=shape, color=color))
        e.add_component(comp.Collider(shape=shape, flag=vars.flags.platform, mask=0, tag=vars.tags.platform))

        tx_top = kwargs.get('top', None)
        tx_front = kwargs.get('front', None)
        if tx_top:
            e.add(make_plat(glm.vec3(0, height, depth) + offset, (width, depth), tx_top))
        if tx_front:
            e.add(make_wall(glm.vec3(0, 0, depth) + offset, (width, height), tx_front))
        #e.add(make_wall(offset + glm.vec3(0, 0, depth), (width, height), '2'))
        #e.add(make_wall(offset + glm.vec3(width, 0, depth), (depth, height), '2', 90))
        return e
    return f