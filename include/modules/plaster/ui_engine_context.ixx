module;

#include <cstdint>
#include <glm/fwd.hpp>
#include <glm/glm.hpp>
#include <string>

export module plaster.ui.engine.context;
import plaster.ui.engine;
import plaster.renderer;
import plaster.input.manager;
import plaster.context;


export namespace plaster {
namespace ui {
struct EngineWithContext : public ui::Engine {
    EngineWithContext(plaster::Renderer* renderer, input::Manager* input) : ui::Engine(renderer, input) {};

    void update(float dt) override {
        ui::Context::current().frame_begin(this->renderer, this->input, this);
        ui::Engine::update(dt);
    };
    void render() override {
        ui::Engine::render();
        ui::Context::current().frame_end();
    };

    bool button(const std::string& label, glm::vec2 pos, glm::vec2 size = {100, 400}) {
        auto& ctx = ui::Context::current();

        auto id = ctx.get_current_id() + "/" + label;
        auto rect = ctx.allocate(size, 5.0f);

        auto style = ctx.get_style();

        this->renderer->push_rect_outline({rect.x, rect.y}, {rect.z, rect.w}, style.border_color, 2.0f);
        this->renderer->push_text({rect.x + 10, rect.y + 10}, label.c_str(), style.text_color, 1.0f);

        auto hovered = ctx.is_mouse_over(rect);
        auto clicked = ctx.is_mouse_clicked(rect);

        if (hovered) {
            this->renderer->push_rect_outline({rect.x, rect.y}, {rect.z, rect.w}, 0xFFFFFFFF, 2.0f);
        }

        return clicked;
    };
    bool checkbox(const std::string& label, glm::vec2 pos, bool* value) {
        auto& ctx = ui::Context::current();

        auto id = ctx.get_current_id() + "/" + label;
        auto rect = ctx.allocate({20, 20}, 5.0f);

        auto style = ctx.get_style();
        auto color = *value ? 0x44FF44FF : 0x444444FF;

        this->renderer->push_quad({rect.x, rect.y}, {rect.z, rect.w}, color);

        auto clicked = ctx.is_mouse_clicked(rect);
        if (clicked) {
            *value = !(*value);
        }
        return clicked;
    };
    void panel(const std::string& id, glm::vec2 size, uint32_t color) {
        auto& ctx = ui::Context::current();
        ctx.push_container(id, ctx.get_cursor_pos(), size);

        auto rect = ctx.allocate(size, 0);
        this->renderer->push_quad({rect.x, rect.y}, {rect.z, rect.w}, color);
    };
    void text(const std::string& text, float scale = 1.0f) {
        auto& ctx = ui::Context::current();

        auto style = ctx.get_style();
        auto rect = ctx.allocate({200, 20}, 5.0f);

        this->renderer->push_text({rect.x, rect.y}, text.c_str(), style.text_color, scale);
    };

    void begin_vertical_layout(const std::string& id, glm::vec2 size) {
        ui::Context::current().push_container(id, ui::Context::current().get_cursor_pos(), size);
    };
    void end_vertical_layout() { ui::Context::current().pop_container(); };

    void begin_horizontal_layout(const std::string& id, glm::vec2 size) {
        // TODO: Implement horizontal layout (cursor advances horizontally)
        ui::Context::current().push_container(id, ui::Context::current().get_cursor_pos(), size);
    };
    void end_horizontal_layout() { ui::Context::current().pop_container(); };
};
} // namespace ui
} // namespace plaster
