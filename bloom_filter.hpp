#pragma once

#include <initializer_list>
#include <array>
#include <utility>
#include <concepts>
#include <cstdint>
#include <cstddef>

template <std::integral ValueType, std::size_t Bits, std::size_t K>
		requires ((Bits >= 10) && (K >= 1))
class bloom_filter
{
public:
	
	constexpr bloom_filter() noexcept = default;

	constexpr bloom_filter(std::initializer_list<ValueType> values) noexcept
	{
		for (const ValueType value : values)
			insert(value);
	}

	constexpr void insert(ValueType value)
	{
		[this, value] <std::size_t... Is>([[maybe_unused]] std::index_sequence<Is...>) {
			(SetBit(Hash(value, Is) % Bits), ...);
		}(std::make_index_sequence<K>{});
	}

	constexpr bool contains(ValueType value) const noexcept
	{
		return [this, value] <std::size_t... Is>([[maybe_unused]] std::index_sequence<Is...>) {
			return (GetBit(Hash(value, Is) % Bits) && ...);
		}(std::make_index_sequence<K>{});
	}

	constexpr void clear() noexcept
	{
		for (std::uint8_t& byteRef : m_bytes)
			byteRef = 0;
	}

	constexpr std::size_t count() const noexcept
	{
		std::size_t c = 0;

		for (const std::uint8_t byte : m_bytes)
			for (std::uint8_t value = 128; value > 0; value /= 2)
				if ((byte & value) != 0)
					++c;

		return c;
	}

	static constexpr std::size_t bits() noexcept
	{
		return Bits;
	}

private:
	
	static constexpr std::size_t s_byteCount = (Bits % 8 == 0) ? (Bits / 8) : (Bits / 8 + 1);

	static constexpr std::size_t Hash(ValueType value, std::size_t index) noexcept
	{
		return static_cast<std::size_t>(value * 69420 * index + 67);
	}

	constexpr void SetBit(std::size_t index)
	{
		std::uint8_t& byteRef = m_bytes[index / 8];
		byteRef |= std::uint8_t(1) << (7 - index % 8);
	}

	constexpr bool GetBit(std::size_t index) const
	{
		return (m_bytes[index / 8] & (std::uint8_t(1) << (7 - index % 8))) != 0;
	}

	std::array<std::uint8_t, s_byteCount> m_bytes;
};
