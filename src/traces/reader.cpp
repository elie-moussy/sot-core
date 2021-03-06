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

/* SOT */
#include <sot/core/reader.hh>
#include <sot/core/debug.hh>

#include <boost/bind.hpp>
#include <sstream>
#include <dynamic-graph/factory.h>

using namespace dynamicgraph;
using namespace dynamicgraph::sot;
using namespace std;

DYNAMICGRAPH_FACTORY_ENTITY_PLUGIN(sotReader,"Reader");

/* --------------------------------------------------------------------- */
/* --- CLASS ----------------------------------------------------------- */
/* --------------------------------------------------------------------- */

sotReader::sotReader( const std::string n )
  :Entity(n)
  ,selectionSIN( NULL,"Reader("+n+")::input(flag)::selec" )
   ,vectorSOUT( boost::bind(&sotReader::getNextData,this,_1,_2),
	      sotNOSIGNAL,
	      "Reader("+n+")::vector" )
   ,matrixSOUT( boost::bind(&sotReader::getNextMatrix,this,_1,_2),
		vectorSOUT,
		"Reader("+n+")::matrix" )
   ,dataSet()
   ,currentData()
   ,iteratorSet(false)
  ,nbRows(0),nbCols(0)
{
  signalRegistration( selectionSIN<<vectorSOUT<<matrixSOUT );
  selectionSIN = true;
  vectorSOUT.setNeedUpdateFromAllChildren(true);
}  

/* --------------------------------------------------------------------- */
/* --------------------------------------------------------------------- */
/* --------------------------------------------------------------------- */


void sotReader::
load( const string& filename )
{
  sotDEBUGIN(15);

  std::ifstream datafile( filename.c_str() );
  const unsigned int SIZE=1024;
  char buffer[SIZE]; 
  std::vector<double> newline;
  while( datafile.good() )
    {
      datafile.getline( buffer,SIZE );
      const unsigned int gcount = datafile.gcount(); 
      if( gcount>=SIZE ) { /* TODO read error, line to long. */ }
      std::istringstream iss(buffer);
      newline.clear();
      sotDEBUG(25) << "Get line = '" << buffer << "'" << std::endl;
      while( 1 ) 
	{
	  double x; iss>>x;
	  if(! iss.fail() )newline.push_back(x); else break;
	  sotDEBUG(45) << "New data = " << x  << std::endl;
	}
      if( newline.size()>0 )dataSet.push_back( newline );
    }

  sotDEBUGOUT(15);
}

void sotReader::clear( void )
{
  sotDEBUGIN(15);

  dataSet.clear();
  iteratorSet = false;

  sotDEBUGOUT(15);
}

void sotReader::
rewind( void )
{
  sotDEBUGIN(15);
  iteratorSet = false;
  sotDEBUGOUT(15);
}

ml::Vector& sotReader::
getNextData( ml::Vector& res, const unsigned int time )
{
  sotDEBUGIN(15);

  if(! iteratorSet ) 
    {
      sotDEBUG(15) << "Start the list" << std::endl; 
      currentData = dataSet.begin(); iteratorSet=true;
    }
  else if( currentData!=dataSet.end() ){ ++currentData;  }

  if( currentData==dataSet.end() )
    {
      sotDEBUGOUT(15);
      return res;
    }
   
  const Flags& selection = selectionSIN(time);
  const std::vector<double> & curr =  *currentData;

  unsigned int dim=0;
  for( unsigned int i=0;i<curr.size();++i ) if( selection(i) ) dim++;

  res.resize(dim);
  unsigned int cursor=0;
  for( unsigned int i=0;i<curr.size();++i ) 
    if( selection(i) ) res(cursor++)=curr[i];
  
  sotDEBUGOUT(15);
  return res;
}

ml::Matrix& sotReader::
getNextMatrix( ml::Matrix& res, const unsigned int time )
{
  sotDEBUGIN(15);
  const ml::Vector& vect = vectorSOUT(time);
  if( vect.size()<nbRows*nbCols ) return res;

  res.resize( nbRows,nbCols );
  for( unsigned int i=0;i<nbRows;++i )
    for( unsigned int j=0;j<nbCols;++j )
      res(i,j)=vect(i*nbCols+j);

  sotDEBUGOUT(15);
  return res;
}
/* --------------------------------------------------------------------- */
/* --------------------------------------------------------------------- */
/* --------------------------------------------------------------------- */


void sotReader::
display( std::ostream& os ) const
{
  os << CLASS_NAME << " " << name << endl;
}


std::ostream& operator<< ( std::ostream& os,const sotReader& t )
{
  t.display(os);
  return os;
}

void sotReader::
commandLine( const std::string& cmdLine
	     ,std::istringstream& cmdArgs
	     ,std::ostream& os )
{
  if( cmdLine=="help" )
    {
      os << "Reader: "<<endl
	 << "  - load" << endl;
	
      Entity::commandLine( cmdLine,cmdArgs,os );
    }
  else if( cmdLine=="load" )
    {
      string filename;
      cmdArgs>>ws>>filename;
      load(filename);
    }
  else if( cmdLine=="rewind" )
    {
      cmdArgs>>ws;
      rewind( );
    }
  else if( cmdLine=="clear" )
    {
      cmdArgs>>ws;
      clear( );
    }
  else if( cmdLine=="resize" )
    {
      cmdArgs >>ws;
      if( cmdArgs.good() ) { cmdArgs >> nbRows >>nbCols; }
      else {  os << "Matrix size = " << nbRows << " x " <<nbCols <<std::endl; }
    }
  else { Entity::commandLine( cmdLine,cmdArgs,os ); }



}
