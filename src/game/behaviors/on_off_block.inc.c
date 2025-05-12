static struct ObjectHitbox sOnOffBlockHitbox = {
    /* interactType:      */ INTERACT_BREAKABLE,
    /* downOffset:        */ 10,
    /* damageOrCoinValue: */ 0,
    /* health:            */ 0,
    /* numLootCoins:      */ 0,
    /* radius:            */ 60,
    /* height:            */ 110,
    /* hurtboxRadius:     */ 60,
    /* hurtboxHeight:     */ 110,
};

Gfx *geo_switch_on_off_block(s32 callContext, struct GraphNode *node, UNUSED Mat4 *mtx) {
    if (callContext == GEO_CONTEXT_RENDER) {
        struct Object *obj = (struct Object *) gCurGraphNodeObject;
        struct GraphNodeSwitchCase *switchCase = (struct GraphNodeSwitchCase *) node;
        
        switch (obj->oOnOffBlockState) {
            case ON_OFF_BLOCK_STATE_RED:
                switchCase->selectedCase = ON_OFF_BLOCK_ANIM_STATE_RED;
                break;
            case ON_OFF_BLOCK_STATE_BLUE:
                switchCase->selectedCase = ON_OFF_BLOCK_ANIM_STATE_BLUE;
                break;
            default:
                switchCase->selectedCase = ON_OFF_BLOCK_ANIM_STATE_RED;
                break;
        }
    }
    return NULL;
}

void on_off_block_change_colors(void) {
    if (o->oOnOffBlockState == ON_OFF_BLOCK_STATE_RED) {
        o->oOnOffBlockState = ON_OFF_BLOCK_STATE_BLUE;
    } else {
        o->oOnOffBlockState = ON_OFF_BLOCK_STATE_RED;
    }
}

void bhv_on_off_block_loop(void) {
    switch (o->oAction) {
        case 0:
            o->oOnOffBlockState = ON_OFF_BLOCK_STATE_RED;
            cur_obj_unhide();
            cur_obj_become_tangible();
            obj_set_hitbox(o, &sOnOffBlockHitbox);
            o->oAction = 1;
            break;
        case 1:
            cur_obj_become_tangible();
            if (cur_obj_was_attacked_or_ground_pounded()) {
                on_off_block_change_colors();
                o->oAction++;
            } else {
                load_object_collision_model();
            }
            break;

        case 2:
            cur_obj_become_intangible();
            if (o->oTimer < 3) {
                o->oPosY += 15;
            } else if (o->oTimer >= 3 && o->oTimer < 6) {
                o->oPosY -= 15;
            } else if (o->oTimer > 25) {
                o->oAction = 1;
            }
    }
}

