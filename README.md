Skydome OpenGL Project
Table of Contents

    Project Overview
    Features
    Installation
    Controls
    Usage
    File Structure
    Methods and Techniques
    Dependencies
    Authors and Acknowledgments
    License

Project Overview

This project is an OpenGL-based application that simulates a skydome with moving clouds, a sun, and a moon. The skydome creates a realistic sky environment that changes over time, providing an immersive experience.
Features

    Realistic Skydome: A hemisphere representing the sky.
    Dynamic Sun and Moon: Moving sun and moon to simulate day and night cycles.
    Cloud Simulation: Clouds that move across the sky.
    Texturing: High-quality textures for the sky, clouds, sun, and moon.
    Lighting Effects: Basic lighting effects to enhance realism.

Installation
Prerequisites

    OpenGL
    GLFW
    GLEW/GLAD
    stb_image.h

Steps

    Clone the repository:

    bash

git clone https://github.com/yourusername/skydome-opengl-project.git

Navigate to the project directory:

bash

cd skydome-opengl-project

Build the project using CMake:

bash

mkdir build
cd build
cmake ..
make

Run the executable:

bash

    ./Skydome

Controls

    W: Move forward
    S: Move backward
    A: Move left
    D: Move right
    Arrow Keys: Rotate camera
    Esc: Exit application

Usage

    Launch the application.
    Use the controls to navigate the scene and observe the sky.
    Observe the dynamic changes in the sky as time progresses.

File Structure

makefile

skydome-opengl-project/
├── src/                  # Source code files
│   ├── main.cpp
│   ├── skydome.cpp
│   ├── skydome.h
│   ├── shaders/
│   │   ├── skydome.vs
│   │   ├── skydome.fs
│   │   ├── sun.vs
│   │   ├── sun.fs
│   │   ├── moon.vs
│   │   ├── moon.fs
├── textures/             # Texture files
│   ├── sky_texture.jpg
│   ├── sun_texture.png
│   ├── moon_texture.png
├── include/              # Header files and libraries
│   ├── GLFW/
│   ├── GLEW/
│   ├── stb_image.h
├── CMakeLists.txt        # CMake build configuration
├── README.md             # Project documentation

##Methods and Techniques
Skydome Generation

    Sphere Geometry: Generated using parametric equations for a hemisphere.
    Texturing: Applied textures to the sphere to create a realistic sky.

Dynamic Sun and Moon

    Position Calculation: Calculated based on time to simulate movement across the sky.
    Textured Quads: Rendered as textured quads or small spheres.

Cloud Simulation

    Texture Mapping: Used alpha-mapped textures for clouds.
    Movement: Clouds move across the sky using simple translation.

Lighting

    Basic Lighting: Applied basic lighting models to enhance realism.

Dependencies

    GLFW: Window and input handling.
    GLEW/GLAD: Loading OpenGL functions.
    stb_image: Loading image files for textures.

Authors and Acknowledgments

    Author: Your Name
    Acknowledgments:
        Professor [Professor's Name] for guidance.
        [OpenGL Tutorial Websites] for resources and tutorials.

License

This project is licensed under the MIT License - see the LICENSE file for details.














__________________________________________________________


# Forest Frenzy 

## Gruppe 

Alexander Fitze
Katharina Nolte
Anna Viktoria Pape
Stefan Rifel
Parvaneh Sarjoughi

## Termine

Abgabe:  23.Juni.2024 (25.06.2024)
Präsentation: 24. - 27. Juni 2024 vergabe über Moodle

## Gruppentermine

- 03.06.2024, 11:45 Präsent 
- wöchentlich online meeting

## Todo

- Laden von Texturen und umsetzung in Shader (Al)
-- 11.06 : Klasse textureLoader implementiert
- Szenegraph erstellen 
- Geometire .obj und Texturen im Internet finden (All)
- Beleuchtung fixen (S)
- Taschenlampe für das mouse movement hinzufügen und beschleuchtung dafür
- tag nacht zyklus 
- skybox hinzufügen
- Material Eigenschaften hinzufügen

nicht wichtig:
- FPS zähler in eigene Datei auslagern
- Controlls auslagern in eigene Klasse
- Camerasteuerung verbessern (gehen und springen) (An)
## Fragen zu klären

- Imgui verwenden für die Gui
- ECS verwenden dürfen

## Libraries 

- https://glew.sourceforge.net/
- https://www.glfw.org/
- https://github.com/nothings/stb/blob/master/stb_image.h
- https://github.com/g-truc/glm

## Bauanleitung in vsCode

https://github.com/StefanRifel/Forest-Frenzy-OpenGL-Nature-Experience 
 
--> copyCode (grünerButton) 
Neues vs Code Fenster öffnen, und git repsository clonen und dort den copyCode einfügen. 

Das herunterladen dauert einige Minuten

unter Forest../libs/SMath ein neues Terminal öffnen
Makefile ausführen (make)

unter Forest../
make ausführen (make)

in Forest../bin wechseln 
 obj datei ausführen (./Forest_frenzy)

###
remove deleted branches: git fetch --prune 