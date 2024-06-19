#ifndef FACE_HH
#define FACE_HH

#include "../../libs/SMath/include/vector.hpp"

// Struct for representing a face in 3D graphic
typedef struct {
    vector<unsigned int> vertexIndices;     // Indices of vertices that form the face
    vector<unsigned int> normalIndices;     // Indices of normals associated with the face
    vector<unsigned int> textureIndices;    // Indices of texture coordinates associated with the face
} Face;

#endif
