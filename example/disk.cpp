#include <gmsh.h>
#include <mesher/mesher.hpp>

using namespace mesher::literals;

int
main(int, char**) {
    mesher::radius              radius(50_mm);
    geometry::d2::Point<float>  center(0.0f, 0.0f);
    mesher::disk<float>         disk(center, radius, 16);

    gmsh::initialize();
    std::unique_ptr<mesher::model<float>> model = std::make_unique<mesher::model<float>>("disk");
    disk(std::move(model), 10_mm);

    gmsh::model::mesh::generate(2);
    gmsh::option::setNumber("Mesh.MshFileVersion", 2.2);
    gmsh::write("disk.msh");
    gmsh::finalize();
    return 0;
}
