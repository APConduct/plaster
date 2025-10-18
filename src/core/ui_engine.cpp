#pragma once

#include <glm/fwd.hpp>
#include <string>
#include "plaster/input_manager.hpp"
#include "plaster/renderer.hpp"
#include "plaster/ui_engine.hpp"

namespace plaster {
ui::Engine::Engine(Renderer* renderer, input::Manager* input) : renderer(renderer), input(input) {}

void ui::Engine::update(float dt) {
    // update_input();
}

void ui::Engine::render() {
    renderer->begin_frame();

    for (auto& [id, elm] : elements) {
        renderer->push_rect_outline({elm.rect.x, elm.rect.y}, {elm.rect.z, elm.rect.w},
                                    elm.hovered ? 0xFFFFFFFF : 0xCCCCCCFF, 2.0f);
    };
    renderer->end_frame();
}

bool ui::Engine::button(const std::string& id, glm::vec2 pos, glm::vec2 size, const std::string& label) {
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
}

bool ui::Engine::checkbox(const std::string& id, glm::vec2 pos, bool* value, const std::string& label) {
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
}

void ui::Engine::panel(const std::string& id, glm::vec2 pos, glm::vec2 size, uint32_t color) {
    ui::Element& elem = elements[id];
    elem.type = "panel";
    elem.id = id;
    elem.rect = {pos.x, pos.y, size.x, size.y};
    elem.color = color;

    renderer->push_quad(pos, size, color);
}

void ui::Engine::text(glm::vec2 pos, const std::string& text, uint32_t color, float scale) {
    renderer->push_text({pos.x, pos.y}, text.c_str(), color, scale);
}

bool ui::Engine::is_point_in_rect(glm::vec2 point, glm::vec4 rect) {
    return point.x >= rect.x && point.x <= rect.x + rect.z && point.y >= rect.y && point.y <= rect.y + rect.w;
}

void ui::Engine::update_input() {
    state.mouse_pos = input->get_mouse_pos();
    state.mouse_pressed = input->is_mouse_pressed(0);
    state.mouse_released = input->is_mouse_released(0);
}

} // namespace plaster
