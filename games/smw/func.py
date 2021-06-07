import vars
import example
import entity
import components as compo
import shapes as sh


def toggle_pause():
    return


def restart():
    vars.invincibility = False
    vars.currentWarp = -1
    example.restart()