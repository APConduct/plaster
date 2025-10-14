#pragma once

#include <string>
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
}
} // namespace plaster
