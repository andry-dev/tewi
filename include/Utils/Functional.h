#pragma once

#include "Utils/Types.h"

#include <algorithm>

#include <string>

#include <type_traits>

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
		std::transform(std::begin(c), std::end(c), std::begin(c), f);
		return c;
	}

	template <typename Container, typename Func>
	inline constexpr Container sort(Container& c, Func&& f)
	{
		std::sort(std::begin(c), std::end(c), std::begin(c), f);
		return c;
	}

	template <typename Container, typename Func>
	inline constexpr Container copy(Container& src, Container& dest)
	{
		std::copy(std::begin(src), std::end(src), std::begin(dest));
		return dest;
	}

	template <typename Container, typename Func>
	inline constexpr Container copy_if(Container& src, Container& dest, Func&& f)
	{
		std::copy_if(std::begin(src), std::begin(src), std::begin(dest), f);
		return dest;
	}

	template <typename Container>
	inline constexpr Container take(Container& c, int num)
	{
		Container new_container(num);
		std::copy_n(std::begin(c), num, new_container);
		return new_container;
	}


	template <sizei Index = 0, typename Func, typename... Ts>
	inline constexpr std::enable_if_t<Index == sizeof...(Ts), void>
	for_each_tuple(std::tuple<Ts...>, Func)
	{
		
	}
	
	template <sizei Index = 0, typename Func, typename... Ts>
	inline constexpr std::enable_if_t<Index < sizeof...(Ts), void>
	for_each_tuple(std::tuple<Ts...> t, Func f)
	{
		f(std::get<Index>(t));
		for_each_tuple<Index + 1, Func, Ts...>(t, f);
	}

}
