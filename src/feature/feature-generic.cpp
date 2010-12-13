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

/* --------------------------------------------------------------------- */
/* --- INCLUDE --------------------------------------------------------- */
/* --------------------------------------------------------------------- */

/* --- SOT --- */
#include <sot-core/debug.h>
#include <sot-core/feature-generic.h>
#include <sot-core/exception-feature.h>
#include <sot-core/factory.h>

using namespace std;
using namespace sot;
using namespace dynamicgraph;
SOT_FACTORY_FEATURE_PLUGIN(FeatureGeneric,"FeatureGeneric")

/* --------------------------------------------------------------------- */
/* --- CLASS ----------------------------------------------------------- */
/* --------------------------------------------------------------------- */



FeatureGeneric::
FeatureGeneric( const string& pointName )
  : FeatureAbstract( pointName )
    ,dimensionDefault(0)
    ,errorSIN( NULL,"sotFeatureGeneric("+name+")::input(vector)::errorIN" )
    ,errordotSIN( NULL,"sotFeatureGeneric("+name+")::input(vector)::errordotIN" )
    ,jacobianSIN( NULL,"sotFeatureGeneric("+name+")::input(matrix)::jacobianIN" )
    ,activationSIN( NULL,"sotFeatureGeneric("+name+")::input(matrix)::activationIN" )
    ,errordotSOUT(  boost::bind(&FeatureGeneric::computeErrorDot,this,_1,_2),
		    selectionSIN<<desiredValueSIN,
		    "sotFeatureAbstract("+name+")::output(vector)::errordot" )

{
  jacobianSOUT.addDependency( jacobianSIN );
  errorSOUT.addDependency( errorSIN );
  // errordotSOUT.addDependency(errordotSIN);
  activationSOUT.addDependency( activationSIN );

  signalRegistration( errorSIN<<jacobianSIN<<activationSIN << errordotSIN << errordotSOUT);
}

/* --------------------------------------------------------------------- */
/* --------------------------------------------------------------------- */
/* --------------------------------------------------------------------- */

unsigned int& FeatureGeneric::
getDimension( unsigned int & dim, int time ) 
{  
  sotDEBUG(25)<<"# In {"<<endl;

  const Flags &fl = selectionSIN.access(time);
  
  if( dimensionDefault==0 )  dimensionDefault = errorSIN.access(time).size();

  dim = 0;
  for( unsigned int i=0;i<dimensionDefault;++i ) if( fl(i) ) dim++;

  sotDEBUG(25)<<"# Out }"<<endl;
  return dim;
}


ml::Vector& FeatureGeneric::
computeError( ml::Vector& res,int time )
{ 
  const ml::Vector& err = errorSIN.access(time);
  const Flags &fl = selectionSIN.access(time);
  const unsigned int & dim = dimensionSOUT(time);

  unsigned int curr = 0;
  res.resize( dim );
  if( err.size()<dim )
    { SOT_THROW ExceptionFeature( ExceptionFeature::UNCOMPATIBLE_SIZE,
				     "Error: dimension uncompatible with des->errorIN size."
				     " (while considering feature <%s>).",getName().c_str() ); }

  FeatureGeneric * sdes = NULL;
  if( desiredValueSIN )
    {
      FeatureAbstract* sdesAbs = desiredValueSIN(time);
      sdes = dynamic_cast<FeatureGeneric*>(sdesAbs);
    }
  
  sotDEBUG(15) << "Err = " << err;
  sotDEBUG(25) << "Dim = " << dim << endl;

  if( sdes )
    {
      const ml::Vector& errDes = sdes->errorSIN(time);
      sotDEBUG(15) << "Err* = " << errDes;
      if( errDes.size()<dim )
	{ SOT_THROW ExceptionFeature( ExceptionFeature::UNCOMPATIBLE_SIZE,
					 "Error: dimension uncompatible with des->errorIN size."
					 " (while considering feature <%s>).",getName().c_str() ); }

      for( unsigned int i=0;i<err.size();++i ) if( fl(i) ) 
	if( fl(i) ) res( curr++ ) = err(i)-errDes(i);
    }
  else for( unsigned int i=0;i<err.size();++i )
    if( fl(i) ) res( curr++ ) = err(i);
  
  return res; 

}

