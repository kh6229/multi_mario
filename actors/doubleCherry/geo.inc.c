#include "src/game/envfx_snow.h"

const GeoLayout doubleCherry_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_SHADOW(1, 204, 200),
		GEO_OPEN_NODE(),
			GEO_DISPLAY_LIST(LAYER_OPAQUE, doubleCherry_doubleCherry_mesh_layer_1),
			GEO_DISPLAY_LIST(LAYER_ALPHA, doubleCherry_doubleCherry_mesh_layer_4),
		GEO_CLOSE_NODE(),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
