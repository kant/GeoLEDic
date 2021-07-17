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

#include "shader.hpp"
#include "texture.hpp"
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

namespace {
const std::string VERTEX_SHADER =
#include "LED.vertexshader"
;

const std::string FRAGMENT_SHADER =
#include "LED.fragmentshader"
;

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

}

#include "LedTexture.hpp"


class Gfx::Impl
{
public:
   Impl(std::vector<LED>& led_coordinates, std::vector<Triangle>& triangles, const Config& config = Config());
   ~Impl();

   bool draw();
   
   void drawLeds();
   void drawLitTriangles();
   
   void controlFrameRate();

   std::vector<LED>& m_leds;
   std::vector<Triangle>* m_triangles;
   Window         m_window;
   GLuint         m_vertex_array_id;
   GLuint         m_triangle_vertex_array_id;
   GLuint         m_program_id;
   GLuint         m_triangle_program_id;
   LedPosition*   m_led_position_size_data;
   LedColor*      m_led_color_data;
   GLuint         m_vertex_buffer;
   GLuint         m_triangle_vertex_buffer;
   GLuint         m_leds_position_buffer;
   GLuint         m_leds_color_buffer;
   GLuint         m_texture;
   GLuint         m_camera_right_worldspace_id;
   GLuint         m_camera_up_worldspace_id;
   GLuint         m_view_proj_matrix_id;
   GLuint         m_texture_id;
   double         m_last_time;
   const double   m_frame_time;
};

Gfx::Impl::Impl(std::vector<LED>& leds, std::vector<Triangle>& triangles, const Config& config):
   m_leds(leds),
   m_triangles(&triangles),
   m_window(config),
   m_led_position_size_data(new LedPosition[m_leds.size()]),
   m_led_color_data(new LedColor[m_leds.size()]),
   m_frame_time(1.0/config.framesPerSecond())
{
   // Enable depth test
   glEnable(GL_DEPTH_TEST);
   // Accept fragment if it closer to the camera than the former one
   glDepthFunc(GL_LESS);
      
   glGenVertexArrays(1, &m_vertex_array_id);
   glBindVertexArray(m_vertex_array_id);
   
   m_program_id = LoadShaders(VERTEX_SHADER.c_str(), FRAGMENT_SHADER.c_str());
      
   // Vertex shader
   m_camera_right_worldspace_id  = glGetUniformLocation(m_program_id, "CameraRight_worldspace");
   m_camera_up_worldspace_id  = glGetUniformLocation(m_program_id, "CameraUp_worldspace");
   m_view_proj_matrix_id = glGetUniformLocation(m_program_id, "VP");
      
   // fragment shader
   m_texture_id  = glGetUniformLocation(m_program_id, "myTextureSampler");
            
   m_texture = loadDDS(blobs::LedTexture, sizeof(blobs::LedTexture));
      
   // The VBO containing the 4 vertices of the leds.
   // Thanks to instancing, they will be shared by all leds.
   static const GLfloat g_vertex_buffer_data[] = {
     -0.5f, -0.5f, 0.0f,
      0.5f, -0.5f, 0.0f,
     -0.5f,  0.5f, 0.0f,
      0.5f,  0.5f, 0.0f,
   };

   glGenBuffers(1, &m_vertex_buffer);
   glBindBuffer(GL_ARRAY_BUFFER, m_vertex_buffer);
   glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
      
   // The VBO containing the positions and sizes of the leds
   glGenBuffers(1, &m_leds_position_buffer);
   glBindBuffer(GL_ARRAY_BUFFER, m_leds_position_buffer);
   // Initialize with empty (NULL) buffer : it will be updated later, each frame.
   glBufferData(GL_ARRAY_BUFFER, m_leds.size() * sizeof(LedPosition), NULL, GL_STREAM_DRAW);
      
   // The VBO containing the colors of the leds
   glGenBuffers(1, &m_leds_color_buffer);
   glBindBuffer(GL_ARRAY_BUFFER, m_leds_color_buffer);
   // Initialize with empty (NULL) buffer : it will be updated later, each frame.
   glBufferData(GL_ARRAY_BUFFER, m_leds.size() * sizeof(LedColor), NULL, GL_STREAM_DRAW);

   m_triangle_program_id = LoadShaders(TRIANGLE_VERTEX_SHADER.c_str(), TRIANGLE_FRAGMENT_SHADER.c_str());
   
   // first, configure the cube's VAO (and VBO)
   glGenVertexArrays(1, &m_triangle_vertex_array_id);
   glGenBuffers(1, &m_triangle_vertex_buffer);

   glBindVertexArray(m_triangle_vertex_array_id);

   glBindBuffer(GL_ARRAY_BUFFER, m_triangle_vertex_buffer);
   glBufferData(GL_ARRAY_BUFFER, sizeof(Triangle) * m_triangles->size(), m_triangles->data(), GL_STATIC_DRAW);


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

   int i = 0;
   for (LED& p: m_leds)
   {
      // Fill the GPU buffer
      m_led_position_size_data[i] = p;
      m_led_color_data[i] = p;
      i++;
   }

   if (m_triangles != nullptr and m_window.shouldDrawLitTriangles())
   {
      drawLitTriangles();
   }
   else
   {
      drawLeds();
   }
   
   m_window.swapBuffers();
   return not m_window.shouldClose();
}
 
