/*
 * Copyright 2010,
 * François Bleibel,
 * Olivier Stasse,
 *
 * CNRS/AIST
 *
 * This file is part of sot-core.
 * sot-core is free software: you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation, either version 3 of
 * the License, or (at your option) any later version.
 * sot-core is distributed in the hope that it will be
 * useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.  You should
 * have received a copy of the GNU Lesser General Public License along
 * with sot-core.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef DYNAMICGRAPH_SOT_VECTOR_CONSTANT_H
#define DYNAMICGRAPH_SOT_VECTOR_CONSTANT_H

// initialize all matrix and vectors to NAN
#ifndef EIGEN_INITIALIZE_MATRICES_BY_NAN
#define EIGEN_INITIALIZE_MATRICES_BY_NAN
#endif	

#include <dynamic-graph/entity.h>
#include <dynamic-graph/linear-algebra.h>
#include <dynamic-graph/all-signals.h>

/* --------------------------------------------------------------------- */
/* --- VECTOR ---------------------------------------------------------- */
/* --------------------------------------------------------------------- */
namespace dynamicgraph {
  namespace sot {

    namespace command {
      namespace vectorConstant {
	class Resize;
      }
    }

    class VectorConstant
      : public Entity
    {
      friend class command::vectorConstant::Resize;
      static const std::string CLASS_NAME;
      virtual const std::string& getClassName( void ) const { return CLASS_NAME; }

      int rows;
      double color;

    public:
      VectorConstant( const std::string& name );

      virtual ~VectorConstant( void ){}

      SignalTimeDependent<dynamicgraph::Vector,int> SOUT;

      /// \brief Set value of vector (and therefore of output signal)
      void setValue(const dynamicgraph::Vector& inValue);

      virtual void commandLine( const std::string& cmdLine,
				std::istringstream& cmdArgs,
				std::ostream& os );

    };

  } // namespace sot
} // namespace dynamicgraph

#endif //DYNAMICGRAPH_SOT_VECTOR_CONSTANT_H
