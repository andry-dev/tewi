#ifndef TEWI_WRITE_ONCE_H
#define TEWI_WRITE_ONCE_H

#include "Log.h"

namespace tewi
{
	/** \brief A const-like class that can write once to a value
	 *
	 * "WHY ON EARTH?"
	 *
	 * Because Java did it better with final:
	 *
	 * \code
	 *
	 * final int a;
	 *
	 * if ( conditions... )
	 * {
	 *     a = 1; // Valid
	 * }
	 * else
	 * {
	 *     a = 2; // Valid
	 * }
	 *
	 * a = 3; // ERROR
	 *
	 * \endcode
	 *
	 * Meanwhile in C++:
	 *
	 * \code
	 *
	 * const int a; // Error or warning, depends on compiler and -fpermissive
	 *
	 * if ( conditions... )
	 * {
	 *     a = 1; // ERROR
	 * }
	 *
	 * \endcode
	 *
	 * Honestly, that's just dumb.
	 *
	 * There are times where a value just needs to be changed once.
	 *
	 *
	 * Example use:
	 *
	 * \code
	 *
	 * WriteOnce<T> a;
	 *
	 * if ( conditions... )
	 * {
	 *     a = 3; // Legal
	 * }
	 *
	 * a = 4; // Runtime error
	 *
	 * \endcode
	 *
	 *
	 * **Caveats:**
	 * * There is a runtime assert, not a compile-time error.
	 *
	 */
	template <typename T>
	class WriteOnce
	{
	public:
		WriteOnce()
			: locked(false)
		{

		}

		WriteOnce(T val)
			: value(val), locked(true)
		{

		}

		operator T() { return value; }
		WriteOnce& operator=(const T& rhs)
		{
			Ensures(!locked, "You're trying to write to a writeonce value");
			value = rhs;

			return *this;
		}

	private:
		T value;
		bool locked;
	};
}

#endif /* TEWI_WRITE_ONCE_H */
