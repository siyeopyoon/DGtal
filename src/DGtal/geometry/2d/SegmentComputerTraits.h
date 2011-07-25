/**
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as
 *  published by the Free Software Foundation, either version 3 of the
 *  License, or  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 **/

#pragma once

/**
 * @file SegmentComputerTraits.h
 * @author Tristan Roussillon (\c
 * tristan.roussillon@liris.cnrs.fr ) Laboratoire d'InfoRmatique en
 * Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS,
 * France
 *
 *
 * @date 2011/07/25
 *
 * Header file for module SegmentComputerTraits.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(SegmentComputerTraits_RECURSES)
#error Recursive header files inclusion detected in SegmentComputerTraits.h
#else // defined(SegmentComputerTraits_RECURSES)
/** Prevents recursive inclusion of headers. */
#define SegmentComputerTraits_RECURSES

#if !defined SegmentComputerTraits_h
/** Prevents repeated inclusion of headers. */
#define SegmentComputerTraits_h



namespace DGtal
{

   struct ForwardSegmentComputer{}; 
   struct BidirectionalSegmentComputer{}; 
   struct DynamicSegmentComputer{}; 
   struct DynamicBidirectionalSegmentComputer{}; 

} // namespace DGtal



//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined SegmentComputerTraits_h

#undef SegmentComputerTraits_RECURSES
#endif // else defined(SegmentComputerTraits_RECURSES)
