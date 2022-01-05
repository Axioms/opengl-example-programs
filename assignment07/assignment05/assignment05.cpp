


#include "GLM/gtc/type_ptr.hpp"



#include <glad/gl.h>


#include "cs4722/callbacks.h"
#include "cs4722/buffer_utilities.h"
#include "cs4722/window.h"
#include "cs4722/texture_utilities.h"
#include "cs4722/compile_shaders.h"

#include "cs4722/view.h"
#include "cs4722/artifact.h"

#include "cs4722/light.h"

#include <GLM/gtc/matrix_inverse.hpp>


#include <GLFW/glfw3.h>


static cs4722::view *the_view;
static GLuint program;
static std::vector<cs4722::artifact*> artifact_list;

static cs4722::light a_light;

static GLint transform_loc;
static GLuint sampler2_loc, samplerC_loc;
static GLint surface_effect_loc;
static GLint diffuse_color_loc;

// many uniform variable locations to deal with
static GLint ambient_light_loc;  // three components of light
static GLint specular_light_loc;
static GLint diffuse_light_loc;
static GLint ambient_color_loc;  // three components of surface material
static GLint specular_color_loc;
static GLint light_position_loc; // dposition of the light
static GLint camera_position_loc;
static GLint specular_shininess_loc;     // exponent for sharpening highlights
static GLint specular_strength_loc;      // extra factor to adjust shininess
static GLint m_transform_loc;
static GLint vp_transform_loc;
static GLint normal_transform_loc;

static GLuint vao;

void init()
{

    the_view = new cs4722::view();
//    the_view->enable_logging = true;
    the_view->set_flup(glm::vec3(0.202971,-0.227978,-0.952277),
                       glm::vec3(-0.978031,0,-0.20846),
                       glm::vec3(0.0475242,0.973667,-0.222969),
                       glm::vec3(-0.146291,0.195185,1.3214));


    the_view->enable_logging = false;
    a_light.ambient_light = cs4722::x11::gray25;
    a_light.is_directional = false;
    a_light.light_direction_position = glm::vec4(1.5, 0, 0,4);


    program = cs4722::compile_shaders("vertex_shader.glsl","fragment_shader.glsl");
    glUseProgram(program);

    transform_loc = glGetUniformLocation(program, "transform");
    sampler2_loc = glGetUniformLocation(program, "sampler2");
    samplerC_loc = glGetUniformLocation(program, "samplerC");
    surface_effect_loc = glGetUniformLocation(program, "surface_effect");
    diffuse_color_loc = glGetUniformLocation(program, "diffuse_color");

    ambient_light_loc = glGetUniformLocation(program, "ambient_light");
    specular_light_loc = glGetUniformLocation(program, "specular_light");
    diffuse_light_loc = glGetUniformLocation(program, "diffuse_light");
    ambient_color_loc = glGetUniformLocation(program, "ambient_color");
    specular_color_loc = glGetUniformLocation(program, "specular_color");
    diffuse_color_loc = glGetUniformLocation(program, "diffuse_color");
    light_position_loc = glGetUniformLocation(program, "light_position");
    camera_position_loc = glGetUniformLocation(program, "camera_position");
    specular_shininess_loc = glGetUniformLocation(program, "specular_shininess");
    specular_strength_loc = glGetUniformLocation(program, "specular_strength");
    // vertex shader uniforms
    m_transform_loc = glGetUniformLocation(program, "m_transform");
    vp_transform_loc = glGetUniformLocation(program, "vp_transform");
    normal_transform_loc = glGetUniformLocation(program, "normal_transform");

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

    artf->surface_material.ambient_color = (cs4722::color(
            0 * 255 / (0-1), 0 * 255 / (0 - 1),
            0 * 255 / (0 - 1), 255));
    artf->surface_material.specular_color = cs4722::x11::white;
    artf->surface_material.diffuse_color = artf->surface_material.ambient_color;
    artf->surface_material.specular_strength = .75;
    artf->surface_material.shininess = 30.0;


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

    artf->surface_material.ambient_color = (cs4722::color(
            1 * 255 / (2-1), 1 * 255 / (2 - 1),
            1 * 255 / (2 - 1), 255));
    artf->surface_material.specular_color = cs4722::x11::white;
    artf->surface_material.diffuse_color = artf->surface_material.ambient_color;
    artf->surface_material.specular_strength = .75;
    artf->surface_material.shininess = 30.0;

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

    artf->surface_material.ambient_color = (cs4722::color(
            3 * 255 / (3-1), 3 * 255 / (3 - 1),
            3 * 255 / (3 - 1), 255));
    artf->surface_material.specular_color = cs4722::x11::white;
    artf->surface_material.diffuse_color = artf->surface_material.ambient_color;
    artf->surface_material.specular_strength = .75;
    artf->surface_material.shininess = 30.0;

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

    artf->surface_material.ambient_color = (cs4722::color(
            4 * 255 / (4-1), 4 * 255 / (4 - 1),
            4 * 255 / (4 - 1), 255));
    artf->surface_material.specular_color = cs4722::x11::white;
    artf->surface_material.diffuse_color = artf->surface_material.ambient_color;
    artf->surface_material.specular_strength = .75;
    artf->surface_material.shininess = 30.0;

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

    artf->surface_material.ambient_color = (cs4722::color(
            6 * 255 / (6-1), 6 * 255 / (6 - 1),
            6 * 255 / (6 - 1), 255));
    artf->surface_material.specular_color = cs4722::x11::white;
    artf->surface_material.diffuse_color = artf->surface_material.ambient_color;
    artf->surface_material.specular_strength = .75;
    artf->surface_material.shininess = 30.0;

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
    artf->surface_material.ambient_color = (cs4722::color(
            7 * 255 / (7-1), 7 * 255 / (7 - 1),
            7 * 255 / (7 - 1), 255));
    artf->surface_material.specular_color = cs4722::x11::white;
    artf->surface_material.diffuse_color = artf->surface_material.ambient_color;
    artf->surface_material.specular_strength = .75;
    artf->surface_material.shininess = 30.0;

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

    artf->surface_material.ambient_color = (cs4722::color(
            8 * 255 / (8-1), 8 * 255 / (8 - 1),
            8 * 255 / (8 - 1), 255));
    artf->surface_material.specular_color = cs4722::x11::white;
    artf->surface_material.diffuse_color = artf->surface_material.ambient_color;
    artf->surface_material.specular_strength = .75;
    artf->surface_material.shininess = 30.0;

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

    artf->surface_material.ambient_color = (cs4722::color(
            9 * 255 / (9-1), 9 * 255 / (9 - 1),
            9 * 255 / (9 - 1), 255));
    artf->surface_material.specular_color = cs4722::x11::white;
    artf->surface_material.diffuse_color = artf->surface_material.ambient_color;
    artf->surface_material.specular_strength = .75;
    artf->surface_material.shininess = 30.0;

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

    artf->surface_material.ambient_color = (cs4722::color(
            10 * 255 / (10-1), 10 * 255 / (10 - 1),
            10 * 255 / (10 - 1), 255));
    artf->surface_material.specular_color = cs4722::x11::white;
    artf->surface_material.diffuse_color = artf->surface_material.ambient_color;
    artf->surface_material.specular_strength = .75;
    artf->surface_material.shininess = 30.0;

    artifact_list.push_back(artf_sky);

    vao = cs4722::init_buffers(program, artifact_list, "bPosition", "", "bTextureCoord");

}


