#include "src/game/envfx_snow.h"

const GeoLayout on_off_block_Switch_opt1[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 0, 0, on_off_block_switch_option_1_mesh_layer_1_mat_override_f3dlite_material_008_0),
	GEO_CLOSE_NODE(),
	GEO_RETURN(),
};
const GeoLayout on_off_block_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_SWITCH_CASE(0, geo_switch_on_off_block),
		GEO_OPEN_NODE(),
			GEO_NODE_START(),
			GEO_OPEN_NODE(),
				GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 0, 0, on_off_block_switch_option_1_mesh_layer_1),
			GEO_CLOSE_NODE(),
			GEO_BRANCH(1, on_off_block_Switch_opt1),
		GEO_CLOSE_NODE(),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
