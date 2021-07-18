#include "Gfx.hpp"
#include <stdio.h>
#include <stdlib.h>

#include <vector>
#include <algorithm>
#include <string>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/norm.hpp>
#ifdef WITH_GLEW
#include <GL/glew.h>
#endif
#include <GLFW/glfw3.h>

#include "Menu.hpp"
#include "shader.hpp"
#include "Window.hpp"
#include <iostream>
#include <unistd.h>


// FastLED needs this symbol. Find a better place for it.
// It is supposed to be provided by the application, so
// we make it weak to allow for it to be reimplemented
uint16_t XY(uint8_t, uint8_t) __attribute__ ((weak));
uint16_t XY(uint8_t, uint8_t)
{
   return 0;
}

namespace gfx {

using namespace glm;
using namespace std;

namespace {

const std::string TRIANGLE_VERTEX_SHADER =
#include "lit_triangle.vertexshader"
;

const std::string TRIANGLE_FRAGMENT_SHADER =
#include "lit_triangle.fragmentshader"
;


struct LedPosition
{
   GLfloat x,y,z;
   
   void operator=(const LED& l)
   {
      x = l.x;
      y = l.y;
      z = l.z;
   }
   
};

struct LedColor
{
   GLfloat r,g,b;
   
   void operator=(const LED& l)
   {
      if (l.color != nullptr)
      {
         r = float(l.color->r)/255;
         g = float(l.color->g)/255;
         b = float(l.color->b)/255;
      }
   }
};

vec3 toVec3(const Vertex& v)
{
   return vec3(v.x, v.y, v.z);
}

}

class Gfx::Impl
{
public:
   Impl(vector<LED>& led_coordinates, vector<Triangle>& triangles, const Config& config = Config());
   ~Impl();

   bool draw();
   
   void drawLeds();
   void drawLitTriangles();
   
   void controlFrameRate();

