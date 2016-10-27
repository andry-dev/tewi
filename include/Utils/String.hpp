#ifndef STRING_LITERAL_H
#define STRING_LITERAL_H

#include <cstdint>

namespace tewi
{
	namespace Utils
	{
		class String
		{
		public:

			template<std::size_t N>
			constexpr String(char const (&str) [N])
			: m_str(str), m_size(N - 1)
			{

			}

			constexpr String() : m_str(), m_size(0) {  }

			constexpr auto getSize() const { return m_size; }

			constexpr operator const char*() const { return m_str; }
			constexpr auto getStr() const { return m_str; }
			constexpr char operator[](std::size_t index) { return m_str[index]; }

			constexpr bool operator>(String& oth)
			{
				if (m_size > oth.m_size)
					return true;

				return false;
			}

			template <std::size_t N>
			constexpr bool operator>(const char (&oth)[N])
			{
				if (m_size > N)
					return true;

				return false;
			}

			constexpr bool operator>(const char* oth)
			{
				if (m_size > strlen(oth))
					return true;

				return false;
			}

			constexpr bool operator<(String& oth)
			{
				if (m_size < oth.m_size)
					return true;

				return false;
			}

			template <std::size_t N>
			constexpr bool operator<(const char(&oth)[N])
			{
				if (m_size < N)
					return true;

				return false;
			}

			constexpr bool operator<(const char* oth)
			{
				if (m_size < strlen(oth))
					return true;

				return false;
			}

			constexpr bool operator<=(String& oth)
			{
				if (m_size <= oth.m_size)
					return true;

				return false;
			}

			constexpr bool operator<=(const char* oth)
			{
				if (m_size <= strlen(oth))
					return true;

				return false;
			}

			template <std::size_t N>
			constexpr bool operator<=(const char(&oth)[N])
			{
				if (m_size <= N)
					return true;

				return false;
			}

			constexpr bool operator>=(String& oth)
			{
				if (m_size >= oth.m_size)
					return true;

				return false;
			}

			template <std::size_t N>
			constexpr bool operator>=(const char(&oth)[N])
			{
				if (m_size >= N)
					return true;

				return false;
			}

			constexpr bool operator>=(const char* oth)
			{
				if (m_size >= strlen(oth))
					return true;

				return false;
			}

			template <std::size_t N>
			constexpr bool operator==(const char(&oth)[N])
			{
				if (N != m_size)
					return false;

				for (std::size_t i = 0; i < m_size; ++i)
				{
					if (m_str[i] != oth[i])
					{
						return false;
					}
				}

				return true;
			}

			constexpr bool operator==(String& oth)
			{
				if (oth.m_size != m_size)
					return false;

				for (std::size_t i = 0; i < m_size; ++i)
				{	
					if (m_str[i] != oth.m_str[i])
					{
						return false;
					}
				}

				return true;
			}

			constexpr bool operator==(const char* oth)
			{
				if (m_size != strlen(oth))
					return false;

				for (std::size_t i = 0; i < m_size; ++i)
				{
					if (m_str[i] != oth[i])
					{
						return false;
					}
				}

				return true;
			}

			constexpr String& operator=(String& oth)
			{
				m_str = oth.m_str;
				m_size = oth.m_size;
				return *this;
			}

			template<std::size_t N>
			constexpr String& operator=(char const (&oth)[N])
			{
				m_str = oth;
				m_size = N - 1;
				return *this;
			}

			constexpr String& operator=(char const* oth)
			{
				m_size = strlen(oth);
				m_str = oth;

				return *this;
			}
		private:

			constexpr inline std::size_t strlen(const char* str)
			{
				std::size_t size = 0;

				for (std::size_t i = 0; str[i] != '\0'; ++i)
				{
					++size;
				}

				return size;
			}

			const char* m_str;
			std::size_t m_size;
		};

	}
}


#endif /* STRING_LITERAL_H */
