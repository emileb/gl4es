#include "gl.h"

#ifndef GL_STATE_H
#define GL_STATE_H

#include "eval.h"
#include "texture.h"
#include "buffers.h"
#include "queries.h"
#include "light.h"
#include "fog.h"
#include "texenv.h"
#include "shader.h"
#include "vertexattrib.h"
#include "program.h"
#include "fpe.h"
#include "pointsprite.h"

typedef struct {
    GLboolean line_stipple,
              auto_normal,
              normalize,
              normal_rescale,
              lighting,
              alpha_test,
              fog,
              color_material,
              blend,
              cull_face,
              color_sum,
              depth_test,
              pointsprite,
              texgen_s[MAX_TEX],
              texgen_t[MAX_TEX],
              texgen_r[MAX_TEX],
              texgen_q[MAX_TEX],
              plane[MAX_CLIP_PLANES],
              light[MAX_LIGHT],
              map1_color4,
              map1_index,
              map1_normal,
              map1_texture1,
              map1_texture2,
              map1_texture3,
              map1_texture4,
              map1_vertex3,
              map1_vertex4,
              map2_color4,
              map2_index,
              map2_normal,
              map2_texture1,
              map2_texture2,
              map2_texture3,
              map2_texture4,
              map2_vertex3,
              map2_vertex4,
              color_logic_op,
              line_smooth,
              point_smooth,
              multisample,
              sample_coverage,
              sample_alpha_to_one,
              sample_alpha_to_coverage;
    GLuint    texture[MAX_TEX]; // flag
} enable_state_t;

typedef struct {
    GLenum S;
    GLenum T;
    GLenum R;
    GLenum Q;
    GLfloat S_E[4]; // Eye Plane
    GLfloat T_E[4];
    GLfloat R_E[4];
    GLfloat Q_E[4];
    GLfloat S_O[4]; // Object Plane
    GLfloat T_O[4];
    GLfloat R_O[4];
    GLfloat Q_O[4];
} texgen_state_t;

typedef struct {
    texenv_t        env;
    texfilter_t     filter;
} texenv_state_t;

typedef struct {
    GLuint unpack_row_length,
           unpack_skip_pixels,
           unpack_skip_rows,
           unpack_image_height;
    GLboolean unpack_lsb_first;
    // TODO: use those values
    GLuint pack_row_length,
           pack_skip_pixels,
           pack_skip_rows,
           pack_image_height;
    GLuint  pack_align,
            unpack_align;            
    GLboolean pack_lsb_first;
    gltexture_t *bound[MAX_TEX][ENABLED_TEXTURE_LAST];
    gltexture_t *zero;  // this is texture 0...
    GLboolean pscoordreplace[MAX_TEX];
    khash_t(tex) *list;
    GLuint active;	// active texture
	GLuint client;	// client active texture
} texture_state_t;

typedef struct {
    renderlist_t *active;
    GLboolean compiling;
    GLboolean pending;
    GLboolean begin;
    GLuint base;
    GLuint name;
    GLenum mode;

    GLuint count;
    GLuint cap;
} displaylist_state_t;

typedef struct {
    rasterpos_t rPos;
    viewport_t viewport;
    GLfloat raster_scale[4];
    GLfloat raster_bias[4];
    GLfloat raster_zoomx;
    GLfloat raster_zoomy;
    GLint index_shift;
    GLint index_offset;
    int     map_color;
    int     map_i2i_size;
    int     map_i2r_size;
    int     map_i2g_size;
    int     map_i2b_size;
    int     map_i2a_size;
    /*
    int     map_s2s_size;
    int     map_r2r_size;
    int     map_g2g_size;
    int     map_b2b_size;
    int     map_a2a_size;
    */
    GLuint  map_i2i[MAX_MAP_SIZE];
    GLubyte map_i2r[MAX_MAP_SIZE];
    GLubyte map_i2g[MAX_MAP_SIZE];
    GLubyte map_i2b[MAX_MAP_SIZE];
    GLubyte map_i2a[MAX_MAP_SIZE];
    /*
    GLuint  map_s2s[MAX_MAP_SIZE];   
    GLubyte map_r2r[MAX_MAP_SIZE];
    GLubyte map_g2g[MAX_MAP_SIZE];
    GLubyte map_b2b[MAX_MAP_SIZE];
    GLubyte map_a2a[MAX_MAP_SIZE];
    */
    GLubyte *data;
    rasterlist_t immediate;
    GLsizei raster_width;
    GLsizei raster_height;
    GLsizei raster_nwidth;
    GLsizei raster_nheight;
    GLint	raster_x1, raster_x2, raster_y1, raster_y2;
    // bitmap specific datas
    int     bm_drawing; // flag if some bitmap are there
    int     bm_x1, bm_y1;
    int     bm_x2, bm_y2;
    GLubyte *bitmap;
    GLsizei bm_alloc;
    GLsizei bm_width, bm_height;
    GLuint  bm_texture;
    int     bm_tnwidth, bm_tnheight;

} raster_state_t;


