#pragma once

#include <utility>

template <typename T, typename U>
T& assign(T* obj, U&& other) {
	if( obj != &other ) {
		obj->T::~T();
		new (static_cast<void*>(obj)) T(std::forward<U>(other));
	}
	return *obj;
}

template <typename T>
class assignable : public T {
public:
#if NO_INHERITABLE_CTORS
	template <typename... Args>
	assignable(Args... args) :
		T(std::forward<Args>(args)...) {
	}
#else
	using T::T;
	assignable(T const& other) :
		T(other) {
	}
	assignable(T&& other) :
		T(std::move(other)) {
	}
#endif

	template <typename U>
	assignable& operator=(U&& other) {
		return assign(this, std::forward<U>(other));
	}
};

