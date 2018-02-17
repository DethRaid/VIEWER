if __name__ == '__main__':
    from src.main.python.viewer.py_wrapper import *

    class Material:
        def __init__(self, ambient, diffuse, specular, emissive, glossiness, shaders, textures):
            self.Ambient = ambient
            self.Diffuse = diffuse
            self.Specular = specular
            self.Emissive = emissive
            self.Glossiness = glossiness
            self.Shaders = shaders
            self.Textures = textures

    mat = Material((1, 1, 1, 1), (2, 2, 2, 2), (3, 3, 3, 3), (4, 4, 4, 4), 25, [], [])

    add_material(mat)
