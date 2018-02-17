/*!
 * \author ddubois 
 * \date 16-Feb-18.
 */

#include "python_interface.h"

#include <easylogging++.h>

INITIALIZE_EASYLOGGINGPP

void add_material(uint32_t id, viewer::material mat) {
    LOG(ERROR) << "Material with id " << id << " and glossiness " << mat.glossiness;
}