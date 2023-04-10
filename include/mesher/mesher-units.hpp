#ifndef MESHER_UNITS_HPP__
#define MESHER_UNITS_HPP__

#include <algorithm>
#include <compare>
#include <cstdint>
#include <limits>
#include <ostream>

namespace mesher {
    class millimeter {
        static constexpr uint32_t MAXIMUM = std::numeric_limits<uint16_t>::max();

        public:
            explicit millimeter() : value_(0) {}
            explicit millimeter(uint16_t value) : value_(value) {}

            friend std::ostream&
            operator<<(std::ostream& os, const millimeter& xs) {
                os << xs.value_ << " mm";
                return os;
            }

            auto operator<=>(const millimeter&) const = default;

            explicit operator float() const     { return static_cast<float>(value_); }
            explicit operator double() const    { return static_cast<double>(value_); }

            explicit operator uint16_t() const  { return static_cast<uint16_t>(value_); }
            explicit operator uint32_t() const  { return static_cast<uint32_t>(value_); }
            explicit operator int32_t() const   { return static_cast<int32_t>(value_); }

            friend millimeter
            operator+(const millimeter& lhs, const millimeter& rhs) {
                uint32_t lh = static_cast<uint32_t>(lhs);
                uint32_t rh = static_cast<uint32_t>(rhs);
                uint32_t v  = std::clamp<uint32_t>(lh + rh, uint32_t(0), MAXIMUM);

                return millimeter(static_cast<uint16_t>(v));
            }

            friend millimeter
            operator-(const millimeter& lhs, const millimeter& rhs) {
                int32_t lh = static_cast<int32_t>(lhs);
                int32_t rh = static_cast<int32_t>(rhs);
                int32_t v  = std::clamp<int32_t>(lh - rh, 0, MAXIMUM);

                return millimeter(static_cast<uint16_t>(v));
            }

            friend millimeter
            operator*(const millimeter& unit, const float& scalar) {
                float u = static_cast<float>(unit);
                float v = std::clamp<float>(u * scalar, 0.0f, MAXIMUM);

                return millimeter(static_cast<uint16_t>(v));
            }

            friend millimeter
            operator*(const float& scalar, const millimeter& unit) {
                float u = static_cast<float>(unit);
                float v = std::clamp<float>(u * scalar, 0.0f, MAXIMUM);

                return millimeter(static_cast<uint16_t>(v));
            }

            friend millimeter
            operator*(const millimeter& unit, const double& scalar) {
                double u = static_cast<double>(unit);
                double v = std::clamp<double>(u * scalar, 0.0, MAXIMUM);

                return millimeter(static_cast<uint16_t>(v));
            }

            friend millimeter
            operator*(const double& scalar, const millimeter& unit) {
                double u = static_cast<double>(unit);
                double v = std::clamp<double>(u * scalar, 0.0, MAXIMUM);

                return millimeter(static_cast<uint16_t>(v));
            }

            friend millimeter
            operator/(const millimeter& unit, const float& scalar) {
                float u = static_cast<float>(unit);
                float v = std::clamp<float>(u / scalar, 0.0f, MAXIMUM);

                return millimeter(static_cast<uint16_t>(v));
            }

            friend millimeter
            operator/(const millimeter& unit, const double& scalar) {
                double u = static_cast<double>(unit);
                double v = std::clamp<double>(u / scalar, 0.0, MAXIMUM);

                return millimeter(static_cast<uint16_t>(v));
            }
        private:
            std::uint16_t value_; // stores up to 65535 mm
    };
namespace literals {
    millimeter operator ""_mm(unsigned long long int);
    millimeter operator ""_cm(unsigned long long int);
    millimeter operator ""_m(unsigned long long int);

    millimeter operator ""_mm(long double);
    millimeter operator ""_cm(long double);
    millimeter operator ""_m(long double);
} // namespace literals
} // namespace mesher

#endif // MESHER_UNITS_HPP__
