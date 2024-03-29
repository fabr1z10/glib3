import mopy.util as utils
import mopy 
import mopy.scumm.shortcut as sc
import example


class pos:
    kitchen_door = [45, 12]
    scummbar_main_door = [64, 19]
    scummbar_kitchen_door = [595, 13]
    mancomb = (115, 18)
    estevan = (194, 10)
    loom = (250, 10)
    village_scummbar_door = (713, 11)
    village_cliffside = (8, 71)
    lookout_stairs = (248, 2)
    lookout_path = (320, 62)
    melee_village = (76, 79)
    melee_clearing = (135, 113)
    melee_fork = (74, 112)
    clearing_path = (496, 4)
    village1_archway = (1008, 34)
    village2_archway = (436, 34)
    village2_archway3 = (160, 59)
    village3_archway = (749, 13)
    village3_alley = (605, 55)
    village_store_door = (670, 23)
    circus_tent = (83, 60)
    circus_entry = (294,32)
    store_entry = (83, 16)
    forest1_entry = (310, 35)
    f1f2 = (238,69)
    f1f2b = (154,69)
    village2_voodoolady = (220, 48)
    voodoolady_door = (108,36)

positions = {
    0: ['village1', pos.village_cliffside, 'e', 'walkarea_0'],
    1: ['lookout', pos.lookout_stairs, 'n', 'walkarea_0'],
    2: ['meleemap', pos.melee_village, 'n', 'walkarea_0'],
    3: ['lookout', pos.lookout_path, 'w', 'walkarea_0'],
    4: ['village2', pos.village2_archway, 's', 'walkarea_0'],
    5: ['village1', pos.village1_archway, 'w', 'walkarea_0'],
    6: ['scummbar', pos.scummbar_main_door, 'e', 'walkarea_0'],
    7: ['voodoolady', pos.voodoolady_door, 'e', 'walkarea_0'],
    8: ['kitchen', pos.kitchen_door, 'e', 'walkarea_0'],
    9: ['scummbar', pos.scummbar_kitchen_door, 'w', 'walkarea_0']
}


class colors:
    guybrush_text = utils.rgb(255, 255, 255)
    cook_text = utils.rgb(85, 255, 255)


# doors can be open, closed or locked
# locked doors cannot be opened. only closed doors can.
class doors:
    scummbar = 'closed'
    voodoolady = 'closed'
    kitchen = 'closed'
    pier = 'closed'

seagull_on_plank = False
seagull_jump = 1
fish_not_taken = True
talked_to_lookout = 0

def is_pier_door_closed():
    return doors.pier == 'closed'


def _select_lookout0():
    return 0 if talked_to_lookout == 0 else 1

def _select_lookout5():
    return 0 if mopy.monkey.engine.data.dialogues['lookout']['lines'][4].get('clicked', 0) else 1

def _select__walkdoor(args):
    door_id = sc.get_item(args[0])['door']
    if getattr(doors, door_id) == 'open':
        return 1
    return 0

def _select_open_door_scummbar_kitchen(args):
    cook = example.get('cook')
    if cook.valid:
        if cook.x > 320:
            return 0
        return 1
    return 2

def _select_walkto_door_scummbar_kitchen(args):
    if doors.kitchen == 'closed':
        return 0
    else:
        cook = example.get('cook')
        if cook.valid:
            if cook.x > 320:
                return 1
            return 2
        return 0


def _select_pickup_fish(args):
    return 1

def _select_cook_init(args):
    if mopy.monkey.engine.previous_room == 'kitchen':
        return 1
    return 0