#include "DAH_header.h"
#include "recompconfig.h"

void Player_Action_54(Player* this, PlayState* play);

enum config_options_swimming {
    CONFIG_TRUE,
    CONFIG_FALSE,
};

bool DekuDive(CONDITION_PARAMETERS) {
    if ((recomp_get_config_u32("Allow_Deku_Swim") == CONFIG_TRUE) && (this->transformation == PLAYER_FORM_DEKU) && (this->stateFlags1 & PLAYER_STATE1_8000000)) {
        *doAction = DO_ACTION_DIVE;
        return true; 
    }
    
    return false;
}

DAH_ON_INIT void DAH_on_init() {
    DoActionHelper_RegisterAction(ACTION, DekuDive, 1, "InfiniteHops");
}
