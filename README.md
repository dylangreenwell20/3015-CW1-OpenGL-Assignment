# 3015-CW1-OpenGL-Assignment
This is my submission for COMP3015 - Coursework 1. I have created an OpenGL scene which has a custom model loaded with a mix of textures displayed on it, BlinnPhong lighting, Toonshading, normal map and a skybox.
The theme of the scene is meant to be a cave-like experience - the background is dark and there is a cavern structure model loaded with moss on it.

# Features
BlinnPhong Lighting - I use a BlinnPhong method to do the lighting in my scene due to its good visuals with low performance cost.\n
Textures - I have implemented textures from a file which are displayed on objects in the scene, such as my skybox and model.
Toonshading - Within my fragment shader, I set up Toonshading to allow me to control how many shades of light there are in the scene.
Mixing - I mixed a moss texture with the model texture to create a mossy look to the model which fits the cave theme of the scene.
Normal map - The model has a normal map loaded to it which brings out more detail in the model.
Skybox - Surrounding the scene, there is a skybox which gives reinforces the dark vibe of the cave.

# Asset Links
Model: https://www.turbosquid.com/3d-models/3d-model-cave-rock-l-base-1947356
Site used to generate skybox: https://tools.wwwtyro.net/space-3d/index.html#animationSpeed=1&fov=80&nebulae=true&pointStars=true&resolution=1024&seed=u9dzesdwk80&stars=true&sun=true

# Demo Video
https://youtu.be/BLudtSniqg4

# Libraries/Specs
I only used the libraries provided with the project template and coded on a Windows 10 system using Visual Studio 2022.
