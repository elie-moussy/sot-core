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

#ifndef __SOT_CONSTRAINT_H__
#define __SOT_CONSTRAINT_H__

/* --------------------------------------------------------------------- */
/* --- INCLUDE --------------------------------------------------------- */
/* --------------------------------------------------------------------- */

/* Matrix */
#include <MatrixAbstractLayer/boost.h>
namespace ml = maal::boost;

/* STD */
#include <string>

/* SOT */
#include <sot-core/feature-abstract.h>
#include <sot-core/flags.h>
#include <sot-core/task-abstract.h>
#include <dynamic-graph/all-signals.h>
#include <sot-core/exception-task.h>
#include <sot-core/exception-signal.h>

/* --------------------------------------------------------------------- */
/* --- API ------------------------------------------------------------- */
/* --------------------------------------------------------------------- */

#if defined (WIN32) 
#  if defined (constraint_EXPORTS)
#    define SOTCONSTRAINT_EXPORT __declspec(dllexport)
#  else  
#    define SOTCONSTRAINT_EXPORT __declspec(dllimport)
#  endif 
#else
#  define SOTCONSTRAINT_EXPORT
#endif


namespace sot {
namespace dg = dynamicgraph;

/* --------------------------------------------------------------------- */
/* --- CLASS ----------------------------------------------------------- */
/* --------------------------------------------------------------------- */



class SOTCONSTRAINT_EXPORT Constraint
: public TaskAbstract
{
 protected:
  typedef std::list< dg::Signal<ml::Matrix,int>* > JacobianList;
  JacobianList jacobianList;
  
 public: 
  static const std::string CLASS_NAME;
  virtual const std::string& getClassName( void ) const { return CLASS_NAME; }

 public:
  Constraint( const std::string& n );

  void addJacobian( dg::Signal<ml::Matrix,int>& sig );
  void clearJacobianList( void );

  void setControlSelection( const Flags& act );
  void addControlSelection( const Flags& act );
  void clearControlSelection( void );

  /* --- COMPUTATION --- */
  ml::Matrix& computeJacobian( ml::Matrix& J,int time );

  /* --- DISPLAY ------------------------------------------------------------ */
  SOTCONSTRAINT_EXPORT friend std::ostream& operator<< ( std::ostream& os,const Constraint& t );

  /* --- PARAMS --- */
  virtual void commandLine( const std::string& cmdLine
			    ,std::istringstream& cmdArgs
			    ,std::ostream& os );
};

} // namespace sot



#endif /* #ifndef __SOT_CONSTRAINT_H__ */


