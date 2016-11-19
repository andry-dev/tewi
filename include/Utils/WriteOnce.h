#ifndef TEWI_WRITE_ONCE_H
#define TEWI_WRITE_ONCE_H

#include "Log.h"

namespace tewi
{
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
