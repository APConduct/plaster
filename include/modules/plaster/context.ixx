module;

#include <cstdint>
#include <glm/glm.hpp>
#include <iostream>
#include <stack>
#include <string>
#include <vector>

export module plaster.context;
import plaster.renderer;
import plaster.input.manager;
import plaster.ui.engine;


export namespace plaster {

namespace layout {
struct Constraints {
    glm::vec2 available_size{};
    glm::vec2 position{};
    float padding{};
    bool absolute_positioning{};
    // bool absolute_size;
};
} // namespace layout

namespace context {
struct Style {
    uint32_t text_color{};
    uint32_t bg_color{};
    uint32_t border_color{};
    float border_width{};
    float corner_radius{};
};
} // namespace context

namespace ui {
// Singleton access
// TODO: Implement and deligate logic to 'AppContext' and 'WindowContext'
struct Context {
    static Context& current() {
        static thread_local Context instance{};
        return instance;
    }

    void frame_begin(Renderer* renderer, input::Manager* input, plaster::ui::Engine<>* engine) {
        this->renderer_ = renderer;
        this->input_ = input;
        this->engine_ = engine;

        while (!container_stack.empty()) {
            container_stack.pop();
        }
        while (!style_stack.empty()) {
            style_stack.pop();
        }
        while (!id_stack.empty()) {
            id_stack.pop();
        }

        this->cursor_pos = {0, 0};

        this->current_style = {.text_color = 0xFFFFFFFF,
                               .bg_color = 0x2C3E50FF,
                               .border_color = 0xCCCCCCFF,
                               .border_width = 1.0f,
                               .corner_radius = 0.0f};
    };
    void frame_end() {
        this->renderer_ = nullptr;
        this->input_ = nullptr;
        this->engine_ = nullptr;
    };

    void push_container(const std::string& id, glm::vec2 pos, glm::vec2 size) {
        this->container_stack.push(ContainerState(id, pos, size, pos, current_style));
        this->cursor_pos = pos;
    };
    void pop_container() {
        if (!container_stack.empty()) {
            container_stack.pop();
            if (!container_stack.empty()) {
                this->cursor_pos = container_stack.top().cursor;
            }
        }
    };

    struct ContainerScope {
        ContainerScope(/*Context& ctx, */ const std::string& id, glm::vec2 pos, glm::vec2 size) {
            ui::Context::current().push_container(id, pos, size);
        };
        ~ContainerScope() { ui::Context::current().pop_container(); };
    };
    void push_style(const context::Style& style) {
        this->style_stack.push(this->current_style);
        this->current_style = style;
    };
    void pop_style() {
        if (!style_stack.empty()) {
            this->current_style = this->style_stack.top();
            style_stack.pop();
        }
    };

    glm::vec2 get_cursor_pos() const { return cursor_pos; };
    void set_cursor_pos(glm::vec2 pos) { cursor_pos = pos; };
    void advance_cursor(float height) { cursor_pos.y += height; };

    glm::vec2 get_container_size() const {
        if (container_stack.empty()) {
            return {1920, 1080};
        }
        return container_stack.top().size;
    };
    layout::Constraints get_constraints() const {
        if (container_stack.empty()) {
            return layout::Constraints({1920, 1080}, {0, 0}, 0, false);
        }
        const auto& cont = container_stack.top();
        return layout::Constraints(cont.size, cont.position, 5.0f, false);
    };
    context::Style get_style() const { return this->current_style; };

    glm::vec4 allocate(glm::vec2 size, float padding = 0.0f) {
        glm::vec4 rect = {cursor_pos.x + padding, cursor_pos.y + padding, size.x, size.y};

        cursor_pos.y += size.y + padding;
        return rect;
    };

    void push_id(const std::string& id) { this->id_stack.push(id); };
    void pop_id() {
        if (!this->id_stack.empty()) {
            this->id_stack.pop();
        }
    };
    std::string get_current_id() {
        auto result = std::string();
        auto temp = this->id_stack;
        auto ids = std::vector<std::string>();

        while (!temp.empty()) {
            ids.push_back(temp.top());
            temp.pop();
        }

        for (auto i = ids.size() - 1; i >= 0; --i) {
            result += ids[i];
            if (i > 0) {
                result += "/";
            }
        }
        return result;
    };

    Renderer* get_renderer() const { return renderer_; }
    input::Manager* get_input_manager() const { return input_; }
    plaster::ui::Engine<>* get_engine() const { return engine_; }

    bool is_mouse_over(glm::vec4 rect) const {
        if (!this->input_) {
            return false;
        }

        auto mouse = this->input_->get_mouse_pos();
        return mouse.x >= rect.x && mouse.x <= rect.x + rect.z && mouse.y >= rect.y && mouse.y <= rect.y + rect.w;
    };
    bool is_mouse_clicked(glm::vec4 rect) const {
        return this->is_mouse_over(rect) && this->input_->is_mouse_pressed(0);
    };

    void print_stack() const {
        std::cout << "Context Stack:\n";
        auto temp = container_stack;
        auto depth = 0;
        while (!temp.empty()) {
            std::cout << std::string(depth * 2, ' ') << "- " << temp.top().id << "\n";
        }
    };

private:
    Context() = default;
    ~Context() = default;
    Context(const Context&) = delete;
    Context& operator=(const Context&) = delete;

    glm::vec2 cursor_pos{};
    context::Style current_style{};

    struct ContainerState {
        std::string id{};
        glm::vec2 position{};
        glm::vec2 size{};
        glm::vec2 cursor{};
        context::Style style{};
    };

    std::stack<ContainerState> container_stack{};
    std::stack<context::Style> style_stack{};
    std::stack<std::string> id_stack{};

    Renderer* renderer_{};
    input::Manager* input_{};
    plaster::ui::Engine<>* engine_{};
};
} // namespace ui

} // namespace plaster
