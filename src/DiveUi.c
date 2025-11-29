#include "DAH_header.h"

void Player_Action_54(Player* this, PlayState* play);
bool isDekuSwimming = false;

bool DekuDive(CONDITION_PARAMETERS) {
    if ((this->transformation == PLAYER_FORM_DEKU) && (this->stateFlags1 & PLAYER_STATE1_8000000)) {
        *doAction = DO_ACTION_DIVE;
        return true;
    }
    
    return false;
}

DAH_ON_INIT void DAH_on_init() {
    DoActionHelper_RegisterAction(ACTION, DekuDive, 1, "InfiniteHops");
}