module;
#include <cstdint>
#include <lauxlib.h>
#include <lua.h>
#include <lualib.h>
#include "glm/glm.hpp"

export module lua;



export namespace plaster::lua {
     const char* PLASTER_METATABLE = "plaster_instance";

    template<typename T>
     struct API{
         protected:
         lua_State* L;
         T* engine;
         public:
         explicit API(lua_State* L, T* engine):L(L), engine(engine)
         {
             lua_pushlightuserdata(L, this);
             lua_setfield(L, LUA_REGISTRYINDEX, PLASTER_METATABLE);
             register_functions();
         }

         void register_functions(){
             lua_newtable(L);

             lua_pushcfunction(L, button);
             lua_setfield(L, -2, "button");

             lua_pushcfunction(L, panel);
             lua_setfield(L, -2, "panel");

             lua_pushcfunction(L, text);
             lua_setfield(L, -2, "text");

             lua_pushcfunction(L, get_mouse_pos);
             lua_setfield(L, -2, "get_mouse_pos");

             lua_setglobal(L, "ui");
         }

         static int button(lua_State* L)
         {
             API* api = get_instance(L);

             const char* id = luaL_checkstring(L, 1);
             float x = static_cast<float>(luaL_checknumber(L, 2));
             float y = static_cast<float>(luaL_checknumber(L, 3));
             float w = static_cast<float>(luaL_checknumber(L, 4));
             float h = static_cast<float>(luaL_checknumber(L, 5));
             const char* label = luaL_optstring(L, 6, "Button");

             glm::vec2 pos(x,y);
             glm::vec2 size(w,h);

             bool clicked = api->engine->button(id,pos,size,label);
             lua_pushboolean(L, clicked);
             return 1;

         }
         static int panel(lua_State* L)
         {
             API* api = get_instance(L);

             const char* id = luaL_checkstring(L, 1);
             float x = static_cast<float>(luaL_checknumber(L, 2));
             float y = static_cast<float>(luaL_checknumber(L, 3));
             float w = static_cast<float>(luaL_checknumber(L, 4));
             float h = static_cast<float>(luaL_checknumber(L, 5));

             uint32_t color = 0xFFFFFFFF;
             if(lua_isnumber(L, 6)) {
                 color =  static_cast<uint32_t>(lua_tonumber(L, 6));
             }

             glm::vec2 pos(x,y);
             glm::vec2 size(w,h);

             api->engine->panel(id,pos,size,color);
             return 0;
         }
         static int text(lua_State* L)
         {
             API* api = get_instance(L);

             const char* str = luaL_checkstring(L, 1);
             float x = static_cast<float>(luaL_checknumber(L, 2));
             float y = static_cast<float>(luaL_checknumber(L, 3));
             uint32_t color = static_cast<uint32_t>(luaL_optnumber(L,4, 0xFFFFFFFF));
             float scale = static_cast<float>(luaL_optnumber(L, 5, 1.0f));

             glm::vec2 pos(x,y);
             api->engine->text(pos,str, color, scale);
             return 0;
         }

         static int get_mouse_pos(lua_State* L) {
             API* api = get_instance(L);
             glm::vec2 pos = api->engine->get_state().mouse_pos;
             lua_pushnumber(L, pos.x);
             lua_pushnumber(L, pos.y);
             return 2;
         };

         static API* get_instance(lua_State* L){
             lua_getfield(L, LUA_REGISTRYINDEX, PLASTER_METATABLE);
             API* instance = static_cast<API*>(lua_touserdata(L, -1));
             lua_pop(L, 1);
             return instance;
         };


    };
}
