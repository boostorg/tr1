/*=============================================================================
    Copyright (c) 1999-2003 Jaakko Järvi
    Copyright (c) 2001-2003 Joel de Guzman

    Permission to copy, use, modify, sell and distribute this software
    is granted provided this copyright notice appears in all copies.
    This software is provided "as is" without express or implied
    warranty, and with no claim as to its suitability for any purpose.
==============================================================================*/
#if !defined(BOOST_PP_IS_ITERATING)
#if !defined(BOOST_TR1_TUPLE_TUPLE_N_IPP)
#define BOOST_TR1_TUPLE_TUPLE_N_IPP

#include <boost/preprocessor/iterate.hpp>

namespace boost {
namespace tr1 {

    namespace tuple_detail
    {
        template <unsigned N>
        struct tuple_holder {};

        struct tuple_holder_0
        {
            template <BOOST_TR1_TUPLE_TEMPLATE_PARAMS_MAX>
            struct data {};
        };

///////////////////////////////////////////////////////////////////////////////
//
//  The following Boost::PP code generates expansions for:
//
//      struct tuple_holder_N
//      {
//          template <typename T0, typename T1, ... typename TM>
//          struct data
//          {
//              data() : m0(), m1(), ..., mN() {}
//              data(
//                  typename boost::call_traits<T0>::param_type _0,
//                  typename boost::call_traits<T1>::param_type _1,
//                  ...
//                  typename boost::call_traits<TN>::param_type _N)
//                  : m0(_0), m1(_1), mN(_N) {}
//
//              template <typename TB0, typename TB1... typename TBN>
//              data(data<TB0, TB1...TBN> const& t)
//                  : m0(t.m0), m1(t.m1)... mN(t.mN) {}
//
//              template <typename TupleT>
//              data& operator=(TupleT const& t)
//              { m0 = t.m0; m1 = t.m1;... mN = t.mN; }
//
//              template <typename TupleT>
//              bool operator==(TupleT const& t) const
//              { m0 == t.m0 && m1 == t.m1 && ... mN == t.mN && true; }
//
//              template <typename TupleT>
//              bool operator!=(TupleT const& t) const
//              { m0 != t.m0 || m1 != t.m1 || ... mN != t.mN || false; }
//
//              template <typename TupleT>
//              bool operator<(TupleT const& t) const
//              { m0 < t.m0 || m1 < t.m1 || ... mN < t.mN || false; }
//
//              template <typename TupleT>
//              bool operator>(TupleT const& t) const
//              { m0 > t.m0 || m1 > t.m1 || ... mN > t.mN || false; }
//
//              template <typename TupleT>
//              bool operator<=(TupleT const& t) const
//              { m0 <= t.m0 && (!(t.m0 <= m0) || (m1 <= t.m1 && (!(t.m1 <= m1)
//                                             || (... mN <= t.mN )))) ... )); }
//
//              template <typename TupleT>
//              bool operator>=(TupleT const& t) const
//              { m0 >= t.m0 && (!(t.m0 >= m0) || (m1 >= t.m1 && (!(t.m1 >= m1)
//                                             || (... mN >= t.mN )))) ... )); }
//
//              T0 m0;
//              T1 m1;
//              ...
//              TN mN;
//          };
//      };
//
//  where N runs from 1 to BOOST_TR1_TUPLE_MAX_ARITY
//  and M is BOOST_TR1_TUPLE_MAX_ARITY
//
///////////////////////////////////////////////////////////////////////////////
#define BOOST_TR1_TUPLE_MEMBER_INIT(z, n, data) \
    BOOST_PP_CAT(m, n)(BOOST_PP_CAT(_, n))

#define BOOST_TR1_TUPLE_MEMBER_COPY(z, n, data) \
    BOOST_PP_CAT(m, n)(t.BOOST_PP_CAT(m, n))

#define BOOST_TR1_TUPLE_MEMBER_ASSIGN(z, n, data) \
    BOOST_PP_CAT(m, n) = t.BOOST_PP_CAT(m, n);

#define BOOST_TR1_TUPLE_MEMBER_EQUAL(z, n, data) \
    BOOST_PP_CAT(m, n) == t.BOOST_PP_CAT(m, n) &&

#define BOOST_TR1_TUPLE_MEMBER_NOT_EQUAL(z, n, data) \
    BOOST_PP_CAT(m, n) != t.BOOST_PP_CAT(m, n) ||

#define BOOST_TR1_TUPLE_MEMBER_LESS_THAN(z, n, data) \
    BOOST_PP_CAT(m, n) < t.BOOST_PP_CAT(m, n) ||

#define BOOST_TR1_TUPLE_MEMBER_GREATER_THAN(z, n, data) \
    BOOST_PP_CAT(m, n) > t.BOOST_PP_CAT(m, n) ||

#define BOOST_TR1_TUPLE_MEMBER_LESS_THAN_EQUAL(z, n, data) \
    BOOST_PP_CAT(m, n) <= t.BOOST_PP_CAT(m, n) \
      && (!(t.BOOST_PP_CAT(m, n) <= BOOST_PP_CAT(m, n)) || (

#define BOOST_TR1_TUPLE_MEMBER_GREATER_THAN_EQUAL(z, n, data) \
    BOOST_PP_CAT(m, n) >= t.BOOST_PP_CAT(m, n) \
      && (!(t.BOOST_PP_CAT(m, n) >= BOOST_PP_CAT(m, n)) || (

#define BOOST_TR1_TUPLE_DOUBLE_PARENTHESIS(z, n, data) ))

#define BOOST_TR1_TUPLE_MEMBER_DATA(z, n, data) \
    BOOST_PP_CAT(T, n) BOOST_PP_CAT(m, n);

#define BOOST_PP_ITERATION_PARAMS_1 \
    (3, (1, BOOST_TR1_TUPLE_MAX_ARITY, "boost/tr1/tuple/tuple_n.ipp"))
#include BOOST_PP_ITERATE()

#undef BOOST_TR1_TUPLE_MEMBER_INIT
#undef BOOST_TR1_TUPLE_MEMBER_COPY
#undef BOOST_TR1_TUPLE_MEMBER_ASSIGN
#undef BOOST_TR1_TUPLE_MEMBER_EQUAL
#undef BOOST_TR1_TUPLE_MEMBER_NOT_EQUAL
#undef BOOST_TR1_TUPLE_MEMBER_LESS_THAN
#undef BOOST_TR1_TUPLE_MEMBER_GREATER_THAN
#undef BOOST_TR1_TUPLE_MEMBER_LESS_THAN_EQUAL
#undef BOOST_TR1_TUPLE_MEMBER_GREATER_THAN_EQUAL
#undef BOOST_TR1_TUPLE_DOUBLE_PARENTHESIS
#undef BOOST_TR1_TUPLE_MEMBER_DATA

///////////////////////////////////////////////////////////////////////////////
//
//  The following Boost::PP code generate expansions for:
//
//      template <typename T0, typename T1... typename TN>
//      struct tuples
//      {
//          typedef boost::mpl::vectorM<
//              tuple_detail::tuple_holder_0,
//              tuple_detail::tuple_holder_1,
//              tuple_detail::tuple_holder_2,
//              ...
//              tuple_detail::tuple_holder_M
//          type;
//      };
//
//  where N = BOOST_TR1_TUPLE_MAX_ARITY and M = N + 1
//
///////////////////////////////////////////////////////////////////////////////

        #define BOOST_TR1_TUPLE_TUPLE_N_PARAM(z, n, data) \
            BOOST_PP_CAT(tuple_detail::tuple_holder_, n)

        struct tuple_holders
        {
            typedef
                BOOST_PP_CAT(
                    boost::mpl::vector,
                    BOOST_PP_INC(BOOST_TR1_TUPLE_MAX_ARITY))
                    <BOOST_PP_ENUM(
                        BOOST_PP_INC(BOOST_TR1_TUPLE_MAX_ARITY),
                        BOOST_TR1_TUPLE_TUPLE_N_PARAM, _) >
            type;
        };

        #undef BOOST_TR1_TUPLE_TUPLE_N_PARAM
    } // namespace tuple_detail
} // namespace tr1
} // namespace boost

///////////////////////////////////////////////////////////////////////////////
//
//  Our BOOST_TR1_TUPLE_MEMBERS_TYPE
//
//      Given N, the number of tuple elements (tuple::length or
//      tuple::length_t), select tuple_holder_N, its nested template
//      data<T0..TN> will be the actual data holder for our tuple (see
//      tuple.hpp's tuple::data member)
//
///////////////////////////////////////////////////////////////////////////////
#if defined __BORLANDC__ && __BORLANDC__ <= 0x561

//  Again, Borland chokes if the template parameter is a static constant
//  passed to boost::mpl::at_c (i.e. tuple::length). On the other hand, MSVC
//  chokes when we are using the tuple's length_t passed to boost::mpl::at.

    #define BOOST_TR1_TUPLE_MEMBERS_TYPE                          \
        typedef typename boost::mpl::at<                        \
            typename tuple_detail::tuple_holders::type,         \
            length_t                                            \
        >::type tuple_holder_t;                                 \
        typename tuple_holder_t::                               \
            template data<BOOST_TR1_TUPLE_TEMPLATE_ARGS>

#else

    #define BOOST_TR1_TUPLE_MEMBERS_TYPE                          \
        typedef typename boost::mpl::at_c<                      \
            typename tuple_detail::tuple_holders::type,         \
            length                                              \
        >::type tuple_holder_t;                                 \
        typename tuple_holder_t::                               \
            template data<BOOST_TR1_TUPLE_TEMPLATE_ARGS>

    #endif

#endif // defined(BOOST_TR1_TUPLE_TUPLE_N_IPP)

///////////////////////////////////////////////////////////////////////////////
//
//  Preprocessor vertical repetition code
//
///////////////////////////////////////////////////////////////////////////////
#else // defined(BOOST_PP_IS_ITERATING)

#define N BOOST_PP_ITERATION()

    struct BOOST_PP_CAT(tuple_holder_, N)
    {
        template <BOOST_TR1_TUPLE_TEMPLATE_PARAMS_MAX>
        struct data
        {
            data() : BOOST_TR1_TUPLE_DEFAULT_INIT_ELEMS(N) {}
            #if (N == 1)
            explicit
            #endif
            data(BOOST_TR1_TUPLE_CALL_TRAITS_PARAMS(N))
                : BOOST_PP_ENUM(N, BOOST_TR1_TUPLE_MEMBER_INIT, _) {}

            template <BOOST_TR1_TUPLE_TEMPLATE_PARAMS_MAX_B>
            data(data<BOOST_PP_ENUM_PARAMS(BOOST_TR1_TUPLE_MAX_ARITY, TB)> const& t)
                : BOOST_PP_ENUM(N, BOOST_TR1_TUPLE_MEMBER_COPY, _) {}

            template <typename TupleT>
            data&
            operator=(TupleT const& t)
            {
                BOOST_PP_REPEAT(N, BOOST_TR1_TUPLE_MEMBER_ASSIGN, _)
                return *this;
            }

            template <typename TupleT>
            bool operator==(TupleT const& t) const
            { return BOOST_PP_REPEAT(N, BOOST_TR1_TUPLE_MEMBER_EQUAL, _) true; }

            template <typename TupleT>
            bool operator!=(TupleT const& t) const
            { return BOOST_PP_REPEAT(N, BOOST_TR1_TUPLE_MEMBER_NOT_EQUAL, _) false; }

            template <typename TupleT>
            bool operator<(TupleT const& t) const
            { return BOOST_PP_REPEAT(N, BOOST_TR1_TUPLE_MEMBER_LESS_THAN, _) false; }

            template <typename TupleT>
            bool operator>(TupleT const& t) const
            { return BOOST_PP_REPEAT(N, BOOST_TR1_TUPLE_MEMBER_GREATER_THAN, _) false; }

            template <typename TupleT>
            bool operator<=(TupleT const& t) const
            { return BOOST_PP_REPEAT(BOOST_PP_DEC(N), BOOST_TR1_TUPLE_MEMBER_LESS_THAN_EQUAL, _)
    	         BOOST_PP_CAT(m, BOOST_PP_DEC(N)) <= t.BOOST_PP_CAT(m, BOOST_PP_DEC(N))
    	         BOOST_PP_REPEAT(BOOST_PP_DEC(N), BOOST_TR1_TUPLE_DOUBLE_PARENTHESIS, _); }

            template <typename TupleT>
            bool operator>=(TupleT const& t) const
            { return BOOST_PP_REPEAT(BOOST_PP_DEC(N), BOOST_TR1_TUPLE_MEMBER_GREATER_THAN_EQUAL, _)
    	         BOOST_PP_CAT(m, BOOST_PP_DEC(N)) >= t.BOOST_PP_CAT(m, BOOST_PP_DEC(N))
    	         BOOST_PP_REPEAT(BOOST_PP_DEC(N), BOOST_TR1_TUPLE_DOUBLE_PARENTHESIS, _); }

            BOOST_PP_REPEAT(N, BOOST_TR1_TUPLE_MEMBER_DATA, _)
        };
    };
    

#undef N
#endif // defined(BOOST_PP_IS_ITERATING)
