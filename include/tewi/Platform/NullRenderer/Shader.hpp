#include "tewi/Common.h"
#include "tewi/Video/API/API.h"
#include "tewi/Video/Shader.hpp"


namespace tewi
{
    template <>
    class TEWI_EXPORT ShaderProgram<API::NullRendererTag>
    {
    public:
        template <typename Container,
                 typename... Shaders,
                 std::enable_if_t<
                     !std::is_same<
                         std::decay_t<typename Container::value_type>,
                         const char*>::value,
                 bool> = false>
        ShaderProgram(const Container& attribs, Shaders&&... pack)
        { }

        template <typename Container,
                 typename... Shaders>
        ShaderProgram(const Container& attribs, Shaders&&... pack)
        { }

        ~ShaderProgram() = default;

        void enable() { }
        void disable() { }

        const asl::u32 getUniformLocation(const std::string& uniformName)
        {
            return 0;
        }

        template <typename Container,
                     std::enable_if_t<
                         !std::is_same<Container, gsl::string_span>::value
                     >
                 >
        std::vector<asl::u32> getUniformLocation(const Container& uniformName)
        {
            return { 0 };
        }

        template <const asl::sizei N, typename StringType>
        std::array<const asl::u32, N> getUniformLocation(const std::array<gsl::string_span, N>& uniformName)
        {
            return { 0 };
        }
    };

    template <template <typename> class ShaderTypePolicy,
             template <class> class ShaderFindPolicy>
    class TEWI_EXPORT Shader<API::NullRendererTag, ShaderTypePolicy, ShaderFindPolicy> final
        : private ShaderTypePolicy<API::NullRendererTag>
        , private ShaderFindPolicy<ShaderTypePolicy<API::NullRendererTag>>
    {
    public:
        using ShaderTypeImpl = ShaderTypePolicy<API::NullRendererTag>;
        using ShaderFindImpl = ShaderFindPolicy<ShaderTypePolicy<API::NullRendererTag>>;

        explicit Shader(const API::Device<API::NullRendererTag>& dev, const char* path)
        {
        }

        using api_num = API::NullRendererTag;

    private:
    };


} // namespace tewi
