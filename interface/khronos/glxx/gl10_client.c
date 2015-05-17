#include "interface/khronos/glxx/glxx_client.h"
#include "interface/khronos/include/GLES/glext.h"

#include "interface/khronos/common/khrn_client_rpc.h"


extern bool is_aligned( GLenum type, size_t value);


GL_API void GL_APIENTRY glActiveTexture (GLenum texture)
{
   CLIENT_THREAD_STATE_T *thread = CLIENT_GET_THREAD_STATE();

      GLXX_CLIENT_STATE_T *state = GLXX_GET_CLIENT_STATE(thread);

      if (texture >= GL_TEXTURE0 && texture < GL_TEXTURE0 + GL11_CONFIG_MAX_TEXTURE_UNITS)
         state->active_texture.server = texture;

      RPC_CALL1(glActiveTexture_impl,
                thread,
                GLACTIVETEXTURE_ID,
                RPC_ENUM(texture));
}

GL_API void GL_APIENTRY glAlphaFunc (GLenum func, GLclampf ref)
{
   CLIENT_THREAD_STATE_T *thread = CLIENT_GET_THREAD_STATE();
   if (IS_OPENGLES_11(thread)) {
      RPC_CALL2(glAlphaFunc_impl_11,
                thread,
                GLALPHAFUNC_ID_11,
                RPC_ENUM(func),
                RPC_FLOAT(ref));
   }
}

GL_API void GL_APIENTRY glAlphaFuncx (GLenum func, GLclampx ref)
{
   CLIENT_THREAD_STATE_T *thread = CLIENT_GET_THREAD_STATE();
   if (IS_OPENGLES_11(thread)) {
      RPC_CALL2(glAlphaFuncx_impl_11,
                thread,
                GLALPHAFUNCX_ID_11,
                RPC_ENUM(func),
                RPC_FIXED(ref));
   }
}

GL_API void GL_APIENTRY glClearColorx (GLclampx red, GLclampx green, GLclampx blue, GLclampx alpha)
{
   CLIENT_THREAD_STATE_T *thread = CLIENT_GET_THREAD_STATE();
   if (IS_OPENGLES_11(thread)) {
      RPC_CALL4(glClearColorx_impl_11,
                thread,
                GLCLEARCOLORX_ID_11,
                RPC_FIXED(red),
                RPC_FIXED(green),
                RPC_FIXED(blue),
                RPC_FIXED(alpha));
   }
}

GL_API void GL_APIENTRY glClearDepthx (GLclampx depth)
{
   CLIENT_THREAD_STATE_T *thread = CLIENT_GET_THREAD_STATE();
   if (IS_OPENGLES_11(thread)) {
      RPC_CALL1(glClearDepthx_impl_11,
                thread,
                GLCLEARDEPTHX_ID_11,
                RPC_FIXED(depth));
   }
}

GL_API void GL_APIENTRY glClientActiveTexture (GLenum texture)
{
   CLIENT_THREAD_STATE_T *thread = CLIENT_GET_THREAD_STATE();
   if (IS_OPENGLES_11(thread)) {
      GLXX_CLIENT_STATE_T *state = GLXX_GET_CLIENT_STATE(thread);

      vcos_assert(state != NULL);

      if (texture >= GL_TEXTURE0 && texture < GL_TEXTURE0 + GL11_CONFIG_MAX_TEXTURE_UNITS)
      {
         state->active_texture.client = texture;
         RPC_CALL1(glClientActiveTexture_impl_11,
                thread,
                GLCLIENTACTIVETEXTURE_ID_11,
                RPC_ENUM(texture));
      }
      else
         set_error(state, GL_INVALID_ENUM);
   }
}

GL_API void GL_APIENTRY glClipPlanef (GLenum plane, const GLfloat *equation)
{
   CLIENT_THREAD_STATE_T *thread = CLIENT_GET_THREAD_STATE();
   if (IS_OPENGLES_11(thread)) {
      RPC_CALL2_IN_CTRL(glClipPlanef_impl_11,
                        thread,
                        GLCLIPPLANEF_ID_11,
                        RPC_ENUM(plane),
                        equation,
                        4 * sizeof(GLfloat));
   }
}

GL_API void GL_APIENTRY glClipPlanex (GLenum plane, const GLfixed *equation)
{
   CLIENT_THREAD_STATE_T *thread = CLIENT_GET_THREAD_STATE();
   if (IS_OPENGLES_11(thread)) {
      RPC_CALL2_IN_CTRL(glClipPlanex_impl_11,
                        thread,
                        GLCLIPPLANEX_ID_11,
                        RPC_ENUM(plane),
                        equation,
                        4 * sizeof(GLfixed));
   }
}

GL_API void GL_APIENTRY glColor4f (GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha)
{
   glintColor(
      clampf(red, 0.0f, 1.0f),
      clampf(green, 0.0f, 1.0f),
      clampf(blue, 0.0f, 1.0f),
      clampf(alpha, 0.0f, 1.0f));
}

GL_API void GL_APIENTRY glColor4ub (GLubyte red, GLubyte green, GLubyte blue, GLubyte alpha)
{
   glintColor(
      (float)red / 255.0f,
      (float)green / 255.0f,
      (float)blue / 255.0f,
      (float)alpha / 255.0f);
}

GL_API void GL_APIENTRY glColor4x (GLfixed red, GLfixed green, GLfixed blue, GLfixed alpha)
{
   glintColor(
      clampf(fixed_to_float(red), 0.0f, 1.0f),
      clampf(fixed_to_float(green), 0.0f, 1.0f),
      clampf(fixed_to_float(blue), 0.0f, 1.0f),
      clampf(fixed_to_float(alpha), 0.0f, 1.0f));
}

