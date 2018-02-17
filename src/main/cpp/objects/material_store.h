/*!
 * \author ddubois 
 * \date 16-Feb-18.
 */

#ifndef VIEWER_MATERIAL_STORE_H
#define VIEWER_MATERIAL_STORE_H

#include <queue>
#include <glm/glm.hpp>
#include "../core/data_transfer_point.h"

namespace viewer {
    struct material {
        glm::vec4 ambient;
        glm::vec4 diffuse;
        glm::vec4 specular;
        glm::vec4 emissive;
        float glossiness = 25.0;

        // The shader object should know if it's a fragment or vertex shader
        // We know we only have two shaders
        uint32_t shaders[2];

        // The texture bind points are indices in this array
        uint32_t textures[8];
    };

    /*!
     * \brief Holds all the materials available
     */
    class material_store : public data_transfer_point<material> {
    private:
        std::queue<material> new_materials;
    };
}


#endif //VIEWER_MATERIAL_STORE_H
