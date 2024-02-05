#include <iostream>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Polygon_2.h>
#include <CGAL/Projection_traits_yz_3.h>
#include <CGAL/Polygon_2_algorithms.h>
#include <CGAL/draw_polygon_2.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2                                          Point_2;
typedef K::Point_3                                          Point_3;
typedef CGAL::Polygon_2<K>                                  Polygon_2;
typedef K::Segment_2                                        Segment_2;


void check_inside(Point_2 pt, Point_2 *pgn_begin, Point_2 *pgn_end, K traits) {
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
    Point_2 points[] = { Point_2(0, 0), Point_2(5.1, 0), Point_2(1,1), Point_2(0.5, 6)};
    Polygon_2 pgn(points, points+4);

    // 2.1 check if the polygon is simple.
    std::cout << "The polygon is " << (CGAL::is_simple_2(points, points+4, K()) ? "" : "not ") << "simple." << std::endl;

    // 2.2 Use check_inside function declared before main()
    check_inside(Point_2(0.5, 0.5), points, points+4, K());
    check_inside(Point_2(1.5, 2.5), points, points+4, K());
    check_inside(Point_2(2.5, 0), points, points+4, K());

    // 2.3 Polygons in 3D Space
    /*Point_3 points_3d[4] = {Point_3(0,1,1), Point_3(0,2,1), Point_3(0,2,2), Point_3(0,1,2)};

    bool b = CGAL::is_simple_2(points_3d, points_3d+4, CGAL::Projection_traits_yz_3<K>());

    if (!b) {
        std::cerr << "Error polygon is not simple" << std::endl;
        return 1;
    }*/

    // 2.4 Iterating over Vertices and Edges
    Polygon_2 p;
    p.push_back(Point_2(0,0));
    p.push_back(Point_2(4, 0));
    p.push_back(Point_2(4,4));
    p.push_back(Point_2(0,4));

    std::cout << "Iterating over the vertices of p: " << std::endl;

    for (int i = 0; i < p.size(); ++i) {
        std::cout << p.vertex(i) << std::endl;
    }

    std::cout << "Iterating over the edges of p: " << std::endl;

    for (int i = 0; i < p.size(); ++i) {
        Segment_2 e = p.edge(i);
        std::cout << e << std::endl;
    }

    // 2.5 Draw polygon p

    CGAL::draw(p);

    return EXIT_SUCCESS;
}
