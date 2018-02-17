/*!
 * \brief Defines all the functions that let UGE deal with VIEWER
 *
 * \author ddubois 
 * \date 16-Feb-18.
 */

#ifndef VIEWER_PYTHON_INTERFACE_H
#define VIEWER_PYTHON_INTERFACE_H

#include <cstdint>
#include "../objects/material_store.h"
#include "../utils/export.h"

extern "C" {
    VIEWER_API void add_material(uint32_t id, viewer::material mat);
}


#endif //VIEWER_PYTHON_INTERFACE_H
