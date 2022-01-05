



#include "GLM/gtc/type_ptr.hpp"



#include <glad/gl.h>
#include <GLFW/glfw3.h>


#include "cs4722/buffer_utilities.h"
#include "cs4722/compile_shaders.h"
#include "cs4722/window.h"

static GLuint program;
static GLuint transform_loc;
static std::vector<cs4722::artifact*> artifact_list;

void init(void)
{
    program = cs4722::compile_shaders("vertex_shader.glsl","fragment_shader.glsl");
    glUseProgram(program);

    transform_loc = glGetUniformLocation(program, "transform");

    glEnable(GL_PROGRAM_POINT_SIZE);
    glEnable(GL_DEPTH_TEST);



    auto* shape = new cs4722::sphere();
    auto* cylinder_north = new cs4722::cylinder();
    auto* cylinder_east = new cs4722::cylinder();
    auto* cylinder_south = new cs4722::cylinder();
    auto* cylinder_west = new cs4722::cylinder();
    shape->color_set_ = std::vector<cs4722::color>({cs4722::x11::wheat1, cs4722::x11::wheat4});
    cylinder_north->color_set_ = std::vector<cs4722::color>({cs4722::x11::red1, cs4722::x11::red4});
    cylinder_east->color_set_ = std::vector<cs4722::color>({cs4722::x11::blue1, cs4722::x11::blue4});
    cylinder_south->color_set_ = std::vector<cs4722::color>({cs4722::x11::yellow1, cs4722::x11::yellow4});
    cylinder_west->color_set_ = std::vector<cs4722::color>({cs4722::x11::green1, cs4722::x11::green4});

    auto number = 5;
    auto d = 4.0f / (2 * number + 1);
    auto radius = d / 8;
    auto base = -1 + 3 * d / 4;

    for (auto x = 0; x < number; ++x)
    {
        for (auto y = 0; y < number; ++y)
        {
            auto* artf = new cs4722::artifact();
            auto* artf_cyinder_north = new cs4722::artifact();
            auto* artf_cyinder_east = new cs4722::artifact();
            auto* artf_cyinder_south = new cs4722::artifact();
            auto* artf_cyinder_west = new cs4722::artifact();


            artf->the_shape = shape;
            artf_cyinder_north->the_shape = cylinder_north;
            artf_cyinder_east->the_shape = cylinder_east;
            artf_cyinder_south->the_shape = cylinder_south;
            artf_cyinder_west->the_shape = cylinder_west;


            artf->world_transform.translate = glm::vec3(base + x * d, base + y * d, base);
            artf_cyinder_north->world_transform.translate = glm::vec3((base + x * d), (base + y * d) + (radius * 1.5), base);
            artf_cyinder_east->world_transform.translate = glm::vec3((base + x * d) + (radius * 2), (base + y * d), base);
            artf_cyinder_south->world_transform.translate = glm::vec3((base + x * d), (base + y * d) - (radius * 1.5), base);
            artf_cyinder_west->world_transform.translate = glm::vec3((base + x * d) - (radius * 2), (base + y * d), base);

            artf_cyinder_north->world_transform.rotation_angle = 1.5708;
            artf_cyinder_east->world_transform.rotation_angle = 1.5708;
            artf_cyinder_south->world_transform.rotation_angle = 1.5708;
            artf_cyinder_west->world_transform.rotation_angle = 1.5708;

            artf->world_transform.scale = glm::vec3(radius, radius, radius);
            artf_cyinder_north->world_transform.scale = glm::vec3(radius/2, radius*2, radius);
            artf_cyinder_east->world_transform.scale = glm::vec3(radius/2, radius*2, radius);
            artf_cyinder_south->world_transform.scale = glm::vec3(radius/2, radius*2, radius);
            artf_cyinder_west->world_transform.scale = glm::vec3(radius/2, radius*2, radius);

            artifact_list.push_back(artf);
            artifact_list.push_back(artf_cyinder_north);
            artifact_list.push_back(artf_cyinder_east);
            artifact_list.push_back(artf_cyinder_south);
            artifact_list.push_back(artf_cyinder_west);

        }
    }

    cs4722::init_buffers(program, artifact_list, "bPosition", "bColor");


}



void display()
{

    static auto last_time = 0.0;
    auto time = glfwGetTime();
    auto delta_time = time - last_time;
    last_time = time;

    // uncomment the following few lines to see the frame rate computed two different ways
//    static double  arate = 0.0;
//    auto x = (100 * arate + 1 / delta_time) / 101;
//    arate  = x;
//	printf("artifact count:  %d      rate:  %.3f    arate: %.3f\n", artifact_list.size(), 1/delta_time, arate);


    for (auto artf : artifact_list) {
        artf->animate(time, delta_time);
        auto model_matrix = artf->animation_transform.matrix() * artf->world_transform.matrix();
        glUniformMatrix4fv(transform_loc, 1, GL_FALSE, glm::value_ptr(model_matrix));

        glDrawArrays(GL_TRIANGLES, artf->the_shape->buffer_start, artf->the_shape->buffer_size);


    }
}

int
main(int argc, char** argv)
{
    glfwInit();
    auto *window = cs4722::setup_window("Assignment 3 Part 2", .9);
    gladLoadGL(glfwGetProcAddress);

    init();

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