static bool is_color_size(GLint size)
{
   return size == 4;
}

static bool is_color_type(GLenum type)
{
   return type == GL_UNSIGNED_BYTE ||
          type == GL_FIXED ||
          type == GL_FLOAT;
}

GL_API void GL_APIENTRY glColorPointer (GLint size, GLenum type, GLsizei stride, const GLvoid *pointer)
{
   if (is_color_type(type)) {
      if (is_color_size(size) && is_aligned(type, (size_t)pointer) && is_aligned(type, (size_t)stride) && stride >= 0) {
         glintAttribPointer(GLXX_API_11, GL11_IX_COLOR, size, type, GL_TRUE, stride, pointer);
      } else
         glxx_set_error_api(GLXX_API_11, GL_INVALID_VALUE);
   } else
      glxx_set_error_api(GLXX_API_11, GL_INVALID_ENUM);
}

GL_API void GL_APIENTRY glDepthRangex (GLclampx zNear, GLclampx zFar)
{
   CLIENT_THREAD_STATE_T *thread = CLIENT_GET_THREAD_STATE();
   if (IS_OPENGLES_11(thread)) {
      RPC_CALL2(glDepthRangex_impl_11,
                thread,
                GLDEPTHRANGEX_ID_11,
                RPC_FIXED(zNear),
                RPC_FIXED(zFar));
   }
}

static void set_enabled_11(GLenum array, GLboolean enabled)
{
   switch (array) {
   case GL_VERTEX_ARRAY:
      glintAttribEnable(GLXX_API_11, GL11_IX_VERTEX, enabled);
      break;
   case GL_NORMAL_ARRAY:
      glintAttribEnable(GLXX_API_11, GL11_IX_NORMAL, enabled);
      break;
   case GL_COLOR_ARRAY:
      glintAttribEnable(GLXX_API_11, GL11_IX_COLOR, enabled);
      break;
   case GL_POINT_SIZE_ARRAY_OES:
      glintAttribEnable(GLXX_API_11, GL11_IX_POINT_SIZE, enabled);
      break;
#if GL_OES_matrix_palette
   case GL_MATRIX_INDEX_ARRAY_OES:
      glintAttribEnable(GLXX_API_11, GL11_IX_MATRIX_INDEX, enabled);
      break;
   case GL_WEIGHT_ARRAY_OES:
      glintAttribEnable(GLXX_API_11, GL11_IX_MATRIX_WEIGHT, enabled);
      break;
#endif
   case GL_TEXTURE_COORD_ARRAY:
      glintAttribEnable(GLXX_API_11, GL11_IX_CLIENT_ACTIVE_TEXTURE, enabled);
      break;
   default:
      glxx_set_error_api(GLXX_API_11, GL_INVALID_ENUM);
      break;
   }
}

GL_API void GL_APIENTRY glDisableClientState (GLenum array)
{
   set_enabled_11(array, GL_FALSE);
}

GL_API void GL_APIENTRY glEnableClientState (GLenum array)
{
   set_enabled_11(array, GL_TRUE);
}

GL_API void GL_APIENTRY glFogf (GLenum pname, GLfloat param)
{
   CLIENT_THREAD_STATE_T *thread = CLIENT_GET_THREAD_STATE();
   if (IS_OPENGLES_11(thread)) {
      RPC_CALL2(glFogf_impl_11,
                thread,
                GLFOGF_ID_11,
                RPC_ENUM(pname),
                RPC_FLOAT(param));
   }
}

GL_API void GL_APIENTRY glFogfv (GLenum pname, const GLfloat *params)
{
   CLIENT_THREAD_STATE_T *thread = CLIENT_GET_THREAD_STATE();
   if (IS_OPENGLES_11(thread)) {
      /*
         the only supported fog params are

         FOG_MODE (1)
         FOG_DENSITY (1)
         FOG_START (1)
         FOG_END (1)
         FOG_COLOR (4)

         so we need to transmit 4 words of parameter data
      */

      RPC_CALL2_IN_CTRL(glFogfv_impl_11,
                        thread,
                        GLFOGFV_ID_11,
                        RPC_ENUM(pname),
                        params,
                        4 * sizeof(GLfloat));
   }
}

GL_API void GL_APIENTRY glFogx (GLenum pname, GLfixed param)
{
   CLIENT_THREAD_STATE_T *thread = CLIENT_GET_THREAD_STATE();
   if (IS_OPENGLES_11(thread)) {
      RPC_CALL2(glFogx_impl_11,
               thread,
               GLFOGX_ID_11,
               RPC_ENUM(pname),
               RPC_FIXED(param));
   }
}

GL_API void GL_APIENTRY glFogxv (GLenum pname, const GLfixed *params)
{
   CLIENT_THREAD_STATE_T *thread = CLIENT_GET_THREAD_STATE();
   if (IS_OPENGLES_11(thread)) {
      /*
         the only supported fog params are

         FOG_MODE (1)
         FOG_DENSITY (1)
         FOG_START (1)
         FOG_END (1)
         FOG_COLOR (4)

         so we need to transmit 4 words of parameter data
      */

      RPC_CALL2_IN_CTRL(glFogxv_impl_11,
                        thread,
                        GLFOGXV_ID_11,
                        RPC_ENUM(pname),
                        params,
                        4 * sizeof(GLfixed));
   }
}

