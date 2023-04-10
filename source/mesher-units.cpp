#include "mesher/mesher-units.hpp"

namespace mesher {
namespace literals {
    millimeter operator ""_mm(unsigned long long int value) {
        return millimeter(static_cast<uint16_t>(value));
    }

    millimeter operator ""_cm(unsigned long long int value) {
        return millimeter(static_cast<uint16_t>(value * 10));
    }

    millimeter operator ""_m(unsigned long long int value) {
        return millimeter(static_cast<uint16_t>(value * 100));
    }

    millimeter operator ""_mm(long double value) {
        return millimeter(static_cast<uint16_t>(value));
    }

    millimeter operator ""_cm(long double value) {
        return millimeter(static_cast<uint16_t>(value * 10.0));
    }

    millimeter operator ""_m(long double value) {
        return millimeter(static_cast<uint16_t>(value * 100.0));
    }
} // namespace literals
} // namespace mesher
