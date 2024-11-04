// checker.h
#ifndef GEOMETRY_CHECKER_H
#define GEOMETRY_CHECKER_H

#include "figures/figure.h"
#include "figures/pentagon.h"
#include "figures/hexagon.h"
#include "figures/octagon.h"
#include <cmath>

template<Scalar T>
class GeometryChecker {
private:
    static double distance(const Point<T>& p1, const Point<T>& p2) {
        T dx = p1.get_x() - p2.get_x();
        T dy = p1.get_y() - p2.get_y();
        return std::sqrt(dx * dx + dy * dy);
    }

    static bool are_equal(double a, double b, double epsilon = 1e-3) {
        return std::abs(a - b) < epsilon;
    }

    template<typename PolygonType>
    static bool is_regular_polygon(const PolygonType& polygon, size_t vertex_count) {
        const auto center = polygon.get_center();
        std::vector<double> side_lengths;
        std::vector<double> radii;

        // Check distances from center to vertices (radii)
        for (size_t i = 0; i < vertex_count; ++i) {
            std::cout << distance(polygon.get_vertex(i), center) << '\n';
            radii.push_back(distance(polygon.get_vertex(i), center));
        }

        // Check side lengths
        for (size_t i = 0; i < vertex_count; ++i) {
            std::cout << distance(polygon.get_vertex(i), polygon.get_vertex((i + 1) % vertex_count)) << '\n';
            side_lengths.push_back(distance(polygon.get_vertex(i),
                                         polygon.get_vertex((i + 1) % vertex_count)));
        }

        // All radii should be equal
        double first_radius = radii[0];
        for (const double& radius : radii) {
            if (!are_equal(radius, first_radius)) return false;
        }

        // All sides should be equal
        double first_side = side_lengths[0];
        for (const double& side : side_lengths) {
            if (!are_equal(side, first_side)) return false;
        }

        return true;
    }

public:
    static bool is_regular_pentagon(const Pentagon<T>& pentagon) {
        return is_regular_polygon(pentagon, 5);
    }

    static bool is_regular_hexagon(const Hexagon<T>& hexagon) {
        return is_regular_polygon(hexagon, 6);
    }

    static bool is_regular_octagon(const Octagon<T>& octagon) {
        return is_regular_polygon(octagon, 8);
    }

    // Additional utility methods
    template<typename PolygonType>
    static double get_perimeter(const PolygonType& polygon) {
        double perimeter = 0.0;
        size_t vertex_count = polygon.get_vertices_count();
        for (size_t i = 0; i < vertex_count; ++i) {
            perimeter += distance(polygon.get_vertex(i),
                                polygon.get_vertex((i + 1) % vertex_count));
        }
        return perimeter;
    }

    template<typename PolygonType>
    static double get_average_radius(const PolygonType& polygon) {
        const auto center = polygon.get_center();
        double total_radius = 0.0;
        size_t vertex_count = polygon.get_vertices_count();
        for (size_t i = 0; i < vertex_count; ++i) {
            total_radius += distance(polygon.get_vertex(i), center);
        }
        return total_radius / vertex_count;
    }
};

#endif
