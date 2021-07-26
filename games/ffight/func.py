# # functions
# import vars
# import data
import example
# import entity
# import monkey
# import sys
# import lib.shapes as sh
# import lib.shapes3d as sh3d
# import actions as act
# import components as comp
# import platformer.states
# from script import Script
# import random
# import math
#

def restart():
    #exit(1)
    #vars.energy = vars.energy_start
    # vars.player_dead = False
    # vars.closest_foe = None
    # vars.invincibility = False
    # vars.currentWarp = -1
    #
    # vars.current_foes.clear()
    # vars.dynamic_foes.clear()
    #vars.scale_factor = 1
    example.restart()

# def check_enemies():
#     playerx = example.get('player').x
#     dist_min = math.inf
#     closest = None
#     for i in vars.dynamic_foes.keys():
#         if i not in vars.current_foes:
#             vars.current_foes[i] = example.getById(i)
#         dist = abs(playerx - vars.current_foes[i].x)
#         if dist < dist_min:
#             dist_min = dist
#             closest = i
#     dmin = 8
#     if dist_min > dmin and vars.closest_foe is not None:
#         vars.closest_foe = None
#         if vars.foe_desc_id:
#             example.remove(vars.foe_desc_id)
#     else:
#         if closest is not None and vars.closest_foe != closest and dist_min < dmin:
#             if vars.foe_desc_id:
#                 example.remove(vars.foe_desc_id)
#             dd = vars.dynamic_foes[closest]
#             a = entity.Entity(pos=(16, 200))
#             b = entity.Entity()
#             b.add_component(comp.Gfx(width=16,height=16,image=dd['portrait']))
#             a.add(b)
#             c = entity.Text(font='main', size=8, text=dd['name'], color=(255,255,255,255), align=entity.TextAlignment.bottom_left, pos=(19,8))
#             d = entity.Text(font='main', size=8, text=vars.get_height_str(dd['height']), color=(255, 255, 255, 255),
#                             align=entity.TextAlignment.bottom_left, pos=(18, 0))
#             a.add(c)
#             a.add(d)
#             vars.foe_desc_id = example.get('diag').add(a)
#             vars.closest_foe = closest
#
#
#
#
# def create_enemy():
#     #print('CURRENT no ENEMIES: ' + str(vars.enemy_count))
#     if vars.enemy_count < vars.max_enemies:
#         if random.random() < vars.prob_new_enemy:
#             # create random enemy
#             import factories.items as irr
#             foe_id = random.choice(vars.foes)
#             foe = vars.characters[foe_id]
#             height_cm = 0
#             if 'height_data' in foe:
#                 hd = foe['height_data']
#                 p0 = glm.vec2(hd[0])
#                 for p in hd[1:]:
#                     height_cm += glm.distance(p0, p)
#                     p0= p
#                 height_cm *= foe['scale'] * vars.cm_per_unit
#
#
#             player = example.get('player')
#             a = None
#             dx = [8, -8]
#             screen_length = 5
#             x = player.x + random.choice([-1, 1]) * 2
#             y = player.y + 5
#             #x = min(vars.world_size[0]-16, max(16, x))
#             #y = 80
#             z =0
#             factory = foe['factory']
#             print ('looking for factory ' + factory)
#             if vars.room_3d:
#                 factory +='3d'
#             f = getattr(irr, factory)
#             e = f(**foe)(x, y, z)
#             aa: example.Wrap1 = example.get('main')
#             vars.enemy_count += 1
#             nid = aa.add(e)
#             vars.dynamic_foes[nid] = {'name': foe['name'], 'height': round(height_cm), 'portrait': 'assets/characters/cody/portrait.png'}
#
#
# def lippa():
#     s = Script()
#     s.add_action(act.Repeat(func=create_enemy, interval=2))
#     example.play(s)
#     s2 = Script()
#     s2.add_action(act.Repeat(func=check_enemies, interval=0.5))
#     example.play(s2)
#     a = example.get('main')
#     import engine
#     #print (monkey.engine.assets['models'])
#     #aaa = monkey.engine.assets['models']['grl3']
#     import factories.items as irr
#
#     # factory = getattr(irr, 'skeleton')
#     # template = vars.characters['grl3']
#     # s = factory(**template)(20, 4, vars.z)
#     # template1 = vars.characters['grl3_2']
#     # s1 = factory(**template1)(30, 4, vars.z)
#     # a.add(s)
#     # a.add(s1)
#     #sc = 0.02
#     #s = entity.Skeleton(model=aaa, pos=(20, 4, vars.z))
#
#
#     #s.scale = sc
#     #s.depth = 0x0207
#     # shadow = entity.Entity(pos = (0,-1432*sc,0))
#     # shadow.add_component(comp.ShadowRenderer(angle=20.0))
#     # s.add(shadow)
#     # # c = comp.ColliderManager()
#     # # pos = [126, -1020]
#     # # c.colliders.append(comp.SkColl(vars.flags.platform, vars.flags.player, vars.tags.moving_platform,
#     # #     50, pos, [1], [1], [pos[0], pos[1]+100], [1], [1]))
#     # # s.add_component(c)
#     # #s.speed_up=1
#     #
#     # # gnd hitters!
#     # if 'custom' in aaa and 'hitters' in aaa['custom']:
#     #     c = comp.ColliderManager()
#     #     for hitter in aaa['custom']['hitters']:
#     #         pos = hitter['pos']
#     #         width = hitter['width']
#     #         bone_index = hitter['bone_index']
#     #         c.colliders.append(comp.SkColl(vars.flags.platform, vars.flags.player, vars.tags.moving_platform,
#     #             width, pos, [bone_index], [1], [pos[0], pos[1]+100], [bone_index], [1]))
#     #         c.colliders.append(comp.SkColl(vars.flags.platform, vars.flags.player, vars.tags.crusher,
#     #             width-5, [pos[0], pos[1]-2], [bone_index], [1], [pos[0], pos[1]-2+100], [bone_index], [1]))
#     #         #c.colliders.append(comp.SkColl(vars.flags.platform, vars.flags.player, vars.tags.moving_platform, 30, lgnd, [4], [1], [lgnd[0], lgnd[1]+100], [4], [1]))
#     #         #         #c.colliders.append(comp.SkColl(vars.flags.platform, vars.flags.player, vars.tags.crusher, 25, [lgnd[0], lgnd[1]-2], [4], [1],
#     # #         #            [lgnd[0], lgnd[1]-2+100], [4], [1]))
#     #     s.add_component(c)
#
#
#
# def reset_invincible():
#     vars.invincibility = False
#
# def compute_height():
#     # compute player's height
#     #return
#     player = example.get('player')
#     h1 = player.getKeyPoint('torso', 'head')
#     f1 = player.getKeyPoint('rfoot', 'heel')
#     heady = h1[1]
#     height = 0
#     if f1:
#         height = max(height, heady - f1[1])
#     s1 = player.getKeyPoint('rshoe', 'heel')
#     if s1:
#         height = max(height, heady - s1[1])
#     hw = player.scale * height * vars.cm_per_unit
#     print ('height in px: ' + str(height))
#     print ('height world: ' + str(hw))
#     example.get('height_label').setText(vars.get_height_str(hw))
#
#
# def restart():
#     #vars.energy = vars.energy_start
#     vars.player_dead = False
#     vars.closest_foe = None
#     vars.invincibility = False
#     vars.currentWarp = -1
#
#     vars.current_foes.clear()
#     vars.dynamic_foes.clear()
#     #vars.scale_factor = 1
#     example.restart()
#
#
# def increment_player_energy(n, player: example.Wrap1, sgn: float, player_left: bool):
#     vars.energy = max(0, vars.energy + n)
#     example.get('energy_label').setText(str(round(vars.energy)))
#
#     if vars.energy > 0:
#         player.setState('ishit', {'sign': sgn})
#         vars.invincibility = True
#         s = Script()
#         s.add_action(act.Blink(duration=1.0, blink_duration=0.2, tag='player'))
#         s.add_action(act.CallFunc(f=reset_invincible))
#         example.play(s)
#     else:
#         aa = player.getCollisionBounds()
#         default_dead_seq(player, aa)
#         # player.setState('killed', {'left': player_left})
#         # vars.player_dead = True
#         # s = Script()
#         # s.add_action(act.Delay(sec=2))
#         # s.add_action(act.CallFunc(f=restart))
#         # example.play(s)
#
#
# def collect_bonus(player: example.Wrap1, foe: example.Wrap1, x, y):
#     info = foe.getInfo()
#     bonus = info['callback']
#     print ('sto cane: ' + str(bonus[3:]))
#     getattr(sys.modules[__name__], bonus[1])(*bonus[3:])
#     example.remove(foe.id)
#
# def grow(*args):
#     s = example.get('player')
#     vars.scale_factor *= 1.05
#     # grow by 5%
#     s.scale = vars.default_scale * vars.scale_factor
#     compute_height()
#
# def shrink(*args):
#     s = example.get('player')
#     vars.scale_factor *= 0.95
#     # shrink by 5%
#     s.scale = vars.default_scale * vars.scale_factor
#     compute_height()
#
# # model change here
# def get_futa(*args):
#     vars.cock_id = args[0]
#     vars.cock_size = args[1]
#     player = example.get('player')
#     dd = data.models.create_model(vars.get_model())
#     model = dd.get('model')
#     # update default scale
#     vars.default_scale = dd.get('scale', 1.0)
#     player.scale = vars.default_scale * vars.scale_factor
#
#     player.setModel(model)
#     compute_height()
#
# def put_on_shoez(*args):
#     print('wearing shoez: ' + args[0])
#     vars.shoez_id = args[0]
#     player = example.get('player')
#     dd = data.models.create_model(vars.get_model())
#     model = dd.get('model')
#     # update default scale
#     vars.default_scale = dd.get('scale', 1.0)
#     player.scale = vars.default_scale * vars.scale_factor
#     player.setModel(model)
#     compute_height()
#
# def update_model(*args):
#     player = example.get('player')
#     vars.model_id = args[0]
#     dd = data.models.create_model(vars.get_model())
#     #dd = getattr(data.models, vars.get_model())#  vars.modelz[vars.model_id])
#     model = dd.get('model')
#     player.setModel(model)
#     compute_height()
#
# def stomp_enemy(player: example.Wrap1, foe: example.Wrap1, x, y):
#     if player.getState() == 'jump' and player.vy < 0:
#         aa = foe.getCollisionBounds()
#         a = entity.Sprite(pos=(foe.x, foe.y, 0), model='sprites/bloodfx/crsh1')
#         a.scale = (0.8*(aa[2]-aa[0]))/49
#         ab = example.get('main')
#         ab.add(a)
#         example.remove(foe.id)
#         default_dead_seq(foe, aa)
#         player.vy = 0.5* (-player.vy)
#         if foe.id in vars.dynamic_foes:
#             vars.enemy_killed += 1
#             vars.enemy_count -= 1
#
#
# def foe_hits_player(foe: example.Wrap1, player: example.Wrap1, x, y):
#     return
#     if vars.invincibility:
#         return
#     foe_left = foe.x < player.x
#     finfo = foe.getInfo()
#     if finfo['tiny'] == True:
#         return
#     hp = finfo['hp'][foe.getState()]
#     make_hit_spark(x, y, player.x < foe.x)
#     #if hp == float('inf'):
#     #    vars.player_dead = True
#     #    player.setState('stomped', {})
#     #else:
#     sgn = 1.0 if (foe_left and not player.flipx) or (not foe_left and player.flipx) else -1.0
#     increment_player_energy(-hp, player, sgn, foe_left)
#
#
# def on_crusher_hit(foe: example.Wrap1, player: example.Wrap1, x, y):
#     print ('cocococo')
#     if not vars.invincibility and not vars.player_dead:
#         ff = foe.getKeyFrame()
#         if ff == 2 or ff== 5:
#             vars.player_dead = True
#             player.setState('stomped', {})
#         #foe.setState('landed', {'left': -1 if foe.flipx else 1})
#     return False
#
#
# def foe_stomps_player(foe: example.Wrap1):
#     if not vars.invincibility and not vars.player_dead:
#         vars.player_dead = True
#         player = example.get('player')
#         aa = player.getCollisionBounds()
#         a = entity.Sprite(pos=(player.x, player.y, 0), model='sprites/bloodfx/crsh1')
#         a.scale = (2*(aa[2]-aa[0]))/40
#         ab = example.get('main')
#         ab.add(a)
#         default_dead_seq(player, aa)
#         # player.setState('stomped', {})
#         foe.setState('landed', {'left': -1 if foe.flipx else 1})
#         rsanim = foe.getInfo()['remain_stomp']
#         s = Script()
#         s.add_action(act.Animate(entity_id=foe.id, anim='landed', sync=True))
#         if not rsanim:
#             s.add_action(act.SetState(entity_id=foe.id, state='walk'))
#         example.play(s)
#         return True
#     return False
#
#
# def fire_hits_foe(player: example.Wrap1, foe: example.Wrap1, x, y):
#     bs = foe.getBoxSize("idle")
#     print(bs)
#     foe.enableUpdate(False)
#     foe.getInfo()['tiny'] = True
#     nscale = vars.size_small/bs[1]
#     s = Script()
#     s.add_action(act.SetState(entity_id=foe.id, state='change_size'))
#     s.add_action(act.Scale(nscale, 1.0, entity_id=foe.id))
#     s.add_action(act.SetState(entity_id=foe.id, state='walk'))
#     s.add_action(act.CallFunc(f= lambda : foe.enableUpdate(True)))
#     example.play(s)
#     #foe.scale = vars.size_small / bs[1]
#
#     return
#     fs = foe.getState()
#     if fs == 'ishit' or fs == 'dead':
#         return
#     foe_info = foe.getInfo()
#
#     example.remove(player.id)
#     foe_info['energy'] -= 1
#     print ('energy left = ' + str(foe_info['energy']))
#     player_left = player.x < foe.x
#     if foe_info['energy'] <= 0:
#         sgn = 1
#         if not foe.flipx:
#             sgn = -1
#         foe.setState('dead', {})
#         s = Script()
#         s.add_action(act.Move(entity_id=foe.id, speed=sgn*200, by=[100, 0]))
#         s.add_action(act.RemoveEntity(entity_id=foe.id))
#         example.play(s)
#         if foe.id in vars.dynamic_foes:
#             vars.enemy_killed += 1
#             vars.enemy_count -= 1
#     else:
#         sgn = -1.0 if (player_left and foe.flipx) or (not player_left and not foe.flipx) else 1.0
#         foe.setState('ishit', {'sign': sgn})
#
#
# def gib_lands(gib: example.Wrap1, foe: example.Wrap1, x, y):
#
#     gx = gib.x
#     gy = gib.y
#     ab = example.get('main')
#     bfx = entity.Sprite(model='sprites/bloodfx/fx2', pos=(gx,gy))
#     bfx.scale = 0.04
#     print (bfx.scale)
#     print ('fottimi')
#     example.remove(gib.id)
#     s = Script()
#     bfxid = ab.add(bfx)
#     s.add_action(act.Animate(entity_id=bfxid,anim='idle',sync=True))
#     s.add_action(act.RemoveEntity(entity_id=bfxid))
#     example.play(s)
#
#
# def player_hits_block(player: example.Wrap1, foe: example.Wrap1, x, y):
#     pos = (foe.x, foe.y)
#     # generate random bonus
#     bonus_set = vars.bonuses[vars.model_prefix][vars.model_id]
#     rb =vars.bonus[random.choice(bonus_set)]
#     s = entity.Sprite(model=rb[0], pos=(foe.x, foe.y))
#     s.add_component(comp.SmartCollider(flag=vars.flags.foe, mask=vars.flags.player, tag=vars.tags.bonus, debug=True))
#     s.add_component(comp.Info(callback=rb))
#     s.scale = rb[2]
#     example.remove(foe.parent().id)
#     example.get('main').add(s)
#
#
# def default_dead_seq(foe, foe_bounds):
#     ab = example.get('main')
#     print(foe_bounds)
#     example.remove(foe.id)
#     foe_width = foe_bounds[2] - foe_bounds[0]
#     foe_height = foe_bounds[3] - foe_bounds[1]
#     nrows = max(int(foe_height // 0.2), 1)
#     ncols = max(int(foe_width // 0.2), 1)
#     w = foe_width / (ncols)
#     h = foe_height / (nrows)
#     for col in range(0, ncols):
#         for row in range(0, nrows):
#             x = foe_bounds[0] + col * w
#             y = foe_bounds[1] + row * h
#             wi = w
#             he = h
#             e = entity.Entity(pos=(x + wi * 0.5, y + he * 0.5, 1))
#             #e.layer = 2
#             #e.depth = 0x0207
#
#             e.add_component(comp.Gfx(image='gfx/gibs/' + str(random.randint(0, 2)) + '.png', width=wi, height=he,
#                                      offset=(-wi * 0.5, -he * 0.5)))
#             vx = ((-1 + col * (2 / (ncols - 1))) if ncols > 1 else 0) + 0.5 * random.uniform(-1, 1)
#             e.add_component(comp.AcceleratedMover(v0=(vx, random.uniform(0, 1)), acceleration=(0, 0.1 * vars.gravity),
#                                                   angular_speed=random.uniform(10, 180)))
#             e.add_component(comp.Collider(debug=False, shape=sh.Rect(width=0.1, height=0.1, offset=[-0.05, -0.05, 0]),
#                                           flag=vars.flags.gib, mask=vars.flags.platform, tag=vars.tags.gib))
#             ab.add(e)
#
# import util
# import glm
#
# def make_hit_spark(x, y, flip):
#     ab = example.get('main')
#     bfx = entity.Sprite(model='sprites/spark1/spark1', pos =(x, y))
#     bfx.scale = 0.04
#     #bfx.flipx = player.x > foe.x
#     bfx.flipx = flip
#     s = Script()
#     bfxid = ab.add(bfx)
#     s.add_action(act.Animate(entity_id=bfxid, anim='default', sync=True))
#     s.add_action(act.RemoveEntity(entity_id=bfxid))
#     example.play(s)
#
#
# def on_foe_killed(id):
#     vars.enemy_killed += 1
#     vars.enemy_count -= 1
#     del vars.dynamic_foes[id]
#     if id in vars.current_foes:
#         del vars.current_foes[id]
#     if vars.enemy_killed >= vars.enemies_to_kill:
#         f = entity.Sprite(model='sprites/01/go_sign', pos=(240, 184, 0))
#         g = entity.Entity(pos=(vars.world_size[0] - 6, 0, 0))
#         g.add_component(comp.Collider(flag=vars.flags.foe, mask=vars.flags.player, tag=vars.tags.gonext, shape=sh3d.AABB((8,8,1)), debug=True))
#         di = example.get('diag')
#         d2 = example.get('main')
#         d2.add(g)
#         di.add(f)
#         # open passage to next stage
#
#
# def gonext(player: example.Wrap1, foe: example.Wrap1, x, y):
#     print('GOING to ' + vars.next_room)
#     example.get('main').enableUpdate(False)
#     example.remove(foe.id)
#     g = entity.Text(pos=(128, 128), font='main', size=8, text='STAGE CLEAR!', color=(255,255,255,255), align=entity.TextAlignment.center)
#     example.get('diag').add(g)
#     s = Script()
#     s.add_action(act.Delay(sec=2))
#     s.add_action(act.ChangeRoom(room=vars.next_room))
#     example.play(s)
#
#
# def player_hits_foe(player: example.Wrap1, foe: example.Wrap1, x, y):
#     fs = foe.getState()
#     print('#### collision point: ' + str(x) + ', ' + str(y))
#     if player.getState() == 'attack2':
#         height = foe.scale * foe.getBoxSize('idle')[1]
#         if height-0.01 < vars.size_small:
#             # put blood
#             e = entity.Entity(pos=(foe.x, foe.y, 0))
#             bfx = random.choice(vars.blood_fx)
#             e.add_component(comp.Gfx(image=bfx[0], offset=(-bfx[1][0], -bfx[1][1])))
#             e.transform = util.mat_to_list(glm.translate(glm.mat4(), glm.vec3(foe.x, foe.y, 0)) *
#                                                          glm.rotate(glm.mat4(), glm.radians(-90), glm.vec3(1, 0, 0)))
#             e.scale = bfx[2]
#             example.get('main').add(e)
#             if foe.id in vars.dynamic_foes:
#                 on_foe_killed(foe.id)
#             example.remove(foe.id)
#         return
#
#     make_hit_spark(x, y, player.x > foe.x)
#     #aa = foe.getCollisionBounds()
#     #ax = player.getAttackCollisionBounds()
#     if fs == 'ishit' or fs == 'dead':
#         return
#     foe_info = foe.getInfo()
#     foe_info['energy'] -= 1
#     player_left = player.x < foe.x
#     if foe_info['energy'] <= 0:
#         #if foe_info['dseq'] == 1:
#         #    foe.setState('dead', {})
#         #elif foe_info['dseq'] == 2:
#         sgn = 1
#         if not foe.flipx:
#             sgn = -1
#         foe.setState('dead', {})
#         s = Script()
#         s.add_action(act.Move(entity_id=foe.id, speed=sgn*200, by=[100, 0]))
#         s.add_action(act.RemoveEntity(entity_id=foe.id))
#         example.play(s)
#         #else:
#         #    # default dead sequence
#         #    default_dead_seq(foe, aa)
#         if foe.id in vars.dynamic_foes:
#             on_foe_killed(foe.id)
#     else:
#         sgn = -1.0 if (player_left and foe.flipx) or (not player_left and not foe.flipx) else 1.0
#         foe.setState('ishit', {'sign': sgn})
#
#
#
#
# def fire(a: example.Wrap1):
#     print('FIRE!')
#     p = example.get('player')
#     speed = p.vx + vars.player_speed
#     b = entity.Sprite(model='sprites/01/fire', pos=(a.x + (-0.2 if a.flipx else 0.2), a.y + 1, vars.z))
#     b.scale = 0.05
#     b.add_component(comp.SmartCollider(flag=vars.flags.player_attack, mask=vars.flags.foe | vars.flags.platform,
#         tag=vars.tags.fire, debug=True))
#     #sm = comp.StateMachine(initial_state='jmp')
#     id = example.get('main').add(b)
#     c = Script()
#     c.add_action(act.MoveAccelerated(v0=[-speed if a.flipx else speed, 0], a=[0, vars.gravity], yStop=-1, entity_id=id))
#     c.add_action(act.RemoveEntity(entity_id=id))
#     example.play(c)
#
