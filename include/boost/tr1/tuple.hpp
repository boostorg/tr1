/*=============================================================================
    Copyright (c) 1999-2002 Jaakko Järvi
    Copyright (c) 2001-2002 Joel de Guzman

    Permission to copy, use, modify, sell and distribute this software
    is granted provided this copyright notice appears in all copies.
    This software is provided "as is" without express or implied
    warranty, and with no claim as to its suitability for any purpose.
==============================================================================*/
#if !defined(BOOST_TR1_TUPLE_HPP)
#define BOOST_TR1_TUPLE_HPP

#if !defined(BOOST_TR1_TUPLE_MAX_ARITY)
    #define BOOST_TR1_TUPLE_MAX_ARITY 6
#endif

#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/arithmetic/inc.hpp>
#include <boost/preprocessor/cat.hpp>

#include <boost/mpl/void.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/begin_end.hpp>
#include <boost/mpl/apply.hpp>
#include <boost/mpl/find.hpp>
#include <boost/mpl/distance.hpp>
#include <boost/mpl/at.hpp>
#include <boost/mpl/size.hpp>
#include <boost/mpl/if.hpp>

//  include mpl::vector0..N where N
//  is BOOST_TR1_TUPLE_MAX_ARITY

#if (BOOST_TR1_TUPLE_MAX_ARITY < 10)
#include <boost/mpl/vector/vector10.hpp>

#elif (BOOST_TR1_TUPLE_MAX_ARITY < 20)
#include <boost/mpl/vector/vector20.hpp>
#if (BOOST_TR1_TUPLE_MAX_ARITY == 11)
#include <boost/mpl/vector/vector10.hpp>

#elif (BOOST_TR1_TUPLE_MAX_ARITY < 30)
#include <boost/mpl/vector/vector30.hpp>
#if (BOOST_TR1_TUPLE_MAX_ARITY == 21)
#include <boost/mpl/vector/vector20.hpp>

#elif (BOOST_TR1_TUPLE_MAX_ARITY < 40)
#include <boost/mpl/vector/vector40.hpp>
#if (BOOST_TR1_TUPLE_MAX_ARITY == 31)
#include <boost/mpl/vector/vector30.hpp>

#elif (BOOST_TR1_TUPLE_MAX_ARITY < 50)
#include <boost/mpl/vector/vector50.hpp>
#if (BOOST_TR1_TUPLE_MAX_ARITY == 41)
#include <boost/mpl/vector/vector40.hpp>

#endif
#endif
#endif
#endif
#endif

#include <boost/ref.hpp>
#include <boost/call_traits.hpp>
#include <boost/type_traits.hpp>
#include <boost/tr1/tuple/macro_utils.hpp>
#include <boost/tr1/tuple/helpers.hpp>

#define BOOST_TR1_TUPLE_TEMPLATE_ARGS \
    BOOST_PP_ENUM_PARAMS(BOOST_TR1_TUPLE_MAX_ARITY, T)

#define BOOST_TR1_TUPLE_TEMPLATE_ARGS_B \
    BOOST_PP_ENUM_PARAMS(BOOST_TR1_TUPLE_MAX_ARITY, TB)

#define BOOST_TR1_TUPLE_TEMPLATE_PARAMS_MAX \
    BOOST_TR1_TUPLE_TEMPLATE_PARAMS(BOOST_TR1_TUPLE_MAX_ARITY)

#define BOOST_TR1_TUPLE_TEMPLATE_PARAMS_MAX_B \
    BOOST_TR1_TUPLE_TEMPLATE_PARAMS_B(BOOST_TR1_TUPLE_MAX_ARITY)

//  include the actual tuple_N implementations
#include <boost/tr1/tuple/tuple_n.ipp>

namespace boost
{
  namespace tr1 
  {
    typedef boost::mpl::void_ void_t;

///////////////////////////////////////////////////////////////////////////////
//
//  tuple forward declaration
//
//      Expands to:
//
//      template <
//          typename T0 = void_t,
//          typename T1 = void_t,
//          ...
//          typename TN = void_t,
//          typename ID = TupleID>
//      struct tuple
//
//      where N = BOOST_TR1_TUPLE_MAX_ARITY
//      and TupleID is a unique type related to the tuple's arity
//
///////////////////////////////////////////////////////////////////////////////
    //  include the BOOST_TR1_TUPLE_ID implementation
    #include <boost/tr1/tuple/tuple_identity.ipp>

