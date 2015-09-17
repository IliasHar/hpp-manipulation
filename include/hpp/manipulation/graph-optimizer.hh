// Copyright (c) 2015, LAAS-CNRS
// Authors: Joseph Mirabel (joseph.mirabel@laas.fr)
//
// This file is part of hpp-manipulation.
// hpp-manipulation is free software: you can redistribute it
// and/or modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation, either version
// 3 of the License, or (at your option) any later version.
//
// hpp-manipulation is distributed in the hope that it will be
// useful, but WITHOUT ANY WARRANTY; without even the implied warranty
// of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// General Lesser Public License for more details.  You should have
// received a copy of the GNU Lesser General Public License along with
// hpp-manipulation. If not, see <http://www.gnu.org/licenses/>.


#ifndef HPP_MANIPULATION_GRAPHOPTIMIZER_HH
# define HPP_MANIPULATION_GRAPHOPTIMIZER_HH

# include <hpp/core/path.hh>
# include <hpp/core/path-vector.hh>
# include <hpp/core/path-optimizer.hh>
# include <hpp/core/problem.hh>

# include <hpp/manipulation/fwd.hh>
# include <hpp/manipulation/graph/fwd.hh>
# include <hpp/manipulation/config.hh>
# include <hpp/manipulation/constraint-set.hh>

namespace hpp {
  namespace manipulation {
    using hpp::core::Path;
    using hpp::core::PathPtr_t;
    using hpp::core::PathVector;
    using hpp::core::PathVectorPtr_t;

    /// \addtogroup path_optimization
    /// \{

    /// Path optimizer for paths created with the constraint graph
    ///
    /// This class encapsulates another path optimizer class. This optimizer
    /// calls the inner optimizer on every subpaths with the same set of
    /// constraints.
    class HPP_MANIPULATION_DLLAPI GraphOptimizer : public PathOptimizer
    {
      public:
        template <typename InnerPathOptimizer_t>
          static GraphOptimizerPtr_t create (const core::Problem& problem);

        virtual PathVectorPtr_t optimize (const PathVectorPtr_t& path);

        /// Get the encapsulated optimizer
        const PathOptimizerPtr_t& innerOptimizer ()
        {
          return pathOptimizer_;
        }

      protected:
        /// Constructor
        GraphOptimizer (const core::Problem& problem, PathOptimizerPtr_t inner) :
          PathOptimizer (problem), pathOptimizer_ (inner)
        {}

      private:
        /// The encapsulated PathOptimizer
        PathOptimizerPtr_t pathOptimizer_;

        /// Append all paths of in to out
        /// \param in a path vector, possibly containing other path vector
        /// \param out a flat PathVector (do not contain PathVector)
        static void unpack (PathVectorPtr_t in, PathVectorPtr_t out);
    };
    /// \}

    /// Member function definition
    template <typename InnerPathOptimizer_t>
      GraphOptimizerPtr_t GraphOptimizer::create
      (const core::Problem& problem)
    {
      return GraphOptimizerPtr_t (
          new GraphOptimizer (problem, InnerPathOptimizer_t::create (problem))
          );
    }

  } // namespace manipulation
} // namespace hpp

#endif // HPP_MANIPULATION_GRAPHOPTIMIZER_HH
