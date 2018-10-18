#pragma once
#include <gfx/entitywrapper.h>

// lua lang extension for Platformer


void RegisterToPlatform(EntityWrapper character, EntityWrapper platform);
void UnregisterToPlatform(EntityWrapper character, EntityWrapper platform);