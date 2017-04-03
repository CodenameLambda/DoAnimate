#include "nodes/node.hh"
#include "nodes/node_system.hh"
#include <vector>
#include <tuple>


namespace doanimate {
    class Manager {
        std::vector<size_t> inputs;
        std::vector<size_t> outputs;

        public:
        nodes::NodeSystem* system;

        float frames_per_second;
        size_t width;
        size_t height;
        size_t audio_chunk_length;
        float audio_chunks_per_second;
        size_t frames;

        Manager(nodes::NodeSystem*);
    };


    struct Image {
        std::vector<std::tuple<unsigned char, unsigned char, unsigned char>> data;
        size_t width;
        size_t height;
    };


    using AudioChunk = std::vector<float>;


    void add_time_input(Manager&);
    
    void audio_time_input(Manager&);

    void add_info_input(Manager&);

    void image_output(Manager&);

    void audio_output(Manager&);

    Image render_image(Manager&);

    std::vector<Image> render_animation(Manager&);

    AudioChunk render_audio_chunk(Manager&);

    std::vector<AudioChunk> render_audio(Manager&);

    std::pair<std::vector<Image>, std::vector<AudioChunk>> render_video(Manager&);
}
