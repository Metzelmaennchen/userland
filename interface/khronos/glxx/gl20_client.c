#include "interface/khronos/glxx/glxx_client.h"
#include "interface/khronos/include/GLES2/gl2ext.h"

#include "interface/khronos/common/khrn_client_rpc.h"


extern void set_blend_func (CLIENT_THREAD_STATE_T *thread, GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha);
extern void set_error(GLXX_CLIENT_STATE_T *state, GLenum error);


#ifndef RPC_DIRECT
static void read_out_bulk(CLIENT_THREAD_STATE_T *thread, void *out)
{
   rpc_recv(thread, out, NULL, (RPC_RECV_FLAG_T)(RPC_RECV_FLAG_BULK | RPC_RECV_FLAG_LEN));
}
#endif

GL_API void GL_APIENTRY glActiveTexture (GLenum texture)
{
   CLIENT_THREAD_STATE_T *thread = CLIENT_GET_THREAD_STATE();

      RPC_CALL1(glActiveTexture_impl,
                thread,
                GLACTIVETEXTURE_ID,
                RPC_ENUM(texture));
}

GL_API void GL_APIENTRY glAttachShader (GLuint program, GLuint shader)
{
   CLIENT_THREAD_STATE_T *thread = CLIENT_GET_THREAD_STATE();
   if (IS_OPENGLES_20(thread)) {
      RPC_CALL2(glAttachShader_impl_20,
                thread,
                GLATTACHSHADER_ID_20,
                RPC_UINT(program),
                RPC_UINT(shader));
   }
}

GL_API void GL_APIENTRY glBindAttribLocation (GLuint program, GLuint index, const char *name)
{
   CLIENT_THREAD_STATE_T *thread = CLIENT_GET_THREAD_STATE();
   if (IS_OPENGLES_20(thread)) {
      RPC_CALL3_IN_BULK(glBindAttribLocation_impl_20,
                        thread,
                        GLBINDATTRIBLOCATION_ID_20,
                        RPC_UINT(program),
                        RPC_UINT(index),
                        name,
                        strlen(name) + 1);
   }
}

GL_API void GL_APIENTRY glBlendColor(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha) // S
{
   CLIENT_THREAD_STATE_T *thread = CLIENT_GET_THREAD_STATE();
   if (IS_OPENGLES_20(thread)) {
      RPC_CALL4(glBlendColor_impl_20,
                thread,
                GLBLENDCOLOR_ID_20,
                RPC_FLOAT(red),
                RPC_FLOAT(green),
                RPC_FLOAT(blue),
                RPC_FLOAT(alpha));
   }
}

GL_API void GL_APIENTRY glBlendEquationSeparate(GLenum modeRGB, GLenum modeAlpha) // S
{
   CLIENT_THREAD_STATE_T *thread = CLIENT_GET_THREAD_STATE();
   if (IS_OPENGLES_20(thread)) {
      RPC_CALL2(glBlendEquationSeparate_impl_20,
                thread,
                GLBLENDEQUATIONSEPARATE_ID_20,
                RPC_ENUM(modeRGB),
                RPC_ENUM(modeAlpha));
   }
}

GL_API void GL_APIENTRY glBlendFuncSeparate (GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha) // S
{
   CLIENT_THREAD_STATE_T *thread = CLIENT_GET_THREAD_STATE();
   if (IS_OPENGLES_20(thread)) set_blend_func(thread, srcRGB, dstRGB, srcAlpha, dstAlpha);
}

GL_API GLuint GL_APIENTRY glCreateProgram (void)
{
   CLIENT_THREAD_STATE_T *thread = CLIENT_GET_THREAD_STATE();
   if (IS_OPENGLES_20(thread)) {
      return RPC_UINT_RES(RPC_CALL0_RES(glCreateProgram_impl_20,
                                        thread,
                                        GLCREATEPROGRAM_ID_20));
   }

   return 0;
}

GL_API GLuint GL_APIENTRY glCreateShader (GLenum type)
{
   CLIENT_THREAD_STATE_T *thread = CLIENT_GET_THREAD_STATE();
   if (IS_OPENGLES_20(thread)) {
      return RPC_UINT_RES(RPC_CALL1_RES(glCreateShader_impl_20,
                                        thread,
                                        GLCREATESHADER_ID_20,
                                        RPC_ENUM(type)));
   }

   return 0;
}

