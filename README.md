# Bloom Filter

A from-scratch Bloom filter implementation in modern C++.

## Features

- Header-only
- Fully `constexpr`
- Templated on value type, bit array size, and number of hash functions
- Supports `insert`, `contains`, `clear`, and `count`

## Example

```cpp
#include "bloom_filter.hpp"
#include <iostream>

int main()
{
    bloom_filter<int, 10000, 3> filter{10, 20, 30, 42};

    std::cout << filter.contains(42) << '\n'; // 1
    std::cout << filter.contains(99) << '\n'; // 0 (probably)
}
```

## Template Parameters

- `ValueType` — must be an integral type
- `Bits` — size of the bit array (≥ 10)
- `K` — number of hash functions (≥ 1)

## Build

```bash
g++ -std=c++20 main.cpp -o bloom_filter
```

Or just include `bloom_filter.hpp` in your project.
