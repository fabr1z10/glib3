##########################
# main function
# ----------------------------------------------
#  this shouldn't change much across games.
#  Typically you call startUp and init factories to initialize
#  factories for rooms and items.

import example
import sys
import vars as v

from pathlib import Path

# add folder
path = Path(__file__)
sys.path.append(str(path.parent.parent / 'lib'))

import lib.engine as eng

engine = eng.Engine()

engine.vars = v
#engine.startUp()

#initFactories()