//----------------------------------------------------------------------------
//
// display
//

static GLfloat light_ambient[4];
static GLfloat light_diffuse[4];
static GLfloat light_specular[4];
static GLfloat material_ambient[4];
static GLfloat material_diffuse[4];
static GLfloat material_specular[4];

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

    glUniform4fv(light_position_loc, 1, glm::value_ptr(a_light.light_direction_position));
    glUniform4fv(camera_position_loc, 1, glm::value_ptr(the_view->camera_position));

    static auto last_time = 0.0;
    auto time = glfwGetTime();
    auto delta_time = time - last_time;
    last_time = time;


    for (auto artf : artifact_list) {

        artf->animate(time, delta_time);

        auto model_transform = artf->animation_transform.matrix() * artf->world_transform.matrix();
        auto transform = vp_transform * model_transform;
        glUniformMatrix4fv(m_transform_loc, 1, GL_FALSE, glm::value_ptr(model_transform));
        glUniformMatrix4fv(vp_transform_loc, 1, GL_FALSE, glm::value_ptr(vp_transform));
        glUniformMatrix4fv(normal_transform_loc, 1, GL_FALSE,
                           glm::value_ptr(glm::inverseTranspose(model_transform)));
        /*
         * Set the texture unit to use for this artf
         */

        a_light.ambient_light.as_float(light_ambient);
        a_light.diffuse_light.as_float(light_diffuse);
        a_light.specular_light.as_float(light_specular);
        artf->surface_material.ambient_color.as_float(material_ambient);
        artf->surface_material.diffuse_color.as_float(material_diffuse);
        artf->surface_material.specular_color.as_float(material_specular);
        glUniform4fv(ambient_light_loc, 1, light_ambient);
        glUniform4fv(diffuse_light_loc, 1, light_diffuse);
        glUniform4fv(specular_light_loc, 1, light_specular);
        glUniform4fv(ambient_color_loc, 1, material_ambient);
        glUniform4fv(diffuse_color_loc, 1,  material_diffuse);
        glUniform4fv(specular_color_loc, 1, material_specular);
        glUniform1f(specular_shininess_loc, artf->surface_material.shininess);
        glUniform1f(specular_strength_loc, artf->surface_material.specular_strength);

        glUniform1i(sampler2_loc, artf->texture_unit);
        glUniform1i(samplerC_loc, artf->texture_unit);

        glUniform1i(surface_effect_loc, artf->surface_effect);

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
