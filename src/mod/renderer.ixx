//
// Created by Aidan Jost on 3/20/25.
//

module;

#include <string>
#include <array>
#include <unordered_map>
#include <glm/glm.hpp>
#include <vector>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#define GLAD_GL_IMPLEMENTATION
#include <glad/gl.h>



export namespace plaster::renderer
{
    class FrameBuffer;
}

export module plaster.renderer;

import plaster.core;

export namespace plaster::renderer
{
    enum class RendererAPI
    {
        None = 0,
        OpenGL = 1
    };

    template<typename T>
    struct Vertex
    {
        Point<T> position;
        Point<T> tex_coords;
        Color color{};

        Vertex() = default;
        Vertex(const Point<T>& position, const Point<T>& tex_coords, const Color& color) : position(position), tex_coords(tex_coords), color(color) {}
    };

    class Shader
    {
    protected:
        uint32_t renderer_id_ = 0;
        std::string name_;

        std::unordered_map<std::string, int> uniforms_location_cache_;

    public:

        Shader(const std::string& vertex_src, const std::string& fragment_src);
        explicit Shader(const std::string& filepath);
        ~Shader();

        void bind() const;
        void unbind() const;

        void set_int(const std::string& name, int value);
        void set_int_array(const std::string& name, int* values, uint32_t count);
        void set_float(const std::string& name, float value);
        void set_float2(const std::string& name, const glm::vec2& value);
        void set_float3(const std::string& name, const glm::vec3& value);
        void set_float4(const std::string& name, const glm::vec4& value);
        void set_mat4(const std::string& name, const glm::mat4& value);

        [[nodiscard]] const std::string& get_name() const{ return name_; }

    protected:
        std::string read_file(const std::string& filepath);
        std::unordered_map<uint32_t, std::string> pre_process(const std::string& source);
        void compile(const std::unordered_map<uint32_t, std::string>& shader_sources);
        int get_uniform_location(const std::string& name);
    };

    class Texture
    {
    public:
        virtual ~Texture() = default;
        [[nodiscard]] virtual uint32_t get_width() const = 0;
        [[nodiscard]] virtual uint32_t get_height() const = 0;
        [[nodiscard]] virtual uint32_t get_renderer_id() const = 0;

        virtual void set_data(void* data, uint32_t size) = 0;

        virtual void bind(uint32_t slot) const = 0;
        void bind() const { bind(0); }

        [[nodiscard]] virtual bool operator==(const Texture& other) const = 0;
    };

    struct Texture2D : Texture
    {
    protected:
        u_int32_t width_, height_, renderer_id_;
        std::string path_;
    public:
        Texture2D(uint32_t width, uint32_t height);
        explicit Texture2D(const std::string& path);
        ~Texture2D() override;

        [[nodiscard]] uint32_t get_width() const override { return width_; }
        [[nodiscard]] uint32_t get_height() const override { return height_; }
        [[nodiscard]] uint32_t get_renderer_id() const override { return renderer_id_; }

        void set_data(void* data, uint32_t size) override;
        void bind(uint32_t slot) const override;

        [[nodiscard]] bool operator==(const Texture& other) const override
        {
            return renderer_id_ == other.get_renderer_id();
        };
    };

    class IndexBuffer
    {
    protected:
        uint32_t renderer_id_ = 0;
        uint32_t count_ = 0;

    public:
        IndexBuffer(uint32_t* indices, uint32_t count);
        ~IndexBuffer();

        void bind() const;
        void unbind() const;

        [[nodiscard]] uint32_t get_count() const { return count_; }
    };

    // Buffer Abstraction
    class VertexBuffer
    {
    protected:
        uint32_t renderer_id_ = 0;

    public:
        explicit VertexBuffer(uint32_t size);
        VertexBuffer(float* vertices, uint32_t size);
        ~VertexBuffer();

        void bind() const;
        void unbind() const;

        void set_data(const void* data, uint32_t size);
    };


    class VertexArray
    {

    protected:
        uint32_t renderer_id_ = 0;
        uint32_t vertex_buffer_id_ = 0;
        std::vector<Ref<VertexBuffer>> vertex_buffers_;
        Ref<IndexBuffer> index_buffer_;

    public:
        VertexArray()
        {
            glGen(1, &renderer_id_); // doesnt want to work

        }

    };



    class Renderer
    {
    protected:
        static RendererAPI api_;

    public:
        static void init();
        static void shutdown();

        static void begin_scene();
        static void end_scene();

        static void submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertex_array, const glm::mat4& transform = glm::mat4(1.0f));


        static void draw_rect(const Rect<float>& rect, const Color& color);

        static void draw_rect_outline(const Rect<float>& rect, const Color& color, float thickness = 1.0f);

        static void draw_circle(const Point<float>& center, float radius, const Color& color, uint32_t segments = 32);

        static void draw_line(const Point<float>& p1, const Point<float>& p2, const Color& color, float thickness = 1.0f);

        static void draw_triangle(const Point<float>& p1, const Point<float>& p2, const Point<float>& p3, const Color& color);

        static void draw_texture(const Ref<Texture>& texture, const Rect<float>& rect, const Color& tint = Color::rgb(255, 255, 255));

        static void set_viewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height);

        static void set_clear_color(const Color& color);

        static RendererAPI get_api() { return api_; }
    };




    class BatchRenderer
    {
    protected:
        struct RenderData
        {
            static constexpr uint32_t MAX_QUADS = 10000;
            static constexpr uint32_t MAX_VERTICES = MAX_QUADS * 4;
            static constexpr uint32_t MAX_TEXTURE_SLOTS = 32;

            std::shared_ptr<VertexArray> quad_vertex_array_;
            std::shared_ptr<VertexBuffer> quad_vertex_buffer_;
            std::shared_ptr<Shader> texture_shader_;

            uint32_t quad_index_count_ = 0;

            Vertex<float> *quad_vertex_buffer_base_ = nullptr;
            Vertex<float> *quad_vertex_buffer_ptr_ = nullptr;

            std::array<std::shared_ptr<Texture2D>, MAX_TEXTURE_SLOTS> texture_slots_;
            uint32_t texture_slot_index_ = 1; // 0 = white texture

            glm::vec4 quad_vertex_positions_[4];

            std::shared_ptr<Texture2D> white_texture_;
        };

        static RenderData data_;

    public:

        static void init();
        static void shutdown();

        static void begin_batch();
        static void end_batch();
        static void flush();

        static void draw_quad(const Point<float>& position, const Size<float>& size, const Color& color);
        static void draw_quade(const Point<float>& position, const Size<float>& size, const Ref<Texture2D>& texture, const Color& tint = Color::rgb(255, 255, 255));

    protected:
        static void next_batch();
    };





}


