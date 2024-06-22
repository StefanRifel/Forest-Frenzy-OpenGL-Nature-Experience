#ifndef FACE_HH
#define FACE_HH

#include "../../../libs/SMath/include/vector.hpp"

/**
 * @brief Struct representing a face in 3D graphics.
 */
typedef struct {
    vector<unsigned int> vertexIndices;     ///< Indices of vertices that form the face
    vector<unsigned int> normalIndices;     ///< Indices of normals associated with the face
    vector<unsigned int> textureIndices;    ///< Indices of texture coordinates associated with the face
} Face;

#endif // FACE_HH