GL_API void GL_APIENTRY glFrustumf (GLfloat left, GLfloat right, GLfloat bottom, GLfloat top, GLfloat zNear, GLfloat zFar)
{
   CLIENT_THREAD_STATE_T *thread = CLIENT_GET_THREAD_STATE();
   if (IS_OPENGLES_11(thread)) {
      RPC_CALL6(glFrustumf_impl_11,
                thread,
                GLFRUSTUMF_ID_11,
                RPC_FLOAT(left),
                RPC_FLOAT(right),
                RPC_FLOAT(bottom),
                RPC_FLOAT(top),
                RPC_FLOAT(zNear),
                RPC_FLOAT(zFar));
   }
}

GL_API void GL_APIENTRY glFrustumx (GLfixed left, GLfixed right, GLfixed bottom, GLfixed top, GLfixed zNear, GLfixed zFar)
{
   CLIENT_THREAD_STATE_T *thread = CLIENT_GET_THREAD_STATE();
   if (IS_OPENGLES_11(thread)) {
      RPC_CALL6(glFrustumx_impl_11,
                thread,
                GLFRUSTUMX_ID_11,
                RPC_FIXED(left),
                RPC_FIXED(right),
                RPC_FIXED(bottom),
                RPC_FIXED(top),
                RPC_FIXED(zNear),
                RPC_FIXED(zFar));
   }
}

/*
   native client-side boolean variables

   VERTEX ARRAY IsEnabled
   NORMAL ARRAY IsEnabled
   COLOR ARRAY IsEnabled
   TEXTURE COORD ARRAY IsEnabled
   POINT SIZE ARRAY OES IsEnabled
   MATRIX INDEX ARRAY OES IsEnabled
   WEIGHT ARRAY OES IsEnabled
*/

static int get_boolean_internal_11(CLIENT_THREAD_STATE_T *thread, GLenum pname, GLboolean *params)
{
   GLXX_CLIENT_STATE_T *state = GLXX_GET_CLIENT_STATE(thread);

   vcos_assert(state != NULL);

   switch (pname) {
   case GL_VERTEX_ARRAY:
      params[0] = state->attrib[GL11_IX_VERTEX].enabled;
      return 1;
   case GL_NORMAL_ARRAY:
      params[0] = state->attrib[GL11_IX_NORMAL].enabled;
      return 1;
   case GL_COLOR_ARRAY:
      params[0] = state->attrib[GL11_IX_COLOR].enabled;
      return 1;
   case GL_TEXTURE_COORD_ARRAY:
      params[0] = state->attrib[state->active_texture.client - GL_TEXTURE0 + GL11_IX_TEXTURE_COORD].enabled;
      return 1;
   case GL_POINT_SIZE_ARRAY_OES:
      params[0] = state->attrib[GL11_IX_POINT_SIZE].enabled;
      return 1;
   case GL_MATRIX_INDEX_ARRAY_OES:
      params[0] = state->attrib[GL11_IX_MATRIX_INDEX].enabled;
      return 1;
   case GL_WEIGHT_ARRAY_OES:
      params[0] = state->attrib[GL11_IX_MATRIX_WEIGHT].enabled;
      return 1;
   default:
      UNREACHABLE();
      break;
   }

   return 0;
}

/*
   native client-side floating-point state variables

   CURRENT_COLOR
   CURRENT_TEXTURE_COORDS
   CURRENT_NORMAL
   POINT_SIZE
*/

static int get_float_internal_11(CLIENT_THREAD_STATE_T *thread, GLenum pname, GLfloat *params)
{
   GLXX_CLIENT_STATE_T *state = GLXX_GET_CLIENT_STATE(thread);

   int i;

   switch (pname) {
   case GL_CURRENT_TEXTURE_COORDS:
   {
      /*
         apparently we need the current texture coordinates for the _server_ active texture unit
      */

      for (i = 0; i < 4; i++)
         params[i] = state->attrib[state->active_texture.server - GL_TEXTURE0 + GL11_IX_TEXTURE_COORD].value[i];
      return 4;
   }
   case GL_CURRENT_COLOR:
   {
      for (i = 0; i < 4; i++)
         params[i] = state->attrib[GL11_IX_COLOR].value[i];
      return 4;
   }
   case GL_CURRENT_NORMAL:
   {
      for (i = 0; i < 3; i++)
         params[i] = state->attrib[GL11_IX_NORMAL].value[i];
      return 3;
   }
   case GL_POINT_SIZE:
      params[0] = state->attrib[GL11_IX_POINT_SIZE].value[0];
      return 1;
   default:
      UNREACHABLE();
      break;
   }

   return 0;
}

/*
   native client-side integer state variables

   CLIENT ACTIVE TEXTURE GetIntegerv
   VERTEX ARRAY SIZE GetIntegerv
   VERTEX ARRAY TYPE GetIntegerv
   VERTEX ARRAY STRIDE GetIntegerv
   NORMAL ARRAY TYPE GetIntegerv
   NORMAL ARRAY STRIDE GetIntegerv
   COLOR ARRAY SIZE GetIntegerv
   COLOR ARRAY TYPE GetIntegerv
   COLOR ARRAY STRIDE GetIntegerv
   TEXTURE COORD ARRAY SIZE GetIntegerv
   TEXTURE COORD ARRAY TYPE GetIntegerv
   TEXTURE COORD ARRAY STRIDE GetIntegerv
   POINT SIZE ARRAY TYPE OES GetIntegerv
   POINT SIZE ARRAY STRIDE OES GetIntegerv

   MATRIX_INDEX_ARRAY_SIZE_OES GetInegerv
   MATRIX_INDEX_ARRAY_TYPE_OES GetInegerv
   MATRIX_INDEX_ARRAY_STRIDE_OES GetInegerv
   WEIGHT_ARRAY_SIZE_OES GetInegerv
   WEIGHT_ARRAY_TYPE_OES GetInegerv
   WEIGHT_ARRAY_STRIDE_OES GetInegerv

   VERTEX ARRAY BUFFER BINDING GetIntegerv
   NORMAL ARRAY BUFFER BINDING GetIntegerv
   COLOR ARRAY BUFFER BINDING GetIntegerv
   TEXTURE COORD ARRAY BUFFER BINDING GetIntegerv
   POINT SIZE ARRAY BUFFER BINDING OES GetIntegerv
   MATRIX_INDEX_ARRAY_BUFFER_BINDING_OES GetIntegerv
   WEIGHT_ARRAY_BUFFER_BINDING_OES GetIntegerv

   UNPACK ALIGNMENT GetIntegerv
   PACK ALIGNMENT GetIntegerv
*/

