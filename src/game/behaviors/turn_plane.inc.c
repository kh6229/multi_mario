void bhv_turn_plane_loop(void) {
    switch (o->oAction) {
        case 0:
            if (o->oTimer == 5) {
                for (u8 i = 0; i < COOP_MARIO_STATES_MAX; i++) {
                    struct MarioState * m = &gMarioStates[i];
                    if (m->marioObj != NULL && m->controlMode == COOP_CM_NPC) {
                        o->oTurnPlaneMiniMarioCount++;
                    }
                }
                o->oAction = 1;
            }
            break;

        case 1:
            if (o->oTurnPlaneType != TURN_PLANE_TYPE_STAY) {
                for (u8 i = 0; i < COOP_MARIO_STATES_MAX; i++) {
                    struct MarioState * m = &gMarioStates[i];
                    if (m->marioObj != NULL && m->controlMode == COOP_CM_NPC && m->marioObj->platform == o && o->oTurnPlaneCooldown == 0) {
                        o->oTurnPlaneMariosTurned++;
                        o->oTurnPlaneCooldown = 30;
                    }
                }

                if (o->oTurnPlaneCooldown > 0) {
                    o->oTurnPlaneCooldown--;
                }
            }
            break;
    }
    o->prevObj->oAnimState = o->oTurnPlaneMariosTurned;
}

void bhv_turn_plane_init(void) {
    o->prevObj = spawn_object(o,MODEL_NUMBER,bhvWeightPlateNumber);
    o->prevObj->oPosY += 400.0f;
    o->prevObj->oAnimState = 0;

    o->oTurnPlaneType         = o->oBehParams2ndByte;
    o->oTurnPlaneYaw          = GET_BPARAM34(o->oBehParams);
    o->oTurnPlaneMariosTurned = 0;
    o->oTurnPlaneMiniMarioCount = 0;
    o->oTurnPlaneCooldown = 0;
    o->oAction = 0;
}