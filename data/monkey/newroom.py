import os
import sys
import shutil

nd = "./rooms/" + sys.argv[1]
gfx = "./gfx/" + sys.argv[1]
if os.path.exists(nd) or os.path.exists(gfx):
	print (sys.argv[1] + " exists!")
else:
	os.makedirs(nd)
	os.makedirs(gfx)
	shutil.copyfile("./templates/room.lua", nd +"/room.lua")
	open(nd+"/items.lua", 'w').close()
	print ("Created new room " + sys.argv[1])