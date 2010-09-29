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

#ifndef __SOT_FEATURE_GENERIC_HH__
#define __SOT_FEATURE_GENERIC_HH__

/* --------------------------------------------------------------------- */
/* --- INCLUDE --------------------------------------------------------- */
/* --------------------------------------------------------------------- */

/* SOT */
#include <sot-core/feature-abstract.h>
#include <sot-core/exception-task.h>

/* --------------------------------------------------------------------- */
/* --- API ------------------------------------------------------------- */
/* --------------------------------------------------------------------- */

#if defined (WIN32)
#  if defined (feature_generic_EXPORTS)
#    define SOTFEATUREGENERIC_EXPORT __declspec(dllexport)
#  else
#    define SOTFEATUREGENERIC_EXPORT __declspec(dllimport)
#  endif
#else
#  define SOTFEATUREGENERIC_EXPORT
#endif

/* --------------------------------------------------------------------- */
/* --- CLASS ----------------------------------------------------------- */
/* --------------------------------------------------------------------- */

namespace sot {
namespace dg = dynamicgraph;

/*!
  \class FeatureGeneric
  \brief Class that defines a generic implementation of the abstract interface for features.

  This class is very useful if the feature can be easily computed using
  the basic operator provided. For instance a free space controller on a end-effector
  is basically directly computed from the Jacobian provided by dyn and some appropriate
  addition and soustraction.
  Instead of building a specific feature for this, it is possible to use the signals
  and plug the computed error, Jacobian and activation to the input of this
  generic feature implementation.

*/
class SOTFEATUREGENERIC_EXPORT FeatureGeneric
: public FeatureAbstract
{

 public:
  /*! Field storing the class name. */
  static const std::string CLASS_NAME;
  /*! Returns the name of the class. */
  virtual const std::string& getClassName( void ) const { return CLASS_NAME; }

 protected:
  unsigned int dimensionDefault;

  /* --- SIGNALS ------------------------------------------------------------ */
 public:
  /*! \name dg::Signals
    @{
  */
  /*! \name Input signals
    @{
   */
  /*! \brief Input for the error. */
  dg::SignalPtr< ml::Vector,int > errorSIN;

  /*! \brief Input for the errordot. */
  dg::SignalPtr< ml::Vector,int > errordotSIN;

  /*! \brief Input for the Jacobian. */
  dg::SignalPtr< ml::Matrix,int > jacobianSIN;

  /*! \brief Input for the activation. */
  dg::SignalPtr< ml::Vector,int > activationSIN;
  /*! @} */

  /*! \name Output signals
    @{
  */
  /*! \brief Publish the jacobian of the feature according to the robot state. */
  using FeatureAbstract::jacobianSOUT;

  /*! \brief Publish the error between the desired and the current value of the feature. */
  using FeatureAbstract::errorSOUT;

  /*! \brief Publish the activation of this feature. */
  using FeatureAbstract::activationSOUT;

  /*! \brief New signal the errordot. */
  dg::SignalTimeDependent< ml::Vector,int > errordotSOUT;

 public:

  /*! \brief Default constructor */
  FeatureGeneric( const std::string& name );

  /*! \brief Default destructor */
  virtual ~FeatureGeneric( void ) {}

  /*! \brief Get the dimension of the feature. */
  virtual unsigned int& getDimension( unsigned int & dim, int time );

  /*! \name Methods to trigger computation related to this feature.
    @{
  */

  /*! \brief Compute the error between the desired value and the value itself. */
  virtual ml::Vector& computeError( ml::Vector& res,int time );

  /*! \brief Compute the desired doterror of the desired value. */
  virtual ml::Vector& computeErrorDot( ml::Vector& res,int time );

  /*! \brief Compute the Jacobian of the value according to the robot state.. */
  virtual ml::Matrix& computeJacobian( ml::Matrix& res,int time );

  /*! \brief Compute the activation according to the time */
  virtual ml::Vector& computeActivation( ml::Vector& res,int time );
  /*! @} */

  /*! \brief Display the information related to this generic implementation. */
  virtual void display( std::ostream& os ) const;

  void commandLine( const std::string& cmdLine,
		    std::istringstream& cmdArgs,
		    std::ostream& os );


} ;

} // namespace sot


#endif // #ifndef __SOT_FEATURE_GENERIC_HH__

/*
 * Local variables:
 * c-basic-offset: 2
 * End:
 */
