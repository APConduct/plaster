module;
#include <cstdint>
#include <expected>
#include <stdexcept>
#include <string>
#include <optional>

export module plater.ui;

import plaster.input;
import plaster.renderer;


export namespace plaster::ui{
struct Element {
    std::string type;
    std::string id;
    glm::vec4 rect;
    uint32_t color;
    bool hovered;
    std::optional<bool> focused;
    std::optional<bool> selected;
    std::optional<bool> disabled;

    std::map<std::string, std::string> props;

    template<typename T>
    std::expected<T, std::string> get_prop(const std::string& key) const {
        auto it = props.find(key);
        if (it==props.end()){
            return std::unexpected<std::string>("Property not found"));
        }
        try{
            return std::stoi(it->second);
        } catch (const std::invalid_argument&) {
            return std::unexpected<std::string>("Invalid value of type: " + std::string(typeid(T).name() + ": " + it-> second + " is not a property of Element: " + std::string(id));
        }
    }

    glm::vec2 get_mouse_pos() const;

    template<typename T, typename FT>
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

struct Engine {
public:
    explicit Engine(Renderer* renderer, input::Manager* input);

    void update(float dt);
    void render();

    bool button(const std::string& id, glm::vec2 pos, glm::vec2 size, std::string& label);

    bool checkbox(const std::string& id, glm::vec2 pos, bool* value, const std::string& label);
    void panel(const std::string& id, glm::vec2 pos,  glm::vec2 size, uint32_t color);
    void text(glm::vec2 pos, const std::string& text, uint32_t color. float scale = 1.0f);

    State get_state() const { return state; };

    protected:
    Renderer* renderer;
    input::Manager* input;
    State state;
    std::map<std::string, Element> elements;

    bool is_point_in_rect(glm::vec2 point, glm::vec4 rect);
    void update_input();

};
}
