import mopy.util as utils


class pos:
    kitchen_door = [45, 12]
    scummbar_main_door = [64, 19]
    scummbar_kitchen_door = [595, 13]
    estevan = (194, 10)
    loom = (250, 10)
    village_scummbar_door = (713, 11)
    village_cliffside = (8, 71)
    lookout_stairs = (248, 2)
    lookout_path = (320, 62)
    melee_village = (0, 0)
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

positions = {
    0: ['village1', pos.village_cliffside, 'e', 'walkarea_0'],
    1: ['lookout', pos.lookout_stairs, 'n', 'walkarea_0']
}


class colors:
    guybrush_text = utils.rgb(255, 255, 255)
    cook_text = utils.rgb(85, 255, 255)

class doors:
    scummbar = 'closed'
    voodoolady = 'closed'
    kitchen = 'closed'
    pier = 'closed'

seagull_on_plank = False
seagull_jump = 1
fish_not_taken = True

def is_pier_door_closed():
    return doors.pier == 'closed'