    template <
      BOOST_TR1_TUPLE_TEMPLATE_PARAMS_WITH_DEFAULT(BOOST_TR1_TUPLE_MAX_ARITY, void_t)
      , typename ID = BOOST_TR1_TUPLE_ID>
    struct tuple;

///////////////////////////////////////////////////////////////////////////////
//
//  tuple_element metafunction
//
//      Given a constant integer N and a tuple type TupleT, returns the plain
//      type, reference or const reference of the tuple element at slot N. (N
//      is a zero based index). Usage:
//
//          tuple_element<N, TupleT>::type
//          tuple_element<N, TupleT>::reference
//          tuple_element<N, TupleT>::const_reference
//
///////////////////////////////////////////////////////////////////////////////
    template <unsigned N, typename TupleT>
    struct tuple_element
    {
      typedef typename
        boost::mpl::at_c<typename TupleT::types, N>::type type;
    };

    namespace tuple_detail {

      template <unsigned N, typename TupleT>
      class get_result {
	typedef typename tuple_element<N, TupleT>::type t; 
      public:
        typedef typename boost::add_reference<t>::type type;
      };

      template <unsigned N, typename TupleT>
      class const_get_result {
	typedef typename tuple_element<N, TupleT>::type t; 
	typedef typename boost::add_const<t>::type ct;
      public:
        typedef typename boost::add_reference<ct>::type type;
      };

    } // namespace tuple_detail

///////////////////////////////////////////////////////////////////////////////
//
//  tuple_size metafunction
//
//      Get the size of TupleT. Usage:
//
//          tuple_size<TupleT>::value
//
///////////////////////////////////////////////////////////////////////////////
    template <typename TupleT>
    struct tuple_size
    {
        BOOST_STATIC_CONSTANT(unsigned, value = TupleT::length);
    };

///////////////////////////////////////////////////////////////////////////////
//
//  get function
//
//      Given a constant integer N and a tuple, returns a reference to
//      the Nth element of the tuple. (N is a zero based index). Usage:
//
//          get<N>(t)
//
///////////////////////////////////////////////////////////////////////////////
    //  include the actual tuple element_at implementations
    #include <boost/tr1/tuple/tuple_element_at.ipp>

    template <unsigned N, BOOST_TR1_TUPLE_TEMPLATE_PARAMS_MAX>
    inline typename tuple_detail::const_get_result<N, tuple<BOOST_TR1_TUPLE_TEMPLATE_ARGS> >
        ::type
    get(tuple<BOOST_TR1_TUPLE_TEMPLATE_ARGS> const& t, boost::mpl::int_<N>* = 0)
    { return tuple_detail::element_at_<N>::type::get(t); }

    template <unsigned N, BOOST_TR1_TUPLE_TEMPLATE_PARAMS_MAX>
    inline typename tuple_detail::get_result<N, tuple<BOOST_TR1_TUPLE_TEMPLATE_ARGS> >
        ::type
    get(tuple<BOOST_TR1_TUPLE_TEMPLATE_ARGS>& t, boost::mpl::int_<N>* = 0)
    { return tuple_detail::element_at_<N>::type::get(t); }

