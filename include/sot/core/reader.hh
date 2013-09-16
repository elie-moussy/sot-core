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

#ifndef __SOT_TRACER_H__
#define __SOT_TRACER_H__

/* --------------------------------------------------------------------- */
/* --- INCLUDE --------------------------------------------------------- */
/* --------------------------------------------------------------------- */

/* STD */
#include <string>
#include <vector>
#include <list>
#include <boost/function.hpp>
#include <fstream>

/* SOT & DG*/
#include <dynamic-graph/signal-base.h>
#include <dynamic-graph/signal-time-dependent.h>
#include <dynamic-graph/signal-ptr.h>
#include <dynamic-graph/entity.h>
#include <dynamic-graph/exception-traces.h>
#include <dynamic-graph/linear-algebra.h>
#include <sot/core/flags.hh>

/* --------------------------------------------------------------------- */
/* --- API ------------------------------------------------------------- */
/* --------------------------------------------------------------------- */

#if defined (WIN32) 
#  if defined (reader_EXPORTS)
#    define SOTREADER_EXPORT __declspec(dllexport)
#  else  
#    define SOTREADER_EXPORT __declspec(dllimport)
#  endif 
#else
#  define SOTREADER_EXPORT
#endif

/* --------------------------------------------------------------------- */
/* --- TRACER ---------------------------------------------------------- */
/* --------------------------------------------------------------------- */

using dynamicgraph::Entity;
using dynamicgraph::SignalPtr;
using dynamicgraph::SignalTimeDependent;
using dynamicgraph::sot::Flags;

class SOTREADER_EXPORT sotReader
: public Entity
{
  DYNAMIC_GRAPH_ENTITY_DECL();
 public: 

  SignalPtr< Flags,int > selectionSIN;
  SignalTimeDependent<dynamicgraph::Vector,int> vectorSOUT;
  SignalTimeDependent<dynamicgraph::Matrix,int> matrixSOUT;

 public:
  sotReader( const std::string n );
  virtual ~sotReader( void ){}

  void load( const std::string& filename );
  void clear( void );
  void rewind( void );

 protected:

  typedef std::list< std::vector<double> > DataType;
  DataType dataSet;
  DataType::const_iterator currentData;
  bool iteratorSet;

  unsigned int nbRows,nbCols;

  dynamicgraph::Vector& getNextData( dynamicgraph::Vector& res, const unsigned int time );
  dynamicgraph::Matrix& getNextMatrix( dynamicgraph::Matrix& res, const unsigned int time );
  void resize(const int & nbRow, const int & nbCol);

 public:
  /* --- PARAMS --- */
  void display( std::ostream& os ) const;
  virtual void initCommands();
};





#endif /* #ifndef __SOT_TRACER_H__ */


