


#include "GLM/gtc/type_ptr.hpp"
#include "GLM/gtc/random.hpp"


#include <glad/gl.h>


#include "cs4722/callbacks.h"
#include "cs4722/buffer_utilities.h"
#include "cs4722/window.h"
#include "cs4722/compile_shaders.h"


static cs4722::view *the_view;
static GLuint program;
static std::vector<cs4722::artifact*> artf_list;

static GLuint transform_loc;
static GLint diffuse_color_loc;


static auto asteroid_center = glm::vec3(0,0,0);
static float asteroid_radius = 20.0;
static float pc_height = 0.1;

static unsigned int random_seed = 314159265;

void init()
{

    the_view = new cs4722::view();
//    the_view->camera_position = glm::vec3(0, 0, 3);
//    the_view->enable_logging = false;

    program = cs4722::compile_shaders("vertex_shader.glsl","fragment_shader.glsl");
    glUseProgram(program);

    transform_loc = glGetUniformLocation(program, "transform");
    diffuse_color_loc = glGetUniformLocation(program, "diffuse_color");

    glEnable(GL_DEPTH_TEST);


    cs4722::shape* b = new cs4722::sphere(100, 200);
    b->color_set_ = std::vector<cs4722::color>({cs4722::color(210,255,210),cs4722::color(230,255,230) });
    auto* artf = new cs4722::artifact_rotating();
    artf->the_shape = (b);
    artf->world_transform.translate = asteroid_center;
    artf->animation_transform.rotation_axis = (glm::vec3(1, 1, 0));
//    artf->rotation_rate = (M_PI / 3);
    artf->world_transform.scale = (glm::vec3(asteroid_radius,asteroid_radius,asteroid_radius));
    artf->animation_transform.rotation_center =
            artf->world_transform.matrix() * glm::vec4(0, 0, 0, 1);
    artf->surface_material.diffuse_color = cs4722::x11::white;
    artf_list.push_back(artf);


    std::srand(random_seed);


    cs4722::shape* shapes[] = {
            new cs4722::block(),
            new cs4722::cylinder(.3, 20),
            new cs4722::cylinder(1.2, 20),
    };
    int num_shapes = 3;
    shapes[0]->color_set_ = std::vector<cs4722::color>({cs4722::x11::gray60, cs4722::x11::gray100});
    shapes[1]->color_set_ = std::vector<cs4722::color>({cs4722::x11::gray60, cs4722::x11::gray100});
    shapes[2]->color_set_ = std::vector<cs4722::color>({cs4722::x11::gray60, cs4722::x11::gray100});

    for(int i = 0; i < 5000; i++ ) {
        float height = glm::linearRand(.01, .2);
        auto position = glm::sphericalRand(asteroid_radius + height/2) + asteroid_center;
//        printf("pos (%f, %f, %f)  distance %f\n", position.x, position.y, position.z,
//               glm::length(position - asteroid_center));
        auto cToP = position - asteroid_center;

        artf = new cs4722::artifact_rotating();
        artf->the_shape = shapes[i % num_shapes];
        artf->world_transform.scale = glm::vec3(height / 4, height, height / 4);
        artf->world_transform.rotation_axis = glm::vec3(cToP.z, 0, -cToP.x);
        artf->world_transform.rotation_angle = glm::acos(position.y / glm::length(position));
        artf->world_transform.rotation_center = glm::vec3(0, 0, 0);
        artf->world_transform.translate = position;

        unsigned int r = (int)glm::linearRand(0,256);
        unsigned int g = (int)glm::linearRand(0,256);
        unsigned int b = (int)glm::linearRand(0,256);
        artf->surface_material.diffuse_color = cs4722::color(r,g,b);

        artf_list.push_back(artf);
    }








    // position the camera
    the_view->camera_position = (asteroid_radius + pc_height) * glm::vec3(1,0,0) + asteroid_center;
    the_view->camera_up = glm::vec3(1,0,0);
    the_view->camera_forward = glm::vec3(0,1,0);
    the_view->camera_left = glm::cross(the_view->camera_up, the_view->camera_forward);



    cs4722::init_buffers(program, artf_list, "bPosition", "bColor");

}


//----------------------------------------------------------------------------
//
// display
//

auto last_time = 0.0;

void
display()
{
    auto view_transform = glm::lookAt(the_view->camera_position,
                                      the_view->camera_position + the_view->camera_forward,
                                      the_view->camera_up);
    auto projection_transform = glm::infinitePerspective(the_view->perspective_fovy,
                                                         the_view->perspective_aspect, the_view->perspective_near);
    auto vp_transform = projection_transform * view_transform;


    auto time = glfwGetTime();
    auto delta_time = time - last_time;
    last_time = time;


    for (auto artf : artf_list) {

        artf->animate(time, delta_time);

        auto model_transform = artf->animation_transform.matrix() * artf->world_transform.matrix();
        auto transform = vp_transform * model_transform;
        glUniformMatrix4fv(transform_loc, 1, GL_FALSE, glm::value_ptr(transform));

        glUniform4fv(diffuse_color_loc, 1, artf->surface_material.diffuse_color.as_float());
        glDrawArrays(GL_TRIANGLES, artf->the_shape->buffer_start, artf->the_shape->buffer_size);
       

    }
}