static int get_integer_internal_11(CLIENT_THREAD_STATE_T *thread, GLenum pname, GLint *params)
{
   GLXX_CLIENT_STATE_T *state = GLXX_GET_CLIENT_STATE(thread);

   vcos_assert(state != NULL);

   switch (pname) {
   case GL_CLIENT_ACTIVE_TEXTURE:
      params[0] = (GLint) state->active_texture.client;
      return 1;
   case GL_VERTEX_ARRAY_SIZE:
      params[0] = (GLint) state->attrib[GL11_IX_VERTEX].size;
      return 1;
   case GL_VERTEX_ARRAY_TYPE:
      params[0] = (GLint) state->attrib[GL11_IX_VERTEX].type;
      return 1;
   case GL_VERTEX_ARRAY_STRIDE:
      params[0] = (GLint) state->attrib[GL11_IX_VERTEX].stride;
      return 1;
   case GL_NORMAL_ARRAY_TYPE:
      params[0] = (GLint) state->attrib[GL11_IX_NORMAL].type;
      return 1;
   case GL_NORMAL_ARRAY_STRIDE:
      params[0] = (GLint) state->attrib[GL11_IX_NORMAL].stride;
      return 1;
   case GL_COLOR_ARRAY_SIZE:
      params[0] = (GLint) state->attrib[GL11_IX_COLOR].size;
      return 1;
   case GL_COLOR_ARRAY_TYPE:
      params[0] = (GLint) state->attrib[GL11_IX_COLOR].type;
      return 1;
   case GL_COLOR_ARRAY_STRIDE:
      params[0] = (GLint) state->attrib[GL11_IX_COLOR].stride;
      return 1;
   case GL_TEXTURE_COORD_ARRAY_SIZE:
      params[0] = (GLint) state->attrib[state->active_texture.client - GL_TEXTURE0 + GL11_IX_TEXTURE_COORD].size;
      return 1;
   case GL_TEXTURE_COORD_ARRAY_TYPE:
      params[0] = (GLint) state->attrib[state->active_texture.client - GL_TEXTURE0 + GL11_IX_TEXTURE_COORD].type;
      return 1;
   case GL_TEXTURE_COORD_ARRAY_STRIDE:
      params[0] = (GLint) state->attrib[state->active_texture.client - GL_TEXTURE0 + GL11_IX_TEXTURE_COORD].stride;
      return 1;
   case GL_POINT_SIZE_ARRAY_TYPE_OES:
      params[0] = (GLint) state->attrib[GL11_IX_POINT_SIZE].type;
      return 1;
   case GL_POINT_SIZE_ARRAY_STRIDE_OES:
      params[0] = (GLint) state->attrib[GL11_IX_POINT_SIZE].stride;
      return 1;
   case GL_MATRIX_INDEX_ARRAY_SIZE_OES:
      params[0] = (GLint) state->attrib[GL11_IX_MATRIX_INDEX].size;
      return 1;
   case GL_MATRIX_INDEX_ARRAY_TYPE_OES:
      params[0] = (GLint) state->attrib[GL11_IX_MATRIX_INDEX].type;
      return 1;
   case GL_MATRIX_INDEX_ARRAY_STRIDE_OES:
      params[0] = (GLint) state->attrib[GL11_IX_MATRIX_INDEX].stride;
      return 1;
   case GL_WEIGHT_ARRAY_SIZE_OES:
      params[0] = (GLint) state->attrib[GL11_IX_MATRIX_WEIGHT].size;
      return 1;
   case GL_WEIGHT_ARRAY_TYPE_OES:
      params[0] = (GLint) state->attrib[GL11_IX_MATRIX_WEIGHT].type;
      return 1;
   case GL_WEIGHT_ARRAY_STRIDE_OES:
      params[0] = (GLint) state->attrib[GL11_IX_MATRIX_WEIGHT].stride;
      return 1;
   case GL_ARRAY_BUFFER_BINDING:
      params[0] = (GLint) state->bound_buffer.array;
      return 1;
   case GL_ELEMENT_ARRAY_BUFFER_BINDING:
      params[0] = (GLint) state->bound_buffer.element_array;
      return 1;
   case GL_VERTEX_ARRAY_BUFFER_BINDING:
      params[0] = (GLint) state->attrib[GL11_IX_VERTEX].buffer;
      return 1;
   case GL_NORMAL_ARRAY_BUFFER_BINDING:
      params[0] = (GLint) state->attrib[GL11_IX_NORMAL].buffer;
      return 1;
   case GL_COLOR_ARRAY_BUFFER_BINDING:
      params[0] = (GLint) state->attrib[GL11_IX_COLOR].buffer;
      return 1;
   case GL_TEXTURE_COORD_ARRAY_BUFFER_BINDING:
      /*
      TODO is this right?
      Most texture state variables are qualified by the value of ACTIVE TEXTURE
to determine which server texture state vector is queried. Client texture
state variables such as texture coordinate array pointers are qualified by the
value of CLIENT ACTIVE TEXTURE. Tables 6.3, 6.4, 6.7, 6.13, 6.15, and 6.21
indicate those state variables which are qualified by ACTIVE TEXTURE or
CLIENT ACTIVE TEXTURE during state queries
      */
      params[0] = (GLint) state->attrib[state->active_texture.client - GL_TEXTURE0 + GL11_IX_TEXTURE_COORD].buffer;
      return 1;
   case GL_POINT_SIZE_ARRAY_BUFFER_BINDING_OES:
      params[0] = (GLint) state->attrib[GL11_IX_POINT_SIZE].buffer;
      return 1;
   case GL_MATRIX_INDEX_ARRAY_BUFFER_BINDING_OES:
      params[0] = (GLint) state->attrib[GL11_IX_MATRIX_INDEX].buffer;
      return 1;
   case GL_WEIGHT_ARRAY_BUFFER_BINDING_OES:
      params[0] = (GLint) state->attrib[GL11_IX_MATRIX_WEIGHT].buffer;
      return 1;

   case GL_UNPACK_ALIGNMENT:
      params[0] = (GLint) state->alignment.unpack;
      return 1;
   case GL_PACK_ALIGNMENT:
      params[0] = (GLint) state->alignment.pack;
      return 1;

   //TODO: these are horrible and don't make any sense
   //Is this a sensible thing to return?
   case GL_IMPLEMENTATION_COLOR_READ_TYPE_OES:
      params[0] = (GLint) GL_UNSIGNED_BYTE;
      return 1;
   case GL_IMPLEMENTATION_COLOR_READ_FORMAT_OES:
      params[0] = (GLint) GL_RGBA;
      return 1;
   //end TODO

   default:
      UNREACHABLE();
      break;
   }

   return 0;
}

