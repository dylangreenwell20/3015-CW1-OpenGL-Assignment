#include "scenebasic_uniform.h"

#include <cstdio>
#include <cstdlib>

#include <string>
using std::string;

#include <sstream>
#include <iostream>
using std::cerr;
using std::endl;

#include "helper/glutils.h"
#include "helper/texture.h"

using glm::vec3;
using glm::vec4;
using glm::mat3;
using glm::mat4;

SceneBasic_Uniform::SceneBasic_Uniform() :
    tPrev(0), angle(0.0f), rotSpeed(glm::pi<float>()/2.0f), sky(450.0f) {
    rock_arch = ObjMesh::load("media/CaveRock_L_Obj.obj", false, true);
}

void SceneBasic_Uniform::initScene()
{
    compile();

    glEnable(GL_DEPTH_TEST);
    
    projection = mat4(1.0f);

    GLuint cubeTex = Texture::loadHdrCubeMap("media/texture/cube/skybox-hdr/skybox");

    model = mat4(1.0f);

    angle = 0.0f;

    prog.setUniform("Light.L", vec3(1.0f));
    prog.setUniform("Light.La", vec3(0.05f));

    GLuint diffTex = Texture::loadTexture("media/texture/CaveRock_L_Base_Diffuse.png");
    GLuint normalTex = Texture::loadTexture("media/texture/CaveRock_L_Base_Normal.png");
    GLuint moss = Texture::loadTexture("media/texture/moss.png");

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, diffTex);

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, normalTex);

    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, moss);

    glActiveTexture(GL_TEXTURE3);
    glBindTexture(GL_TEXTURE_CUBE_MAP, cubeTex);
}

void SceneBasic_Uniform::compile()
{
	try {
		prog.compileShader("shader/basic_uniform.vert");
		prog.compileShader("shader/basic_uniform.frag");
		prog.link();
		prog.use();
	} catch (GLSLProgramException &e) {
		cerr << e.what() << endl;
		exit(EXIT_FAILURE);
	}
}

void SceneBasic_Uniform::update( float t )
{
    float deltaT = t - tPrev;

    if (tPrev == 0.0f) {
        deltaT = 0.0f;
    }

    tPrev = t;

    angle += (rotSpeed / 2) * deltaT;

    if (angle > glm::two_pi<float>()) {
        angle -= glm::two_pi<float>();
    }
}

void SceneBasic_Uniform::render()
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    
    vec3 cameraPos = vec3(-100.0f * cos(angle), 0.0f, 7.0f * sin(angle));
    view = glm::lookAt(cameraPos, vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));
    prog.setUniform("Light.Position", view * glm::vec4(10.0f * cos(angle), 1.0f, 10.0f * sin(angle), 1.0f));

    prog.setUniform("Material.Kd", vec3(0.2f, 0.55f, 0.9f));
    prog.setUniform("Material.Ks", vec3(0.95f, 0.95f, 0.95f));
    prog.setUniform("Material.Ka", 0.2f * 0.3f, 0.55f * 0.3f, 0.9f * 0.3f);
    prog.setUniform("Material.Shininess", 100.0f);

    model = mat4(1.0f);

    sky.render();

    model = mat4(1.0f);

    model = glm::rotate(model, glm::radians(90.0f), vec3(0.0f, 1.0f, 0.0f));

    setMatrices();
    rock_arch->render();

    
}

void SceneBasic_Uniform::resize(int w, int h)
{
    width = w;
    height = h;

    glViewport(0, 0, w, h);
    
    projection = glm::perspective(glm::radians(70.0f), (float)w / h, 0.3f, 1000.0f);
}

void SceneBasic_Uniform::setMatrices() {
    mat4 mv = view * model;

    prog.setUniform("ModelViewMatrix", mv);
    prog.setUniform("NormalMatrix", glm::mat3(vec3(mv[0]), vec3(mv[1]), vec3(mv[2])));
    prog.setUniform("MVP", projection * mv);
}