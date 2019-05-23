#pragma once

#define NOCOPY(x)\
	x(const x&) = delete;\
	x(x&) = delete;\
    void operator=(const x&) = delete;\
    void operator=(x&) = delete;