GL_API void GL_APIENTRY glGetBooleanv (GLenum pname, GLboolean *params)
{
   CLIENT_THREAD_STATE_T *thread = CLIENT_GET_THREAD_STATE();
   if (IS_OPENGLES_11(thread)) {
      switch (pname) {
      case GL_VERTEX_ARRAY:
      case GL_NORMAL_ARRAY:
      case GL_COLOR_ARRAY:
      case GL_TEXTURE_COORD_ARRAY:
      case GL_POINT_SIZE_ARRAY_OES:
         get_boolean_internal_11(thread, pname, params);
         break;
      case GL_CLIENT_ACTIVE_TEXTURE:
      case GL_VERTEX_ARRAY_SIZE:
      case GL_VERTEX_ARRAY_TYPE:
      case GL_VERTEX_ARRAY_STRIDE:
      case GL_NORMAL_ARRAY_TYPE:
      case GL_NORMAL_ARRAY_STRIDE:
      case GL_COLOR_ARRAY_SIZE:
      case GL_COLOR_ARRAY_TYPE:
      case GL_COLOR_ARRAY_STRIDE:
      case GL_TEXTURE_COORD_ARRAY_SIZE:
      case GL_TEXTURE_COORD_ARRAY_TYPE:
      case GL_TEXTURE_COORD_ARRAY_STRIDE:
      case GL_POINT_SIZE_ARRAY_TYPE_OES:
      case GL_POINT_SIZE_ARRAY_STRIDE_OES:
      case GL_ARRAY_BUFFER_BINDING:
      case GL_ELEMENT_ARRAY_BUFFER_BINDING:
      case GL_VERTEX_ARRAY_BUFFER_BINDING:
      case GL_NORMAL_ARRAY_BUFFER_BINDING:
      case GL_COLOR_ARRAY_BUFFER_BINDING:
      case GL_TEXTURE_COORD_ARRAY_BUFFER_BINDING:
      case GL_POINT_SIZE_ARRAY_BUFFER_BINDING_OES:
      case GL_UNPACK_ALIGNMENT:
      case GL_PACK_ALIGNMENT:
      case GL_IMPLEMENTATION_COLOR_READ_TYPE_OES:
      case GL_IMPLEMENTATION_COLOR_READ_FORMAT_OES:
      {
         GLint temp;

         get_integer_internal_11(thread, pname, &temp);

         params[0] = temp != 0;
         break;
      }
      case GL_CURRENT_TEXTURE_COORDS:
      case GL_CURRENT_COLOR:
      case GL_CURRENT_NORMAL:
      case GL_POINT_SIZE:
      {
         GLfloat temp[4];
         GLuint count = (GLuint) get_float_internal_11(thread, pname, temp);
         GLuint i;

         vcos_assert(count <= 4);

         for (i = 0; i < count; i++)
            params[i] = temp[i] != 0.0f;

         break;
      }
      default:
         RPC_CALL2_OUT_CTRL(glGetBooleanv_impl,
                            thread,
                            GLGETBOOLEANV_ID,
                            RPC_ENUM(pname),
                            params);
         break;
      }
   }
}

GL_API void GL_APIENTRY glGetClipPlanef (GLenum pname, GLfloat eqn[4])
{
   CLIENT_THREAD_STATE_T *thread = CLIENT_GET_THREAD_STATE();
   if (IS_OPENGLES_11(thread)) {
      RPC_CALL2_OUT_CTRL(glGetClipPlanef_impl_11,
                         thread,
                         GLGETCLIPPLANEF_ID_11,
                         RPC_ENUM(pname),
                         eqn);
   }
}

