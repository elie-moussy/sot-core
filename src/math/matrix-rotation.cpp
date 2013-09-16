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

#include <sot/core/matrix-rotation.hh>
#include <sot/core/vector-utheta.hh>

using namespace std;
using namespace dynamicgraph::sot;


void MatrixRotation::fromVector( VectorUTheta& vec )
{
  vec.toMatrix( *this );
}
  
MatrixRotation& MatrixRotation::operator=( const dynamicgraph::Matrix& m)
{
  resize(m.rows(),m.cols());
  ((dynamicgraph::Matrix&)*this).noalias() = m;
  return *this;
}

