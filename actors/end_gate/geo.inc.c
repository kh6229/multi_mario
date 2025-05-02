#include "src/game/envfx_snow.h"

const GeoLayout end_gate_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, end_gate_End_Gate_Visual_mesh_layer_1),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
