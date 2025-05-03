void bhv_turn_plane_loop(void) {

}

void bhv_turn_plane_init(void) {
    o->oTurnPlaneType = o->oBehParams2ndByte;
    o->oTurnPlaneYaw  = GET_BPARAM34(o->oBehParams);
}