#include <ultra64.h>
#include "sm64.h"
#include "behavior_data.h"
#include "model_ids.h"
#include "seq_ids.h"
#include "dialog_ids.h"
#include "segment_symbols.h"
#include "level_commands.h"

#include "game/level_update.h"

#include "levels/scripts.h"

#include "actors/common1.h"
#include "make_const_nonconst.h"
#include "levels/bob/header.h"

/* Fast64 begin persistent block [scripts] */
/* Fast64 end persistent block [scripts] */

const LevelScript level_bob_entry[] = {
	INIT_LEVEL(),
	LOAD_YAY0(0x07, _bob_segment_7SegmentRomStart, _bob_segment_7SegmentRomEnd), 
	LOAD_YAY0_TEXTURE(0x09, _generic_yay0SegmentRomStart, _generic_yay0SegmentRomEnd), 
	LOAD_YAY0(0x0A, _water_skybox_yay0SegmentRomStart, _water_skybox_yay0SegmentRomEnd), 
	LOAD_YAY0(0x05, _group3_yay0SegmentRomStart, _group3_yay0SegmentRomEnd), 
	LOAD_RAW(0x0C, _group3_geoSegmentRomStart, _group3_geoSegmentRomEnd), 
	LOAD_YAY0(0x06, _group14_yay0SegmentRomStart, _group14_yay0SegmentRomEnd), 
	LOAD_RAW(0x0D, _group14_geoSegmentRomStart, _group14_geoSegmentRomEnd), 
	LOAD_YAY0(0x08, _common0_yay0SegmentRomStart, _common0_yay0SegmentRomEnd), 
	LOAD_RAW(0x0F, _common0_geoSegmentRomStart, _common0_geoSegmentRomEnd), 
	ALLOC_LEVEL_POOL(),
	MARIO(MODEL_MARIO, 0x00000001, bhvMario), 
	JUMP_LINK(script_func_global_1), 
	JUMP_LINK(script_func_global_4), 
	JUMP_LINK(script_func_global_15), 
	LOAD_MODEL_FROM_GEO(MODEL_BOB_BUBBLY_TREE, bubbly_tree_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_BOB_CHAIN_CHOMP_GATE, bob_geo_000440), 
	LOAD_MODEL_FROM_GEO(MODEL_BOB_SEESAW_PLATFORM, bob_geo_000458), 
	LOAD_MODEL_FROM_GEO(MODEL_BOB_BARS_GRILLS, bob_geo_000470), 
	/* Fast64 begin persistent block [level commands] */
	/* Fast64 end persistent block [level commands] */

	AREA(1, bob_area_1),
		WARP_NODE(0x0A, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0xF0, LEVEL_CASTLE, 0x01, 0x32, WARP_NO_CHECKPOINT),
		WARP_NODE(0xF1, LEVEL_CASTLE, 0x01, 0x64, WARP_NO_CHECKPOINT),
		OBJECT(MODEL_BLACK_BOBOMB, -3477, -156, -2814, 0, 0, 0, 0x00000000, bhvBobomb),
		OBJECT(MODEL_BLACK_BOBOMB, -2669, -156, -3145, 0, 0, 0, 0x00000000, bhvBobomb),
		OBJECT(MODEL_BLACK_BOBOMB, -3494, -156, -1679, 0, 0, 0, 0x00000000, bhvBobomb),
		OBJECT(MODEL_BLACK_BOBOMB, -3149, -156, -767, 0, 0, 0, 0x00000000, bhvBobomb),
		OBJECT(MODEL_DIRECTION_PLATE, -6876, 2539, -2602, 0, 0, 0, 0x00000000, bhvDirectionPlate),
		MARIO_POS(0x01, -180, 2035, 737, 2144),
		OBJECT(MODEL_NONE, 638, 813, 2041, 0, -180, 0, (COOP_CM_NPC << 16), bhvSpawnCoopMario),
		OBJECT(MODEL_NONE, 638, 810, 1541, 0, -180, 0, (COOP_CM_NPC << 16), bhvSpawnCoopMario),
		OBJECT(MODEL_NONE, 638, 786, 1041, 0, -180, 0, (COOP_CM_NPC << 16), bhvSpawnCoopMario),
		OBJECT(MODEL_MINI_MARIO_BUTTON, -272, 801, -302, 0, 0, 0, 0x00000000, bhvMiniMarioButton),
		OBJECT(MODEL_EXCLAMATION_POINT_2, 2035, 150, 2144, 0, 0, 0, (0x01 << 16), bhvTextTrigger),
		OBJECT(MODEL_EXCLAMATION_POINT_2, -272, 781, 187, 0, 0, 0, (0x02 << 16), bhvTextTrigger),
		OBJECT(MODEL_EXCLAMATION_POINT_2, -1618, -155, -2679, 0, 0, 0, (0x03 << 16), bhvTextTrigger),
		OBJECT(MODEL_EXCLAMATION_POINT_2, -5812, 1698, -359, 0, 0, 0, (0x04 << 16), bhvTextTrigger),
		OBJECT(MODEL_BOB_BUBBLY_TREE, 1551, 100, 693, 0, 0, 0, 0x00000000, bhvTree),
		OBJECT(MODEL_BOB_BUBBLY_TREE, 1423, 113, -800, 0, 0, 0, 0x00000000, bhvTree),
		OBJECT(MODEL_TURN_PLANE, 638, -155, -2982, 0, -90, 0, 0x00024000, bhvTurnPlane),
		OBJECT(MODEL_TURN_PLANE, -2940, -155, -2982, 0, 0, 0, 0x00014000, bhvTurnPlane),
		OBJECT(MODEL_TURN_PLANE, -3005, 996, 2527, 0, 0, 0, 0x0000C000, bhvTurnPlane),
		OBJECT(MODEL_TURN_PLANE, -3005, 445, 1629, 0, 0, 0, 0x0000C000, bhvTurnPlane),
		OBJECT(MODEL_TURN_PLANE, -4449, 445, 1629, 0, 0, 0, 0x00004000, bhvTurnPlane),
		OBJECT(MODEL_TURN_PLANE, -4449, 595, 2078, 0, 0, 0, 0x00004000, bhvTurnPlane),
		OBJECT(MODEL_TURN_PLANE, -3005, 845, 2078, 0, 0, 0, 0x0000C000, bhvTurnPlane),
		OBJECT(MODEL_TURN_PLANE, -6798, 1912, 2527, 0, 0, 0, 0x0000C000, bhvTurnPlane),
		OBJECT(MODEL_NONE, 2035, 737, 2144, 0, -180, 0, (0x0A << 16), bhvSpinAirborneWarp),
		TERRAIN(bob_area_1_collision),
		MACRO_OBJECTS(bob_area_1_macro_objs),
		SET_BACKGROUND_MUSIC(0x00, SEQ_LEVEL_GRASS),
		TERRAIN_TYPE(TERRAIN_GRASS),
		/* Fast64 begin persistent block [area commands] */
		/* Fast64 end persistent block [area commands] */
	END_AREA(),
	FREE_LEVEL_POOL(),
	MARIO_POS(0x01, -180, 2035, 737, 2144),
	CALL(0, lvl_init_or_update),
	CALL_LOOP(1, lvl_init_or_update),
	CLEAR_LEVEL(),
	SLEEP_BEFORE_EXIT(1),
	EXIT(),
};