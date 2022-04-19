// Copyright (c) 2019, Joseph Mirabel
// Authors: Joseph Mirabel (joseph.mirabel@laas.fr)
//

// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
// 1. Redistributions of source code must retain the above copyright
//    notice, this list of conditions and the following disclaimer.
//
// 2. Redistributions in binary form must reproduce the above copyright
// notice, this list of conditions and the following disclaimer in the
// documentation and/or other materials provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
// DAMAGE.

#include <hpp/core/plugin.hh>
#include <hpp/core/problem-solver.hh>
#include <hpp/manipulation/path-optimization/spline-gradient-based.hh>

namespace hpp {
namespace manipulation {
class SplineGradientBasedPlugin : public core::ProblemSolverPlugin {
 public:
  SplineGradientBasedPlugin()
      : ProblemSolverPlugin("SplineGradientBasedPlugin", "0.0") {}

 protected:
  virtual bool impl_initialize(core::ProblemSolverPtr_t ps) {
    // ps->pathOptimizers.add
    // ("SplineGradientBased_cannonical1",pathOptimization::SplineGradientBased<core::path::CanonicalPolynomeBasis,
    // 1>::createFromCore); ps->pathOptimizers.add
    // ("SplineGradientBased_cannonical2",pathOptimization::SplineGradientBased<core::path::CanonicalPolynomeBasis,
    // 2>::createFromCore); ps->pathOptimizers.add
    // ("SplineGradientBased_cannonical3",pathOptimization::SplineGradientBased<core::path::CanonicalPolynomeBasis,
    // 3>::createFromCore);
    ps->pathOptimizers.add(
        "SplineGradientBased_bezier1",
        pathOptimization::SplineGradientBased<core::path::BernsteinBasis,
                                              1>::createFromCore);
    // ps->pathOptimizers.add
    // ("SplineGradientBased_bezier2",pathOptimization::SplineGradientBased<core::path::BernsteinBasis,
    // 2>::createFromCore);
    ps->pathOptimizers.add(
        "SplineGradientBased_bezier3",
        pathOptimization::SplineGradientBased<core::path::BernsteinBasis,
                                              3>::createFromCore);

    return true;
  }
};
}  // namespace manipulation
}  // namespace hpp

HPP_CORE_DEFINE_PLUGIN(hpp::manipulation::SplineGradientBasedPlugin)
