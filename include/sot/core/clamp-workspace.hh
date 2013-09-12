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

#ifndef __SOT_CLAMP_WORKSPACE_HH__
#define __SOT_CLAMP_WORKSPACE_HH__

/* STL */
#include <utility>

/* Matrix */
#include <jrl/mal/malv2.hh>
DECLARE_MAL_NAMESPACE(ml);

/* SOT */
#include <dynamic-graph/entity.h>
#include <sot/core/exception-task.hh>
#include <dynamic-graph/all-signals.h>
#include <sot/core/vector-roll-pitch-yaw.hh>
#include <sot/core/matrix-rotation.hh>
#include <sot/core/matrix-homogeneous.hh>
#include <sot/core/matrix-twist.hh>


/* --------------------------------------------------------------------- */
/* --- API ------------------------------------------------------------- */
/* --------------------------------------------------------------------- */

#if defined (WIN32)
#  if defined (clamp_workspace_EXPORTS)
#    define SOTCLAMPWORKSPACE_EXPORT __declspec(dllexport)
#  else
#    define SOTCLAMPWORKSPACE_EXPORT __declspec(dllimport)
#  endif
#else
#  define SOTCLAMPWORKSPACE_EXPORT
#endif

namespace dynamicgraph { namespace sot {
namespace dg = dynamicgraph;

/* --------------------------------------------------------------------- */
/* --- CLASS ----------------------------------------------------------- */
/* --------------------------------------------------------------------- */

class SOTCLAMPWORKSPACE_EXPORT ClampWorkspace
  : public dg::Entity
{
 public:
  static const std::string CLASS_NAME;
  virtual const std::string& getClassName( void ) const { return CLASS_NAME; }

  /* --- SIGNALS ------------------------------------------------------------ */
 public:

  dg::SignalPtr< MatrixHomogeneous,int > positionrefSIN;
  dg::SignalPtr< MatrixHomogeneous,int > positionSIN;
  dg::SignalTimeDependent< ml::Matrix,int > alphaSOUT;
  dg::SignalTimeDependent< ml::Matrix,int > alphabarSOUT;
  dg::SignalTimeDependent< MatrixHomogeneous,int > handrefSOUT;

 public:

  ClampWorkspace( const std::string& name );
  virtual ~ClampWorkspace( void ) {}

  void update( int time );

  virtual ml::Matrix& computeOutput( ml::Matrix& res, int time );
  virtual ml::Matrix& computeOutputBar( ml::Matrix& res, int time );
  virtual MatrixHomogeneous& computeRef( MatrixHomogeneous& res, int time );

  virtual void display( std::ostream& ) const;
  void commandLine( const std::string& cmdLine,
		    std::istringstream& cmdArgs,
		    std::ostream& os );

 private:

  int timeUpdate;

  ml::Matrix alpha;
  ml::Matrix alphabar;
  MatrixHomogeneous prefMp;
  ml::Vector pd;
  MatrixRotation Rd;
  MatrixHomogeneous handref;

  double beta;
  double scale;
  double dm_min;
  double dm_max;
  double dm_min_yaw;
  double dm_max_yaw;
  double theta_min;
  double theta_max;
  int mode;

  enum {
    FRAME_POINT,
    FRAME_REF
  } frame;

  std::pair<double,double> bounds[3];
};


} /* namespace sot */} /* namespace dynamicgraph */


#endif