ml::Vector& FeatureGeneric::
computeErrorDot( ml::Vector& res,int time )
{ 
  const Flags &fl = selectionSIN.access(time);
  const unsigned int & dim = dimensionSOUT(time);

  unsigned int curr = 0;
  res.resize( dim );

  FeatureGeneric * sdes = NULL;
  if( desiredValueSIN )
    {
      FeatureAbstract* sdesAbs = desiredValueSIN(time);
      sdes = dynamic_cast<FeatureGeneric*>(sdesAbs);
    }
  
  sotDEBUG(25) << "Dim = " << dim << endl;

  if( sdes )
    {
      const ml::Vector& errdotDes = sdes->errordotSIN(time);
      sotDEBUG(15) << "Err* = " << errdotDes;
      if( errdotDes.size()<dim )
	{ SOT_THROW ExceptionFeature( ExceptionFeature::UNCOMPATIBLE_SIZE,
					 "Error: dimension uncompatible with des->errorIN size."
					 " (while considering feature <%s>).",getName().c_str() ); }

      for( unsigned int i=0;i<errdotDes.size();++i ) if( fl(i) ) 
	if( fl(i) ) res( curr++ ) = errdotDes(i);
    }
  else for( unsigned int i=0;i<dim;++i )
    if( fl(i) ) res( curr++ ) = 0.0;
  
  return res; 

}


ml::Matrix& FeatureGeneric::
computeJacobian( ml::Matrix& res,int time )
{ 
  sotDEBUGIN(15);

  const ml::Matrix& Jac = jacobianSIN.access(time);
  const Flags &fl = selectionSIN.access(time);
  const unsigned int &dim = dimensionSOUT(time);

  unsigned int curr = 0;
  res.resize( dim,Jac.nbCols() );

  for( unsigned int i=0;curr<dim;++i ) 
    if( fl(i) ) 
      {
	for( unsigned int j=0;j<Jac.nbCols();++j ) 
	  res( curr,j ) = Jac(i,j);
	curr++;
      }
  
  sotDEBUGOUT(15);
  return res; 
}

ml::Vector& FeatureGeneric::
computeActivation( ml::Vector& res,int time )
{ 
  if( activationSIN )
    {
      const ml::Vector& err = activationSIN.access(time);
      const Flags &fl = selectionSIN.access(time);
      
      unsigned int curr = 0;
      res.resize( dimensionSOUT(time) );
      for( unsigned int i=0;i<err.size();++i ) if( fl(i) ) res( curr++ ) = err(i);
    }
  else
    {
      res.resize( dimensionSOUT(time) );
      res.fill( 1. );
    }
      
  return res; 
}

/* --------------------------------------------------------------------- */
/* --------------------------------------------------------------------- */
/* --------------------------------------------------------------------- */

void FeatureGeneric::
display( std::ostream& os ) const
{
  os <<"Generic <"<<name<<">: " <<std::endl;

  try{ 
    os << "  error= "<< errorSIN.accessCopy() << endl
       << "  J    = "<< jacobianSIN.accessCopy() << endl
       << "  act  = "<<activationSIN.accessCopy() << endl;
  }  catch(ExceptionAbstract e){ os<< " All SIN not set."; }
}


void FeatureGeneric::
commandLine( const std::string& cmdLine,
	     std::istringstream& cmdArgs,
	     std::ostream& os )
{
  if( cmdLine == "help" )
    {
      os << "FeatureGeneric: " 
	 << "  - dimDefault [<int>]: get/set the dimension value. " << std::endl;
    }
  else if( cmdLine == "dimDefault" )
    {
      cmdArgs >>std::ws; 
      if( cmdArgs.good() )
	{
	  unsigned int val; cmdArgs>>val; 
	  dimensionDefault = val;
	}
      else { os << "dimensionDefault = " << dimensionDefault << std::endl;}
    }
  else { Entity::commandLine( cmdLine,cmdArgs,os); }
}


/*
 * Local variables:
 * c-basic-offset: 2
 * End:
 */