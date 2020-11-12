#pragma once

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
#include <Windows.h>

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

using Vec2 = D3DXVECTOR2;