#ifndef PEENGINE_CPEGRAPHICAL_VERTEX_H
#define PEENGINE_CPEGRAPHICAL_VERTEX_H

#define GLM_ENABLE_EXPERIMENTAL

#include <glm/glm.hpp>
#include <glm/gtx/hash.hpp>
#include <vulkan/vulkan.h>
#include <array>

namespace vk {
    struct Vertex {
        glm::vec3 pos;
        glm::vec3 color;
        glm::vec2 texCoord;

        static VkVertexInputBindingDescription getBindingDescription();

        static std::array<VkVertexInputAttributeDescription, 3> getAttributeDescriptions();

        bool operator==(const Vertex& other) const;
    };
}


namespace std {
    template<> struct hash<vk::Vertex> {
        size_t operator()(vk::Vertex const& vertex) const {
            return ((hash<glm::vec3>()(vertex.pos) ^ (hash<glm::vec3>()(vertex.color) << 1)) >> 1) ^ (hash<glm::vec2>()(vertex.texCoord) << 1);
        }
    };
}

#endif