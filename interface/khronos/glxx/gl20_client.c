#include "interface/khronos/glxx/glxx_client.h"
#include "interface/khronos/include/GLES2/gl2ext.h"

#include "interface/khronos/common/khrn_client_rpc.h"


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
