/*
 * (C) Copyright 2022 UCAR
 *
 * This software is licensed under the terms of the Apache Licence Version 2.0
 * which can be obtained at http://www.apache.org/licenses/LICENSE-2.0.
 */

#ifndef MPASJEDI_STATEMPASPARAMETERS_H_
#define MPASJEDI_STATEMPASPARAMETERS_H_

#include <string>

#include "oops/base/ParameterTraitsVariables.h"
#include "oops/base/Variables.h"
#include "oops/base/WriteParametersBase.h"
#include "oops/util/parameters/OptionalParameter.h"
#include "oops/util/parameters/Parameters.h"
#include "oops/util/parameters/RequiredParameter.h"

namespace oops {
  class Variables;
}

namespace mpas {

// -------------------------------------------------------------------------------------------------

/// Parameters for Analytic Init
class AnalyticInitParameters : public oops::Parameters {
  OOPS_CONCRETE_PARAMETERS(AnalyticInitParameters, Parameters)

 public:
  /// Analytic initial condition parameter, currently available options are
  /// dcmip-test-1-1: 3D deformational flow
  /// dcmip-test-1-2: 3D Hadley-like meridional circulation
  /// dcmip-test-3-1: Non-hydrostatic gravity wave
  /// dcmip-test-4-0: Baroclinic instability
  oops::Parameter<std::string> method{"method", "dcmip-test-4-0", this};
};

// -------------------------------------------------------------------------------------------------

// Configuration options recognized by mpas_state_mod and mpas_fields_mod
class StateMPASParameters : public oops::Parameters {
  OOPS_CONCRETE_PARAMETERS(StateMPASParameters, Parameters)

 public:
  oops::RequiredParameter<oops::Variables> state_variables{"state variables", this};
  // Either analytic_init or filename must be set
  // Analytic initial condition parameter for analytic_IC
  oops::OptionalParameter<AnalyticInitParameters> analytic_init{"analytic init", this};
  // Read parameters for read_fields
  // when analytic init is not set, filename must be set
  oops::OptionalParameter<std::string> filename{"filename", this};
  oops::RequiredParameter<util::DateTime> date{"date", this};
  oops::Parameter<std::string> stream_name{"stream name", "background", this};
  oops::Parameter<bool> transform_model_to_analysis{"transform model to analysis", true, this};
};

// -------------------------------------------------------------------------------------------------

/// Configuration options recognized by mpas_fields_mod for write_fields
class StateMPASWriteParameters : public oops::WriteParametersBase {
  OOPS_CONCRETE_PARAMETERS(StateMPASWriteParameters, WriteParametersBase)

 public:
  // Write parameters
  oops::RequiredParameter<std::string> filename{"filename", this};
  oops::Parameter<std::string> stream_name{"stream name", "da_state", this};
};

// -------------------------------------------------------------------------------------------------

}  // namespace mpas

#endif  // MPASJEDI_STATEMPASPARAMETERS_H_
