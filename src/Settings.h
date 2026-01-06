#ifndef MPM_METHOD_SETTINGS_H
#define MPM_METHOD_SETTINGS_H

constexpr GLuint locationIndex = 0;
constexpr GLint vertexSize = 3;
constexpr GLenum vertexType = GL_FLOAT;
constexpr GLboolean normalize = GL_FALSE;
constexpr GLsizei vertexStride = vertexSize * sizeof(float);
inline const void* dataPosition = reinterpret_cast<void*>(0);

inline GLint firstVertexIndex = 0;
inline GLsizei numberOfVertices = 3;

#endif