void Gfx::Impl::drawLeds()
{
   const glm::mat4& view_matrix = m_window.getViewMatrix();
   glm::vec3 camera_position(glm::inverse(view_matrix)[3]);
   glm::mat4 ViewProjectionMatrix = m_window.getProjectionMatrix() * view_matrix;
   
   // Update the buffers that OpenGL uses for rendering.
   // There are much more sophisticated means to stream data from the CPU to the GPU, 
   // but this is outside the scope of this tutorial.
   // http://www.opengl.org/wiki/Buffer_Object_Streaming
   
   
   glBindBuffer(GL_ARRAY_BUFFER, m_leds_position_buffer);
   glBufferData(GL_ARRAY_BUFFER, m_leds.size() * sizeof(LedPosition), NULL, GL_STREAM_DRAW); // Buffer orphaning, a common way to improve streaming perf. See above link for details.
   glBufferSubData(GL_ARRAY_BUFFER, 0, m_leds.size() * sizeof(LedPosition), m_led_position_size_data);
   
   glBindBuffer(GL_ARRAY_BUFFER, m_leds_color_buffer);
   glBufferData(GL_ARRAY_BUFFER, m_leds.size() * sizeof(LedColor), NULL, GL_STREAM_DRAW); // Buffer orphaning, a common way to improve streaming perf. See above link for details.
   glBufferSubData(GL_ARRAY_BUFFER, 0, m_leds.size() * sizeof(LedColor), m_led_color_data);
   
   
   glEnable(GL_BLEND);
   glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
   
   // Use our shader
   glUseProgram(m_program_id);
   
   // Bind our texture in Texture Unit 0
   glActiveTexture(GL_TEXTURE0);
   glBindTexture(GL_TEXTURE_2D, m_texture);
   // Set our "myTextureSampler" sampler to use Texture Unit 0
   glUniform1i(m_texture_id, 0);
   
   glUniform3f(m_camera_right_worldspace_id, view_matrix[0][0], view_matrix[1][0], view_matrix[2][0]);
   glUniform3f(m_camera_up_worldspace_id   , view_matrix[0][1], view_matrix[1][1], view_matrix[2][1]);
   
   glUniformMatrix4fv(m_view_proj_matrix_id, 1, GL_FALSE, &ViewProjectionMatrix[0][0]);
   
   // 1rst attribute buffer : vertices
   glEnableVertexAttribArray(0);
   glBindBuffer(GL_ARRAY_BUFFER, m_vertex_buffer);
   glVertexAttribPointer(
      0,                  // attribute. No particular reason for 0, but must match the layout in the shader.
      3,                  // size
      GL_FLOAT,           // type
      GL_FALSE,           // normalized?
      0,                  // stride
      (void*)0            // array buffer offset
   );
   
   // 2nd attribute buffer : positions of leds' centers
   glEnableVertexAttribArray(1);
   glBindBuffer(GL_ARRAY_BUFFER, m_leds_position_buffer);
   glVertexAttribPointer(
      1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
      3,                                // size : x + y + z + size => 4
      GL_FLOAT,                         // type
      GL_FALSE,                         // normalized?
      0,                                // stride
      (void*)0                          // array buffer offset
   );
   
   // 3rd attribute buffer : leds' colors
   glEnableVertexAttribArray(2);
   glBindBuffer(GL_ARRAY_BUFFER, m_leds_color_buffer);
   glVertexAttribPointer(
      2,                                // attribute. No particular reason for 1, but must match the layout in the shader.
      3,                                // size : r + g + b => 3
      GL_FLOAT,                         // type
      GL_FALSE,                          // normalized?
      0,                                // stride
      (void*)0                          // array buffer offset
   );
   glBindVertexArray(m_vertex_array_id);

   // These functions are specific to glDrawArrays*Instanced*.
   // The first parameter is the attribute buffer we're talking about.
   // The second parameter is the "rate at which generic vertex attributes advance when rendering multiple instances"
   // http://www.opengl.org/sdk/docs/man/xhtml/glVertexAttribDivisor.xml
   glVertexAttribDivisor(0, 0); // leds vertices : always reuse the same 4 vertices -> 0
   glVertexAttribDivisor(1, 1); // positions : one per quad (its center)                 -> 1
   glVertexAttribDivisor(2, 1); // color : one per quad                                  -> 1
   
   // Draw the leds !
   // This draws many times a small triangle_strip (which looks like a quad).
   // This is equivalent to :
   // for(i in m_num_leds) : glDrawArrays(GL_TRIANGLE_STRIP, 0, 4), 
   // but faster.
   glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, 4, m_leds.size());

   glBindBuffer(GL_ARRAY_BUFFER, 0);

   glDisableVertexAttribArray(0);
   glDisableVertexAttribArray(1);
   glDisableVertexAttribArray(2);
}