GL_API void GL_APIENTRY glGetClipPlanex (GLenum pname, GLfixed eqn[4])
{
   CLIENT_THREAD_STATE_T *thread = CLIENT_GET_THREAD_STATE();
   if (IS_OPENGLES_11(thread)) {
      RPC_CALL2_OUT_CTRL(glGetClipPlanex_impl_11,
                         thread,
                         GLGETCLIPPLANEX_ID_11,
                         RPC_ENUM(pname),
                         eqn);
   }
}

GL_API void GL_APIENTRY glGetFixedv (GLenum pname, GLfixed *params)
{
   CLIENT_THREAD_STATE_T *thread = CLIENT_GET_THREAD_STATE();
   if (IS_OPENGLES_11(thread)) {
      switch (pname) {
      case GL_VERTEX_ARRAY:
      case GL_NORMAL_ARRAY:
      case GL_COLOR_ARRAY:
      case GL_TEXTURE_COORD_ARRAY:
      case GL_POINT_SIZE_ARRAY_OES:
      {
         GLboolean temp[4];

         int count = get_boolean_internal_11(thread, pname, temp);
         int i;

         vcos_assert(count <= 4);

         for (i = 0; i < count; i++)
            params[i] = temp[i] ? (GLfixed)float_to_fixed(1.0f) : (GLfixed)float_to_fixed(0.0f);

         break;
      }
      case GL_CURRENT_TEXTURE_COORDS:
      case GL_CURRENT_COLOR:
      case GL_CURRENT_NORMAL:
      case GL_POINT_SIZE:
      {
         GLfloat temp[4];

         int count = get_float_internal_11(thread, pname, temp);
         int i;

         vcos_assert(count <= 4);

         for (i = 0; i < count; i++)
            params[i] = (GLfixed) float_to_fixed(temp[i]);

         break;
      }
      case GL_CLIENT_ACTIVE_TEXTURE:
      case GL_VERTEX_ARRAY_SIZE:
      case GL_VERTEX_ARRAY_TYPE:
      case GL_VERTEX_ARRAY_STRIDE:
      case GL_NORMAL_ARRAY_TYPE:
      case GL_NORMAL_ARRAY_STRIDE:
      case GL_COLOR_ARRAY_SIZE:
      case GL_COLOR_ARRAY_TYPE:
      case GL_COLOR_ARRAY_STRIDE:
      case GL_TEXTURE_COORD_ARRAY_SIZE:
      case GL_TEXTURE_COORD_ARRAY_TYPE:
      case GL_TEXTURE_COORD_ARRAY_STRIDE:
      case GL_POINT_SIZE_ARRAY_TYPE_OES:
      case GL_POINT_SIZE_ARRAY_STRIDE_OES:
      case GL_ARRAY_BUFFER_BINDING:
      case GL_ELEMENT_ARRAY_BUFFER_BINDING:
      case GL_VERTEX_ARRAY_BUFFER_BINDING:
      case GL_NORMAL_ARRAY_BUFFER_BINDING:
      case GL_COLOR_ARRAY_BUFFER_BINDING:
      case GL_TEXTURE_COORD_ARRAY_BUFFER_BINDING:
      case GL_POINT_SIZE_ARRAY_BUFFER_BINDING_OES:
      case GL_UNPACK_ALIGNMENT:
      case GL_PACK_ALIGNMENT:
      case GL_IMPLEMENTATION_COLOR_READ_TYPE_OES:
      case GL_IMPLEMENTATION_COLOR_READ_FORMAT_OES:
      {
         GLint temp;

         get_integer_internal_11(thread, pname, &temp);

         params[0] = (GLfixed) float_to_fixed((GLfloat)temp);
         break;
      }
      default:
         RPC_CALL2_OUT_CTRL(glGetFixedv_impl_11,
                            thread,
                            GLGETFIXEDV_ID_11,
                            RPC_ENUM(pname),
                            params);
         break;
      }
   }
}

GL_API void GL_APIENTRY glGetFloatv (GLenum pname, GLfloat *params)
{
   CLIENT_THREAD_STATE_T *thread = CLIENT_GET_THREAD_STATE();
   if (IS_OPENGLES_11(thread)) {
      switch (pname) {
      case GL_VERTEX_ARRAY:
      case GL_NORMAL_ARRAY:
      case GL_COLOR_ARRAY:
      case GL_TEXTURE_COORD_ARRAY:
      case GL_POINT_SIZE_ARRAY_OES:
      {
         GLboolean temp[4];
         GLuint count = (GLuint) get_boolean_internal_11(thread, pname, temp);
         GLuint i;

         vcos_assert(count <= 4);

         for (i = 0; i < count; i++)
            params[i] = temp[i] ? 1.0f : 0.0f;

         break;
      }
      case GL_CURRENT_TEXTURE_COORDS:
      case GL_CURRENT_COLOR:
      case GL_CURRENT_NORMAL:
      case GL_POINT_SIZE:
         get_float_internal_11(thread, pname, params);

         break;
      case GL_CLIENT_ACTIVE_TEXTURE:
      case GL_VERTEX_ARRAY_SIZE:
      case GL_VERTEX_ARRAY_TYPE:
      case GL_VERTEX_ARRAY_STRIDE:
      case GL_NORMAL_ARRAY_TYPE:
      case GL_NORMAL_ARRAY_STRIDE:
      case GL_COLOR_ARRAY_SIZE:
      case GL_COLOR_ARRAY_TYPE:
      case GL_COLOR_ARRAY_STRIDE:
      case GL_TEXTURE_COORD_ARRAY_SIZE:
      case GL_TEXTURE_COORD_ARRAY_TYPE:
      case GL_TEXTURE_COORD_ARRAY_STRIDE:
      case GL_POINT_SIZE_ARRAY_TYPE_OES:
      case GL_POINT_SIZE_ARRAY_STRIDE_OES:
      case GL_ARRAY_BUFFER_BINDING:
      case GL_ELEMENT_ARRAY_BUFFER_BINDING:
      case GL_VERTEX_ARRAY_BUFFER_BINDING:
      case GL_NORMAL_ARRAY_BUFFER_BINDING:
      case GL_COLOR_ARRAY_BUFFER_BINDING:
      case GL_TEXTURE_COORD_ARRAY_BUFFER_BINDING:
      case GL_POINT_SIZE_ARRAY_BUFFER_BINDING_OES:
      case GL_UNPACK_ALIGNMENT:
      case GL_PACK_ALIGNMENT:
      case GL_IMPLEMENTATION_COLOR_READ_TYPE_OES:
      case GL_IMPLEMENTATION_COLOR_READ_FORMAT_OES:
      {
         GLint temp;

         get_integer_internal_11(thread, pname, &temp);

         params[0] = (GLfloat)temp;
         break;
      }
      default:
         RPC_CALL2_OUT_CTRL(glGetFloatv_impl,
                            thread,
                            GLGETFLOATV_ID,
                            RPC_ENUM(pname),
                            params);
         break;
      }
   }
}

