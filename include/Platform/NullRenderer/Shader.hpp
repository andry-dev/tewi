#include "Common.h"
#include "Video/API/API.h"
#include "Video/Shader.hpp"


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

        asl::u32 getUniformLocation(const std::string& uniformName)
        {
            return 0;
        }

        template <typename Container,
                 std::enable_if_t<
                     !std::is_same<
                        typename Container::value_type, const char*>::value,
                 bool> = false>
        std::vector<asl::mut_u32> getUniformLocation(const Container& uniformName)
        {
            return { 0 };
        }

        template <asl::sizei N>
        std::array<asl::u32, N> getUniformLocation(const std::array<const char*, N>& uniformName)
        {
            return { 0 };
        }

        template <asl::sizei N, typename StringType>
        std::array<asl::u32, N> getUniformLocation(const std::array<StringType, N>& uniformName)
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

        explicit Shader(API::Device<API::NullRendererTag>& dev, const char* path)
        {
        }

        using api_num = API::NullRendererTag;

    private:
    };


} // namespace tewi