GL_API void GL_APIENTRY glDeleteProgram (GLuint program)
{
   CLIENT_THREAD_STATE_T *thread = CLIENT_GET_THREAD_STATE();
   if (IS_OPENGLES_20(thread)) {
      RPC_CALL1(glDeleteProgram_impl_20,
                thread,
                GLDELETEPROGRAM_ID_20,
                RPC_UINT(program));
   }
}

GL_API void GL_APIENTRY glDeleteShader (GLuint shader)
{
   CLIENT_THREAD_STATE_T *thread = CLIENT_GET_THREAD_STATE();
   if (IS_OPENGLES_20(thread)) {
      RPC_CALL1(glDeleteShader_impl_20,
                thread,
                GLDELETESHADER_ID_20,
                RPC_UINT(shader));
   }
}

GL_API void GL_APIENTRY glDetachShader (GLuint program, GLuint shader)
{
   CLIENT_THREAD_STATE_T *thread = CLIENT_GET_THREAD_STATE();
   if (IS_OPENGLES_20(thread)) {
      RPC_CALL2(glDetachShader_impl_20,
                thread,
                GLDETACHSHADER_ID_20,
                RPC_UINT(program),
                RPC_UINT(shader));
   }
}

GL_APICALL void GL_APIENTRY glGetActiveAttrib (GLuint program, GLuint index, GLsizei bufsize, GLsizei *length, GLint *size, GLenum *type, char *name)
{
   CLIENT_THREAD_STATE_T *thread = CLIENT_GET_THREAD_STATE();
   if (IS_OPENGLES_20(thread)) {
#ifdef RPC_DIRECT
      RPC_CALL7(glGetActiveAttrib_impl_20, thread, no_id, program, index, bufsize, length, size, type, name);
#else
      GLuint result[3];

      rpc_begin(thread);

      RPC_CALL4_OUT_CTRL(no_function,
                         thread,
                         GLGETACTIVEATTRIB_ID_20,
                         RPC_UINT(program),
                         RPC_UINT(index),
                         RPC_SIZEI(bufsize),
                         result);

      if (length)
         *length = (GLsizei)result[0];
      if (size)
         *size = (GLint)result[1];
      if (type)
         *type = (GLenum)result[2];

      read_out_bulk(thread, name);

      rpc_end(thread);
#endif
   }
}

GL_APICALL void GL_APIENTRY glGetActiveUniform (GLuint program, GLuint index, GLsizei bufsize, GLsizei *length, GLint *size, GLenum *type, char *name)
{
   CLIENT_THREAD_STATE_T *thread = CLIENT_GET_THREAD_STATE();
   if (IS_OPENGLES_20(thread)) {
#ifdef RPC_DIRECT
      RPC_CALL7(glGetActiveUniform_impl_20, thread, no_id, program, index, bufsize, length, size, type, name);
#else
      GLuint result[3];

      rpc_begin(thread);

      RPC_CALL4_OUT_CTRL(no_function,
                         thread,
                         GLGETACTIVEUNIFORM_ID_20,
                         RPC_UINT(program),
                         RPC_UINT(index),
                         RPC_SIZEI(bufsize),
                         result);

      if (length)
         *length = (GLsizei)result[0];
      if (size)
         *size = (GLint)result[1];
      if (type)
         *type = (GLenum)result[2];

      read_out_bulk(thread, name);

      rpc_end(thread);
#endif
   }
}

GL_APICALL void GL_APIENTRY glGetAttachedShaders (GLuint program, GLsizei maxcount, GLsizei *count, GLuint *shaders)
{
   CLIENT_THREAD_STATE_T *thread = CLIENT_GET_THREAD_STATE();
   if (IS_OPENGLES_20(thread)) {
#ifdef RPC_DIRECT
   RPC_CALL4(glGetAttachedShaders_impl_20, thread, no_id, program, maxcount, count, shaders);
#else
   GLuint i;

   GLuint result[3];

   RPC_CALL3_OUT_CTRL(no_function,
                      thread,
                      GLGETATTACHEDSHADERS_ID_20,
                      RPC_UINT(program),
                      RPC_SIZEI(maxcount),
                      result);

   if (count)
      *count = (GLsizei) result[0];

   for (i = 0; i < 2; i++)
      if ((GLuint)maxcount > i && result[0] > i)
         shaders[i] = result[i + 1];
#endif
   }
}