GL_API void GL_APIENTRY glGetIntegerv (GLenum pname, GLint *params)
{
   CLIENT_THREAD_STATE_T *thread = CLIENT_GET_THREAD_STATE();
   if (IS_OPENGLES_11(thread)) {
      switch (pname) {
      case GL_VERTEX_ARRAY:
      case GL_NORMAL_ARRAY:
      case GL_COLOR_ARRAY:
      case GL_TEXTURE_COORD_ARRAY:
      case GL_POINT_SIZE_ARRAY_OES:
      {
         GLboolean temp[4];
         GLuint count = (GLuint) get_boolean_internal_11(thread, pname, temp);
         GLuint i;

         vcos_assert(count <= 4);

         for (i = 0; i < count; i++)
            params[i] = temp[i] ? 1 : 0;

         break;
      }
      case GL_CURRENT_COLOR:
      case GL_CURRENT_NORMAL:
      {
         GLfloat temp[4];
         GLuint count = (GLuint) get_float_internal_11(thread, pname, temp);
         GLuint i;

         vcos_assert(count <= 4);

         for (i = 0; i < count; i++)
            params[i] = (GLint)floor((4294967295.0f * temp[i] - 1.0f) / 2.0f + 0.5f);

         //TODO: that the above is correct wrt table 2.7 in the GL spec

         break;
      }
      case GL_CURRENT_TEXTURE_COORDS:
      case GL_POINT_SIZE:
      {
         GLfloat temp[4];
         GLuint count = (GLuint) get_float_internal_11(thread, pname, temp);
         GLuint i;

         vcos_assert(count <= 4);

         for (i = 0; i < count; i++)
            params[i] = (GLint) float_to_int(temp[i]);

         break;
      }
      case GL_CLIENT_ACTIVE_TEXTURE:
      case GL_VERTEX_ARRAY_SIZE:
      case GL_VERTEX_ARRAY_TYPE:
      case GL_VERTEX_ARRAY_STRIDE:
      case GL_NORMAL_ARRAY_TYPE:
      case GL_NORMAL_ARRAY_STRIDE:
      case GL_COLOR_ARRAY_SIZE:
      case GL_COLOR_ARRAY_TYPE:
      case GL_COLOR_ARRAY_STRIDE:
      case GL_TEXTURE_COORD_ARRAY_SIZE:
      case GL_TEXTURE_COORD_ARRAY_TYPE:
      case GL_TEXTURE_COORD_ARRAY_STRIDE:
      case GL_POINT_SIZE_ARRAY_TYPE_OES:
      case GL_POINT_SIZE_ARRAY_STRIDE_OES:
      case GL_MATRIX_INDEX_ARRAY_SIZE_OES:
      case GL_MATRIX_INDEX_ARRAY_TYPE_OES:
      case GL_MATRIX_INDEX_ARRAY_STRIDE_OES:
      case GL_WEIGHT_ARRAY_SIZE_OES:
      case GL_WEIGHT_ARRAY_TYPE_OES:
      case GL_WEIGHT_ARRAY_STRIDE_OES:
      case GL_ARRAY_BUFFER_BINDING:
      case GL_ELEMENT_ARRAY_BUFFER_BINDING:
      case GL_VERTEX_ARRAY_BUFFER_BINDING:
      case GL_NORMAL_ARRAY_BUFFER_BINDING:
      case GL_COLOR_ARRAY_BUFFER_BINDING:
      case GL_TEXTURE_COORD_ARRAY_BUFFER_BINDING:
      case GL_POINT_SIZE_ARRAY_BUFFER_BINDING_OES:
      case GL_MATRIX_INDEX_ARRAY_BUFFER_BINDING_OES:
      case GL_WEIGHT_ARRAY_BUFFER_BINDING_OES:
      case GL_UNPACK_ALIGNMENT:
      case GL_PACK_ALIGNMENT:
      case GL_IMPLEMENTATION_COLOR_READ_TYPE_OES:
      case GL_IMPLEMENTATION_COLOR_READ_FORMAT_OES:
         get_integer_internal_11(thread, pname, params);
         break;
      default:
         RPC_CALL2_OUT_CTRL(glGetIntegerv_impl,
                            thread,
                            GLGETINTEGERV_ID,
                            RPC_ENUM(pname),
                            params);
         break;
      }
   }
}

