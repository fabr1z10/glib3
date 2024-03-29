import mopy.util

sci_viewport = (0, 0, 320, 190)
current_player = 'graham'
default_text_offset =(0, 0)
default_speed = 50
use_keyboard = True

actions = ['walk', 'look', 'use', 'talk', -1]
# action number 0 must always be the walk action!
current_action = 0

max_score = 158
score = 0
ui_txt_color = mopy.util.rgb(238, 207, 165)
msg_font = 'fonts.msg'
msg_inner_texture = 'gfx/txtbg.png'
msg_border_texture = 'gfx/txtbordr.png'

inventory = dict()