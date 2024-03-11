// Example program for the linear_least_square_fitting function
// on a set of 3D triangles
#include <CGAL/Simple_cartesian.h>
#include <CGAL/Search_traits_3.h>
#include <CGAL/K_neighbor_search.h>
#include <CGAL/Orthogonal_incremental_neighbor_search.h>
#include <CGAL/linear_least_squares_fitting_3.h>
#include <vector>
#include <list>
#include <fstream>
#include <iostream>
#include <filesystem>
#include <iomanip>

typedef double                                                      FT;
typedef CGAL::Simple_cartesian<FT>                                  K;
typedef K::Line_3                                                   Line;
typedef K::Plane_3                                                  Plane;
typedef K::Point_3                                                  Point3;
typedef K::Triangle_3                                               Triangle;
typedef CGAL::Search_traits_3<K>                                    TreeTraits;
typedef CGAL::Orthogonal_incremental_neighbor_search<TreeTraits>    NN_search;
typedef NN_search::Tree                                                Tree;

namespace fs = std::filesystem;

struct PointGeoms {
    Point3 point;
    double roughness;

    PointGeoms(Point3 p, double r) : point(p), roughness(r) {}
};

std::vector<Point3> findKNearestNeighbors(const Tree& tree, const Point3& query_point, std::size_t k) {
    std::vector<Point3> neighbors;
    NN_search search(tree, query_point, k);

    for (auto it = search.begin(); it != search.end(); ++it) {
        neighbors.push_back(it->first);
    }

    return neighbors;
}


int main(void) {
    std::string path = "../data";
    std::vector<std::vector<PointGeoms>> PointClouds; // Vector to store point clouds

    if (!fs::exists(path)) {
        std::cerr << "Data directory does not exist." << std::endl;
        return EXIT_FAILURE;
    }

    // Iterate over the files in the directory
    for (const auto& entry : fs::directory_iterator(path)) {
        if (entry.path().extension() == ".xyz") {
            std::ifstream file(entry.path());
            std::vector<PointGeoms> points; // Vector to store points from the current file

            if (file) {
                FT x, y, z;
                double defaultRoughness = 0.5;
                // Read points from the .xyz file
                while (file >> x >> y >> z) {
                    Point3 p(x, y, z);
                    points.push_back(PointGeoms(p, defaultRoughness));
                }
                file.close();

                // Add the current file's points vector to the PointClouds vector
                PointClouds.push_back(points);
            } else {
                std::cerr << "Could not open file " << entry.path() << std::endl;
            }
        }
    }

    // Output the total number of point clouds and the number of points in each point cloud
    std::cout << PointClouds.size() << " point clouds loaded." << std::endl;
    for (size_t i = 0; i < PointClouds.size(); ++i) {
        std::cout << "Point cloud " << i + 1 << " contains " << PointClouds[i].size() << " points." << std::endl;
    }

    // Create a search tree from point cloud data
    std::vector<PointGeoms> pointCloud = PointClouds[0];

    std::list<Point3> points_for_tree;
    for (const auto& pg : pointCloud) {
        points_for_tree.push_back(pg.point);
    }

    Tree tree(points_for_tree.begin(), points_for_tree.end());

    for (auto& pg : pointCloud) {
        // find k-nearest neighbors of the current point
        auto neighbors = findKNearestNeighbors(tree, pg.point, 2);

        Plane bestPlane;
        CGAL::linear_least_squares_fitting_3(neighbors.begin(), neighbors.end(), bestPlane, CGAL::Dimension_tag<0>());

        pg.roughness = std::sqrt(CGAL::squared_distance(pg.point, bestPlane));

    }

    std::cout << "Point Coordinates and Roughness:" << std::endl;
    for (const auto& pg : pointCloud) {
        std::cout << std::fixed << std::setprecision(2);
        std::cout << "Point: (" << pg.point.x() << ", " << pg.point.y() << ", " << pg.point.z() << "), " << "Roughness: " << pg.roughness << std::endl;
    }

    return 0;
}
