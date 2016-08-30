#ifndef STRING_LITERAL_H
#define STRING_LITERAL_H

#include <cstdint>

namespace tewi
{
	namespace Utils
	{
		class StringLiteral
		{
		public:
			template<std::size_t N>
			constexpr StringLiteral(char const (&str) [N])
				: m_str(str), m_size(N - 1)
			{

			}

			constexpr auto getSize() { return m_size; }

			constexpr operator const char*() { return m_str; }
			constexpr char operator[](std::size_t index) { return m_str[index]; }

			constexpr bool operator==(StringLiteral& other)
			{
				if (other.getSize() > m_size)
					return false;

				for (std::size_t i = 0; i < m_size; ++i)
					if (m_str[i] != other.m_str[i])
						return false;

				return true;
			}

			
		private:
			
			char const* m_str;
			std::size_t m_size;
		};

	}
}


#endif /* STRING_LITERAL_H */
