from mopy.script import Script
import mopy.actions as act
import example
import data


def foe_hits_mario(player, foe, x, y):
    if player.getState() == 'jump' and player.vy < 0:
        s = Script()
        player.vy = data.globals.jump_velocity * 0.5
        s.add_action(act.SetState(state='dead', entity_id=foe.id))
        s.add_action(act.Delay(211))
        s.add_action(act.RemoveEntity(foe.id))
        example.play(s)
    else:
        pass
        #player_hit_by_enemy(player)


def hit_brick_sensor(player, sensor : example.Wrap1, x, y):
    sensor.parent().vy = 10
