#include "types.h"

#ifndef MARIO_COOP_H
#define MARIO_COOP_H

enum {
    COOP_CM_TAKE_TURNS, // Player controls one Mario at a time, press L to change active Mario
    COOP_CM_ALL_ACTIVE, // Player controls every Mario at once, press L to change Mario perspective
    COOP_CM_NPC, // Player only controls Mario 0, other Marios use
    COOP_CM_CUSTOM // For custom programmed behavior
};
#define COOP_CONTROL_MODE COOP_CM_TAKE_TURNS

#define COOP_MARIO_HITBOX_SIZE 80.0f // For Mario vs. Mario collision

#define COOP_MARIO_STATES_MAX 10 // Maximum amount of Marios allowed to be spawned at once
/*
If the emulator crashes from spawning too many Marios, try increasing GFX_POOL_SIZE in config_graphics.h
If the game freezes with music still playing from spawning too many Marios, try increasing OBJECT_POOL_CAPACITY in object_list_processor.h
*/

// Comment out to disable
#define COOP_MAIN_MARIO_MUST_LIVE // If defined, game over when your initial Mario dies
#define COOP_DEBUG_SPAWN_MARIO_WITH_DDOWN // If defined, spawn Mario when pressing D-Pad down
#define COOP_SNAPPY_SWAP_CAMERA // If defined, camera will swap instantly instead of gradually

extern int gCoopActiveMarios;
extern int gCoopActiveMarioIndex;

struct MarioState * coop_spawn_mario_with_id(Vec3f pos, int marioID);
struct MarioState * coop_spawn_mario(Vec3f pos);
void coop_give_control_to_next(void);
int coop_delete_mario(struct MarioState * m);

void coop_npc_behavior(struct MarioState * m);

void coop_reset_state(void);
void coop_mario_collision(struct MarioState * m);

#endif