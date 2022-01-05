


#include "GLM/gtc/type_ptr.hpp"



#include <glad/gl.h>


#include "cs4722/callbacks.h"
#include "cs4722/buffer_utilities.h"
#include "cs4722/window.h"
#include "cs4722/texture_utilities.h"
#include "cs4722/compile_shaders.h"

#include <GLM/gtc/type_ptr.hpp>



#include <glad/gl.h>


#include "cs4722/view.h"
#include "cs4722/artifact.h"
#include "cs4722/buffer_utilities.h"
#include "cs4722/texture_utilities.h"
#include "cs4722/compile_shaders.h"


#include "cs4722/window.h"
#include "cs4722/callbacks.h"

static cs4722::view *the_view;
static GLuint program;
static std::vector<cs4722::artifact*> artifact_list;

static GLint transform_loc;
static GLuint sampler2_loc, samplerC_loc;
static GLint surface_effect_loc;
static GLint diffuse_color_loc;

static GLuint vao;

void init()
{

    the_view = new cs4722::view();
//    the_view->enable_logging = true;
    the_view->set_flup(glm::vec3(0.202971,-0.227978,-0.952277),
                       glm::vec3(-0.978031,0,-0.20846),
                       glm::vec3(0.0475242,0.973667,-0.222969),
                       glm::vec3(-0.146291,0.195185,1.3214));
    



    program = cs4722::compile_shaders("vertex_shader.glsl","fragment_shader.glsl");
    glUseProgram(program);

    transform_loc = glGetUniformLocation(program, "transform");
    sampler2_loc = glGetUniformLocation(program, "sampler2");
    samplerC_loc = glGetUniformLocation(program, "samplerC");
    surface_effect_loc = glGetUniformLocation(program, "surface_effect");
    diffuse_color_loc = glGetUniformLocation(program, "diffuse_color");

    glEnable(GL_PROGRAM_POINT_SIZE);
    glEnable(GL_DEPTH_TEST);


    /*
     *  Create two textures, one from a file and one procedurally generated
        Note the different texture units assigned.
     */
    cs4722::init_texture_from_file("../media/tulips-bed-2048x2048.png", 2);
    cs4722::init_texture_from_file("../media/square-background-1456646_1024.png", 3);
    cs4722::init_texture_from_file("../media/square-2703542_960_720.jpg", 4);
    cs4722::init_texture_computed(1, 128);

    // sphere 1
    cs4722::shape* b = new cs4722::sphere(15, 50);
    auto* artf = new cs4722::artifact_rotating();
    artf->the_shape = (b);
    artf->world_transform.translate = (glm::vec3(-.5, -.5, 0));
    artf->animation_transform.rotation_axis = (glm::vec3(1, 1, 0));
    artf->rotation_rate = (M_PI / 3);
    artf->world_transform.scale = (glm::vec3(.4f, .4f, .4f));
    artf->animation_transform.rotation_center =
            artf->world_transform.matrix() * glm::vec4(0, 0, 0, 1);
    /*
     * Each artifact can be assigned a texture unit, this is used in the display function
     */
    artf->texture_unit = 1;
    artf->surface_material.diffuse_color = cs4722::x11::violet_red;
    artf->surface_effect = 1;
    artifact_list.push_back(artf);

    // sphere 2
    b = new cs4722::sphere(15, 50);
    artf = new cs4722::artifact_rotating();
    artf->the_shape = (b);
    artf->world_transform.translate = (glm::vec3(1.7, .5, 0));
    artf->animation_transform.rotation_axis = (glm::vec3(1, 1, 0));
    artf->rotation_rate = (M_PI / 2);
    artf->world_transform.scale = (glm::vec3(.4f, .4f, .4f));
    artf->animation_transform.rotation_center =
            artf->world_transform.matrix() * glm::vec4(0, 0, 0, 1);
    /*
     * Each artifact can be assigned a texture unit, this is used in the display function
     */
    artf->texture_unit = 3;
    artf->surface_material.diffuse_color = cs4722::x11::violet_red;
    artf->surface_effect = 1;
    artifact_list.push_back(artf);

    // block 1
    cs4722::shape* b1 = new cs4722::block();
    auto* artf1 = new cs4722::artifact_rotating();
    artf1->the_shape = (b1);
    artf1->world_transform.translate = (glm::vec3(-.5, .5, 0));
    artf1->animation_transform.rotation_axis = (glm::vec3(1, 0, 1));
    artf1->rotation_rate = (M_PI / 3);
    artf1->world_transform.scale = (glm::vec3(.4f, .4f, .4f));
    artf1->animation_transform.rotation_center =
            artf1->world_transform.matrix() * glm::vec4(0, .3f, 0, 1);
    artf1->texture_unit = 2;
    artf1->surface_material.diffuse_color = cs4722::x11::slate_blue;
    artf1->surface_effect = 0;
    artifact_list.push_back(artf1);

    // block 2
    b1 = new cs4722::block();
    auto* artf2 = new cs4722::artifact();
    artf2->the_shape = (b1);
    artf2->world_transform.translate = (glm::vec3(.7, -0.2, 0));
    artf2->world_transform.scale = (glm::vec3(.4f, .4f, .4f));
    artf2->animation_transform.rotation_center =
            artf2->world_transform.matrix() * glm::vec4(0, .3f, 0, 1);
    artf2->surface_material.diffuse_color = cs4722::x11::slate_blue;
    artf2->texture_unit = 1;
    artf2->surface_effect = 1;
    artifact_list.push_back(artf2);

    // cylinder 1
    b1 = new cs4722::cylinder();
    artf1 = new cs4722::artifact_rotating();
    artf1->the_shape = (b1);
    artf1->world_transform.translate = (glm::vec3(.5, .5, 0));
    artf1->animation_transform.rotation_axis = (glm::vec3(1, 0, 1));
    artf1->rotation_rate = (M_PI / 3);
    artf1->world_transform.scale = (glm::vec3(.4f, .4f, .4f));
    artf1->animation_transform.rotation_center =
            artf1->world_transform.matrix() * glm::vec4(0, .3f, 0, 1);
    artf1->texture_unit = 1;
    artf1->surface_material.diffuse_color = cs4722::x11::olive_drab;
    artf1->surface_effect = 2;
    artifact_list.push_back(artf1);

    // cylinder 2
    b1 = new cs4722::cylinder();
    artf2 = new cs4722::artifact();
    artf2->the_shape = (b1);
    artf2->world_transform.translate = (glm::vec3(.5*2, -.5*2, 0.8));
    artf2->animation_transform.rotation_axis = (glm::vec3(1, 0, 1));
    artf2->world_transform.scale = (glm::vec3(.4f, .4f, .4f));
    artf2->animation_transform.rotation_center =
            artf1->world_transform.matrix() * glm::vec4(0, .3f, 0, 1);
    artf2->texture_unit = 4;
    artf2->surface_material.diffuse_color = cs4722::x11::olive_drab;
    artf2->surface_effect = 0;
    artifact_list.push_back(artf2);

    // torus 1
    b1 = new cs4722::torus();
    artf1 = new cs4722::artifact_rotating();
    artf1->the_shape = (b1);
    artf1->world_transform.translate = (glm::vec3(0, .5, .6));
    artf1->animation_transform.rotation_axis = (glm::vec3(1, 0, 1));
    artf1->rotation_rate = (M_PI / 3);
    artf1->world_transform.scale = (glm::vec3(.4f, .4f, .4f));
    artf1->animation_transform.rotation_center =
            artf1->world_transform.matrix() * glm::vec4(0, .3f, 0, 1);
    artf1->texture_unit = 3;
    artf1->surface_material.diffuse_color = cs4722::x11::aquamarine3;
    artf1->surface_effect = 2;
    artifact_list.push_back(artf1);

    // torus 2
    b1 = new cs4722::torus();
    artf2 = new cs4722::artifact();
    artf2->the_shape = (b1);
    artf2->world_transform.translate = (glm::vec3(.5*2, .5, 0.8));
    artf2->animation_transform.rotation_axis = (glm::vec3(1, 0, 1));
    artf2->world_transform.scale = (glm::vec3(.4f, .4f, .4f));
    artf2->animation_transform.rotation_center =
            artf2->world_transform.matrix() * glm::vec4(0, .3f, 0, 1);
    artf2->texture_unit = 3;
    artf2->surface_material.diffuse_color = cs4722::x11::olive_drab;
    artf2->surface_effect = 0;
    artifact_list.push_back(artf2);

    // Sky Box
    auto env_val = 10;
    cs4722::init_cube_texture_from_path("../media/skybox", env_val, "jpg");
    auto skybox_scale = 40000.0f;
    auto* box = new cs4722::sphere();
    auto* artf_sky = new cs4722::artifact_rotating();
    artf_sky->the_shape = (box);
    artf_sky->world_transform.scale = glm::vec3(skybox_scale);
    artf_sky->texture_unit = env_val;
    artf_sky->surface_effect = 3;
    artifact_list.push_back(artf_sky);

    vao = cs4722::init_buffers(program, artifact_list, "bPosition", "", "bTextureCoord");

}


