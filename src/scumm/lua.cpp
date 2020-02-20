#include "factories.h"
#include "components/character.h"

char GetDirection(EntityWrapper* e) {
    e->m_underlying->GetComponent<StateCharacter>()->GetDirection();
}