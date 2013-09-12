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

#ifndef __SOT_VECTOR_ROLLPITCHYAW_H__
#define __SOT_VECTOR_ROLLPITCHYAW_H__

/* --- SOT --- */
#include <sot/core/vector-rotation.hh>
#include "sot/core/api.hh"

/* --------------------------------------------------------------------- */
/* --------------------------------------------------------------------- */
/* --------------------------------------------------------------------- */
namespace dynamicgraph { namespace sot {

class SOT_CORE_EXPORT VectorRollPitchYaw
: public VectorRotation
{
 public:

  VectorRollPitchYaw( void ) : VectorRotation() { }
  VectorRollPitchYaw( const VectorRollPitchYaw & v ) : VectorRotation(v) { }
  virtual ~VectorRollPitchYaw( void ) { }

  virtual VectorRotation& fromMatrix( const MatrixRotation& rot );
  virtual MatrixRotation& toMatrix( MatrixRotation& rot ) const;

};

} /* namespace sot */} /* namespace dynamicgraph */

#endif /* #ifndef __SOT_VECTOR_ROLLPITCHYAW_H__ */
