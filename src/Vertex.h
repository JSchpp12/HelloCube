#pragma once 
#define GLFW_INCLUDE_VULKAN

#include "VertexColor.h"
#include "Vertex.h"

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <array>

//both vertex and vert attribute data is contained in one array of verticies == 'interleaving vertex' attributes
struct Vertex {
    glm::vec3 pos;

    /// <summary>
    /// Generates VkVertexInputBindingDescription from vertex object. This describes at which rate to load data from memory throughout the verticies. 
    /// Such as: number of bytes between data entries or if should move the next data entry after each vertex or after each instance
    /// </summary>
    /// <returns></returns>
    static VkVertexInputBindingDescription getBindingDescription() {
        VkVertexInputBindingDescription bindingDescription{};

        //all vertex data is in one array, so only using one binding 
        bindingDescription.binding = 0; //specifies index of the binding in the array of bindings

        //number of bytes from one entry to the next
        bindingDescription.stride = sizeof(Vertex);

        //can have one of the following: 
            //1. VK_VERTEX_INPUT_RATE_VERTEX: move to the next data entry after each vertex
            //2. VK_VERTEX_INPUT_RATE_INSTANCE: move to the next data entry after each instance
        //not using instanced rendering so per-vertex data
        bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

        return bindingDescription;
    }

    /// <summary>
    /// Generates attribute data for the verticies. VkVertexInputAttributeDescriptions describes to vulkan how to extract a vertex attribute froma chunk of 
    /// vertex data originating from a binding descritpion. For this program, there are 2: position and color. 
    /// </summary>
    /// <returns>Array containing attribute descriptions</returns>
    static std::array<VkVertexInputAttributeDescription, 1> getAttributeDescriptions() {
        std::array<VkVertexInputAttributeDescription, 1> attributeDescriptions{};

        /* Struct */
            //1. binding - which binding the per-vertex data comes in 
            //2. location - references the location directive of the input in the vertex shader 
            //3. format - describes type of data 
                // common shader and formats used 
                // float : VK_FORMAT_R32_SFLOAT 
                // vec2  : VK_FORMAT_R32G32_SFLOAT
                // vec3  : VK_FORMAT_R32G32B32_SFLOAT
                // vec4  : VK_FORMAT_R32G32B32A32_SFLOAT
                    //more odd examples
                        // ivec2 : VK_FORMAT_R32G32_SINT -- 2 component vector of 32-bit signed integers
                        // uvec4 : VK_FORMAT_R32G32B32A32_UINT -- 4 component vector of 32-bit unsigned integers 
                        // double: VK_FORMAT_R64_SFLOAT -- double precision 64-bit float 
            //4. offset - specifies the number of bytes since the start of the per-vertex data to read from
        attributeDescriptions[0].binding = 0;
        attributeDescriptions[0].location = 0;
        attributeDescriptions[0].format = VK_FORMAT_R32G32B32_SFLOAT;

        //the binding is loading over vertex at a time and the position attribute is at an offset of 0 bytes from the beginning of the struct.
        //offset macro calculates this distance for us
        attributeDescriptions[0].offset = offsetof(Vertex, pos);

        return attributeDescriptions;
    }
};