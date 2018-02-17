"""
Wraps the VIEWER C API so life can be easy
"""

from ctypes import *

view_native = cdll.viewer

glm_vec4 = c_float * 4

class ViewerMaterial(Structure):
    _fields_ = [("ambient", glm_vec4),
                ("diffuse", glm_vec4),
                ("specular", glm_vec4),
                ("emissive", glm_vec4),
                ("glossiness", c_float),
                ("shaders", c_uint32 * 2),
                ("textures", c_uint32 * 4)]


def add_material(material):
    """Converts the provided material into a pretty struct using ctypes, then passes it in"""
    conv_mat = ViewerMaterial()
    conv_mat.ambient = glm_vec4(*material.Ambient)
    conv_mat.diffuse = glm_vec4(*material.Diffuse)
    conv_mat.specular = glm_vec4(*material.Specular)
    conv_mat.emissive = glm_vec4(*material.Emissive)
    conv_mat.glossiness = material.Glossiness

    # TODO: Handle textures and shaders

    view_native.add_material(34, conv_mat);

