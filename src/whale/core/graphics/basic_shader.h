#pragma once

#ifdef PLATFORM_OPENGL
#include <glad/glad.h>
#endif

#include <concepts>
#include <string>

namespace whale
{
	class basic_shader
	{
	public:
		friend class shader_program;

		basic_shader(const std::string& source);
		basic_shader(const basic_shader&) = delete;
		basic_shader& operator=(const basic_shader&) = delete;
		basic_shader(basic_shader&&) = default;
		virtual ~basic_shader() noexcept;

		std::string source;

	protected:
#ifdef PLATFORM_OPENGL
		using native_handle = GLuint;
#endif
		native_handle handle;

		void check_status() const;
	};

	namespace detail
	{
		template <typename T>
		struct is_shader : std::false_type {};

		template<typename T>
		requires std::derived_from<std::remove_cvref_t<T>, basic_shader>
		struct is_shader<T> : std::true_type {};

		template <typename T>
		inline constexpr bool is_shader_v = is_shader<T>::value;
	}

	template <typename T>
	concept is_shader = detail::is_shader_v<T>;

	template <typename T>
	concept is_shader_ptr = requires(T&& t)
	{
		*t;
		requires std::derived_from<std::remove_cvref_t<decltype(*t)>, basic_shader>;
	};
}
