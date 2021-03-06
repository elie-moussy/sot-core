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

#include <sot/core/matrix-homogeneous.hh>
#include <sot/core/matrix-rotation.hh>
#include <sot/core/debug.hh>

using namespace dynamicgraph::sot;

MatrixHomogeneous::
MatrixHomogeneous( void )
 :ml::Matrix(4,4)
{
  setIdentity();
}

MatrixHomogeneous::
MatrixHomogeneous( const ml::Matrix & copy )
  :ml::Matrix(copy)
{
  assert( nbCols() == 4 && nbRows() == 4 );
  assert( elementAt(3,0)==0 && elementAt(3,1)==0
	  && elementAt(3,2)==0 && elementAt(3,3)==1 );
  /* wana check the orthogonality of the rotation part? */
}

MatrixHomogeneous& MatrixHomogeneous::
buildFrom( const MatrixRotation& rot, const ml::Vector& trans )
{
  for( int i=0;i<3;++i )
    {
      elementAt( i,3 ) = trans(i);
      for( int j=0;j<3;++j )
	elementAt( i,j ) = rot( i,j );
      elementAt( 3,i ) = 0.;
    }
  
  elementAt( 3,3 ) = 1.;

  return *this;
}

ml::Matrix& MatrixHomogeneous::
extract( ml::Matrix& rot ) const
{
  for( int i=0;i<3;++i )
    for( int j=0;j<3;++j )
      rot( i,j ) = elementAt( i,j );

  return rot;
}

MatrixRotation& MatrixHomogeneous::
extract( MatrixRotation& rot ) const
{
  for( int i=0;i<3;++i )
    for( int j=0;j<3;++j )
      rot( i,j ) = elementAt( i,j );

  return rot;
}

ml::Vector& MatrixHomogeneous::
extract( ml::Vector& trans ) const
{
  for( int i=0;i<3;++i )
    trans( i ) = elementAt( i,3 );

  return trans;
}


MatrixHomogeneous& MatrixHomogeneous::
operator=( const ml::Matrix& m2)
{
  if( (m2.nbRows()==4)&&(m2.nbCols()==4) )
    ((ml::Matrix&)*this) = m2;
    
  return *this;

}

MatrixHomogeneous MatrixHomogeneous::
operator*(const MatrixHomogeneous& h) const
{
  MatrixHomogeneous res;
  double h00 = h(0,0), h01 = h(0,1), h02 = h(0,2), h03 = h(0,3);
  double h10 = h(1,0), h11 = h(1,1), h12 = h(1,2), h13 = h(1,3);
  double h20 = h(2,0), h21 = h(2,1), h22 = h(2,2), h23 = h(2,3);
  
  double self00 = elementAt(0,0), self01 = elementAt(0,1),
    self02 = elementAt(0,2), self03 = elementAt(0,3);
  double self10 = elementAt(1,0), self11 = elementAt(1,1),
    self12 = elementAt(1,2), self13 = elementAt(1,3);
  double self20 = elementAt(2,0), self21 = elementAt(2,1),
    self22 = elementAt(2,2), self23 = elementAt(2,3);

  res(0,0) = self00*h00 + self01*h10 + self02*h20;
  res(0,1) = self00*h01 + self01*h11 + self02*h21;
  res(0,2) = self00*h02 + self01*h12 + self02*h22;
  res(1,0) = self10*h00 + self11*h10 + self12*h20;
  res(1,1) = self10*h01 + self11*h11 + self12*h21;
  res(1,2) = self10*h02 + self11*h12 + self12*h22;
  res(2,0) = self20*h00 + self21*h10 + self22*h20;
  res(2,1) = self20*h01 + self21*h11 + self22*h21;
  res(2,2) = self20*h02 + self21*h12 + self22*h22;

  res(0,3) = self00*h03 + self01*h13 + self02*h23 + self03;
  res(1,3) = self10*h03 + self11*h13 + self12*h23 + self13;
  res(2,3) = self20*h03 + self21*h13 + self22*h23 + self23;

  return res;
}

MatrixHomogeneous& MatrixHomogeneous::
inverse( MatrixHomogeneous& invMatrix ) const 
{
  sotDEBUGIN(25);

  double R00 = elementAt(0,0), R01 = elementAt(0,1), R02 = elementAt(0,2);
  double R10 = elementAt(1,0), R11 = elementAt(1,1), R12 = elementAt(1,2);
  double R20 = elementAt(2,0), R21 = elementAt(2,1), R22 = elementAt(2,2);

  double t0 = elementAt(0,3);
  double t1 = elementAt(1,3);
  double t2 = elementAt(2,3);

  invMatrix(0,0) = R00, invMatrix(0,1) = R10, invMatrix(0,2) = R20;
  invMatrix(1,0) = R01, invMatrix(1,1) = R11, invMatrix(1,2) = R21;
  invMatrix(2,0) = R02, invMatrix(2,1) = R12, invMatrix(2,2) = R22;

  invMatrix(0,3) = -(R00*t0+ R10*t1 + R20*t2);
  invMatrix(1,3) = -(R01*t0+ R11*t1 + R21*t2);
  invMatrix(2,3) = -(R02*t0+ R12*t1 + R22*t2);

  sotDEBUGOUT(25);
  return invMatrix;
}


ml::Vector& MatrixHomogeneous::
multiply( const ml::Vector& v1,ml::Vector& res ) const
{
  sotDEBUGIN(15);

  bool translate=true;
  if( 3==v1.size() ) res.resize(3);
  else if( 4==v1.size() )
    { res.resize(4); if(res(3)==0) { translate=false; } else res(3)=1.; }
  else {
    sotERROR << "Error while multiplying HOMOxVECTOR."<<std::endl;
    return res;
  }
  res.fill(0.);
  for( unsigned int i=0;i<3;++i )
    {
      for( unsigned int j=0;j<3;++j )
	{	  res(i)+=matrix(i,j)*v1(j); 	}
      if(translate)res(i)+=matrix(i,3);
    }

  sotDEBUGOUT(15);
  return res;
}
