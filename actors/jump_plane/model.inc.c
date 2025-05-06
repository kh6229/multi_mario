Vtx jump_plane_Jump_Plane_mesh_layer_1_vtx_cull[8] = {
	{{ {-100, 0, 100}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {-100, 0, 100}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {-100, 0, -100}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {-100, 0, -100}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {100, 0, 100}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {100, 0, 100}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {100, 0, -100}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {100, 0, -100}, 0, {0, 0}, {0, 0, 0, 0} }},
};

Vtx jump_plane_Jump_Plane_mesh_layer_1_vtx_0[3] = {
	{{ {100, 0, 100}, 0, {1008, 1008}, {0, 127, 0, 255} }},
	{{ {-100, 0, -100}, 0, {-16, -16}, {0, 127, 0, 255} }},
	{{ {-100, 0, 100}, 0, {-16, 1008}, {0, 127, 0, 255} }},
};

Gfx jump_plane_Jump_Plane_mesh_layer_1_tri_0[] = {
	gsSPVertex(jump_plane_Jump_Plane_mesh_layer_1_vtx_0 + 0, 3, 0),
	gsSP1Triangle(0, 1, 2, 0),
	gsSPEndDisplayList(),
};


Gfx mat_jump_plane_f3dlite_material_005[] = {
	gsSPLightColor(LIGHT_1, 0xFF00FFFF),
	gsSPLightColor(LIGHT_2, 0x7F007FFF),
	gsDPPipeSync(),
	gsDPSetCombineLERP(0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT, 0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT),
	gsDPSetAlphaDither(G_AD_NOISE),
	gsSPTexture(65535, 65535, 0, 0, 1),
	gsSPEndDisplayList(),
};

Gfx mat_revert_jump_plane_f3dlite_material_005[] = {
	gsDPPipeSync(),
	gsDPSetAlphaDither(G_AD_DISABLE),
	gsSPEndDisplayList(),
};

Gfx jump_plane_Jump_Plane_mesh_layer_1[] = {
	gsSPClearGeometryMode(G_LIGHTING),
	gsSPVertex(jump_plane_Jump_Plane_mesh_layer_1_vtx_cull + 0, 8, 0),
	gsSPSetGeometryMode(G_LIGHTING),
	gsSPCullDisplayList(0, 7),
	gsSPDisplayList(mat_jump_plane_f3dlite_material_005),
	gsSPDisplayList(jump_plane_Jump_Plane_mesh_layer_1_tri_0),
	gsSPDisplayList(mat_revert_jump_plane_f3dlite_material_005),
	gsDPPipeSync(),
	gsSPSetGeometryMode(G_LIGHTING),
	gsSPClearGeometryMode(G_TEXTURE_GEN),
	gsDPSetCombineLERP(0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT, 0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT),
	gsSPTexture(65535, 65535, 0, 0, 0),
	gsDPSetEnvColor(255, 255, 255, 255),
	gsDPSetAlphaCompare(G_AC_NONE),
	gsSPEndDisplayList(),
};

