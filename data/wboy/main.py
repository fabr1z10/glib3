##########################
# main function
# ----------------------------------------------
#  this shouldn't change much across games. 
#  Typically you call startUp and init factories to initialize
#  factories for rooms and items.

import example
import lib_py.engine as engine

from factories.init import initFactories

engine.startUp()

initFactories()
