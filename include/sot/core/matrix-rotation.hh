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

#ifndef __SOT_MATRIX_ROTATION_H__
#define __SOT_MATRIX_ROTATION_H__

#include "sot/core/api.hh"
#include <dynamic-graph/linear-algebra.h>

namespace dynamicgraph {
  namespace sot {
    class VectorUTheta;
    
    /* --------------------------------------------------------------------- */
    /* --------------------------------------------------------------------- */
    /* --------------------------------------------------------------------- */
    class SOT_CORE_EXPORT MatrixRotation
      : public dynamicgraph::Matrix
    {
      
    public: 
      
      MatrixRotation( void ) : dynamicgraph::Matrix(3,3) { setIdentity(); }
      MatrixRotation( const MatrixRotation & m ) : dynamicgraph::Matrix(m) {}
      virtual ~MatrixRotation( void ) { }
      MatrixRotation& operator=( const dynamicgraph::Matrix& m);
      
      void fromVector( VectorUTheta& );
      MatrixRotation& operator= ( VectorUTheta&th ) { fromVector(th); return *this; } 
    };
  } // namespace sot
} // namespace dynamicgraph
#endif /* #ifndef __SOT_MATRIX_ROTATION_H__ */






