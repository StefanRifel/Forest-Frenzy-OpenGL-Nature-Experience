#ifndef TEXTURE_HH
#define TEXTURE_HH

#include <string>

/**
 * @brief Struct representing a texture with an identifier, type, and associated material name.
 */
typedef struct {
    unsigned int id;             ///< Identifier of the texture
    std::string type;            ///< Type of the texture (e.g., "diffuse", "specular", etc.)
    std::string materialName;    ///< Name of the material associated with the texture
} Texture;

#endif // TEXTURE_HH
