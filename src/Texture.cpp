//
// Created by Shuyang Zhang on 2023/9/13.
//

#include "Texture.hpp"
#include <cmath>

namespace EE {
    glm::vec3 Texture::getValue(float u, float v) const {
        float pixelX = u * (float)(width - 1);
        float pixelY = v * (float)(height - 1);

        int x1 = floor(pixelX);
        int x2 = x1 + 1;
        int y1 = floor(pixelY);
        int y2 = y1 + 1;

        float fx = pixelX - (float) x1;
        float fy = pixelY - (float) y1;

        // Only deal with RGB or Gray
        assert(channel == 3 || channel == 1);

        glm::vec3 c1, c2, c3, c4;

        if (channel == 3) {
            c1 = glm::vec3(raw_data[(y1 * width + x1) * channel],
                            raw_data[(y1 * width + x1) * channel + 1],
                            raw_data[(y1 * width + x1) * channel + 2]);
            c2 = glm::vec3(raw_data[(y1 * width + x2) * channel],
                            raw_data[(y1 * width + x2) * channel + 1],
                            raw_data[(y1 * width + x2) * channel + 2]);
            c3 = glm::vec3(raw_data[(y2 * width + x1) * channel],
                            raw_data[(y2 * width + x1) * channel + 1],
                            raw_data[(y2 * width + x1) * channel + 2]);
            c4 = glm::vec3(raw_data[(y2 * width + x2) * channel],
                            raw_data[(y2 * width + x2) * channel + 1],
                            raw_data[(y2 * width + x2) * channel + 2]);
        } else {
            unsigned char gray1 = raw_data[y1 * width + x1];
            unsigned char gray2 = raw_data[y1 * width + x2];
            unsigned char gray3 = raw_data[y2 * width + x1];
            unsigned char gray4 = raw_data[y2 * width + x2];
            c1 = glm::vec3(gray1, gray1, gray1);
            c2 = glm::vec3(gray2, gray2, gray2);
            c3 = glm::vec3(gray3, gray3, gray3);
            c4 = glm::vec3(gray4, gray4, gray4);
        }
        glm::vec3 c12 = c1 * (1 - fx) + c2 * fx;
        glm::vec3 c34 = c3 * (1 - fx) + c4 * fx;

        return c12 * (1 - fy) + c34 * fy;
    }
} // EE