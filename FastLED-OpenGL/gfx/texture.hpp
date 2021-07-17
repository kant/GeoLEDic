#ifndef TEXTURE_HPP
#define TEXTURE_HPP

namespace gfx {

// Load a .DDS file using GLFW's own loader
GLuint loadDDS(const unsigned char* binary_image, unsigned size);

}

#endif
