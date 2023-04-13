#ifndef MESHER_MODEL_HPP__
#define MESHER_MODEL_HPP__

#include <dimension/dimension.hpp>
#include <gmsh.h>
#include <geometry/geometry.hpp>
#include <string>

// #include "mesher-units.hpp"

namespace mesher {
    using Tag   = int;
    using Tags  = std::vector<Tag>;

    template <typename Precision>
    class model {
        public:
            model(const std::string& name) {
                gmsh::model::add(name);
            }

            ~model() {
                gmsh::model::geo::synchronize();
            }

            int
            point(const geometry::d2::Point<Precision>& p) {
                return gmsh::model::geo::addPoint(p.x(), p.y(), 0.0);
            }

            int
            point(const geometry::d2::Point<Precision>& p, const dimension::millimeter& size) {
                return gmsh::model::geo::addPoint(p.x(), p.y(), 0.0, static_cast<Precision>(size));
            }

            int
            point(const geometry::d2::Point<Precision>& p, const dimension::millimeter& size, Tag tag) {
                return gmsh::model::geo::addPoint(p.x(), p.y(), 0.0, static_cast<Precision>(size), tag);
            }

            int
            line(const int start, const int end) {
                return gmsh::model::geo::addLine(start, end);
            }

            int
            line(const int start, const int end, Tag tag) {
                return gmsh::model::geo::addLine(start, end, tag);
            }

            int
            arc(const Tag start, const Tag center, const Tag end, Tag tag) {
                return gmsh::model::geo::addCircleArc(start, center, end, tag);
            }
            
            int
            curve_loop(const std::vector<Tag>& tags) {
                return gmsh::model::geo::addCurveLoop(tags);
            }

            int
            curve_loop(const std::vector<Tag>& tags, Tag tag) {
                return gmsh::model::geo::addCurveLoop(tags, tag);
            }

            int
            plane_surface(const std::vector<Tag>& tags) {
                return gmsh::model::geo::addPlaneSurface(tags);
            }

            int
            plane_surface(const Tags& tags, Tag tag) {
                return gmsh::model::geo::addPlaneSurface(tags, tag);
            }

            int
            physical_group(int dim, const Tags& tags, Tag tag, const std::string& name) {
                return gmsh::model::geo::addPhysicalGroup(dim, tags, tag, name);
            }
        private:
    };
} // namespace mesher

#endif // MESHER_MODEL_HPP__
