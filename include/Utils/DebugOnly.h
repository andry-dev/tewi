/* -*- Mode: C++; tab-width: 8; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/* vim: set ts=8 sts=2 et sw=2 tw=80: */
/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

/*
 * Provides DebugOnly, a type for variables used only in debug builds (i.e. by
 * assertions).
 */

#ifndef DEBUG_ONLY_H
#define DEBUG_ONLY_H

namespace tewi {

	template<typename T>
	class DebugOnly
	{
	public:
#ifndef NDEBUG
	  T value;

	  DebugOnly() { }
	  DebugOnly(const T& aOther) : value(aOther) { }
	  DebugOnly(const DebugOnly& aOther) : value(aOther.value) { }
	  DebugOnly& operator=(const T& aRhs) {
		value = aRhs;
		return *this;
	  }

	  void operator++(int) { value++; }
	  void operator--(int) { value--; }

	  // Do not define operator+=(), etc. here.  These will coerce via the
	  // implicit cast and built-in operators.  Defining explicit methods here
	  // will create ambiguity the compiler can't deal with.

	  T* operator&() { return &value; }

	  operator T&() { return value; }
	  operator const T&() const { return value; }

	  T& operator->() { return value; }
	  const T& operator->() const { return value; }

#else
	  DebugOnly() { }
	  DebugOnly(const T&) { }
	  DebugOnly(const DebugOnly&) { }
	  DebugOnly& operator=(const T&) { return *this; }
	  void operator++(int) { }
	  void operator--(int) { }
	  DebugOnly& operator+=(const T&) { return *this; }
	  DebugOnly& operator-=(const T&) { return *this; }
	  DebugOnly& operator&=(const T&) { return *this; }
	  DebugOnly& operator|=(const T&) { return *this; }
	  DebugOnly& operator^=(const T&) { return *this; }
#endif

	  /*
	   * DebugOnly must always have a destructor or else it will
	   * generate "unused variable" warnings, exactly what it's intended
	   * to avoid!
	   */
	  ~DebugOnly() {}
	};

}

#endif /* DEBUG_ONLY_H */
