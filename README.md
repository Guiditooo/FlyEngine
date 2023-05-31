# FlyEngine
 An OpenGL based Graphic Engine developed by Guido Tello.
 Image Campus Signature: Graficos I, II & III.

# First Part
 1) Set up Libraries - * Am here * 
    * GLFW - DONE
    * GLEW - DONE
    * GLM - DONE
    * STB - DONE
    * TINYXML2 - DONE
    * ASSIMP - ONGOING
 
 2) Place a rectangle
    * Entity
    * Renderer (Shader inside just for testing purpose)
    * Window
    * Additionaly, create a Timer class.

 3) Take action in window
    * Set up Transformations on Entity (Translation, Scale, Rotation)
    * Get Input with poll events
    * Extract the shaders from Renderer and create a Shader class.
    * Additionaly, create a Material class.
        - The material is component of the different shapes and models.
        - There can be more than a shader applied at once on the same mat.

 4) Create Shape classes
    * Entity2D : Entity
        - Check Collisions 
        - Draw Method
        - Has a material attached. 
    * Rectangle : Entity2D
    * Triangle : Entity2D

 5) Sprites Update
    * Create Importer. 
        - It will provide the control on the game as well as on the engine.
    * Sprite : Entity2D
    * Create Texture class just to change the sprite img on runtime...
    * Create Animation class just to let the sprite move.
        - Sprite Sheet Reader class just to make it easier and more friendly.

 6) Tilemap Update
    * Tilemap : Entity2D
        - This should make collision if that tile is wall or inwalkable.
    * Create Tile class
        - A tilemap is just a matrix of tiles. 
    * Atlas reader 
        - This should be capable to get tile from a XML file using TINYXML2 
    * Set multiple layers.
        - Sometimes there are some layes as foliage that can be walkable or rocks that cant be walkable through, but at background it has a grass tile.


# Second Part
    ~ On Going ~