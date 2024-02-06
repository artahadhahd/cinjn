#ifndef HDR_PARSING_IMAGE_H
#define HDR_PARSING_IMAGE_H
// #include <types.h>
// #include <string.h>

// enum file_format {
//     PPM_P1,
//     PPM_P6,
//     IMAGE_JPG
// };

// struct image {
//     char* content;
//     enum file_format file_format;
// };

// enum file_format identify_image_format(const char* const path);
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>
#endif