GL_API void GL_APIENTRY glGetLightfv (GLenum light, GLenum pname, GLfloat *params)
{
   CLIENT_THREAD_STATE_T *thread = CLIENT_GET_THREAD_STATE();
   if (IS_OPENGLES_11(thread)) {
      RPC_CALL3_OUT_CTRL(glGetLightfv_impl_11,
                         thread,
                         GLGETLIGHTFV_ID_11,
                         RPC_ENUM(light),
                         RPC_ENUM(pname),
                         params);
   }
}

GL_API void GL_APIENTRY glGetLightxv (GLenum light, GLenum pname, GLfixed *params)
{
   CLIENT_THREAD_STATE_T *thread = CLIENT_GET_THREAD_STATE();
   if (IS_OPENGLES_11(thread)) {
      RPC_CALL3_OUT_CTRL(glGetLightxv_impl_11,
                         thread,
                         GLGETLIGHTXV_ID_11,
                         RPC_ENUM(light),
                         RPC_ENUM(pname),
                         params);
   }
}

GL_API void GL_APIENTRY glGetMaterialfv (GLenum face, GLenum pname, GLfloat *params)
{
   CLIENT_THREAD_STATE_T *thread = CLIENT_GET_THREAD_STATE();
   if (IS_OPENGLES_11(thread)) {
      RPC_CALL3_OUT_CTRL(glGetMaterialfv_impl_11,
                         thread,
                         GLGETMATERIALFV_ID_11,
                         RPC_ENUM(face),
                         RPC_ENUM(pname),
                         params);
   }
}

GL_API void GL_APIENTRY glGetMaterialxv (GLenum face, GLenum pname, GLfixed *params)
{
   CLIENT_THREAD_STATE_T *thread = CLIENT_GET_THREAD_STATE();
   if (IS_OPENGLES_11(thread)) {
      RPC_CALL3_OUT_CTRL(glGetMaterialxv_impl_11,
                         thread,
                         GLGETMATERIALXV_ID_11,
                         RPC_ENUM(face),
                         RPC_ENUM(pname),
                         params);
   }
}

GL_API const GLubyte * GL_APIENTRY glGetString (GLenum name)
{
   CLIENT_THREAD_STATE_T *thread = CLIENT_GET_THREAD_STATE();
   if (IS_OPENGLES_11(thread)) {
      GLXX_CLIENT_STATE_T *state = GLXX_GET_CLIENT_STATE(thread);

      vcos_assert(state != NULL);

      switch (name) {
      case GL_VENDOR:
#ifndef NDEBUG
         return (const GLubyte *)"Broadcom DEBUG";
#else
         return (const GLubyte *)"Broadcom";
#endif
      case GL_RENDERER:
         return (const GLubyte *)"VideoCore IV HW";
      case GL_VERSION:
         return (const GLubyte *)"OpenGL ES-CM 1.1";
      case GL_EXTENSIONS:
         return (const GLubyte *)"GL_OES_compressed_ETC1_RGB8_texture "
                                 "GL_OES_compressed_paletted_texture "
                                 "GL_OES_texture_npot "  /*TODO is npot right? I can't find it in glext.h */
                                 "GL_OES_EGL_image "
                                 "GL_OES_EGL_image_external "
                                 "GL_EXT_discard_framebuffer "
                                 "GL_OES_query_matrix "
                                 "GL_OES_framebuffer_object "
                                 "GL_OES_rgb8_rgba8 "
                                 "GL_OES_depth24 "
                                 "GL_OES_depth32 "
                                 "GL_OES_stencil8 "
                                 "GL_OES_draw_texture "
                                 "GL_OES_mapbuffer "
#if GL_EXT_texture_format_BGRA8888
                                 "GL_EXT_texture_format_BGRA8888 "
#endif
#if GL_APPLE_rgb_422
                                 "GL_APPLE_rgb_422 "
#endif
#if GL_OES_matrix_palette
                                 "GL_OES_matrix_palette "
#endif
#ifdef GL_EXT_debug_marker
                                 "GL_EXT_debug_marker "
#endif
                                 ;
      default:
         set_error(state, GL_INVALID_ENUM);
         return NULL;
      }
   }

   return NULL;
}

GL_API void GL_APIENTRY glGetTexEnviv (GLenum env, GLenum pname, GLint *params)
{
   CLIENT_THREAD_STATE_T *thread = CLIENT_GET_THREAD_STATE();
   if (IS_OPENGLES_11(thread)) {
      RPC_CALL3_OUT_CTRL(glGetTexEnviv_impl_11,
                         thread,
                         GLGETTEXENVIV_ID_11,
                         RPC_ENUM(env),
                         RPC_ENUM(pname),
                         params);
   }
}

GL_API void GL_APIENTRY glGetTexEnvfv (GLenum env, GLenum pname, GLfloat *params)
{
   CLIENT_THREAD_STATE_T *thread = CLIENT_GET_THREAD_STATE();
   if (IS_OPENGLES_11(thread)) {
      RPC_CALL3_OUT_CTRL(glGetTexEnvfv_impl_11,
                         thread,
                         GLGETTEXENVFV_ID_11,
                         RPC_ENUM(env),
                         RPC_ENUM(pname),
                         params);
   }
}

GL_API void GL_APIENTRY glGetTexEnvxv (GLenum env, GLenum pname, GLfixed *params)
{
   CLIENT_THREAD_STATE_T *thread = CLIENT_GET_THREAD_STATE();
   if (IS_OPENGLES_11(thread)) {
      RPC_CALL3_OUT_CTRL(glGetTexEnvxv_impl_11,
                         thread,
                         GLGETTEXENVXV_ID_11,
                         RPC_ENUM(env),
                         RPC_ENUM(pname),
                         params);
   }
}


