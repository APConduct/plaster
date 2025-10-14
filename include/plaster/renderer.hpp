#pragma once

#include <bgfx/bgfx.h>
#include <cstdint>
#include <glm/glm.hpp>
#include <vector>

namespace plaster {
struct Vertex {
    glm::vec2 pos;
    uint32_t color;
    glm::vec2 uv;
};

struct DrawCommand {
    uint32_t vertex_offset;
    uint32_t vertex_count;
    uint32_t index_offset;
    uint32_t index_count;
    bgfx::TextureHandle texture;
};

struct Renderer {
public:
    Renderer(uint16_t width, uint16_t height);
    ~Renderer();

    void begin_frame();
    void end_frame();

    void push_quad(glm::vec2 pos, glm::vec2 size, uint32_t color);
    void push_rect_outline(glm::vec2 pos, glm::vec2 size, uint32_t color, float thickness);
    void push_text(glm::vec2 pos, const char* text, uint32_t color, float scale);

    void reset();
    void resize(uint16_t width, uint16_t height);

private:
    std::vector<Vertex> vertices;
    std::vector<uint16_t> indices;
    std::vector<DrawCommand> commands;

    bgfx::ProgramHandle shader_program;
    bgfx::VertexBufferHandle vertex_buffer;
    bgfx::IndexBufferHandle index_buffer;

    void flush_commands();
};

} // namespace plaster
