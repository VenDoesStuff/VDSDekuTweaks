#ifndef DAH_HEADER

#define DAH_HEADER

#include "global.h"
#include "modding.h"

#define CONDITION_PARAMETERS DoAction* doAction, PlayState* play, Player* this

typedef enum {
    ATTACK_GORON,
    ATTACK_ZORA,
    ATTACK_DEKU,
    ATTACK_HUMAN,
    ACTION
} DoActionLevel;

typedef bool (*DoActionCondition) (CONDITION_PARAMETERS);

RECOMP_IMPORT("mm_recomp_do_action_helper", void DoActionHelper_RegisterAction(DoActionLevel level, DoActionCondition condition, unsigned int priority, char name[32]));

#define DAH_ON_INIT RECOMP_CALLBACK("mm_recomp_do_action_helper", DAH_on_init)

#endif // DAH_HEADER