GL_APICALL int GL_APIENTRY glGetAttribLocation (GLuint program, const char *name)
{
   CLIENT_THREAD_STATE_T *thread = CLIENT_GET_THREAD_STATE();
   if (IS_OPENGLES_20(thread)) {
      return RPC_INT_RES(RPC_CALL2_IN_BULK_RES(glGetAttribLocation_impl_20,
                                               thread,
                                               GLGETATTRIBLOCATION_ID_20,
                                               RPC_UINT(program),
                                               name,
                                               strlen(name) + 1));
   }

   return 0;
}

static int get_integer_internal_20(CLIENT_THREAD_STATE_T *thread, GLenum pname, GLint *params)
{
   GLXX_CLIENT_STATE_T *state = GLXX_GET_CLIENT_STATE(thread);

   vcos_assert(state != NULL);

   switch (pname) {
   case GL_UNPACK_ALIGNMENT:
      params[0] = state->alignment.unpack;
      return 1;
   case GL_PACK_ALIGNMENT:
      params[0] = state->alignment.pack;
      return 1;
   default:
      UNREACHABLE();
      break;
   }

   return 0;
}

GL_API void GL_APIENTRY glGetBooleanv (GLenum pname, GLboolean *params)
{
   CLIENT_THREAD_STATE_T *thread = CLIENT_GET_THREAD_STATE();
   if (IS_OPENGLES_20(thread)) {
      switch (pname) {
      case GL_UNPACK_ALIGNMENT:
      case GL_PACK_ALIGNMENT:
      {
         GLint temp = 0;

         get_integer_internal_20(thread, pname, &temp);

         params[0] = temp != 0;
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

GL_API void GL_APIENTRY glGetFloatv (GLenum pname, GLfloat *params)
{
   CLIENT_THREAD_STATE_T *thread = CLIENT_GET_THREAD_STATE();
   if (IS_OPENGLES_20(thread)) {
      switch (pname) {
      case GL_UNPACK_ALIGNMENT:
      case GL_PACK_ALIGNMENT:
      {
         GLint temp = 0;

         get_integer_internal_20(thread, pname, &temp);

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
   if (IS_OPENGLES_20(thread)) {
      switch (pname) {
      case GL_UNPACK_ALIGNMENT:
      case GL_PACK_ALIGNMENT:
         get_integer_internal_20(thread, pname, params);
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

GL_APICALL void GL_APIENTRY glGetProgramiv (GLuint program, GLenum pname, GLint *params)
{
   CLIENT_THREAD_STATE_T *thread = CLIENT_GET_THREAD_STATE();
   if (IS_OPENGLES_20(thread)) {
      RPC_CALL3_OUT_CTRL(glGetProgramiv_impl_20,
                         thread,
                         GLGETPROGRAMIV_ID_20,
                         RPC_UINT(program),
                         RPC_ENUM(pname),
                         params);
   }
}

GL_APICALL void GL_APIENTRY glGetProgramInfoLog (GLuint program, GLsizei bufsize, GLsizei *length, char *infolog)
{
   CLIENT_THREAD_STATE_T *thread = CLIENT_GET_THREAD_STATE();
   if (IS_OPENGLES_20(thread)) {
#ifdef RPC_DIRECT
      RPC_CALL4(glGetProgramInfoLog_impl_20, thread, no_id, program, bufsize, length, infolog);
#else
      GLuint result[1];

      rpc_begin(thread);

      RPC_CALL3_OUT_CTRL(no_function,
                         thread,
                         GLGETPROGRAMINFOLOG_ID_20,
                         RPC_UINT(program),
                         RPC_SIZEI(bufsize),
                         result);

      if (length)
         *length = (GLsizei)result[0];

      read_out_bulk(thread, infolog);

      rpc_end(thread);
#endif
   }
}

GL_API const GLubyte * GL_APIENTRY glGetString (GLenum name)
{
   CLIENT_THREAD_STATE_T *thread = CLIENT_GET_THREAD_STATE();
   if (IS_OPENGLES_20(thread)) {
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
         return (const GLubyte *)"OpenGL ES 2.0";
      case GL_SHADING_LANGUAGE_VERSION:
         return (const GLubyte *)"OpenGL ES GLSL ES 1.00";
      case GL_EXTENSIONS:
         return (const GLubyte *)"GL_OES_compressed_ETC1_RGB8_texture "
                                 "GL_OES_compressed_paletted_texture "
                                 "GL_OES_texture_npot "
                                 "GL_OES_depth24 "
                                 "GL_OES_vertex_half_float "
                                 "GL_OES_EGL_image "
                                 "GL_OES_EGL_image_external "
                                 "GL_EXT_discard_framebuffer "
                                 "GL_OES_rgb8_rgba8 "
                                 "GL_OES_depth32 "
                                 "GL_OES_mapbuffer "
#if GL_EXT_texture_format_BGRA8888
                                 "GL_EXT_texture_format_BGRA8888 "
#endif
#if GL_APPLE_rgb_422
                                 "GL_APPLE_rgb_422 "
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

GL_APICALL void GL_APIENTRY glGetUniformfv (GLuint program, GLint location, GLfloat *params)
{
   CLIENT_THREAD_STATE_T *thread = CLIENT_GET_THREAD_STATE();
   if (IS_OPENGLES_20(thread)) {
      RPC_CALL3_OUT_CTRL(glGetUniformfv_impl_20,
                         thread,
                         GLGETUNIFORMFV_ID_20,
                         RPC_UINT(program),
                         RPC_INT(location),
                         params);
   }
}

GL_APICALL void GL_APIENTRY glGetUniformiv (GLuint program, GLint location, GLint *params)
{
   CLIENT_THREAD_STATE_T *thread = CLIENT_GET_THREAD_STATE();
   if (IS_OPENGLES_20(thread)) {
      RPC_CALL3_OUT_CTRL(glGetUniformiv_impl_20,
                         thread,
                         GLGETUNIFORMIV_ID_20,
                         RPC_UINT(program),
                         RPC_INT(location),
                         params);
   }
}

GL_APICALL int GL_APIENTRY glGetUniformLocation (GLuint program, const char *name)
{
   CLIENT_THREAD_STATE_T *thread = CLIENT_GET_THREAD_STATE();
   if (IS_OPENGLES_20(thread)) {
      return RPC_INT_RES(RPC_CALL2_IN_BULK_RES(glGetUniformLocation_impl_20,
                                               thread,
                                               GLGETUNIFORMLOCATION_ID_20,
                                               RPC_UINT(program),
                                               name,
                                               strlen(name) + 1));
   }

   return 0;
}

/*
   GetVertexAttrib

   VERTEX ATTRIB ARRAY ENABLED False GetVertexAttrib
   VERTEX ATTRIB ARRAY SIZE 4 GetVertexAttrib
   VERTEX ATTRIB ARRAY STRIDE 0 GetVertexAttrib
   VERTEX ATTRIB ARRAY TYPE FLOAT GetVertexAttrib
   VERTEX ATTRIB ARRAY NORMALIZED False GetVertexAttrib
   VERTEX ATTRIB ARRAY BUFFER BINDING 0 GetVertexAttrib

   CURRENT VERTEX ATTRIB 0,0,0,1 GetVertexAttributes
*/

GL_APICALL void GL_APIENTRY glGetVertexAttribfv (GLuint index, GLenum pname, GLfloat *params)
{
   CLIENT_THREAD_STATE_T *thread = CLIENT_GET_THREAD_STATE();
   if (IS_OPENGLES_20(thread)) {
      GLXX_CLIENT_STATE_T *state = GLXX_GET_CLIENT_STATE(thread);

      vcos_assert(state != NULL);

      if (index < GL20_CONFIG_MAX_VERTEX_ATTRIBS)
         switch (pname) {
         case GL_CURRENT_VERTEX_ATTRIB:
            params[0] = state->attrib[index].value[0];
            params[1] = state->attrib[index].value[1];
            params[2] = state->attrib[index].value[2];
            params[3] = state->attrib[index].value[3];
            break;

         //TODO: is this the best way to handle conversions? We duplicate
         //the entire switch statement.
         case GL_VERTEX_ATTRIB_ARRAY_ENABLED:
            params[0] = state->attrib[index].enabled ? 1.0f : 0.0f;
            break;
         case GL_VERTEX_ATTRIB_ARRAY_SIZE:
            params[0] = (GLfloat)state->attrib[index].size;
            break;
         case GL_VERTEX_ATTRIB_ARRAY_STRIDE:
            params[0] = (GLfloat)state->attrib[index].stride;
            break;
         case GL_VERTEX_ATTRIB_ARRAY_TYPE:
            params[0] = (GLfloat)state->attrib[index].type;
            break;
         case GL_VERTEX_ATTRIB_ARRAY_NORMALIZED:
            params[0] = state->attrib[index].normalized ? 1.0f : 0.0f;
            break;
         case GL_VERTEX_ATTRIB_ARRAY_BUFFER_BINDING:
            params[0] = (GLfloat)state->attrib[index].buffer;
            break;



         default:
            set_error(state, GL_INVALID_ENUM);
            break;
         }
      else
         set_error(state, GL_INVALID_VALUE);
   }
}

GL_APICALL void GL_APIENTRY glGetVertexAttribiv (GLuint index, GLenum pname, GLint *params)
{
   CLIENT_THREAD_STATE_T *thread = CLIENT_GET_THREAD_STATE();
   if (IS_OPENGLES_20(thread)) {
      GLXX_CLIENT_STATE_T *state = GLXX_GET_CLIENT_STATE(thread);

      vcos_assert(state != NULL);

      if (index < GL20_CONFIG_MAX_VERTEX_ATTRIBS)
         switch (pname) {
         case GL_VERTEX_ATTRIB_ARRAY_ENABLED:
            params[0] = (GLint) state->attrib[index].enabled ? GL_TRUE : GL_FALSE;
            break;
         case GL_VERTEX_ATTRIB_ARRAY_SIZE:
            params[0] = (GLint) state->attrib[index].size;
            break;
         case GL_VERTEX_ATTRIB_ARRAY_STRIDE:
            params[0] = (GLint) state->attrib[index].stride;
            break;
         case GL_VERTEX_ATTRIB_ARRAY_TYPE:
            params[0] = (GLint) state->attrib[index].type;
            break;
         case GL_VERTEX_ATTRIB_ARRAY_NORMALIZED:
            params[0] = (GLint) state->attrib[index].normalized ? GL_TRUE : GL_FALSE;
            break;
         case GL_VERTEX_ATTRIB_ARRAY_BUFFER_BINDING:
            params[0] = (GLint) state->attrib[index].buffer;
            break;


         //TODO: is this the best way to handle conversions? We duplicate
         //the entire switch statement.
         case GL_CURRENT_VERTEX_ATTRIB:
            params[0] = (GLint)state->attrib[index].value[0];
            params[1] = (GLint)state->attrib[index].value[1];
            params[2] = (GLint)state->attrib[index].value[2];
            params[3] = (GLint)state->attrib[index].value[3];
            break;

         default:
            set_error(state, GL_INVALID_ENUM);
            break;
         }
      else
         set_error(state, GL_INVALID_VALUE);
   }
}

GL_API GLboolean GL_APIENTRY glIsEnabled (GLenum cap)
{
   CLIENT_THREAD_STATE_T *thread = CLIENT_GET_THREAD_STATE();
   if (IS_OPENGLES_20(thread)) {
      return RPC_BOOLEAN_RES(RPC_CALL1_RES(glIsEnabled_impl,
                                           thread,
                                           GLISENABLED_ID,
                                           RPC_ENUM(cap)));
   }

   return 0;
}

GL_API GLboolean GL_APIENTRY glIsProgram (GLuint program)
{
   CLIENT_THREAD_STATE_T *thread = CLIENT_GET_THREAD_STATE();
   if (IS_OPENGLES_20(thread)) {
      return RPC_BOOLEAN_RES(RPC_CALL1_RES(glIsProgram_impl_20,
                                           thread,
                                           GLISPROGRAM_ID_20,
                                           RPC_UINT(program)));
   }

   return 0;
}

GL_API GLboolean GL_APIENTRY glIsShader (GLuint shader)
{
   CLIENT_THREAD_STATE_T *thread = CLIENT_GET_THREAD_STATE();
   if (IS_OPENGLES_20(thread)) {
      return RPC_BOOLEAN_RES(RPC_CALL1_RES(glIsShader_impl_20,
                                           thread,
                                           GLISSHADER_ID_20,
                                           RPC_UINT(shader)));
   }

   return 0;
}


