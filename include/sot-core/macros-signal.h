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

/* --- GENERIC MACROS ------------------------------------------------------- */
/* --- GENERIC MACROS ------------------------------------------------------- */
/* --- GENERIC MACROS ------------------------------------------------------- */

#define SOT_CALL_SIG(sotName,sotType)          \
  boost::bind(&Signal<sotType,int>::access, \
	      &sotName,_2)

/* --- STATIC MACROS -------------------------------------------------------- */
/* --- STATIC MACROS -------------------------------------------------------- */
/* --- STATIC MACROS -------------------------------------------------------- */

#define SOT_INIT_SIGNAL_1(sotFunction,             \
			  sotArg1,sotArg1Type)     \
boost::bind(&sotFunction,                          \
	    SOT_CALL_SIG(sotArg1,sotArg1Type),_1), \
  sotArg1

#define SOT_INIT_SIGNAL_2(sotFunction,             \
			  sotArg1,sotArg1Type,     \
			  sotArg2,sotArg2Type)     \
boost::bind(&sotFunction,                          \
	    SOT_CALL_SIG(sotArg1,sotArg1Type),     \
	    SOT_CALL_SIG(sotArg2,sotArg2Type),_1), \
  sotArg1<<sotArg2
#define SOT_INIT_SIGNAL_3(sotFunction,             \
			  sotArg1,sotArg1Type,     \
			  sotArg2,sotArg2Type,     \
			  sotArg3,sotArg3Type)     \
boost::bind(&sotFunction,                          \
	    SOT_CALL_SIG(sotArg1,sotArg1Type),     \
	    SOT_CALL_SIG(sotArg2,sotArg2Type),     \
	    SOT_CALL_SIG(sotArg3,sotArg3Type),_1), \
  sotArg1<<sotArg2<<sotArg3

#define SOT_INIT_SIGNAL_4(sotFunction,             \
			  sotArg1,sotArg1Type,     \
			  sotArg2,sotArg2Type,     \
			  sotArg3,sotArg3Type,     \
			  sotArg4,sotArg4Type)     \
boost::bind(&sotFunction,                          \
	    SOT_CALL_SIG(sotArg1,sotArg1Type),     \
	    SOT_CALL_SIG(sotArg2,sotArg2Type),     \
	    SOT_CALL_SIG(sotArg3,sotArg3Type),     \
	    SOT_CALL_SIG(sotArg4,sotArg4Type),_1), \
  sotArg1<<sotArg2<<sotArg3<<sotArg4

#define SOT_INIT_SIGNAL_5(sotFunction,             \
			  sotArg1,sotArg1Type,     \
			  sotArg2,sotArg2Type,     \
			  sotArg3,sotArg3Type,     \
			  sotArg4,sotArg4Type,     \
			  sotArg5,sotArg5Type)     \
boost::bind(&sotFunction,                          \
	    SOT_CALL_SIG(sotArg1,sotArg1Type),     \
	    SOT_CALL_SIG(sotArg2,sotArg2Type),     \
	    SOT_CALL_SIG(sotArg3,sotArg3Type),     \
	    SOT_CALL_SIG(sotArg4,sotArg4Type),     \
	    SOT_CALL_SIG(sotArg5,sotArg5Type),_1), \
  sotArg1<<sotArg2<<sotArg3<<sotArg4<<sotArg5

#define SOT_INIT_SIGNAL_6(sotFunction,             \
			  sotArg1,sotArg1Type,     \
			  sotArg2,sotArg2Type,     \
			  sotArg3,sotArg3Type,     \
			  sotArg4,sotArg4Type,     \
			  sotArg5,sotArg5Type,     \
			  sotArg6,sotArg6Type)     \
boost::bind(&sotFunction,                          \
	    SOT_CALL_SIG(sotArg1,sotArg1Type),     \
	    SOT_CALL_SIG(sotArg2,sotArg2Type),     \
	    SOT_CALL_SIG(sotArg3,sotArg3Type),     \
	    SOT_CALL_SIG(sotArg4,sotArg4Type),     \
	    SOT_CALL_SIG(sotArg5,sotArg5Type),     \
	    SOT_CALL_SIG(sotArg6,sotArg6Type),_1), \
  sotArg1<<sotArg2<<sotArg3<<sotArg4<<sotArg5<<sotArg6