   std::vector<LED>& m_leds;
   std::vector<Triangle>& m_triangles;
   Config              m_config;
   Window              m_window;
   Menu                m_menu;
   GLuint              m_triangle_vertex_array_id;
   GLuint              m_triangle_program_id;
   vector<LedPosition> m_led_position_data;
   vector<LedColor>    m_led_color_data;
   GLuint              m_triangle_vertex_buffer;
   double              m_last_time;
   const double        m_frame_time;
};

Gfx::Impl::Impl(std::vector<LED>& leds, std::vector<Triangle>& triangles, const Config& config):
   m_leds(leds),
   m_triangles(triangles),
   m_config(config),
   m_window(m_config),
   m_menu(m_config, m_window.get()),
   m_led_position_data(m_leds.size()),
   m_led_color_data(m_leds.size()),
   m_frame_time(1.0/m_config.framesPerSecond())
{
   copy(m_leds.begin(), m_leds.end(), m_led_position_data.begin());
   
   // Enable depth test
   glEnable(GL_DEPTH_TEST);
   // Accept fragment if it closer to the camera than the former one
   glDepthFunc(GL_LESS);
      
   m_triangle_program_id = LoadShaders(TRIANGLE_VERTEX_SHADER.c_str(), TRIANGLE_FRAGMENT_SHADER.c_str());
   
   // first, configure the cube's VAO (and VBO)
   glGenVertexArrays(1, &m_triangle_vertex_array_id);
   glGenBuffers(1, &m_triangle_vertex_buffer);

   glBindVertexArray(m_triangle_vertex_array_id);

   glBindBuffer(GL_ARRAY_BUFFER, m_triangle_vertex_buffer);
   glBufferData(GL_ARRAY_BUFFER, sizeof(Triangle) * m_triangles.size(), m_triangles.data(), GL_STATIC_DRAW);

   // position attribute for triangles
   glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
   glEnableVertexAttribArray(0);

   glBindBuffer(GL_ARRAY_BUFFER, 0);
   glBindVertexArray(0);
   
   // front facing side of the triangles is with vertices going clockwise
   glFrontFace(GL_CW);
}

void Gfx::Impl::controlFrameRate()
{
   if (m_last_time != 0)
   {
      double dt = glfwGetTime() - m_last_time;
      if (dt < m_frame_time)
      {
         usleep((m_frame_time - dt)*1000000);
      }
   }
   m_last_time = glfwGetTime();
   
   // wait for last iteration to finish rendering
   glFinish();
}

bool Gfx::Impl::draw()
{
   controlFrameRate();
   
   // Clear the screen
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   m_window.processInputs();

   copy(m_leds.begin(), m_leds.end(), m_led_color_data.begin());

   glUseProgram(m_triangle_program_id);

   // view/projection transformations
   glUniformMatrix4fv(glGetUniformLocation(m_triangle_program_id, "projection"), 1, GL_FALSE, &m_window.getProjectionMatrix()[0][0]);
   glUniformMatrix4fv(glGetUniformLocation(m_triangle_program_id, "view"), 1, GL_FALSE, &m_window.getViewMatrix()[0][0]);
   glUniform3fv(glGetUniformLocation(m_triangle_program_id, "direction"), 1, &m_window.getDirection()[0]);

   // world transformation
   glm::mat4 model = glm::mat4(1.0f);
   glUniformMatrix4fv(glGetUniformLocation(m_triangle_program_id, "model"), 1, GL_FALSE, &model[0][0]);
   
   float cutoff = m_config.cutoffDistance();
   glUniform1f(glGetUniformLocation(m_triangle_program_id, "cutoff_distance_square"), cutoff * cutoff);
   glUniform1f(glGetUniformLocation(m_triangle_program_id, "attenuation_constant"), m_config.attenuationConstant());
   glUniform1f(glGetUniformLocation(m_triangle_program_id, "attenuation_linear"), m_config.attenuationLinear());
   glUniform1f(glGetUniformLocation(m_triangle_program_id, "attenuation_square"), m_config.attenuationSquare());
   

   for (unsigned k = 0; k < m_triangles.size(); k++)
   {
      Triangle& t(m_triangles[k]);
      vec3 normal = glm::normalize(glm::cross(toVec3(t.vertices[1]) - toVec3(t.vertices[0]), toVec3(t.vertices[2]) - toVec3(t.vertices[0])));
      glUniform3fv(glGetUniformLocation(m_triangle_program_id, "normal"), 1, &normal[0]);

      // led color and position
      glUniform3fv(glGetUniformLocation(m_triangle_program_id, "led_color"), m_leds.size()*sizeof(LedPosition), &m_led_color_data[t.vertices[0].start_led_ix].r);
      glUniform3fv(glGetUniformLocation(m_triangle_program_id, "led_pos"), m_leds.size()*sizeof(LedColor), &m_led_position_data[t.vertices[0].start_led_ix].x);
      glUniform1i(glGetUniformLocation(m_triangle_program_id, "num_leds"), t.vertices[0].num_leds);

      // render the triangle
      glBindVertexArray(m_triangle_vertex_array_id);
      glDrawArrays(GL_TRIANGLES, k*3, 3);
      glBindVertexArray(0);
   }
   
   m_menu.draw();
      
   m_window.swapBuffers();
   return not m_window.shouldClose();
}

Gfx::Impl::~Impl()
{
   // Cleanup VBO and shader
   glDeleteProgram(m_triangle_program_id);
   glDeleteVertexArrays(1, &m_triangle_vertex_array_id);
}

Gfx::Gfx(std::vector<LED>& led_coordinates, std::vector<Triangle>& triangles, const Config& config):
    m_i(*new Gfx::Impl(led_coordinates, triangles, config))
{
}


bool Gfx::draw()
{
   return m_i.draw();
}

Gfx::~Gfx()
{
   delete &m_i;
}

}