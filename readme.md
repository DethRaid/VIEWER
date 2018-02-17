# VIEWER
## Model viewer for the Universal Game Editor

### Internals
(I'm jotting down notes here deal with it)

Much of the design of this renderer is based on http://realtimecollisiondetection.net/blog/?p=86. While that article is
almost ten years old, it should remain relatively relevant for a renderer with an OpenGL 2.1 and OpenGL 1.1 backend
(like this one has)

We'll traverse the scene and add a render command for each thing. The render command can have
