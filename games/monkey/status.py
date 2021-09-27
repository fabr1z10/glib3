import vars


class doors:
    kitchen = "closed"
    pier = "closed"
    scummbar = "closed"
    store = 'closed'

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


class colors:
    cook_text_color = [85, 255, 255, 255]

seagull_on_plank = False
seagull_jump = 1
meat_in_pot = False
pirates_know_guybrush = 0
cook_in_kitchen = True
circus_status = 0
circus_feat_done = 0
talked_to_lookout = 0
knows_sword_price = 0
knows_shovel_price = 0
paid_sword = 0
paid_shovel = 0


def has_sword_not_paid():
    return 'sword' in vars.inventory and paid_sword == 0

def enough_money_for_sword():
    return vars.inventory.get('pieces_of_eight', 0) >= 100

def has_shovel_not_paid():
    return 'shovel' in vars.inventory and paid_shovel == 0