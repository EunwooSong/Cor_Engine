#pragma once

#pragma warning (disable : 4996)
#pragma warning (disable : 4244)
#pragma warning (disable : 4305)
#pragma warning (disable : 4309)

#include <algorithm>
#include <cstdarg>
#include <cstdio>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <list>
#include <queue>
#include <set>
#include <stdexcept>
#include <string>
#include <vector>
#include <chrono>
#include <mutex>
#include <map>
#include <random>

#include <d3dx9.h>
#include <d3d9.h>
#include <d3dx9math.h>
#include <Windows.h>

#include "ZeroMath.h"

//DELETE Macro
#define SAFE_DELETE(p)     \
    {                      \
        if (p) {           \
            delete (p);    \
            (p) = nullptr; \
        }                  \
    }

#define SAFE_DELETE_ARRAY(p) \
    {                        \
        if (p) {             \
            delete[](p);     \
            (p) = nullptr;   \
        }                    \
    }

#define SAFE_RELEASE(p)     \
    {                       \
        if (p) {            \
            (p)->Release(); \
            (p) = nullptr;  \
        }                   \
    }