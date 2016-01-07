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
 * @file KhalimskySpaceND.h
 * @author Jacques-Olivier Lachaud (\c jacques-olivier.lachaud@univ-savoie.fr )
 * Laboratory of Mathematics (CNRS, UMR 5807), University of Savoie, France
 * @author Roland Denis (\c roland.denis@univ-smb.fr )
 * Laboratory of Mathematics (CNRS, UMR 5807), University of Savoie, France
 *
 * @date 2011/02/08
 *
 * Header file for module KhalimskySpaceND.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(KhalimskySpaceND_RECURSES)
#error Recursive header files inclusion detected in KhalimskySpaceND.h
#else // defined(KhalimskySpaceND_RECURSES)
/** Prevents recursive inclusion of headers. */
#define KhalimskySpaceND_RECURSES

#if !defined KhalimskySpaceND_h
/** Prevents repeated inclusion of headers. */
#define KhalimskySpaceND_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include <set>
#include <map>
#include "DGtal/base/Common.h"
#include "DGtal/kernel/CInteger.h"
#include "DGtal/kernel/PointVector.h"
#include "DGtal/kernel/SpaceND.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{

  /**
     @brief Represents an (unsigned) cell in a cellular grid space by its
     Khalimsky coordinates.
  */
  template < Dimension dim,
             typename TInteger = DGtal::int32_t >
  struct KhalimskyCell
  {

    //Integer must be a model of the concept CInteger.
    BOOST_CONCEPT_ASSERT(( concepts::CInteger<TInteger> ) );

  public:
    typedef TInteger Integer;

    typedef typename NumberTraits<Integer>::UnsignedVersion UnsignedInteger;
    typedef PointVector< dim, Integer > Point;

    Point myCoordinates;

    /**
     * Constructor.
     */
    KhalimskyCell( Integer dummy = 0 );

    /**
     * Copy constructor.
     *
     * @param other any other cell.
     */
    KhalimskyCell( const KhalimskyCell & other );

    /**
     * Constructor from point.
     *
     * @param point any point.
     */
    KhalimskyCell( const Point & point );

    /**
     * Copy constructor.
     *
     * @param other any other cell.
     */
    KhalimskyCell & operator=( const KhalimskyCell & other );

    /**
       Equality operator.
       @param other any other cell.
    */
    bool operator==( const KhalimskyCell & other ) const;

    /**
       Difference operator.
       @param other any other cell.
    */
    bool operator!=( const KhalimskyCell & other ) const;

    /**
       Inferior operator. (lexicographic order).
       @param other any other cell.
    */
    bool operator<( const KhalimskyCell & other ) const;

    // --------------- CDrawableWithBoard2D realization -------------------
  public:

    /**
     * Default drawing style object.
     * @return the dyn. alloc. default style for this object.
     */
    //DrawableWithBoard2D* defaultStyle( std::string mode = "" ) const;

    /**
     * @return the style name used for drawing this object.
     */
    std::string className() const;

  };

  template < Dimension dim,
             typename TInteger >
  std::ostream &
  operator<<( std::ostream & out,
              const KhalimskyCell< dim, TInteger > & object );

  /**
     @brief Represents a signed cell in a cellular grid space by its
     Khalimsky coordinates and a boolean value.
  */
  template < Dimension dim,
             typename TInteger = DGtal::int32_t >
  struct SignedKhalimskyCell
  {
    //Integer must be a model of the concept CInteger.
    BOOST_CONCEPT_ASSERT(( concepts::CInteger<TInteger> ) );

  public:
    typedef TInteger Integer;
    typedef typename NumberTraits<Integer>::UnsignedVersion UnsignedInteger;
    typedef PointVector< dim, Integer > Point;

    Point myCoordinates;
    bool myPositive;

    /**
     * Constructor.
     */
    SignedKhalimskyCell( Integer dummy = 0 );

    /**
     * Copy constructor.
     *
     * @param other any other cell.
     */
    SignedKhalimskyCell( const SignedKhalimskyCell & other );

    /**
     * Constructor from point.
     *
     * @param point any point.
     * @param positive if cell has positive sign.
     */
    SignedKhalimskyCell( const Point & point, bool positive );

    /**
     * Copy constructor.
     *
     * @param other any other cell.
     */
    SignedKhalimskyCell & operator=( const SignedKhalimskyCell & other );

    /**
       Equality operator.
       @param other any other cell.
    */
    bool operator==( const SignedKhalimskyCell & other ) const;

    /**
       Difference operator.
       @param other any other cell.
    */
    bool operator!=( const SignedKhalimskyCell & other ) const;

    /**
       Inferior operator. (lexicographic order).
       @param other any other cell.
    */
    bool operator<( const SignedKhalimskyCell & other ) const;

    // --------------- CDrawableWithBoard2D realization -------------------
  public:

    /**
     * Default drawing style object.
     * @return the dyn. alloc. default style for this object.
     */
    //DrawableWithBoard2D* defaultStyle( std::string mode = "" ) const;

    /**
     * @return the style name used for drawing this object.
     */
    std::string className() const;

  };

  template < Dimension dim,
             typename TInteger >
  std::ostream &
  operator<<( std::ostream & out,
              const SignedKhalimskyCell< dim, TInteger > & object );

  /**
     @brief This class is useful for looping on all "interesting" coordinates of a
     cell. For instance, surfels in Z3 have two interesting coordinates (the
     ones spanned by the surfel).
     @code
     KSpace::Cell p;
     KnSpace::DirIterator q;
     for ( q = ks.uDirs( p ); q != 0; ++q )
     {
     KSpace::Dimension dir = *q;
     ...
     }
     @endcode
  */
  template < Dimension dim,
             typename TInteger = DGtal::int32_t >
  class CellDirectionIterator
  {
  public:
    typedef TInteger Integer;
    // Cells
    typedef KhalimskyCell< dim, Integer > Cell;
    typedef SignedKhalimskyCell< dim, Integer > SCell;

  public:
    /**
     * Constructor from cell.
     * @param cell any unsigned cell
     */
    CellDirectionIterator( Cell cell, bool open = true );

    /**
     * Constructor from signed cell.
     * @param scell any signed cell
     */
    CellDirectionIterator( SCell scell, bool open = true );

    /**
     * @return the current direction.
     */
    Dimension operator*() const;

    /**
     * Pre-increment. Go to next direction.
     */
    CellDirectionIterator & operator++();

    /**
     * Fast comparison with unsigned integer (unused
     * parameter). Comparison is 'false' at the end of the iteration.
     *
     * @return 'true' if the iterator is finished.
     */
    bool operator!=( const Integer ) const;

    /**
     * @return 'true' if the iteration is ended.
     */
    bool end() const;

    /**
     * Slow comparison with other iterator. Useful to check for end of loop.
     * @param other any direction iterator.
     */
    bool operator!=( const CellDirectionIterator & other ) const;

    /**
     * Slow comparison with other iterator.
     * @param other any direction iterator.
     */
    bool operator==( const CellDirectionIterator & other ) const;

  private:
    /** the current direction. */
    Dimension myDir;
    /** the cell. */
    Cell myCell;
    /** If 'true', returns open coordinates, otherwise returns closed
        coordinates. */
    bool myOpen;

  private:
    /** Look for next valid coordinate. */
    void find();
  };

  /////////////////////////////////////////////////////////////////////////////
  /** Internal class of KhalimskySpaceND that provides some optimizations
   * depending on the space type.
   */
  template < class TKhalimskySpace >
  class KhalimskySpaceNDHelper;

  /////////////////////////////////////////////////////////////////////////////
  // template class KhalimskySpaceND
  /**
   * Description of template class 'KhalimskySpaceND' <p>
   *
   * \brief Aim: This class is a model of CCellularGridSpaceND. It
   * represents the cubical grid as a cell complex, whose cells are
   * defined as an array of integers. The topology of the cells is
   * defined by the parity of the coordinates (even: closed, odd:
   * open).
   *
   * When \b initializing the space using init(),
   * the user should choose, for each dimension spanned by the space,
   * between a closed and non-periodic (default) cell dimension,
   * an open cell dimension or a periodic cell dimension.
   * The space is generally finite, except for arbitrary size
   * integers and when the space has a periodic dimension.
   *
   * Supposing that the space has been initialized with digital bounds \c lower and \c upper,
   * the methods lowerBound() and upperBound() will always return, respectively, \c lower and \c upper.
   * It as also true for periodic dimension, in order to span over the unique digital points of the space.
   *
   * In the same way, lowerCell() and upperCell() respect the following rules:
   * - the k-th Khalimsky coordinate of lowerCell() is equal to:
   *    - `2*lower[k]` if the k-th dimension is closed or periodic,
   *    - `2*lower[k]+1` if the k-th dimension is open;
   * - the k-th Khalimsky coordinate of upperCell() is equal to:
   *    - `2*upper[k]+2` if the k-th dimension is closed,
   *    - `2*upper[k]+1` if the k-th dimension is open or periodic.
   *    .
   * .
   * The special behavior for __periodic dimensions__ guarantees that each cell has unique
   * Khalimsky coordinates in this range.
   * It is useful to span the space and also for cell-based containers (see e.g. CubicalComplex).
   * Uniqueness also gives meaning to equality tests between cells.
   *
   * Following this concept, the related methods size(), min(), max(),
   * uFirst(), uLast(), uGetMin(), uGetMax(), uDistanceToMin(), uDistanceToMax(),
   * sFirst(), sLast(), sGetMin(), sGetMax(), sDistanceToMin() and sDistanceToMax()
   * behave for periodic dimensions like for finite dimensions, using the bounds described above.
   *
   * Thus, if a cell needs to be __compared to the bounds__, prefer using dedicated tests like
   * uIsMin(), uIsMax(), sIsMin() and sIsMax() that return always \c false for a periodic dimension,
   * and uIsInside() and sIsInside() that return always \c true for a periodic dimension.
   *
   * To be consistent with those choices, each cell returned or modified by a KhalimskySpaceND method
   * will have his Khalimsky coordinates along periodic dimensions between the corresponding
   * coordinates of lowerCell() and upperCell().
   * But, in order to keep low computational cost, each cell passed by parameter to a KhalimskySpaceND
   * method must follow the same conditions.
   * This validity can be tested with the dedicated methods uIsValid() and sIsValid().
   *
   * Exceptions exist for uCell(const Cell &) const and sCell(const SCell &) const that are specially featured
   * to correct Khalimsky coordinates of a given cell.
   * In addition, methods returning digital or Khalimsky coordinate of a cell have a flag to control if this
   * coordinate must be corrected.
   * However, when a method accepts a coordinate as parameter, it is always corrected along periodic dimensions.
   *
   * @tparam dim the dimension of the digital space.
   * @tparam TInteger the Integer class used to specify the arithmetic computations (default type = int32).
   * @note Essentially a backport from [ImaGene](https://gforge.liris.cnrs.fr/projects/imagene).
   *
   * @warning Periodic Khalimsky space and per-dimension closure specification are new features.
   * Therefore, there is no guarantee that it is compatible with the whole DGtal library.
   *
  */
  template < Dimension dim,
             typename TInteger = DGtal::int32_t >
  class KhalimskySpaceND
    : private KhalimskySpaceNDHelper< KhalimskySpaceND< dim, TInteger > >
  {

    typedef KhalimskySpaceNDHelper< KhalimskySpaceND< dim, TInteger > > Helper; ///< Features basic operations on coordinates, especially for periodic dimensions.
    friend class KhalimskySpaceNDHelper< KhalimskySpaceND< dim, TInteger > >;

    //Integer must be signed to characterize a ring.
    BOOST_CONCEPT_ASSERT(( concepts::CInteger<TInteger> ) );

  public:
    ///Arithmetic ring induced by (+,-,*) and Integer numbers.
    typedef TInteger Integer;

    ///Type used to represent sizes in the digital space.
    typedef typename NumberTraits<Integer>::UnsignedVersion Size;

    // Cells
    typedef KhalimskyCell< dim, Integer > Cell;
    typedef SignedKhalimskyCell< dim, Integer > SCell;
    typedef SCell Surfel;
    typedef bool Sign;
    typedef CellDirectionIterator< dim, Integer > DirIterator;

    //Points and Vectors
    typedef PointVector< dim, Integer > Point;
    typedef PointVector< dim, Integer > Vector;

    typedef SpaceND<dim, Integer> Space;
    typedef KhalimskySpaceND<dim, Integer> KhalimskySpace;

#if defined ( WIN32 )
    // static constants
    static const Dimension dimension = dim;
    static const Dimension DIM = dim;
    static const Sign POS = true;
    static const Sign NEG = false;
#else
    // static constants
    static const Dimension dimension = dim;
    static const Dimension DIM;
    static const Sign POS;
    static const Sign NEG;
#endif //WIN32

    template <typename CellType>
    struct AnyCellCollection : public std::deque<CellType> {
      typedef CellType Value;
      typedef typename std::deque<CellType> Container;
      typedef typename std::deque<CellType>::iterator Iterator;
      typedef typename std::deque<CellType>::const_iterator ConstIterator;
    };

    // Neighborhoods, Incident cells, Faces and Cofaces
    typedef AnyCellCollection<Cell> Cells;
    typedef AnyCellCollection<SCell> SCells;

    // Sets, Maps
    /// Preferred type for defining a set of Cell(s).
    typedef std::set<Cell> CellSet;
    /// Preferred type for defining a set of SCell(s).
    typedef std::set<SCell> SCellSet;
    /// Preferred type for defining a set of surfels (always signed cells).
    typedef std::set<SCell> SurfelSet;
    /// Template rebinding for defining the type that is a mapping
    /// Cell -> Value.
    template <typename Value> struct CellMap {
      typedef std::map<SCell,Value> Type;
    };
    /// Template rebinding for defining the type that is a mapping
    /// SCell -> Value.
    template <typename Value> struct SCellMap {
      typedef std::map<SCell,Value> Type;
    };
    /// Template rebinding for defining the type that is a mapping
    /// SCell -> Value.
    template <typename Value> struct SurfelMap {
      typedef std::map<SCell,Value> Type;
    };

    /// Boundaries closure type
    enum Closure
      {
        closed,   ///< The dimension is closed and non-periodic.
        open,     ///< The dimension is open.
        periodic  ///< The dimension is periodic.
      };

    // ----------------------- Standard services ------------------------------
    /** @name Standard services
     * @{
     */
  public:

    /**
     * Destructor.
     */
    ~KhalimskySpaceND();

    /**
     * Default onstructor.
     */
    KhalimskySpaceND();

    /**
     * Copy constructor.
     * @param other the object to clone.
     */
    KhalimskySpaceND ( const KhalimskySpaceND & other );

    /**
     * Assignment.
     * @param other the object to copy.
     * @return a reference on 'this'.
     */
    KhalimskySpaceND & operator= ( const KhalimskySpaceND & other );

    /**
     * Specifies the upper and lower bounds for the maximal cells in
     * this space.
     *
     * @param lower the lowest point in this space (digital coords)
     * @param upper the upper point in this space (digital coords)
     * @param isClosed 'true' if this space is closed and non-periodic in every dimension, 'false' if open.
     *
     * @return true if the initialization was valid (ie, such bounds
     * are representable with these integers).
     */
    bool init( const Point & lower,
               const Point & upper,
               bool isClosed );

    /**
     * Specifies the upper and lower bounds for the maximal cells in
     * this space.
     *
     * @param lower the lowest point in this space (digital coords)
     * @param upper the upper point in this space (digital coords)
     * @param closure \a closed, \a open or \a periodic if this space is resp. closed (and non-periodic),
     *        open or periodic in every dimension.
     *
     * @return true if the initialization was valid (ie, such bounds
     * are representable with these integers).
     */
    bool init( const Point & lower,
               const Point & upper,
               Closure closure );

    /**
     * Specifies the upper and lower bounds for the maximal cells in
     * this space.
     *
     * @param lower the lowest point in this space (digital coords)
     * @param upper the upper point in this space (digital coords)
     * @param closure an array of \a closed, \a open or \a periodic if this space is resp. closed (and non-periodic),
     *        open or periodic in the corresponding dimension.
     *
     * @return true if the initialization was valid (ie, such bounds
     * are representable with these integers).
     */
    bool init( const Point & lower,
               const Point & upper,
               Closure closure[dim] );

    /// @}

    // ------------------------- Basic services ------------------------------
    /** @name Basic services
     * @{
     */
  public:

    /**
     * @param k a coordinate (from 0 to 'dim()-1').
     * @return the width of the space in the [k]-dimension.
     * @note for periodic dimension, it returns the number of unique coordinates along that dimension.
     */
    Size size( Dimension k ) const;

    /**
     * @param k a coordinate (from 0 to 'dim()-1').
     * @return the minimal coordinate in the [k]-dimension.
     */
    Integer min( Dimension k ) const;

    /**
     * @param k a coordinate (from 0 to 'dim()-1').
     * @return the maximal coordinate in the [k]-dimension.
     */
    Integer max( Dimension k ) const;

    /**
     * @return the lower bound for digital points in this space.
     */
    const Point & lowerBound() const;

    /**
     * @return the upper bound for digital points in this space.
     */
    const Point & upperBound() const;

    /**
     * @return the lower bound for cells in this space.
     * @todo doc for periodic
     */
    const Cell & lowerCell() const;

    /**
     * @return the upper bound for cells in this space.
     * @todo doc for periodic
     */
    const Cell & upperCell() const;

    /**
     * @param c a signed cell.
     * @param k a dimension.
     * @returns \c true if the given unsigned cell has his k-th Khalimsky coordinate
     * between those of the cells returned by lowerCell and upperCell.
     * @note For periodic dimension, even if there is no bounds, it guarantees that
     * each cell has unique coordinates.
     */
    bool uIsValid( const Cell & c, Dimension k ) const;
    
    /**
     * @param c a signed cell.
     * @returns \c true if the given unsigned cell has Khalimsky coordinates
     * between those of the cells returned by lowerCell and upperCell.
     * @note For periodic dimension, even if there is no bounds, it guarantees that
     * each cell has unique coordinates.
     */
    bool uIsValid( const Cell & c ) const;

    /**
     * @param c an unsigned cell.
     * @param k a dimension.
     * @returns \c true if the given signed cell his k-th Khalimsky coordinate
     * between those of the cells returned by lowerCell and upperCell.
     * @note For periodic dimension, even if there is no bounds, it guarantees that
     * each cell has unique coordinates.
     */
    bool sIsValid( const SCell & c, Dimension k ) const;
    
    /**
     * @param c an unsigned cell.
     * @returns \c true if the given signed cell has Khalimsky coordinates
     * between those of the cells returned by lowerCell and upperCell.
     * @note For periodic dimension, even if there is no bounds, it guarantees that
     * each cell has unique coordinates.
     */
    bool sIsValid( const SCell & c ) const;

    /// @}

    // ----------------------- Closure type query --------------------------
    /** @name Closure type query
     *  @{
     */
  public:

    /**
     * @return 'true' iff the space is closed or periodic along every dimension.
     */
    bool isSpaceClosed() const;

    /**
     * @param k the dimension.
     * @return 'true' iff the space is closed or periodic along the specified dimension.
     */
    bool isSpaceClosed( Dimension k ) const;

    /**
     * @return 'true' iff the space is periodic along every dimension.
     */
    bool isSpacePeriodic() const;

    /**
     * @param k the dimension.
     * @return 'true' iff the space is periodic along the specified dimension.
     */
    bool isSpacePeriodic( Dimension k ) const;

    /**
     * @return 'true' iff the space is periodic along at least one dimension.
     */
    bool isAnyDimensionPeriodic() const;

    /** Gets closure type.
     * @param k the dimension.
     * @return closure type along the specified dimension.
     */
    Closure getClosure( Dimension k ) const;

    /// @}

    // ----------------------- Cell creation services --------------------------
    /** @name Cell creation services
     * @{
     */
  public:

    /**
     * From a cell, returns the same cell with appropriate
     * Khalimsky coordinates when the space has periodic
     * dimension.
     *
     * This is only useful for convertion between non-periodic
     * and periodic Khalimsky spaces.
     *
     * @note For periodic dimension, the corresponding Khalimsky coordinate
     * of the returned cell lies into the fundamental domain.
     *
     * @param c a cell.
     * @return the same cell with appropriate Khalimsky coordinates
     *         along periodic dimensions.
     */
    Cell uCell( const Cell & c ) const;

    /**
     * From the Khalimsky coordinates of a cell, builds the
     * corresponding unsigned cell.
     *
     * @note For periodic dimension, the corresponding Khalimsky coordinate
     * of the returned cell lies into the fundamental domain.
     *
     * @param kp an integer point (Khalimsky coordinates of cell).
     * @return the unsigned cell.
     */
    Cell uCell( const Point & kp ) const;

    /**
     * From the digital coordinates of a point in Zn and a cell type,
     * builds the corresponding cell.
     *
     * @note For periodic dimension, the corresponding Khalimsky coordinate
     * of the returned cell lies into the fundamental domain.
     *
     * @param p an integer point (digital coordinates of cell).
     * @param c another cell defining the topology.
     * @return the cell having the topology of [c] and the given
     * digital coordinates [p].
     */
    Cell uCell( Point p, const Cell & c ) const;

    /**
     * From a signed cell, returns the same signed cell with
     * appropriate Khalimsky coordinates when the space has
     * periodic dimension.
     *
     * This is only useful for convertion between non-periodic
     * and periodic Khalimsky spaces.
     *
     * @note For periodic dimension, the corresponding Khalimsky coordinate
     * of the returned cell lies into the fundamental domain.
     *
     * @param c a signed cell.
     * @return the same signed cell with appropriate Khalimsky coordinates
     *          along periodic dimensions.
     */
    SCell sCell( const SCell & c ) const;

    /**
     * From the Khalimsky coordinates of a cell and a sign, builds the
     * corresponding unsigned cell.
     *
     * @note For periodic dimension, the corresponding Khalimsky coordinate
     * of the returned cell lies into the fundamental domain.
     *
     * @param kp an integer point (Khalimsky coordinates of cell).
     * @param sign the sign of the cell (either POS or NEG).
     * @return the signed cell.
     */
    SCell sCell( const Point & kp, Sign sign = POS ) const;

    /**
     * From the digital coordinates of a point in Zn and a signed cell
     * type, builds the corresponding signed cell.
     *
     * @note For periodic dimension, the corresponding Khalimsky coordinate
     * of the returned cell lies into the fundamental domain.
     *
     * @param p an integer point (digital coordinates of cell).
     * @param c another cell defining the topology and sign.
     *
     * @return the cell having the topology and sign of [c] and the given
     * digital coordinates [p].
     */
    SCell sCell( Point p, const SCell & c ) const;

    /**
     * From the digital coordinates of a point in Zn, creates the spel
     * (cell of maximal dimension) with these coordinates.
     *
     * @note For periodic dimension, the corresponding Khalimsky coordinate
     * of the returned cell lies into the fundamental domain.
     *
     * @param p an integer point (digital coordinates of cell).
     *
     * @return the spel having the given digital coordinates [p].
     */
    Cell uSpel( Point p ) const;

    /**
     * From the digital coordinates of a point in Zn, creates the spel
     * (cell of maximal dimension) with these coordinates.
     *
     * @note For periodic dimension, the corresponding Khalimsky coordinate
     * of the returned cell lies into the fundamental domain.
     *
     * @param p an integer point (digital coordinates of cell).
     * @param sign the sign of the cell (either POS or NEG).
     *
     * @return the signed spel having the given digital coordinates [p].
     */
    SCell sSpel( Point p, Sign sign = POS ) const;

    /**
     * From the digital coordinates of a point in Zn, creates the pointel
     * (cell of dimension 0) with these coordinates.
     *
     * @note For periodic dimension, the corresponding Khalimsky coordinate
     * of the returned cell lies into the fundamental domain.
     *
     * @param p an integer point (digital coordinates of cell).
     *
     * @return the pointel having the given digital coordinates [p].
     */
    Cell uPointel( Point p ) const;

    /**
     * From the digital coordinates of a point in Zn, creates the pointel
     * (cell of dimension 0) with these coordinates.
     *
     * @note For periodic dimension, the corresponding Khalimsky coordinate
     * of the returned cell lies into the fundamental domain.
     *
     * @param p an integer point (digital coordinates of cell).
     * @param sign the sign of the cell (either POS or NEG).
     *
     * @return the signed pointel having the given digital coordinates [p].
     */
    SCell sPointel( Point p, Sign sign = POS ) const;

    ///@}

    // ----------------------- Read accessors to cells ------------------------
    /** @name Read accessors to cells
     * @{
     */
  public:
    /**
     * @param c any unsigned cell.
     * @param k any valid dimension.
     * @param correct if set to 'true', the coordinate is corrected if \a k is a periodic dimension.
     * @return its Khalimsky coordinate along [k], corrected to lie into the fundamental domain if
     *         the dimension is periodic and if \a correct is set to 'true'.
     *
     * @note it is not needed to set \a correct to 'true' if the cell \a c has been
     * created and modified by the methods of this KhalimskySpaceND instance.
     */
    Integer uKCoord( const Cell & c, Dimension k, bool correct = false ) const;

    /**
     * @param c any unsigned cell.
     * @param k any valid dimension.
     * @param correct if set to 'true', the coordinate is corrected if \a k is a periodic dimension.
     * @return its digital coordinate along [k], corrected to lie into the fundamental domain if
     *         the dimension is periodic and if \a correct is set to 'true'.
     *
     * @note it is not needed to set \a correct to 'true' if the cell \a c has been
     * created and modified by the methods of this KhalimskySpaceND instance.
     */
    Integer uCoord( const Cell & c, Dimension k, bool correct = false ) const;

    /**
     * @param c any unsigned cell.
     * @param correct is set to 'true', the coordinates are corrected for periodic dimensions.
     * @return its Khalimsky coordinates, corrected to lie into the fundamental domain
     * for periodic dimensions if \a correct is set to 'true'.
     *
     * @note it is not needed to set \a correct to 'true' if the cell \a c has been
     * created and modified by the methods of this KhalimskySpaceND instance.
     */
    Point uKCoords( const Cell & c, bool correct = false ) const;

    /**
     * @param c any unsigned cell.
     * @param correct is set to 'true', the coordinates are corrected for periodic dimensions.
     * @return its digital coordinates, corrected to lie into the fundamental domain
     * for periodic dimensions if \a correct is set to 'true'.
     *
     * @note it is not needed to set \a correct to 'true' if the cell \a c has been
     * created and modified by the methods of this KhalimskySpaceND instance.
     */
    Point uCoords( const Cell & c, bool correct = false ) const;

    /**
     * @param c any signed cell.
     * @param k any valid dimension.
     * @param correct if set to 'true', the coordinate is corrected if \a k is a periodic dimension.
     * @return its Khalimsky coordinate along [k], corrected to lie into the fundamental domain if
     *         the dimension is periodic and if \a correct is set to 'true'.
     *
     * @note it is not needed to set \a correct to 'true' if the cell \a c has been
     * created and modified by the methods of this KhalimskySpaceND instance.
     */
    Integer sKCoord( const SCell & c, Dimension k, bool correct = false ) const;

    /**
     * @param c any signed cell.
     * @param k any valid dimension.
     * @param correct if set to 'true', the coordinate is corrected if \a k is a periodic dimension.
     * @return its digital coordinate along [k], corrected to lie into the fundamental domain if
     *         the dimension is periodic and if \a correct is set to 'true'.
     *
     * @note it is not needed to set \a correct to 'true' if the cell \a c has been
     * created and modified by the methods of this KhalimskySpaceND instance.
     */
    Integer sCoord( const SCell & c, Dimension k, bool correct = false ) const;

    /**
     * @param c any signed cell.
     * @param correct is set to 'true', the coordinates are corrected for periodic dimensions.
     * @return its Khalimsky coordinates, corrected to lie into the fundamental domain
     * for periodic dimensions if \a correct is set to 'true'.
     *
     * @note it is not needed to set \a correct to 'true' if the cell \a c has been
     * created and modified by the methods of this KhalimskySpaceND instance.
     */
    Point sKCoords( const SCell & c, bool correct = false ) const;

    /**
     * @param c any signed cell.
     * @param correct is set to 'true', the coordinates are corrected for periodic dimensions.
     * @return its digital coordinates, corrected to lie into the fundamental domain
     * for periodic dimensions if \a correct is set to 'true'.
     *
     * @note it is not needed to set \a correct to 'true' if the cell \a c has been
     * created and modified by the methods of this KhalimskySpaceND instance.
     */
    Point sCoords( const SCell & c, bool correct = false ) const;

    /**
     * @param c any signed cell.
     * @return its sign.
     */
    Sign sSign( const SCell & c ) const;

    /// @}

    // ----------------------- Write accessors to cells ------------------------
    /** @name Write accessors to cells
     * @{
     */
  public:

    /**
     * Sets the [k]-th Khalimsky coordinate of [c] to [i].
     * @param c any unsigned cell.
     * @param k any valid dimension.
     * @param i an integer coordinate within the space.
     */
    void uSetKCoord( Cell & c, Dimension k, Integer i ) const;

    /**
     * Sets the [k]-th Khalimsky coordinate of [c] to [i].
     * @param c any signed cell.
     * @param k any valid dimension.
     * @param i an integer coordinate within the space.
     */
    void sSetKCoord( SCell & c, Dimension k, Integer i ) const;

    /**
     * Sets the [k]-th digital coordinate of [c] to [i].
     * @param c any unsigned cell.
     * @param k any valid dimension.
     * @param i an integer coordinate within the space.
     */
    void uSetCoord( Cell & c, Dimension k, Integer i ) const;

    /**
     * Sets the [k]-th digital coordinate of [c] to [i].
     * @param c any signed cell.
     * @param k any valid dimension.
     * @param i an integer coordinate within the space.
     */
    void sSetCoord( SCell & c, Dimension k, Integer i ) const;

    /**
     * Sets the Khalimsky coordinates of [c] to [kp].
     * @param c any unsigned cell.
     * @param kp the new Khalimsky coordinates for [c].
     */
    void uSetKCoords( Cell & c, const Point & kp ) const;

    /**
     * Sets the Khalimsky coordinates of [c] to [kp].
     * @param c any signed cell.
     * @param kp the new Khalimsky coordinates for [c].
     */
    void sSetKCoords( SCell & c, const Point & kp ) const;

    /**
     * Sets the digital coordinates of [c] to [kp].
     * @param c any unsigned cell.
     * @param kp the new Khalimsky coordinates for [c].
     */
    void uSetCoords( Cell & c, const Point & kp ) const;

    /**
     * Sets the digital coordinates of [c] to [kp].
     * @param c any signed cell.
     * @param kp the new Khalimsky coordinates for [c].
     */
    void sSetCoords( SCell & c, const Point & kp ) const;

    /**
     * Sets the sign of the cell.
     * @param c (modified) any signed cell.
     * @param s any sign.
     */
    void sSetSign( SCell & c, Sign s ) const;

    /// @}

    // -------------------- Conversion signed/unsigned ------------------------
    /** @name Conversion signed/unsigned
     * @{
     */
  public:
    /**
     * Creates a signed cell from an unsigned one and a given sign.
     * @param p any unsigned cell.
     * @param s a sign.
     * @return the signed version of the cell [p] with sign [s].
     */
    SCell signs( const Cell & p, Sign s ) const;

    /**
     * Creates an unsigned cell from a signed one.
     * @param p any signed cell.
     * @return the unsigned version of the cell [p].
     */
    Cell unsigns( const SCell & p ) const;

    /**
     * Creates the signed cell with the inverse sign of [p].
     * @param p any signed cell.
     * @return the cell [p] with opposite sign.
     */
    SCell sOpp( const SCell & p ) const;

    /// @}

    // ------------------------- Cell topology services -----------------------
    /** @name Cell topology services
     * @{
     */
  public:
    /**
     * @param p any unsigned cell.
     * @return the topology word of [p].
     */
    Integer uTopology( const Cell & p ) const;

    /**
     * @param p any signed cell.
     * @return the topology word of [p].
     */
    Integer sTopology( const SCell & p ) const;

    /**
     * @param p any unsigned cell.
     * @return the dimension of the cell [p].
     */
    Dimension uDim( const Cell & p ) const;

    /**
     * @param p any signed cell.
     * @return the dimension of the cell [p].
     */
    Dimension sDim( const SCell & p ) const;

    /**
     * @param b any unsigned cell.
     * @return 'true' if [b] is a surfel (spans all but one coordinate).
     */
    bool uIsSurfel( const Cell & b ) const;

    /**
     * @param b any signed cell.
     * @return 'true' if [b] is a surfel (spans all but one coordinate).
     */
    bool sIsSurfel( const SCell & b ) const;

    /**
       @param p any cell.
       @param k any direction.
       @return 'true' if [p] is open along the direction [k].
    */
    bool uIsOpen( const Cell & p, Dimension k ) const;

    /**
       @param p any signed cell.
       @param k any direction.
       @return 'true' if [p] is open along the direction [k].
    */
    bool sIsOpen( const SCell & p, Dimension k ) const;

    /// @}

    // -------------------- Iterator services for cells ------------------------
    /** @name Iterator services for cells
     * @{
     */
  public:

    /**
       Given an unsigned cell [p], returns an iterator to iterate over
       each coordinate the cell spans. (A spel spans all coordinates; a
       surfel all but one, etc). Example:

       @code
       KSpace::Cell p;
       ...
       for ( KSpace::DirIterator q = ks.uDirs( p ); q != 0; ++q )
       {
         Dimension dir = *q;
       ...
       }
       @endcode

       @param p any unsigned cell.

       @return an iterator that points on the first coordinate spanned
       by the cell.
    */
    DirIterator uDirs( const Cell & p ) const;

    /**
       Given a signed cell [p], returns an iterator to iterate over
       each coordinate the cell spans. (A spel spans all coordinates; a
       surfel all but one, etc). Example:

       @code
       KSpace::SCell p;
       ...
       for ( KSpace::DirIterator q = ks.uDirs( p ); q != 0; ++q )
       {
         Dimension dir = *q;
       ...
       }
       @endcode

       @param p any signed cell.

       @return an iterator that points on the first coordinate spanned
       by the cell.
    */
    DirIterator sDirs( const SCell & p ) const;

    /**
       Given an unsigned cell [p], returns an iterator to iterate over each
       coordinate the cell does not span. (A spel spans all coordinates;
       a surfel all but one, etc). Example:

       @code
       KSpace::Cell p;
       ...
       for ( KSpace::DirIterator q = ks.uOrthDirs( p ); q != 0; ++q )
       {
         Dimension dir = *q;
       ...
       }
       @endcode

       @param p any unsigned cell.

       @return an iterator that points on the first coordinate spanned
       by the cell.
    */
    DirIterator uOrthDirs( const Cell & p ) const;

    /**
       Given a signed cell [p], returns an iterator to iterate over each
       coordinate the cell does not span. (A spel spans all coordinates;
       a surfel all but one, etc). Example:

       @code
       KSpace::SCell p;
       ...
       for ( KSpace::DirIterator q = ks.uOrthDirs( p ); q != 0; ++q )
       {
         Dimension dir = *q;
       ...
       }
       @endcode

       @param p any signed cell.

       @return an iterator that points on the first coordinate spanned
       by the cell.
    */
    DirIterator sOrthDirs( const SCell & p ) const;

    /**
       Given an unsigned surfel [s], returns its orthogonal direction (ie,
       the coordinate where the surfel is closed).

       @param s an unsigned surfel
       @return the orthogonal direction of [s]
    */
    Dimension uOrthDir( const Cell & s ) const;

    /**
       Given a signed surfel [s], returns its orthogonal direction (ie,
       the coordinate where the surfel is closed).

       @param s a signed surfel
       @return the orthogonal direction of [s]
    */
    Dimension sOrthDir( const SCell & s ) const;

    /// @}

    // -------------------- Unsigned cell geometry services --------------------
    /** @name Unsigned cell geometry services
     * @{
     */
  public:

    /**
       @return the k-th coordinate of the first cell of the space with the same type as [p].
    */
    Integer uFirst( const Cell & p, Dimension k ) const;

    /**
       @return the first cell of the space with the same type as [p].
    */
    Cell uFirst( const Cell & p ) const;

    /**
       @return the k-th coordinate of the last cell of the space with the same type as [p].
    */
    Integer uLast( const Cell & p, Dimension k ) const;

    /**
       @return the last cell of the space with the same type as [p].
    */
    Cell uLast( const Cell & p ) const;

    /**
       NB: you can go out of the space.
       @param p any cell.
       @param k the coordinate that is changed.

       @return the same element as [p] except for the incremented
       coordinate [k].
    */
    Cell uGetIncr( Cell p, Dimension k ) const;

    /**
       Useful to check if you are going out of the space.
       @param p any cell.
       @param k the tested coordinate.

       @return true if [p] cannot have its [k]-coordinate augmented
       without leaving the space.
    */
    bool uIsMax( const Cell & p, Dimension k ) const;


    /**
       Useful to check if you are going out of the space.
       @param p any cell.
       @param k the tested coordinate.

       @return true if [p] has its [k]-coordinate within the allowed bounds.
    */
    bool uIsInside( const Cell & p, Dimension k ) const;


    /**
       Useful to check if you are going out of the space.
       @param p any cell.
       @param k the concerned coordinate.

       @return the cell similar to [p] but with the maximum allowed
       [k]-coordinate.
    */
    Cell uGetMax( Cell p, Dimension k ) const;

    /**
       NB: you can go out of the space.
       @param p any cell.
       @param k the coordinate that is changed.

       @return the same element as [p] except for an decremented
       coordinate [k].
    */
    Cell uGetDecr( Cell p, Dimension k ) const;

    /**
       Useful to check if you are going out of the space.
       @param p any cell.
       @param k the tested coordinate.

       @return true if [p] cannot have its [k]-coordinate decreased
       without leaving the space.
    */
    bool uIsMin( const Cell & p, Dimension k ) const;

    /**
       Useful to check if you are going out of the space.
       @param p any cell.
       @param k the concerned coordinate.

       @return the cell similar to [p] but with the minimum allowed
       [k]-coordinate.
    */
    Cell uGetMin( Cell p, Dimension k ) const;


    /**
       NB: you can go out of the space.
       @param p any cell.
       @param k the coordinate that is changed.
       @param x the increment.

       @return the same element as [p] except for a coordinate [k]
       incremented with x.
    */
    Cell uGetAdd( Cell p, Dimension k, const Integer & x ) const;

    /**
       NB: you can go out of the space.
       @param p any cell.
       @param k the coordinate that is changed.
       @param x the decrement.

       @return the same element as [p] except for a coordinate [k]
       decremented with x.
    */
    Cell uGetSub( Cell p, Dimension k, const Integer & x ) const;

    /**
       Useful to check if you are going out of the space.
       @param p any cell.
       @param k the coordinate that is tested.
       @return the number of increment to do to reach the maximum value.
       @note if \a k is a periodic dimension, the corresponding coordinate of \a p is supposed to lie into the fundamental domain.
       If not, use before uCell(const Cell &) const on \a p.
    */
    Integer uDistanceToMax( const Cell & p, Dimension k ) const;

    /**
       Useful to check if you are going out of the space.
       @param p any cell.
       @param k the coordinate that is tested.

       @return the number of decrement to do to reach the minimum
       value.
       @note if \a k is a periodic dimension, the corresponding coordinate of \a p is supposed to lie into the fundamental domain.
       If not, use before uCell(const Cell &) const on \a p.
    */
    Integer uDistanceToMin( const Cell & p, Dimension k ) const;

    /**
       Add the vector [vec] to [p].
       NB: you can go out of the space.
       @param p any cell.
       @param vec any pointel.
       @return the unsigned code of the cell [p] translated by [coord].
    */
    Cell uTranslation( Cell p, const Vector & vec ) const;

    /**
       Return the projection of [p] along the [k]th direction toward
       [bound]. Otherwise said, p[ k ] == bound[ k ] afterwards.

       @param p any cell.
       @param bound the element acting as bound (same topology as p).
       @param k the concerned coordinate.
       @return the projection.
       @note if \a k is a periodic dimension, the corresponding coordinate of \a bound is supposed to lie into the fundamental domain.
       If not, use before uCell(const Cell &) const on \a bound.
    */
    Cell uProjection( Cell p, const Cell & bound, Dimension k ) const;

    /**
       Projects [p] along the [k]th direction toward
       [bound]. Otherwise said, p[ k ] == bound[ k ] afterwards.

       @param [in,out] p any cell.
       @param [in] bound the element acting as bound (same topology as p).
       @param [in] k the concerned coordinate.
       @note if \a k is a periodic dimension, the corresponding coordinate of \a bound is supposed to lie into the fundamental domain.
       If not, use before uCell(const Cell &) const on \a bound.
    */
    void uProject( Cell & p, const Cell & bound, Dimension k ) const;

    /**
       Increment the cell [p] to its next position (as classically done in
       a scanning). Example:

       \code
       KSpace K;
       Cell first, last; // lower and upper bounds
       Cell p = first;
       do
       { // ... whatever [p] is the current cell
       }
       while ( K.uNext( p, first, last ) );
       \endcode

       @param p any cell.
       @param lower the lower bound.
       @param upper the upper bound.

       @return true if p is still within the bounds, false if the
       scanning is finished.
    */
    bool uNext( Cell & p, const Cell & lower, const Cell & upper ) const;

    /// @}

    // -------------------- Signed cell geometry services --------------------
    /** @name Signed cell geometry services
     * @{
     */
  public:

    /**
       @return the k-th coordinate of the first cell of the space with the same type as [p].
    */
    Integer sFirst( const SCell & p, Dimension k ) const;

    /**
       @return the first cell of the space with the same type as [p].
    */
    SCell sFirst( const SCell & p ) const;

    /**
       @return the k-th coordinate of the last cell of the space with the same type as [p].
    */
    Integer sLast( const SCell & p, Dimension k ) const;

    /**
       @return the last cell of the space with the same type as [p].
    */
    SCell sLast( const SCell & p ) const;

    /**
       NB: you can go out of the space.
       @param p any cell.
       @param k the coordinate that is changed.

       @return the same element as [p] except for the incremented
       coordinate [k].
    */
    SCell sGetIncr( SCell p, Dimension k ) const;

    /**
       Useful to check if you are going out of the space.
       @param p any cell.
       @param k the tested coordinate.

       @return true if [p] cannot have its [k]-coordinate augmented
       without leaving the space.
    */
    bool sIsMax( const SCell & p, Dimension k ) const;

    /**
       Useful to check if you are going out of the space.
       @param p any cell.
       @param k the tested coordinate.

       @return true if [p] has its [k]-coordinate within the allowed bounds.
    */
    bool sIsInside( const SCell & p, Dimension k ) const;

    /**
       Useful to check if you are going out of the space.
       @param p any cell.
       @param k the concerned coordinate.

       @return the cell similar to [p] but with the maximum allowed
       [k]-coordinate.
    */
    SCell sGetMax( SCell p, Dimension k ) const;

    /**
       NB: you can go out of the space.
       @param p any cell.
       @param k the coordinate that is changed.

       @return the same element as [p] except for an decremented
       coordinate [k].
    */
    SCell sGetDecr( SCell p, Dimension k ) const;

    /**
       Useful to check if you are going out of the space.
       @param p any cell.
       @param k the tested coordinate.

       @return true if [p] cannot have its [k]-coordinate decreased
       without leaving the space.
    */
    bool sIsMin( const SCell & p, Dimension k ) const;

    /**
       Useful to check if you are going out of the space.
       @param p any cell.
       @param k the concerned coordinate.

       @return the cell similar to [p] but with the minimum allowed
       [k]-coordinate.
    */
    SCell sGetMin( SCell p, Dimension k ) const;

    /**
       NB: you can go out of the space.
       @param p any cell.
       @param k the coordinate that is changed.
       @param x the increment.

       @return the same element as [p] except for a coordinate [k]
       incremented with x.
    */
    SCell sGetAdd( SCell p, Dimension k, const Integer & x ) const;

    /**
       NB: you can go out of the space.
       @param p any cell.
       @param k the coordinate that is changed.
       @param x the decrement.

       @return the same element as [p] except for a coordinate [k]
       decremented with x.
    */
    SCell sGetSub( SCell p, Dimension k, const Integer & x ) const;

    /**
       Useful to check if you are going out of the space.
       @param p any cell.
       @param k the coordinate that is tested.
       @return the number of increment to do to reach the maximum value.
       @note if \a k is a periodic dimension, the corresponding coordinate of \a p is supposed to lie into the fundamental domain.
       If not, use before sCell(const SCell &) const on \a p.
    */
    Integer sDistanceToMax( const SCell & p, Dimension k ) const;

    /**
       Useful to check if you are going out of the space.
       @param p any cell.
       @param k the coordinate that is tested.

       @return the number of decrement to do to reach the minimum
       @note if \a k is a periodic dimension, the corresponding coordinate of \a p is supposed to lie into the fundamental domain.
       If not, use before sCell(const SCell &) const on \a p.
       value.
    */
    Integer sDistanceToMin( const SCell & p, Dimension k ) const;

    /**
       Add the vector [vec] to [p].
       NB: you can go out of the space.
       @param p any cell.
       @param vec any pointel.
       @return the signed code of the cell [p] translated by [coord].
    */
    SCell sTranslation( SCell p, const Vector & vec ) const;

    /**
       Return the projection of [p] along the [k]th direction toward
       [bound]. Otherwise said, p[ k ] == bound[ k ] afterwards.

       @param p any cell.
       @param bound the element acting as bound (same topology as p).
       @param k the concerned coordinate.
       @return the projection.
       @note if \a k is a periodic dimension, the corresponding coordinate of \a bound is supposed to lie into the fundamental domain.
       If not, use before uCell(const Cell &) const on \a bound.
    */
    SCell sProjection( SCell p, const SCell & bound, Dimension k ) const;

    /**
       Projects [p] along the [k]th direction toward
       [bound]. Otherwise said, p[ k ] == bound[ k ] afterwards.

       @param p any cell.
       @param bound the element acting as bound (same topology as p).
       @param k the concerned coordinate.
       @note if \a k is a periodic dimension, the corresponding coordinate of \a bound is supposed to lie into the fundamental domain.
       If not, use before uCell(const Cell &) const on \a bound.
    */
    void sProject( SCell & p, const SCell & bound, Dimension k ) const;

    /**
       Increment the cell [p] to its next position (as classically done in
       a scanning). Example:

       \code
       KSpace K;
       Cell first, last; // lower and upper bounds
       Cell p = first;
       do
       { // ... whatever [p] is the current cell
       }
       while ( K.uNext( p, first, last ) );
       \endcode

       @param p any cell.
       @param lower the lower bound.
       @param upper the upper bound.

       @return true if p is still within the bounds, false if the
       scanning is finished.
    */
    bool sNext( SCell & p, const SCell & lower, const SCell & upper ) const;

    /// @}

    // ----------------------- Neighborhood services --------------------------
    /** @name Neighborhood services
     * @{
     */
  public:

    /**
       Computes the 1-neighborhood of the cell [c] and returns
       it. It is the set of cells with same topology that are adjacent
       to [c] and which are within the bounds of this space.

       @param cell the unsigned cell of interest.
       @return the cells of the 1-neighborhood of [cell].
    */
    Cells uNeighborhood( const Cell & cell ) const;

    /**
       Computes the 1-neighborhood of the cell [c] and returns
       it. It is the set of cells with same topology that are adjacent
       to [c] and which are within the bounds of this space.

       @param cell the signed cell of interest.
       @return the cells of the 1-neighborhood of [cell].
    */
    SCells sNeighborhood( const SCell & cell ) const;

    /**
       Computes the proper 1-neighborhood of the cell [c] and returns
       it. It is the set of cells with same topology that are adjacent
       to [c], different from [c] and which are within the bounds of
       this space.

       @param cell the unsigned cell of interest.
       @return the cells of the proper 1-neighborhood of [cell].
    */
    Cells uProperNeighborhood( const Cell & cell ) const;

    /**
       Computes the proper 1-neighborhood of the cell [c] and returns
       it. It is the set of cells with same topology that are adjacent
       to [c], different from [c] and which are within the bounds of
       this space.

       @param cell the signed cell of interest.
       @return the cells of the proper 1-neighborhood of [cell].
    */
    SCells sProperNeighborhood( const SCell & cell ) const;

    /**
       NB: you can go out of the space.
       @param p any cell.
       @param k the coordinate that is changed.
       @param up if 'true' the orientation is forward along axis
       [k], otherwise backward.

       @return the adjacent element to [p] along axis [k] in the given
       direction and orientation.

       @note It is an alias to 'up ? uGetIncr( p, k ) : uGetDecr( p, k )'.
    */
    Cell uAdjacent( const Cell & p, Dimension k, bool up ) const;
    /**
       NB: you can go out of the space.
       @param p any cell.
       @param k the coordinate that is changed.
       @param up if 'true' the orientation is forward along axis
       [k], otherwise backward.

       @return the adjacent element to [p] along axis [k] in the given
       direction and orientation.

       @note It is an alias to 'up ? sGetIncr( p, k ) : sGetDecr( p, k )'.
    */
    SCell sAdjacent( const SCell & p, Dimension k, bool up ) const;

    /// @}

    // ----------------------- Incidence services --------------------------
    /** @name Incidence services
     * @{
     */
  public:

    /**
       @param c any unsigned cell.
       @param k any coordinate.

       @param up if 'true' the orientation is forward along axis
       [k], otherwise backward.

       @return the forward or backward unsigned cell incident to [c]
       along axis [k], depending on [forward].

       @note It may be a lower incident cell if [c] is open along axis
       [k], else an upper incident cell.

       @note The cell should have an incident cell in this
       direction/orientation.
    */
    Cell uIncident( Cell c, Dimension k, bool up ) const;

    /**
       @param c any signed cell.
       @param k any coordinate.

       @param up if 'true' the orientation is forward along axis
       [k], otherwise backward.

       @return the forward or backward signed cell incident to [c]
       along axis [k], depending on [forward]. It is worthy to note
       that the forward and backward cell have opposite
       sign. Furthermore, the sign of these cells is defined so as to
       satisfy a boundary operator.

       @note It may be a lower incident cell if [c] is open along axis
       [k], else an upper incident cell.

       @note The cell should have an incident cell in this
       direction/orientation.
    */
    SCell sIncident( SCell c, Dimension k, bool up ) const;

    /**
       @param c any unsigned cell.
       @return the cells directly low incident to c in this space.
    */
    Cells uLowerIncident( const Cell & c ) const;

    /**
       @param c any unsigned cell.
       @return the cells directly up incident to c in this space.
    */
    Cells uUpperIncident( const Cell & c ) const;

    /**
       @param c any signed cell.
       @return the signed cells directly low incident to c in this space.
       @note it is the lower boundary of c expressed as a list of signed cells.
    */
    SCells sLowerIncident( const SCell & c ) const;

    /**
       @param c any signed cell.
       @return the signed cells directly up incident to c in this space.
       @note it is the upper boundary of c expressed as a list of signed cells.
    */
    SCells sUpperIncident( const SCell & c ) const;

    /**
       @param c any unsigned cell.
       @return the proper faces of [c] (chain of lower incidence).
    */
    Cells uFaces( const Cell & c ) const;

    /**
       @param c any unsigned cell.
       @return the proper cofaces of [c] (chain of upper incidence).
    */
    Cells uCoFaces( const Cell & c ) const;

    /**
       Return 'true' if the direct orientation of [p] along [k] is in
       the positive coordinate direction. The direct orientation in a
       direction allows to go from positive incident cells to positive
       incident cells.  This means that
       @code
       K.sSign( K.sIncident( p, k, K.sDirect( p, k ) ) ) == K.POS
       @endcode
       is always true.

       @param p any signed cell.
       @param k any coordinate.

       @return the direct orientation of [p] along [k] (true is
       upward, false is backward).
    */
    bool sDirect( const SCell & p, Dimension k ) const;

    /**
       @param p any signed cell.
       @param k any coordinate.

       @return the direct incident cell of [p] along [k] (the incident
       cell along [k] whose sign is positive).
    */
    SCell sDirectIncident( SCell p, Dimension k ) const;

    /**
       @param p any signed cell.
       @param k any coordinate.

       @return the indirect incident cell of [p] along [k] (the incident
       cell along [k] whose sign is negative).
    */
    SCell sIndirectIncident( SCell p, Dimension k ) const;

    /// @}

    // ----------------------- Interface --------------------------------------
    /** @name DGtal interface
     * @{
     */
  public:

    /**
     * Writes/Displays the object on an output stream.
     * @param out the output stream where the object is written.
     */
    void selfDisplay ( std::ostream & out ) const;

    /**
     * Checks the validity/consistency of the object.
     * @return 'true' if the object is valid, 'false' otherwise.
     */
    bool isValid() const;

    /// @}

    // ------------------------- Protected Datas ------------------------------
  private:
    // ------------------------- Private Datas --------------------------------
  private:
    Point myLower;
    Point myUpper;
    Cell myCellLower;
    Cell myCellUpper;
    Closure myClosure[dim];

    // ------------------------- Hidden services ------------------------------
  protected:


  private:



    // ------------------------- Internals ------------------------------------
    /** @name Internals
     * @{
     */
  private:
    /**
       Used by uFaces for computing incident faces.
    */
    void uAddFaces( Cells& faces, const Cell& c, Dimension axis ) const;

    /**
       Used by uCoFaces for computing incident cofaces.
    */
    void uAddCoFaces( Cells& cofaces, const Cell& c, Dimension axis ) const;

    /// @}

  }; // end of class KhalimskySpaceND


  /**
   * Overloads 'operator<<' for displaying objects of class 'KhalimskySpaceND'.
   * @param out the output stream where the object is written.
   * @param object the object of class 'KhalimskySpaceND' to write.
   * @return the output stream after the writing.
   */
  template < Dimension dim,
             typename TInteger >
  std::ostream&
  operator<< ( std::ostream & out,
               const KhalimskySpaceND<dim, TInteger > & object );

} // namespace DGtal


///////////////////////////////////////////////////////////////////////////////
// Includes inline functions.
#include "DGtal/topology/KhalimskySpaceND.ih"

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined KhalimskySpaceND_h

#undef KhalimskySpaceND_RECURSES
#endif // else defined(KhalimskySpaceND_RECURSES)