float speed = .1f;
float lr_scale = speed;
float fb_scale = speed;
float ud_scale = speed;

float lr_pan_scale = .01f;
float ud_pan_scale = lr_pan_scale;


/*
 * These variables are used to hold the window height and width and position to use when
 *  exiting full screen.
 */
static int old_width, old_height, old_xpos, old_ypos;

void general_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
//    auto* view = static_cast<cs4722::view*>(glfwGetWindowUserPointer(window));
    // the_scene->the_view->key_callback(window, key, scancode, action, mods);
    // std::cout << "key " << key << std::endl;
    if (action != GLFW_PRESS && action != GLFW_REPEAT)
    {
        // only process key presses and repeats
    }
    else if (key == GLFW_KEY_A )
    {
        the_view->camera_position += lr_scale * the_view->camera_left;
    }
    else if (key == GLFW_KEY_D)
    {
        the_view->camera_position -= lr_scale * the_view->camera_left;
    }
    else if (key == GLFW_KEY_W)
    {
        the_view->camera_position += fb_scale * the_view->camera_forward;
    }
    else if (key == GLFW_KEY_S)
    {
        the_view->camera_position -= fb_scale * the_view->camera_forward;
    }
    else if (key == GLFW_KEY_ESCAPE)
    {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
    else if (key == GLFW_KEY_F11 && action == GLFW_PRESS)
    {
        if (!glfwGetWindowMonitor(window)) {
            glfwGetWindowPos(window, &old_xpos, &old_ypos);
            glfwGetWindowSize(window, &old_width, &old_height);
            auto monitor = glfwGetPrimaryMonitor();
            const auto* mode = glfwGetVideoMode(monitor);
            glfwSetWindowMonitor(window, monitor, 0, 0, mode->width, mode->height, mode->refreshRate);
        }
        else
        {
            glfwSetWindowMonitor(window, nullptr, old_xpos, old_ypos, old_width, old_height, 0);
        }
    }
    else
    {

    }

    // display the position of the camera and its distance from the center
    printf("position (%f, %f, %f)      distance from center: %f     should be: %f\n",
       the_view->camera_position.x,the_view->camera_position.y, the_view->camera_position.z,
       glm::length(the_view->camera_position - asteroid_center),
       asteroid_radius + pc_height);
}



void window_size_callback(GLFWwindow* window, int width, int height)
{
    int widthfb, heightfb;
    glfwGetFramebufferSize(window, &widthfb, &heightfb);
    glViewport(0, 0, widthfb, heightfb);
    the_view->perspective_aspect =
        (static_cast<float>(widthfb) / static_cast<float>(heightfb));

}


void move_callback(GLFWwindow* window, double xpos, double ypos)
{
    static double last_x = 0.0;
    static double last_y = 0.0;

    auto dx = xpos - the_view->last_x;
    auto dy = ypos - the_view->last_y;
    the_view->last_x = xpos;
    the_view->last_y = ypos;


    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT))
    {
        // std::cout << "(" << xpos << "," << ypos << ")" << std::endl;
        // auto const rot_lr = glm::mat3(glm::rotate(glm::identity<glm::mat4>(),
        //     static_cast<float>(-dx * lr_pan_scale), camera_up_));
        auto const rot_lr = glm::mat3(glm::rotate(glm::identity<glm::mat4>(),
                                                  static_cast<float>(-dx * lr_pan_scale), glm::vec3(0, 1, 0)));
        the_view->camera_left = rot_lr * the_view->camera_left;
        the_view->camera_forward = rot_lr * the_view->camera_forward;
        the_view->camera_up = rot_lr * the_view->camera_up;

        auto const rot_ud = glm::mat3(glm::rotate(glm::identity<glm::mat4>(),
                                                  static_cast<float>(dy * ud_pan_scale), the_view->camera_left));
        the_view->camera_up = rot_ud * the_view->camera_up;
        the_view->camera_forward = rot_ud * the_view->camera_forward;
    }
}


int
main(int argc, char** argv)
{
    glfwInit();

    auto aspect_ratio = 1.0;
    auto* window = cs4722::setup_window("Window Events", 0.9, aspect_ratio);

    gladLoadGL(glfwGetProcAddress);
    cs4722::setup_debug_callbacks();

    init();
    the_view->perspective_aspect = aspect_ratio;

    glfwSetWindowUserPointer(window, the_view);
    glfwSetKeyCallback(window, general_key_callback);
    glfwSetWindowSizeCallback(window, window_size_callback);

	
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
