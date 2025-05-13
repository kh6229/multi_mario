static struct ObjectHitbox sOnOffBlockHitbox = {
    /* interactType:      */ INTERACT_BREAKABLE,
    /* downOffset:        */ 20,
    /* damageOrCoinValue: */ 0,
    /* health:            */ 0,
    /* numLootCoins:      */ 0,
    /* radius:            */ 70,
    /* height:            */ 120,
    /* hurtboxRadius:     */ 70,
    /* hurtboxHeight:     */ 120,
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

Gfx *geo_switch_colored_block(s32 callContext, struct GraphNode *node, UNUSED Mat4 *mtx) {
    if (callContext == GEO_CONTEXT_RENDER) {
        struct Object *obj = (struct Object *) gCurGraphNodeObject;
        struct GraphNodeSwitchCase *switchCase = (struct GraphNodeSwitchCase *) node;

        switch (obj->oColoredBlockState) {
            case COLORED_BLOCK_TRANSPARENT:
                switchCase->selectedCase = COLORED_BLOCK_ANIM_STATE_TRANSPARENT;
                break;
            case COLORED_BLOCK_SOLID:
                switchCase->selectedCase = COLORED_BLOCK_ANIM_STATE_SOLID;
                break;
            default:
                switchCase->selectedCase = COLORED_BLOCK_ANIM_STATE_TRANSPARENT;
                break;
        }
    }
    return NULL;
}

void bhv_colored_block_loop(void) {
    struct Object *parentBlock = cur_obj_nearest_object_with_behavior(bhvOnOffBlock);
    switch (o->oAction) {
        case 0:
            o->oColoredBlockColor = o->oBehParams2ndByte;
            o->oColoredBlockState = COLORED_BLOCK_TRANSPARENT;
            o->oAction = 1;
            break;
        case 1:
            if (parentBlock != NULL && parentBlock->oOnOffBlockState == o->oColoredBlockColor) {
                o->oColoredBlockState = COLORED_BLOCK_SOLID;
                load_object_collision_model();
            } else {
                o->oColoredBlockState = COLORED_BLOCK_TRANSPARENT;
            }
    }
}

void on_off_block_change_colors(void) {
    if (o->oOnOffBlockState == ON_OFF_BLOCK_STATE_RED) {
        o->oOnOffBlockState = ON_OFF_BLOCK_STATE_BLUE;
    } else {
        o->oOnOffBlockState = ON_OFF_BLOCK_STATE_RED;
    }
}

void bhv_on_off_block_loop(void) {
    struct Object * nearestBlock = cur_obj_nearest_object_with_behavior(bhvOnOffBlock);
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
            if (nearestBlock != NULL && nearestBlock->oOnOffBlockState != o->oOnOffBlockState) {
                on_off_block_change_colors();
            }
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

