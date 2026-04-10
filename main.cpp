#include <iostream>
#include <format>
#include <array>
#include <ranges>
#include <algorithm>
#include <random>
#include "bloom_filter.hpp"

int main()
{
	bloom_filter<int, 10000, 3> bFilter;

	std::random_device rd;
	std::uniform_int_distribution<int> dist(0, 100);

	std::array<int, 10> addedValues;
	for (int i = 0; i < 10; ++i)
	{
		addedValues[i] = dist(rd);
		bFilter.insert(addedValues[i]);
	}

	for (int value = 0; value <= 100; ++value)
		std::cout << std::format("{} is in bloom filter? {} ({})\n", value, bFilter.contains(value),
														std::ranges::contains(addedValues, value));
}
