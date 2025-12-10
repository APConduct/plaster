module;

#include <expected>
#include <glm/glm.hpp>
#include <map>
#include <string>

export module plaster.ui.engine;
import plaster.input.manager;
import plaster.renderer;


export namespace plaster {
namespace ui {
struct Element {
    std::string type;
    std::string id;
    glm::vec4 rect;
    uint32_t color;
    bool hovered;
    bool clicked;
    // bool focused;
    // bool selected;
    // bool disabled;

    std::map<std::string, std::string> props;

    template <typename T>
    std::expected<T, std::string> get_prop(const std::string& key) const {
        auto it = props.find(key);
        if (it == props.end()) {
            return std::unexpected<std::string>("Property not found");
        }
        try {
            return std::stoi(it->second);
        }
        catch (const std::invalid_argument&) {
            return std::unexpected<std::string>("Invalid value of type: " + std::string(typeid(T).name()) + ": " +
                                                it->second + " is not a property of Element: " + std::string(id));
        }
    }

    glm::vec2 get_mouse_pos() const;

    template <typename T, typename FT>
    T on_(FT&& func) {
        return func();
    }
};

struct State {
    glm::vec2 mouse_pos;
    bool mouse_pressed;
    bool mouse_released;
    std::string focused_element;
};

template <typename State = plaster::ui::State, typename Manager = input::Manager, typename Renderer = plaster::Renderer>
struct Engine {
    Engine(Renderer* renderer, Manager* input);

    virtual void update(float dt) { update_input(); };
    virtual void render() {
        renderer->begin_frame();

        for (auto& [id, elm] : elements) {
            renderer->push_rect_outline({elm.rect.x, elm.rect.y}, {elm.rect.z, elm.rect.w},
                                        elm.hovered ? 0xFFFFFFFF : 0xCCCCCCFF, 2.0f);
        };
        renderer->end_frame();
    };

    bool button(const std::string& id, glm::vec2 pos, glm::vec2 size, const std::string& label) {
        ui::Element& elem = elements[id];
        elem.type = "button";
        elem.id = id;
        elem.rect = {pos.x, pos.y, size.x, size.y};
        elem.color = 0x4488FFFF;

        elem.hovered = is_point_in_rect(state.mouse_pos, elem.rect);

        if (elem.hovered && state.mouse_pressed) {
            elem.clicked = true;
            return true;
        }

        elem.clicked = false;
        return false;
    };

    bool checkbox(const std::string& id, glm::vec2 pos, bool* value, const std::string& label) {
        ui::Element& elem = elements[id];
        elem.type = "checkbox";
        elem.id = id;
        elem.rect = {pos.x, pos.y, 20, 20};
        elem.color = *value ? 0x44FF44FF : 0x444444FF;

        elem.hovered = is_point_in_rect(state.mouse_pos, elem.rect);

        if (elem.hovered && state.mouse_pressed) {
            *value = !*value;
            elem.clicked = true;
            return true;
        }

        elem.clicked = false;
        return false;
    };
    void panel(const std::string& id, glm::vec2 pos, glm::vec2 size, uint32_t color) {
        ui::Element& elem = elements[id];
        elem.type = "panel";
        elem.id = id;
        elem.rect = {pos.x, pos.y, size.x, size.y};
        elem.color = color;

        this->renderer->push_quad(pos, size, color);
    };
    void text(glm::vec2 pos, const std::string& text, uint32_t color, float scale = 1.0f) {
        this->renderer->push_text({pos.x, pos.y}, text.c_str(), color, scale);
    };

    State get_state() const { return state; }

protected:
    Renderer* renderer{};
    input::Manager* input{};
    State state{};
    std::map<std::string, Element> elements{};

    bool is_point_in_rect(glm::vec2 point, glm::vec4 rect) {
        return point.x >= rect.x && point.x <= rect.x + rect.z && point.y >= rect.y && point.y <= rect.y + rect.w;
    };
    void update_input() {
        state.mouse_pos = input->get_mouse_pos();
        state.mouse_pressed = input->is_mouse_pressed(0);
        state.mouse_released = input->is_mouse_released(0);
    };
};
} // namespace ui
} // namespace plaster
