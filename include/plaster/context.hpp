#pragma once
#include <cstdint>
#include <glm/fwd.hpp>
#include <glm/glm.hpp>
#include <memory>
#include <stack>
#include <string>
#include <vector>
#include "plaster/input_manager.hpp"
#include "plaster/ui_engine.hpp"

namespace plaster {

struct Renderer;
namespace input {
struct Manager;
}
// namespace ui {
// struct Engine;
// }

namespace layout {
struct Constraints {
    glm::vec2 available_size;
    glm::vec2 position;
    float padding;
    bool absolute_positioning;
    // bool absolute_size;
};

namespace context {
struct Style {
    uint32_t text_color;
    uint32_t bg_color;
    uint32_t border_color;
    float border_width;
    float border_radius;
};
} // namespace context

namespace ui {
struct Context {
    static Context& current() {
        static thread_local Context instance;
        return instance;
    }

    void frame_begin(Renderer* renderer, input::Manager* input, plaster::ui::Engine* engine);
    void frame_end();

    void push_container(const std::string& id, glm::vec2 pos, glm::vec2 size);
    void pop_container();

    struct ContainerScope {
        ContainerScope(Context& ctx, const std::string& id, glm::vec2 pos, glm::vec2 size);
        ~ContainerScope();
    };
    void push_style(const context::Style& style);
    void pop_style();

    glm::vec2 get_cursor_pos() const { return cursor_pos; };
    void set_cursor_pos(glm::vec2 pos) { cursor_pos = pos; };
    void advance_cursor(float height) { cursor_pos.y += height; };

    glm::vec2 get_container_size() const;
    layout::Constraints get_constraints() const;
    context::Style get_style() const;

    glm::vec4 allocate(glm::vec2 size, float padding = 0.0f);

    void push_id(const std::string& id);
    void pop_id();
    std::string get_current_id();

    Renderer* get_renderer() const { return renderer; }
    input::Manager* get_input_manager() const { return input; }
    plaster::ui::Engine* get_engine() const { return engine; }

    bool is_mouse_over(glm::vec4 rect) const;
    bool is_mouse_clicked(glm::vec4 rect) const;

    void print_stack();

private:
    Context() = default;
    ~Context() = default;
    Context(const Context&) = delete;
    Context& operator=(const Context&) = delete;

    glm::vec2 cursor_pos;
    context::Style current_style;

    struct ContainerState {
        std::string id;
        glm::vec2 position;
        glm::vec2 size;
        glm::vec2 cursor;
        context::Style style;
    };

    std::stack<ContainerState> container_stack;
    std::stack<context::Style> style_stack;
    std::stack<std::string> id_stack;

    Renderer* renderer;
    input::Manager* input;
    plaster::ui::Engine* engine;
};
} // namespace ui

} // namespace layout


} // namespace plaster
