#include <iostream>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Polygon_2.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2 Point;
typedef CGAL::Polygon_2<K> Polygon_2;

void check_inside(Point pt, Point *pgn_begin, Point *pgn_end, K traits) {
    std::cout << "The point " << pt;
    switch(CGAL::bounded_side_2(pgn_begin, pgn_end, pt, traits)) {
        case CGAL::ON_BOUNDED_SIDE :
            std::cout << " is insde the polygon.\n";
            break;
        case CGAL::ON_BOUNDARY :
            std::cout << " is on the polygon boundary.\n";
            break;
        case CGAL::ON_UNBOUNDED_SIDE :
            std::cout << " is outside the polygon.\n";
            break;
    }
}

int main() {
    Point points[] = { Point(0, 0), Point(5.1, 0), Point(1,1), Point(0.5, 6)};
    Polygon_2 pgn(points, points+4);

    // 2.1 check if the polygon is simple.
    std::cout << "The polygon is " << (CGAL::is_simple_2(points, points+4, K()) ? "" : "not ") << "simple." << std::endl;

    // 2.2 Use check_inside function declared before main()
    check_inside(Point(0.5, 0.5), points, points+4, K());
    check_inside(Point(1.5, 2.5), points, points+4, K());
    check_inside(Point(2.5, 0), points, points+4, K());

    return 0;
}