void Gfx::Impl::drawLitTriangles()
{
   glUseProgram(m_triangle_program_id);

   for (unsigned k = 0; k < m_triangles->size(); k++)
   {
      // led color and position
      glUniform3fv(glGetUniformLocation(m_triangle_program_id, "led_color"), m_leds.size()*sizeof(LedPosition), &m_led_color_data[(*m_triangles)[k].vertices[0].start_led_ix].r);
      glUniform3fv(glGetUniformLocation(m_triangle_program_id, "led_pos"), m_leds.size()*sizeof(LedColor), &m_led_position_size_data[(*m_triangles)[k].vertices[0].start_led_ix].x);
      glUniform1i(glGetUniformLocation(m_triangle_program_id, "num_leds"), (*m_triangles)[k].vertices[0].num_leds);

      // view/projection transformations
      glUniformMatrix4fv(glGetUniformLocation(m_triangle_program_id, "projection"), 1, GL_FALSE, &m_window.getProjectionMatrix()[0][0]);
      glUniformMatrix4fv(glGetUniformLocation(m_triangle_program_id, "view"), 1, GL_FALSE, &m_window.getViewMatrix()[0][0]);

      // world transformation
      glm::mat4 model = glm::mat4(1.0f);
      glUniformMatrix4fv(glGetUniformLocation(m_triangle_program_id, "model"), 1, GL_FALSE, &model[0][0]);

      // render the triangle
      glBindVertexArray(m_triangle_vertex_array_id);
      glDrawArrays(GL_TRIANGLES, k*3, 3);
      glBindVertexArray(0);
   }
}

Gfx::Impl::~Impl()
{
   delete[] m_led_position_size_data;
   delete[] m_led_color_data;
   
   // Cleanup VBO and shader
   glDeleteBuffers(1, &m_leds_color_buffer);
   glDeleteBuffers(1, &m_leds_position_buffer);
   glDeleteBuffers(1, &m_vertex_buffer);
   glDeleteProgram(m_program_id);
   glDeleteTextures(1, &m_texture);
   glDeleteVertexArrays(1, &m_vertex_array_id);
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
