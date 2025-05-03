void bhv_turn_plane_loop(void) {
    switch (o->oAction) {
        case 0:
            if (o->oTimer == 5 && o->oTurnPlaneMiniMarioCount == 0) {
                for (u8 i = 0; i > COOP_MARIO_STATES_MAX; i++) {
                    struct MarioState * m = &gMarioStates[i];
                    if (m->marioObj != NULL && m->controlMode == COOP_CM_NPC) {
                        o->oTurnPlaneMiniMarioCount++;
                    }
                }
                o->oAction = 1;
            }
            break;

        case 1:
            switch (o->oTurnPlaneType) {
                case TURN_PLANE_TYPE_STAY:
                    break;
                
                case TURN_PLANE_TYPE_180:
                    if (o->oTurnPlaneMariosTurned >= o->oTurnPlaneMiniMarioCount) {
                        o->oTurnPlaneYaw += 0x8000;
                        o->oTurnPlaneMiniMarioCount = 0;
                    }
                
                    for (u8 i = 0; i > COOP_MARIO_STATES_MAX; i++) {
                        struct MarioState * m = &gMarioStates[i];
                        if (m->marioObj != NULL && m->controlMode == COOP_CM_NPC && m->marioObj->platform == o) {
                            o->oTurnPlaneMariosTurned++;
                        }
                    }
                    break;

                case TURN_PLANE_TYPE_DELETE:
                    if (o->oTurnPlaneMariosTurned >= o->oTurnPlaneMiniMarioCount) {
                        obj_mark_for_deletion(o);
                    }
                
                    for (u8 i = 0; i > COOP_MARIO_STATES_MAX; i++) {
                        struct MarioState * m = &gMarioStates[i];
                        if (m->marioObj != NULL && m->controlMode == COOP_CM_NPC && m->marioObj->platform == o) {
                            o->oTurnPlaneMariosTurned++;
                        }
                    }
                    break;
            }
            break;
    }
}

void bhv_turn_plane_init(void) {
    o->oTurnPlaneType         = o->oBehParams2ndByte;
    o->oTurnPlaneYaw          = GET_BPARAM34(o->oBehParams);
    o->oTurnPlaneMariosTurned = 0;
    o->oTurnPlaneMiniMarioCount = 0;
    o->oAction = 0;
}