Vtx on_off_block_Cube_mesh_layer_1_vtx_cull[8] = {
	{{ {-100, 0, 100}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {-100, 200, 100}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {-100, 200, -100}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {-100, 0, -100}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {100, 0, 100}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {100, 200, 100}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {100, 200, -100}, 0, {0, 0}, {0, 0, 0, 0} }},
	{{ {100, 0, -100}, 0, {0, 0}, {0, 0, 0, 0} }},
};

Vtx on_off_block_Cube_mesh_layer_1_vtx_0[14] = {
	{{ {-100, 0, 100}, 0, {368, 1008}, {183, 183, 73, 255} }},
	{{ {-100, 200, 100}, 0, {624, 1008}, {183, 73, 73, 255} }},
	{{ {-100, 200, -100}, 0, {624, 752}, {183, 73, 183, 255} }},
	{{ {-100, 0, -100}, 0, {368, 752}, {183, 183, 183, 255} }},
	{{ {100, 200, -100}, 0, {624, 496}, {73, 73, 183, 255} }},
	{{ {100, 0, -100}, 0, {368, 496}, {73, 183, 183, 255} }},
	{{ {100, 200, 100}, 0, {624, 240}, {73, 73, 73, 255} }},
	{{ {-100, 200, 100}, 0, {880, 240}, {183, 73, 73, 255} }},
	{{ {-100, 200, -100}, 0, {880, 496}, {183, 73, 183, 255} }},
	{{ {100, 0, 100}, 0, {368, 240}, {73, 183, 73, 255} }},
	{{ {-100, 200, 100}, 0, {624, -16}, {183, 73, 73, 255} }},
	{{ {-100, 0, 100}, 0, {368, -16}, {183, 183, 73, 255} }},
	{{ {-100, 0, -100}, 0, {112, 496}, {183, 183, 183, 255} }},
	{{ {-100, 0, 100}, 0, {112, 240}, {183, 183, 73, 255} }},
};

Gfx on_off_block_Cube_mesh_layer_1_tri_0[] = {
	gsSPVertex(on_off_block_Cube_mesh_layer_1_vtx_0 + 0, 14, 0),
	gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
	gsSP2Triangles(3, 2, 4, 0, 3, 4, 5, 0),
	gsSP2Triangles(5, 4, 6, 0, 4, 7, 6, 0),
	gsSP2Triangles(4, 8, 7, 0, 5, 6, 9, 0),
	gsSP2Triangles(9, 6, 10, 0, 9, 10, 11, 0),
	gsSP2Triangles(12, 5, 9, 0, 12, 9, 13, 0),
	gsSPEndDisplayList(),
};


Gfx mat_on_off_block_f3dlite_material_007[] = {
	gsSPLightColor(LIGHT_1, 0xFF0000FF),
	gsSPLightColor(LIGHT_2, 0x7F0000FF),
	gsDPPipeSync(),
	gsDPSetCombineLERP(0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT, 0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT),
	gsDPSetAlphaDither(G_AD_NOISE),
	gsSPTexture(65535, 65535, 0, 0, 1),
	gsSPEndDisplayList(),
};

Gfx mat_revert_on_off_block_f3dlite_material_007[] = {
	gsDPPipeSync(),
	gsDPSetAlphaDither(G_AD_DISABLE),
	gsSPEndDisplayList(),
};

Gfx on_off_block_Cube_mesh_layer_1[] = {
	gsSPClearGeometryMode(G_LIGHTING),
	gsSPVertex(on_off_block_Cube_mesh_layer_1_vtx_cull + 0, 8, 0),
	gsSPSetGeometryMode(G_LIGHTING),
	gsSPCullDisplayList(0, 7),
	gsSPDisplayList(mat_on_off_block_f3dlite_material_007),
	gsSPDisplayList(on_off_block_Cube_mesh_layer_1_tri_0),
	gsSPDisplayList(mat_revert_on_off_block_f3dlite_material_007),
	gsDPPipeSync(),
	gsSPSetGeometryMode(G_LIGHTING),
	gsSPClearGeometryMode(G_TEXTURE_GEN),
	gsDPSetCombineLERP(0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT, 0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT),
	gsSPTexture(65535, 65535, 0, 0, 0),
	gsDPSetEnvColor(255, 255, 255, 255),
	gsDPSetAlphaCompare(G_AC_NONE),
	gsSPEndDisplayList(),
};