#define SOT_INIT_SIGNAL_7(sotFunction,             \
			  sotArg1,sotArg1Type,     \
			  sotArg2,sotArg2Type,     \
			  sotArg3,sotArg3Type,     \
			  sotArg4,sotArg4Type,     \
			  sotArg5,sotArg5Type,     \
			  sotArg6,sotArg6Type,     \
			  sotArg7,sotArg7Type)     \
boost::bind(&sotFunction,                          \
	    SOT_CALL_SIG(sotArg1,sotArg1Type),     \
	    SOT_CALL_SIG(sotArg2,sotArg2Type),     \
	    SOT_CALL_SIG(sotArg3,sotArg3Type),     \
	    SOT_CALL_SIG(sotArg4,sotArg4Type),     \
	    SOT_CALL_SIG(sotArg5,sotArg5Type),     \
	    SOT_CALL_SIG(sotArg6,sotArg6Type),     \
	    SOT_CALL_SIG(sotArg7,sotArg7Type),_1), \
  sotArg1<<sotArg2<<sotArg3<<sotArg4<<sotArg5<<sotArg6<<sotArg7

/* --- MEMBERS MACROS ------------------------------------------------------- */
/* --- MEMBERS MACROS ------------------------------------------------------- */
/* --- MEMBERS MACROS ------------------------------------------------------- */


#define SOT_MEMBER_SIGNAL_1(sotFunction,             \
			    sotArg1,sotArg1Type)    \
boost::bind(&sotFunction,this,                       \
	    SOT_CALL_SIG(sotArg1,sotArg1Type),_1),   \
  sotArg1

#define SOT_MEMBER_SIGNAL_2(sotFunction,             \
			    sotArg1,sotArg1Type,     \
			    sotArg2,sotArg2Type)     \
boost::bind(&sotFunction,this,                       \
	    SOT_CALL_SIG(sotArg1,sotArg1Type),       \
	    SOT_CALL_SIG(sotArg2,sotArg2Type),_1),   \
  sotArg1<<sotArg2
#define SOT_MEMBER_SIGNAL_5(sotFunction,             \
			    sotArg1,sotArg1Type,     \
			    sotArg2,sotArg2Type,     \
			    sotArg3,sotArg3Type,     \
			    sotArg4,sotArg4Type,     \
			    sotArg5,sotArg5Type)     \
boost::bind(&sotFunction,this,                       \
	    SOT_CALL_SIG(sotArg1,sotArg1Type),       \
	    SOT_CALL_SIG(sotArg2,sotArg2Type),       \
	    SOT_CALL_SIG(sotArg3,sotArg3Type),       \
	    SOT_CALL_SIG(sotArg4,sotArg4Type),       \
	    SOT_CALL_SIG(sotArg5,sotArg5Type),_1),   \
  sotArg1<<sotArg2<<sotArg3<<sotArg4<<sotArg5

#define SOT_MEMBER_SIGNAL_6(sotFunction,             \
			    sotArg1,sotArg1Type,     \
			    sotArg2,sotArg2Type,     \
			    sotArg3,sotArg3Type,     \
			    sotArg4,sotArg4Type,     \
			    sotArg5,sotArg5Type,     \
			    sotArg6,sotArg6Type)     \
boost::bind(&sotFunction,this,                       \
	    SOT_CALL_SIG(sotArg1,sotArg1Type),       \
	    SOT_CALL_SIG(sotArg2,sotArg2Type),       \
	    SOT_CALL_SIG(sotArg3,sotArg3Type),       \
	    SOT_CALL_SIG(sotArg4,sotArg4Type),       \
	    SOT_CALL_SIG(sotArg5,sotArg5Type),       \
	    SOT_CALL_SIG(sotArg6,sotArg6Type),_1),   \
  sotArg1<<sotArg2<<sotArg3<<sotArg4<<sotArg5<<sotArg6
