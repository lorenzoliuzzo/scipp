#include <iostream>
#include <cmath>

template<typename T, typename U>
struct measurement {
    T value;

    constexpr measurement() : value(T()) {}
    constexpr measurement(const T& v) : value(v) {}

    constexpr T get_value() const { return value; }
};

template<typename T>
struct unit {};

// Base units
struct meter : public unit<meter> {};
struct kilogram : public unit<kilogram> {};
struct second : public unit<second> {};

// Derived units
struct radian : public unit<radian> {};

// Type aliases for measurements with units
using length = measurement<double, meter>;
using angle = measurement<double, radian>;

// Coordinate system interface
struct CoordinateSystem {
    virtual length x() const = 0;
    virtual length y() const = 0;
    virtual length z() const = 0;
};

// Cartesian coordinate system
struct CartesianCoordinateSystem : public CoordinateSystem {
    length x_;
    length y_;
    length z_;

    constexpr CartesianCoordinateSystem(const length& x, const length& y, const length& z)
        : x_(x), y_(y), z_(z) {}

    constexpr length x() const override { return x_; }
    constexpr length y() const override { return y_; }
    constexpr length z() const override { return z_; }
};

// Polar coordinate system
struct PolarCoordinateSystem : public CoordinateSystem {
    length r_;
    angle theta_;
    length z_;

    constexpr PolarCoordinateSystem(const length& r, const angle& theta, const length& z)
        : r_(r), theta_(theta), z_(z) {}

    constexpr length x() const override { return r_ * std::cos(theta_.get_value()); }
    constexpr length y() const override { return r_ * std::sin(theta_.get_value()); }
    constexpr length z() const override { return z_; }
};

// Cylindrical coordinate system
struct CylindricalCoordinateSystem : public CoordinateSystem {
    length r_;
    angle theta_;
    length h_;

    constexpr CylindricalCoordinateSystem(const length& r, const angle& theta, const length& h)
        : r_(r), theta_(theta), h_(h) {}

    constexpr length x() const override { return r_ * std::cos(theta_.get_value()); }
    constexpr length y() const override { return r_ * std::sin(theta_.get_value()); }
    constexpr length z() const override { return h_; }
};

int main() {
    CartesianCoordinateSystem cartesian(length(1.0), length(2.0), length(3.0));
    PolarCoordinateSystem polar(length(3.0), angle(M_PI / 4), length(1.0));
    CylindricalCoordinateSystem cylindrical(
