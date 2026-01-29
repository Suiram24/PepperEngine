#pragma once

#include <cstdint>


namespace engine
{

    namespace core
    {

        namespace cexp
        {

            // Small implementation of std::array, needed until constexpr
            // is added to the function 'reference operator[](size_type)'
            template <typename T, size_t N>
            struct array {
                T m_data[N];

                using value_type = T;
                using reference = value_type&;
                using const_reference = const value_type&;
                using size_type = size_t;

                // This is NOT constexpr in std::array until C++17
                constexpr reference operator[](size_type i) noexcept {
                    return m_data[i];
                }

                constexpr const_reference operator[](size_type i) const noexcept {
                    return m_data[i];
                }

                constexpr size_type size() const noexcept {
                    return N;
                }
            };

        }

        constexpr auto gen_crc32_table() {
            constexpr auto num_bytes = 256;
            constexpr auto num_iterations = 8;
            constexpr auto polynomial = 0xEDB88320;

            auto crc32_table = cexp::array<uint32_t, num_bytes>{};

            for (auto byte = 0u; byte < num_bytes; ++byte) {
                auto crc = byte;

                for (auto i = 0; i < num_iterations; ++i) {
                    auto mask = -(crc & 1);
                    crc = (crc >> 1) ^ (polynomial & mask);
                }

                crc32_table[byte] = crc;
            }

            return crc32_table;
        }

        static constexpr auto crc32_table = gen_crc32_table();

        constexpr auto crc32(const char* in) {
            auto crc = 0xFFFFFFFFu;

            for (auto i = 0u; auto c = in[i]; ++i) {
                crc = crc32_table[(crc ^ c) & 0xFF] ^ (crc >> 8);
            }

            return ~crc;
        }
    }
    
}

