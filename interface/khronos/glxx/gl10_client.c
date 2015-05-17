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


