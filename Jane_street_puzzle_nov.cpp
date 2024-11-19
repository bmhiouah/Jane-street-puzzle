#include <iostream>
#include <random>
#include <vector>
#include <cmath>
#include <algorithm>

struct Point {
    double x, y;
};

struct Line {
    double a, b, c; // ax + by + c = 0
};

struct Segment {
    Point p1, p2;
};

double distanceToLine(const Point& p, const Line& line) {
    return std::abs(line.a * p.x + line.b * p.y + line.c) / std::sqrt(line.a * line.a + line.b * line.b);
}

bool isIntersecting(const Segment& seg, const Line& line) {
    // Check signs of the line equation at segment endpoints
    double val1 = line.a * seg.p1.x + line.b * seg.p1.y + line.c;
    double val2 = line.a * seg.p2.x + line.b * seg.p2.y + line.c;

    return (val1 * val2 <= 0); // Opposite signs mean intersection
}

int main() {
    const int n = 1000000; // Number of runs
    int intersections = 0;

    // Random number generation
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, 1.0);

    // Define square sides as segments
    std::vector<Segment> sides = {
        {{0, 0}, {1, 0}}, // Bottom
        {{1, 0}, {1, 1}}, // Right
        {{0, 1}, {1, 1}}, // Top
        {{0, 0}, {0, 1}}  // Left
    };

    for (int i = 0; i < n; ++i) {
        // Generate two random points
        Point blue = {dis(gen), dis(gen)};
        Point red = {dis(gen), dis(gen)};

        // Midpoint calculation
        Point midpoint = {(blue.x + red.x) / 2.0, (blue.y + red.y) / 2.0};

        // Calculate perpendicular bisector (ax + by + c = 0)
        double dx = red.x - blue.x;
        double dy = red.y - blue.y;

        Line bisector;
        if (dx == 0) { // Vertical line
            bisector = {1, 0, -midpoint.x};
        } else if (dy == 0) { // Horizontal line
            bisector = {0, 1, -midpoint.y};
        } else {
            double slope = -dx / dy;
            bisector = {slope, -1, midpoint.y - slope * midpoint.x};
        }

        // Find closest side to the blue point
        double min_distance = std::numeric_limits<double>::max();
        Segment closest_side;

        for (const auto& side : sides) {
            double distance = std::min(distanceToLine(side.p1, bisector), distanceToLine(side.p2, bisector));
            if (distance < min_distance) {
                min_distance = distance;
                closest_side = side;
            }
        }

        // Check if bisector intersects the closest side
        if (isIntersecting(closest_side, bisector)) {
            ++intersections;
        }
    }

    // Compute empirical probability
    double probability = static_cast<double>(intersections) / n;
    std::cout << "Empirical Probability: " << probability << std::endl;

    return 0;
}
