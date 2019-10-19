#pragma once
#include <gfx/entitywrapper.h>

// lua lang extension for Platformer

void SetEnemyDir (EntityWrapper character, bool left);
void RegisterToPlatform(EntityWrapper character, EntityWrapper platform);
void UnregisterToPlatform(EntityWrapper character, EntityWrapper platform);