typedef struct {
    map_state_t *vertex3,
                *vertex4,
                *index,
                *color4,
                *normal,
                *texture1,
                *texture2,
                *texture3,
                *texture4;
} map_states_t;

typedef struct {
	int		top;
	GLuint	*names;
} namestack_t;

typedef struct {
	GLuint  count;
    GLuint *buffer;
    GLuint  size;
    GLfloat zmin;
    GLfloat zmax;
    GLfloat zminoverall;
    GLfloat zmaxoverall;
    GLuint  overflow;
    GLuint  pos;
    GLboolean  hit;
} selectbuf_t;

typedef struct {
	int		top;
    int     identity;
	GLfloat	*stack;
} matrixstack_t;

typedef struct {
    khash_t(shaderlist)    *shaders;
    khash_t(programlist)   *programs;
    GLuint                 program;
    program_t              *glprogram;
    int                    es2; // context is es2
} glsl_t;

typedef struct {
    vertexattrib_t  vertexattrib[MAX_VATTRIB];
    vertexattrib_t  wanted[MAX_VATTRIB];
    GLuint          program;
    program_t       *glprogram;
} gleshard_t;

typedef struct {
    GLuint          vertexshader;
    GLuint          pixelshader;
    GLuint          vertexshader_alpha;
    GLuint          pixelshader_alpha;
    GLuint          program;
    GLuint          program_alpha;
    GLfloat         vert[8], tex[8];
} glesblit_t;

typedef struct {
    GLboolean  secondary_array,
    color_array,
    normal_array,
    vertex_array,
    fog_array,
    tex_coord_array[MAX_TEX];

    GLuint          client; //active client texture

    pointer_state_t vert;
    pointer_state_t normal;
    pointer_state_t color;
    pointer_state_t secondary;
    pointer_state_t fog;
    pointer_state_t tex[MAX_TEX];

    char*           shadersource; // scrach buffer for fpe shader construction
    int             shadersize;
} fpestatus_t;

typedef struct {
    GLint factor;
    GLushort pattern;
    GLubyte *data;
    GLuint texture;
} linestipple_t;

// FBO structures
// Need  to keep track of Renderbuffer that are created as DEPTH_STENCIL, to create 2 seperate buffers...
typedef struct {
    GLuint      renderbuffer;   // This is the Depth buffer...
    GLuint      stencil;        // this will be the secondary Stencil buffer
} gldepthstencil_t;

KHASH_MAP_INIT_INT(dsr, gldepthstencil_t *)

typedef struct {
    GLuint      framebuffer;
    GLuint      texture;
    int         width;
    int         height;
} gltexframebuffer_t;

typedef struct {
    khash_t(dsr) *depthstencil;
    GLuint current_rb;
    GLuint current_fb;
    
    GLuint mainfbo_fbo; // The MainFBO
    GLuint mainfbo_tex; // Texture Attachment
    GLuint mainfbo_dep; // Depth attachment
    GLuint mainfbo_ste; // Stencil attachement
    int mainfbo_width;
    int mainfbo_height;
    int mainfbo_nwidth;
    int mainfbo_nheight;
    GLuint fbo_read;    // if not 0, that's the READ only Framebuffer attached
    GLuint fbo_draw;     // if not 0, that's the DRAW only Framebuffer attached
    GLuint *old_fbos;
    int nbr_fbos;
    int cap_fbos;
    gltexframebuffer_t *tex_fbo;   // (1st) texture attached to fbos
    int nbr_fbot;
    int cap_fbot;
    GLenum fb_status;
} fbo_t;


#endif
