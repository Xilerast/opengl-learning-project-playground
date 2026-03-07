#include "config.h"
#include "stb_image.h"

Material::Material(const char *filename) {
    // Load image
    int width, height, channels;
    unsigned char *data = stbi_load(filename, &width, &height, &channels, STBI_rgb_alpha);

    // Make texture
    glCreateTextures(GL_TEXTURE_2D, 1, &this->texture);
    glBindTexture(GL_TEXTURE_2D, this->texture);

    // Upload Data to GPU
    glTexImage2D(
        GL_TEXTURE_2D,
        0,          // Describes what GPU is getting
        GL_RGBA,    // Describes what GPU is getting
        width,      // Describes what GPU is getting
        height,     // Describes what GPU is getting
        0,          // Describes what GPU is getting
        GL_RGBA,    // Is what GPU is getting
        GL_UNSIGNED_BYTE, // Is what GPU is getting
        data    // Is what GPU is getting
    );

    // free data from memory since it's on GPU
    stbi_image_free(data);

    // configure sampler
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
}

Material::~Material() {
    glDeleteTextures(1, &this->texture);
}

void Material::use(int unit) {
    // Choose which unit/texture to use
    glActiveTexture(GL_TEXTURE0 + unit);
    // Bind texture handle
    glBindTexture(GL_TEXTURE_2D, this->texture);
}