    /* Note: boost::mpl::int_<N>* = 0 is a workaround to an MSVC 6 bug */

///////////////////////////////////////////////////////////////////////////////
//
//  tuple
//
//      Holds heterogeneously typed values that can be accessed individually
//      by its zero based index. The maximum number of elements is limited by
//      the user #definable constant BOOST_TR1_TUPLE_MAX_ARITY, which defaults
//      to 3. Usage examples:
//
//          tuple<int, char>    t2(1, 'x'); //  constructor
//          tuple<long, short>  t2(1);      //  short is default constructed
//
//          t1 = t2;        //  assignment, tuples with same number of elements
//                          //  may be assigned as long as each corresponding
//                          //  element are assignable, i.e long <- int and
//                          //  short <- char. This is also true for copy
//                          //  construction if the tuple elements are copy
//                          //  constructible.
//
//          t1 == t2;       //  comparison, tuples with same number of elements
//                          //  may be assigned as long as each corresponding
//                          //  element are comparable, This is also true for
//                          //  !=, <, <=, > and >=.
//
//          std::pair<long, short>  p(1, 1.0);
//          tuple<long, short>  t3(p);          //  copy from a std::pair
//          t3 = p;                             //  assign from a std::pair
//
//      The actual interface, without the preprocessor gunk looks like this:
//      (where N = BOOST_TR1_TUPLE_MAX_ARITY)
//
//      template <typename T0, typename T1, ... typename TN, typename ID>
//      struct tuple
//      {
//          typedef tuple<T0, T1...TN> self_t;
//          typedef boost::mpl::vectorN<T0, T1...TN> types;
//          typedef typename boost::mpl::begin<types>::type begin_t;
//          typedef typename boost::mpl::find<types, void_t>::type end_t;
//          typedef typename boost::mpl::distance<begin_t, end_t>::type length_t;
//
//          static unsigned const length = length_t::value;
//
//          tuple()
//              : data() {}
//
//          tuple(
//              typename boost::call_traits<T0>::param_type _0)
//              : data(_0) {}
//
//          tuple(
//              typename boost::call_traits<T0>::param_type _0,
//              typename boost::call_traits<T1>::param_type _1)
//              : data(_0, _1) {}
//
//          ...
//
//          tuple(
//              typename boost::call_traits<T0>::param_type _0,
//              typename boost::call_traits<T1>::param_type _1,
//              ...
//              typename boost::call_traits<TN>::param_type _N)
//              : data(_0, _1,... _N) {}
//
//          template <typename TB0, typename TB1... typename TBN>
//          tuple(tuple<TB0, TB1... TBN, ID> const& t)
//              : data(t.data) {}
//
//          template <typename FirstT, typename SecondT>
//          tuple(std::pair<FirstT, SecondT> const& t)
//              : data(t.first, t.second) { BOOST_STATIC_ASSERT(length == 2); }
//
//          template <typename TB0, typename TB1... typename TBN>
//          tuple& operator=(tuple<TB0, TB1... TBN, ID> const& t)
//          { data = t.data; return *this; }
//
//          template <typename FirstT, typename SecondT>
//          tuple&
//          operator=(std::pair<FirstT, SecondT> const& t)
//          {
//              BOOST_STATIC_ASSERT(length == 2);
//              tuple_detail::element_at_<0>::type::get(*this) = t.first;
//              tuple_detail::element_at_<1>::type::get(*this) = t.second;
//              return *this;
//          }
//
//          BOOST_TR1_TUPLE_MEMBERS_TYPE data
//      };
//
//      BOOST_TR1_TUPLE_MEMBERS_TYPE is an implementation defined type
//
///////////////////////////////////////////////////////////////////////////////
    template <BOOST_TR1_TUPLE_TEMPLATE_PARAMS_MAX, typename ID>
    struct tuple
    {
        typedef tuple<BOOST_TR1_TUPLE_TEMPLATE_ARGS, ID> self_t;
        typedef BOOST_PP_CAT(boost::mpl::vector, BOOST_TR1_TUPLE_MAX_ARITY)<
            BOOST_TR1_TUPLE_TEMPLATE_ARGS> types;
        typedef typename boost::mpl::begin<types>::type begin_t;
        typedef typename boost::mpl::find<types, void_t>::type end_t;
        typedef typename boost::mpl::distance<begin_t, end_t>::type length_t;

        BOOST_STATIC_CONSTANT(unsigned, length = length_t::value);

        //  Bring in the constructors
        #include <boost/tr1/tuple/tuple_constructor.ipp>

        template <BOOST_TR1_TUPLE_TEMPLATE_PARAMS_MAX_B>
        tuple(tuple<BOOST_TR1_TUPLE_TEMPLATE_ARGS_B, ID> const& t)
            : data(t.data) {}

        template <typename FirstT, typename SecondT>
        tuple(std::pair<FirstT, SecondT> const& t)
            : data(t.first, t.second) { BOOST_STATIC_ASSERT(length == 2); }

        template <BOOST_TR1_TUPLE_TEMPLATE_PARAMS_MAX_B>
        tuple& operator=(tuple<BOOST_TR1_TUPLE_TEMPLATE_ARGS_B, ID> const& t)
        { data = t.data; return *this; }

        template <typename FirstT, typename SecondT>
        tuple&
        operator=(std::pair<FirstT, SecondT> const& t)
        {
            BOOST_STATIC_ASSERT(length == 2);
            tuple_detail::element_at_<0>::type::get(*this) = t.first;
            tuple_detail::element_at_<1>::type::get(*this) = t.second;
            return *this;
        }

