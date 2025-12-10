module;

#include <bgfx/bgfx.h>
#include <cstdint>
#include <glm/glm.hpp>

export module plaster.renderer;

export namespace plaster {

const char* vs_color_quad = R"(
            #version 120
            void main() {
                gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
                gl_FrontColor = gl_Color;
            }
        )";

const char* fs_color_quad = R"(
            #version 120
            void main() {
                gl_FragColor = gl_Color;
            }
        )";

struct Vertex {
    glm::vec2 pos;
    uint32_t color;
    glm::vec2 uv;
};

namespace draw {
struct Command {
    uint32_t vertex_offset;
    uint32_t vertex_count;
    uint32_t index_offset;
    uint32_t index_count;
    bgfx::TextureHandle texture;
};
} // namespace draw

struct Renderer {
    explicit Renderer(uint16_t width, uint16_t height) {
        bgfx::Init init;
        init.type = bgfx::RendererType::Count;
        init.resolution.width = width;
        init.resolution.height = height;
        init.resolution.reset = BGFX_RESET_VSYNC;
        bgfx::init(init);

        bgfx::setDebug(BGFX_DEBUG_TEXT);
        bgfx::setViewClear(0, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, 0x303030ff, 1.0f, 0);
    };
    ~Renderer() { bgfx::shutdown(); };

    void begin_frame() {
        vertices.clear();
        indices.clear();
        commands.clear();
    };

    void end_frame() {
        flush_commands();
        bgfx::frame();
    };

    void push_quad(glm::vec2 pos, glm::vec2 size, uint32_t color) {
        uint32_t v_offset = vertices.size();

        vertices.push_back({{pos.x, pos.y}, color, {0, 0}});
        vertices.push_back({{pos.x + size.x, pos.y}, color, {1, 0}});
        vertices.push_back({{pos.x + size.x, pos.y + size.y}, color, {1, 1}});
        vertices.push_back({{pos.x, pos.y + size.y}, color, {0, 1}});

        indices.push_back(v_offset + 0);
        indices.push_back(v_offset + 1);
        indices.push_back(v_offset + 2);
        indices.push_back(v_offset + 0);
        indices.push_back(v_offset + 2);
        indices.push_back(v_offset + 3);
    };

    void push_rect_outline(glm::vec2 pos, glm::vec2 size, uint32_t color, float thickness) {
        float t = thickness / 2.0f;
        // Top
        push_quad(pos, {size.x, thickness}, color);
        // Bottom
        push_quad({pos.x, pos.y + size.y - thickness}, {size.x, thickness}, color);
        // Left
        push_quad(pos, {thickness, size.y}, color);
        // Right
        push_quad({pos.x + size.x - thickness, pos.y}, {thickness, size.y}, color);
    };

    void push_text(glm::vec2 pos, const char* text, uint32_t color, float scale) {
        // TODO: implement font atlasing for actual text rendering
        // For now, render a small quad where text would go
        push_quad(pos, {100.0f * scale, 20.0f * scale}, color);
    };

    void reset() {
        vertices.clear();
        indices.clear();
        commands.clear();
    };

    void resize(uint16_t width, uint16_t height) { bgfx::reset(width, height, BGFX_RESET_VSYNC); };

private:
    std::vector<Vertex> vertices{};
    std::vector<uint16_t> indices{};
    std::vector<draw::Command> commands{};

    bgfx::ProgramHandle shader_program{};
    bgfx::VertexBufferHandle vertex_buffer{};
    bgfx::IndexBufferHandle index_buffer{};

    void flush_commands() {
        if (vertices.empty() || indices.empty()) {
            return;
        }

        bgfx::TransientVertexBuffer tvb{};
        bgfx::TransientIndexBuffer tib{};

        // TODO: Implement vertex buffer allocation with proper vertex layout
        // bgfx::allocTransientVertexBuffer(&tvb, vertices.size(), vertex_layout);
        bgfx::allocTransientIndexBuffer(&tib, indices.size());

        std::memcpy(tvb.data, vertices.data(), vertices.size() * sizeof(Vertex));
        std::memcpy(tib.data, indices.data(), indices.size() * sizeof(uint16_t));

        bgfx::setViewRect(0, 0, 0, 1920, 1080);
        bgfx::setVertexBuffer(0, &tvb);
        bgfx::setIndexBuffer(&tib);
        bgfx::submit(0, shader_program);
    };
};

} // namespace plaster