//----------------------------------------------------------------------------
//
// display
//


void
display()
{
    glBindVertexArray(vao);
    glUseProgram(program);

    auto view_transform = glm::lookAt(the_view->camera_position,
                                      the_view->camera_position + the_view->camera_forward,
                                      the_view->camera_up);
    auto projection_transform = glm::infinitePerspective(the_view->perspective_fovy,
                                                         the_view->perspective_aspect, the_view->perspective_near);
    auto vp_transform = projection_transform * view_transform;


    static auto last_time = 0.0;
    auto time = glfwGetTime();
    auto delta_time = time - last_time;
    last_time = time;


    for (auto artf : artifact_list) {

        artf->animate(time, delta_time);

        auto model_transform = artf->animation_transform.matrix() * artf->world_transform.matrix();
        auto transform = vp_transform * model_transform;
        glUniformMatrix4fv(transform_loc, 1, GL_FALSE, glm::value_ptr(transform));
        /*
         * Set the texture unit to use for this artf
         */
        glUniform1i(sampler2_loc, artf->texture_unit);
        glUniform1i(samplerC_loc, artf->texture_unit);

        glUniform1i(surface_effect_loc, artf->surface_effect);
        glUniform4fv(diffuse_color_loc, 1, artf->surface_material.diffuse_color.as_float());

        glDrawArrays(GL_TRIANGLES, artf->the_shape->buffer_start, artf->the_shape->buffer_size);
    }
}


int
main(int argc, char** argv)
{
    glfwInit();

    auto aspect_ratio = 16.0/9.0;
    auto* window = cs4722::setup_window("Multiple Textures", 0.9,
                                        aspect_ratio);

    gladLoadGL(glfwGetProcAddress);
    cs4722::setup_debug_callbacks();

    init();
    the_view->perspective_aspect = aspect_ratio;

    cs4722::setup_user_callbacks(window);
    glfwSetWindowUserPointer(window, the_view);
	
    while (!glfwWindowShouldClose(window))
    {
        glClearBufferfv(GL_COLOR, 0, cs4722::x11::gray50.as_float());
        glClear(GL_DEPTH_BUFFER_BIT);

        display();
        glfwSwapBuffers(window);
        glfwPollEvents();

    }

    glfwDestroyWindow(window);

    glfwTerminate();
}
