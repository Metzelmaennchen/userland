#include "interface/khronos/glxx/glxx_client.h"
#include "interface/khronos/include/GLES2/gl2ext.h"

#include "interface/khronos/common/khrn_client_rpc.h"


extern void set_blend_func (CLIENT_THREAD_STATE_T *thread, GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha);


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