        BOOST_TR1_TUPLE_MEMBERS_TYPE data;
    };

///////////////////////////////////////////////////////////////////////////////
//
//  Relational operators
//
//      Expands to:
//
//          template <
//              typename T0, typename T1... typename TN,
//              typename TB0, typename TB1... typename TBN,
//              typename ID>
//          inline bool operator OP(
//              tuple<T0, T1... TN, ID> const& a
//              tuple<TB0, TB1... TBN, ID> const& b)
//          { return a.data OP b.data; }
//
//      where N = BOOST_TR1_TUPLE_MAX_ARITY and with one function
//      for each OP, where OP is: ==, !=, <, >, <=, and >=.
//
///////////////////////////////////////////////////////////////////////////////
    template <
        BOOST_TR1_TUPLE_TEMPLATE_PARAMS_MAX,
        BOOST_TR1_TUPLE_TEMPLATE_PARAMS_MAX_B, typename ID>
    inline bool operator==(
        tuple<BOOST_TR1_TUPLE_TEMPLATE_ARGS, ID> const& a,
        tuple<BOOST_TR1_TUPLE_TEMPLATE_ARGS_B, ID> const& b)
    { return a.data == b.data; }

    template <
        BOOST_TR1_TUPLE_TEMPLATE_PARAMS_MAX,
        BOOST_TR1_TUPLE_TEMPLATE_PARAMS_MAX_B, typename ID>
    inline bool operator!=(
        tuple<BOOST_TR1_TUPLE_TEMPLATE_ARGS, ID> const& a,
        tuple<BOOST_TR1_TUPLE_TEMPLATE_ARGS_B, ID> const& b)
    { return a.data != b.data; }

    template <
        BOOST_TR1_TUPLE_TEMPLATE_PARAMS_MAX,
        BOOST_TR1_TUPLE_TEMPLATE_PARAMS_MAX_B, typename ID>
    inline bool operator<(
        tuple<BOOST_TR1_TUPLE_TEMPLATE_ARGS, ID> const& a,
        tuple<BOOST_TR1_TUPLE_TEMPLATE_ARGS_B, ID> const& b)
    { return a.data < b.data; }

    template <
        BOOST_TR1_TUPLE_TEMPLATE_PARAMS_MAX,
        BOOST_TR1_TUPLE_TEMPLATE_PARAMS_MAX_B, typename ID>
    inline bool operator>(
        tuple<BOOST_TR1_TUPLE_TEMPLATE_ARGS, ID> const& a,
        tuple<BOOST_TR1_TUPLE_TEMPLATE_ARGS_B, ID> const& b)
    { return a.data > b.data; }

    template <
        BOOST_TR1_TUPLE_TEMPLATE_PARAMS_MAX,
        BOOST_TR1_TUPLE_TEMPLATE_PARAMS_MAX_B, typename ID>
    inline bool operator<=(
        tuple<BOOST_TR1_TUPLE_TEMPLATE_ARGS, ID> const& a,
        tuple<BOOST_TR1_TUPLE_TEMPLATE_ARGS_B, ID> const& b)
    { return a.data <= b.data; }

    template <
        BOOST_TR1_TUPLE_TEMPLATE_PARAMS_MAX,
        BOOST_TR1_TUPLE_TEMPLATE_PARAMS_MAX_B, typename ID>
    inline bool operator>=(
        tuple<BOOST_TR1_TUPLE_TEMPLATE_ARGS, ID> const& a,
        tuple<BOOST_TR1_TUPLE_TEMPLATE_ARGS_B, ID> const& b)
    { return a.data >= b.data; }

#if defined __GNUC__ && __GNUC__ <= 2

///////////////////////////////////////////////////////////////////////////////
//
//  Relational operators for tuples of the same type. The following
//  relational ops are workarounds over the ambiguity with the relops
//  provided by g++ 2.9x
//
//      Expands to:
//
//          template <typename T0, typename T1... typename TN, typename ID>
//          inline bool operator OP(
//              tuple<T0, T1... TN, ID> const& a
//              tuple<T0, T1... TN, ID> const& b)
//          { return a.data OP b.data; }
//
//      where N = BOOST_TR1_TUPLE_MAX_ARITY and with one function
//      for each OP, where OP is: ==, !=, <, >, <=, and >=.
//
///////////////////////////////////////////////////////////////////////////////

    template <BOOST_TR1_TUPLE_TEMPLATE_PARAMS_MAX, typename ID>
    inline bool operator==(
        tuple<BOOST_TR1_TUPLE_TEMPLATE_ARGS, ID> const& a,
        tuple<BOOST_TR1_TUPLE_TEMPLATE_ARGS, ID> const& b)
    { return a.data == b.data; }

