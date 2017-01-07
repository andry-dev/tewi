#pragma once

#include "Utils/Types.h"

#include <algorithm>

#include <string>

namespace tewi
{
	/** A map function.
	 *
	 * I probably need a range library.
	 *
	 */
	template <typename Container, typename Func>
	inline constexpr Container map(Container& c, Func&& f) noexcept
	{
		std::transform(c.begin(), c.end(), c.begin(), f);
		return c;
	}

	template <typename Container, typename Func>
	inline constexpr Container sort(Container& c, Func&& f)
	{
		std::sort(c.begin(), c.end(), c.begin(), f);
		return c;
	}

	template <typename Container, typename Func>
	inline constexpr Container copy(Container& src, Container& dest)
	{
		std::copy(src.begin(), src.end(), dest.begin());
		return dest;
	}

	template <typename Container, typename Func>
	inline constexpr Container copy_if(Container& src, Container& dest, Func&& f)
	{
		std::copy_if(src.begin(), src.end(), dest.begin(), f);
		return dest;
	}

	template <typename Container>
	inline constexpr Container take(Container& c, int num)
	{
		Container new_container(num);
		std::copy_n(c.begin(), num, new_container);
		return new_container;
	}
}
