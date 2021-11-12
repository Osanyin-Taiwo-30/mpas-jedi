/*
 * (C) Copyright 2020 UCAR
 *
 * This software is licensed under the terms of the Apache Licence Version 2.0
 * which can be obtained at http://www.apache.org/licenses/LICENSE-2.0.
 */

#include "oops/util/abor1_cpp.h"
#include "oops/util/DateTime.h"
#include "oops/util/Logger.h"

#include "ufo/GeoVaLs.h"

#include "mpasjedi/GeometryMPAS.h"
#include "mpasjedi/getvalues/LinearGetValues.h"
#include "mpasjedi/IncrementMPAS.h"
#include "mpasjedi/StateMPAS.h"

namespace mpas {

// -----------------------------------------------------------------------------

LinearGetValues::LinearGetValues(const GeometryMPAS & geom,
  const ufo::Locations & locs, const eckit::Configuration & config)
  : locs_(locs), geom_(new GeometryMPAS(geom)) {
  oops::Log::trace() << "LinearGetValues::LinearGetValues starting"
    << std::endl;

  mpas_lineargetvalues_create_f90(keyLinearGetValues_, geom_->toFortran(), locs,
    config);

  oops::Log::trace() << "LinearGetValues::LinearGetValues done" << std::endl;
}

// -----------------------------------------------------------------------------

LinearGetValues::~LinearGetValues() {
  oops::Log::trace() << "LinearGetValues::~LinearGetValues starting"
    << std::endl;

  mpas_lineargetvalues_delete_f90(keyLinearGetValues_);

  oops::Log::trace() << "LinearGetValues::~LinearGetValues done" << std::endl;
}

// -----------------------------------------------------------------------------

void LinearGetValues::setTrajectory(const StateMPAS & state,
  const util::DateTime & t1, const util::DateTime & t2,
  ufo::GeoVaLs & geovals) {
  oops::Log::trace() << "LinearGetValues::setTrajectory starting" << std::endl;

  mpas_lineargetvalues_set_trajectory_f90(
    keyLinearGetValues_, geom_->toFortran(), state.toFortran(),
    t1, t2, locs_, geovals.toFortran());

  oops::Log::trace() << "LinearGetValues::setTrajectory done" << std::endl;
}

// -----------------------------------------------------------------------------

void LinearGetValues::fillGeoVaLsTL(const IncrementMPAS & inc,
  const util::DateTime & t1, const util::DateTime & t2,
  ufo::GeoVaLs & geovals) const {
  oops::Log::trace() << "LinearGetValues::fillGeoVaLsTL starting" << std::endl;

  mpas_lineargetvalues_fill_geovals_tl_f90(
    keyLinearGetValues_, geom_->toFortran(), inc.toFortran(),
    t1, t2, locs_, geovals.toFortran());

  oops::Log::trace() << "LinearGetValues::fillGeoVaLsTL done" << std::endl;
}

// -----------------------------------------------------------------------------

void LinearGetValues::fillGeoVaLsAD(IncrementMPAS & inc,
  const util::DateTime & t1, const util::DateTime & t2,
  const ufo::GeoVaLs & geovals) const {
  oops::Log::trace() << "LinearGetValues::fillGeoVaLsAD starting" << std::endl;

  mpas_lineargetvalues_fill_geovals_ad_f90(
    keyLinearGetValues_, geom_->toFortran(), inc.toFortran(),
    t1, t2, locs_, geovals.toFortran());

  oops::Log::trace() << "LinearGetValues::fillGeoVaLsAD done" << std::endl;
}

// -----------------------------------------------------------------------------

void LinearGetValues::print(std::ostream & os) const {
  os << " LinearGetValues for mpas-jedi" << std::endl;
}

// -----------------------------------------------------------------------------

}  // namespace mpas