    template <BOOST_TR1_TUPLE_TEMPLATE_PARAMS_MAX, typename ID>
    inline bool operator!=(
        tuple<BOOST_TR1_TUPLE_TEMPLATE_ARGS, ID> const& a,
        tuple<BOOST_TR1_TUPLE_TEMPLATE_ARGS, ID> const& b)
    { return a.data != b.data; }

    template <BOOST_TR1_TUPLE_TEMPLATE_PARAMS_MAX, typename ID>
    inline bool operator<(
        tuple<BOOST_TR1_TUPLE_TEMPLATE_ARGS, ID> const& a,
        tuple<BOOST_TR1_TUPLE_TEMPLATE_ARGS, ID> const& b)
    { return a.data < b.data; }

    template <BOOST_TR1_TUPLE_TEMPLATE_PARAMS_MAX, typename ID>
    inline bool operator>(
        tuple<BOOST_TR1_TUPLE_TEMPLATE_ARGS, ID> const& a,
        tuple<BOOST_TR1_TUPLE_TEMPLATE_ARGS, ID> const& b)
    { return a.data > b.data; }

    template <BOOST_TR1_TUPLE_TEMPLATE_PARAMS_MAX, typename ID>
    inline bool operator<=(
        tuple<BOOST_TR1_TUPLE_TEMPLATE_ARGS, ID> const& a,
        tuple<BOOST_TR1_TUPLE_TEMPLATE_ARGS, ID> const& b)
    { return a.data <= b.data; }

    template <BOOST_TR1_TUPLE_TEMPLATE_PARAMS_MAX, typename ID>
    inline bool operator>=(
        tuple<BOOST_TR1_TUPLE_TEMPLATE_ARGS, ID> const& a,
        tuple<BOOST_TR1_TUPLE_TEMPLATE_ARGS, ID> const& b)
    { return a.data >= b.data; }

#endif

///////////////////////////////////////////////////////////////////////////////
//
//  The make_tuple, tie generators
//
//      Expands to:
//
//          template <typename T0, typename T1... typename TN>
//          inline tuple<
//              typename tuple_detail::as_tuple_element<T0>::type,
//              typename tuple_detail::as_tuple_element<T1>::type,
//              ...
//              typename tuple_detail::as_tuple_element<TN>::type,
//          make_tuple(T0 const& _0, T1 const& _1... TN const& _N)
//          {
//              return tuple<
//                  typename tuple_detail::as_tuple_element<T0>::type,
//                  typename tuple_detail::as_tuple_element<T1>::type,
//                  ...
//                  typename tuple_detail::as_tuple_element<TN>::type>(_0, _1... _N);
//          }
//
//          template <typename T0, typename T1... typename TN>
//          inline tuple<T0&, T1&... TN&>
//          tie(T0& _0, T1& _1... TN& _N)
//          {
//              return tuple<T0&, T1&... TN&>(_0, _1... _N);
//          }
//
//      where N runs from 1 to BOOST_TUPLE_MAX_ARITY and as_tuple_element
//      is a metafunction that converts a ref(T) to a reference to T, a
//      cref(T) to a const reference to T and of course, a T left unconverted
//      as-is to a T.
//
///////////////////////////////////////////////////////////////////////////////
    //  Bring in the generators
    #include <boost/tr1/tuple/tuple_generator.ipp>

    //  Swallows any assignment (by Doug Gregor)
    namespace tuple_detail
    {
        struct swallow_assign
        {
            template<typename T>
            swallow_assign const&
            operator=(const T&) const
            { return *this; }
        };
    }

    //  "ignore" allows tuple positions to be ignored when using "tie".
    tuple_detail::swallow_assign const ignore = tuple_detail::swallow_assign();

} // end of namespace tr1
} // end of namespace boost

// The macro defs need to be in effect in tupleio.hpp too
#include <boost/tr1/tuple/tupleio.hpp>

#undef BOOST_TR1_TUPLE_TEMPLATE_ARGS
#undef BOOST_TR1_TUPLE_TEMPLATE_ARGS_B
#undef BOOST_TR1_TUPLE_TEMPLATE_PARAMS_MAX
#undef BOOST_TR1_TUPLE_TEMPLATE_PARAMS_MAX_B
#undef BOOST_TR1_TUPLE_ID
#undef BOOST_TR1_TUPLE_MEMBERS_TYPE




#endif // defined(BOOST_TR1_TUPLE_HPP)
