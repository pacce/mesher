#ifndef MESHER_DISK_HPP__
#define MESHER_DISK_HPP__

#include <dimension/dimension.hpp>
#include <geometry/geometry.hpp>

#include <memory>
#include <numeric>

#include "mesher-model.hpp"

namespace mesher {
    template <typename Precision>
    class disk {
        using Point = geometry::d2::Point<Precision>;
        public:
            explicit disk(
                    const Point&                center
                    , const dimension::radius&  radius
                    , std::size_t               electrodes
                    ) 
                : center_(center)
                , radius_(radius) 
                , electrodes_(electrodes)
            {}

            void
            operator()(std::unique_ptr<model<Precision>> model, const dimension::millimeter& size) const {
                const Precision PI          = 2.0 * std::numbers::pi_v<Precision>;
                const Precision radius      = static_cast<Precision>(radius_);
                const Precision electrodes  = static_cast<Precision>(electrodes_);

                std::vector<Tag> ps = {};
                for (std::size_t electrode = 0; electrode < electrodes_; electrode++) {
                    Precision step  = static_cast<Precision>(electrode) / electrodes;
                    Precision angle = PI * step;

                    Point p(radius * std::cos(angle), radius * std::sin(angle));
                    ps.push_back(
                        model->point(p + center_, size, electrode + 1)
                        );
                }
                Tag center = model->point(center_, size, ps.back() + 1);

                std::vector<Tag> loop = {};
                for (std::size_t p = 0; p < ps.size(); p++) {
                    Tag fst = ps[p];
                    Tag snd = ps[(p + 1) % ps.size()];

                    loop.push_back(model->arc(fst, center, snd, p + 1));
                }
                model->curve_loop(loop, 1);
                model->plane_surface({1});

                model->physical_group(0, ps, -1, "electrodes");
                model->physical_group(0, {center}, -1, "center");
                model->physical_group(1, loop, -1, "contour");
                model->physical_group(2, loop, -1, "domain");
            }
        private:
            geometry::d2::Point<Precision>  center_;
            dimension::radius               radius_;
            std::size_t                     electrodes_;
    };
} // namespace mesher

#endif // MESHER_DISK_HPP__
