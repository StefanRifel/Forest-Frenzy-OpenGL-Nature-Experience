#ifndef FACE_HH
#define FACE_HH

#include "../../libs/SMath/include/vector.hpp"

typedef struct {
    vector<unsigned int> vertexIndices;
    vector<unsigned int> normalIndices;
    vector<unsigned int> textureIndices;
} Face;

#endif
