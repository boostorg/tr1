/*=============================================================================
    Copyright (c) 1999-2003 Jaakko Järvi
    Copyright (c) 2001-2003 Joel de Guzman

    Permission to copy, use, modify, sell and distribute this software
    is granted provided this copyright notice appears in all copies.
    This software is provided "as is" without express or implied
    warranty, and with no claim as to its suitability for any purpose.
==============================================================================*/
#if !defined(BOOST_PP_IS_ITERATING)
#if !defined(BOOST_TR1_TUPLE_ELEMENT_AT_IPP)
#define BOOST_TR1_TUPLE_ELEMENT_AT_IPP

#include <boost/preprocessor/iterate.hpp>

///////////////////////////////////////////////////////////////////////////////
//
//  The following Boost::PP code generate expansions for:
//
//      struct element_at_N
//      {
//          template <typename T0... typename TM>
//          static typename element<N, tuple<T0... TM> >::const_reference
//          get(tuple<T0... TM> const& t) { return t.data.mN; }
//
//          template <typename T0... typename TM>
//          static typename element<N, tuple<T0... TM> >::reference
//          get(tuple<T0... TM>& t) { return t.data.mN; }
//      };
//
//  where N runs from 0 to BOOST_TR1_TUPLE_MAX_ARITY
//  and M = BOOST_TR1_TUPLE_MAX_ARITY
//
///////////////////////////////////////////////////////////////////////////////
namespace tuple_detail
{
    #define BOOST_PP_ITERATION_PARAMS_1                     \
        (3, (0, BOOST_TR1_TUPLE_MAX_ARITY,                   \
        "boost/tr1/tuple/tuple_element_at.ipp"))
    #include BOOST_PP_ITERATE()
}

///////////////////////////////////////////////////////////////////////////////
//
//  The following Boost::PP code generates:
//
//      typename boost::mpl::at_c<
//          boost::mpl::vectorMAX<
//              tuple_detail::element_at_0,
//              tuple_detail::element_at_1,
//              ...
//              tuple_detail::element_at_MAX>,
//          N
//      >::type
//
//  where MAX = BOOST_TR1_TUPLE_MAX_ARITY+1
//
///////////////////////////////////////////////////////////////////////////////
    #define BOOST_TR1_TUPLE_ELEMENT_AT_N_PARAM(z, n, data)          \
        BOOST_PP_CAT(tuple_detail::element_at_, n)
    #define BOOST_TR1_TUPLE_ELEMENT_AT_N                            \
        typename boost::mpl::at_c<                          \
            BOOST_PP_CAT(                                   \
                boost::mpl::vector,                         \
                BOOST_PP_INC(BOOST_TR1_TUPLE_MAX_ARITY))     \
                <BOOST_PP_ENUM(                             \
                    BOOST_PP_INC(BOOST_TR1_TUPLE_MAX_ARITY), \
                    BOOST_TR1_TUPLE_ELEMENT_AT_N_PARAM, _)>,        \
            N                                               \
        >::type                                             \

namespace tuple_detail
{
    template <unsigned N>
    struct element_at_
    {
        typedef BOOST_TR1_TUPLE_ELEMENT_AT_N type;
    };
}

#undef BOOST_TR1_TUPLE_ELEMENT_AT_N_PARAM
#undef BOOST_TR1_TUPLE_ELEMENT_AT_N
#endif // defined(BOOST_TR1_TUPLE_ELEMENT_AT_IPP)

///////////////////////////////////////////////////////////////////////////////
//
//  Preprocessor vertical repetition code
//
///////////////////////////////////////////////////////////////////////////////
#else // defined(BOOST_PP_IS_ITERATING)

#define N BOOST_PP_ITERATION()

    struct BOOST_PP_CAT(element_at_, N)
    {
        template <BOOST_TR1_TUPLE_TEMPLATE_PARAMS(BOOST_TR1_TUPLE_MAX_ARITY)>
        static
        typename tuple_detail::const_get_result<N, tuple<BOOST_TR1_TUPLE_TEMPLATE_ARGS> >::type
        get(tuple<BOOST_TR1_TUPLE_TEMPLATE_ARGS> const& t)
        { return t.data.BOOST_PP_CAT(m, N); }

        template <BOOST_TR1_TUPLE_TEMPLATE_PARAMS(BOOST_TR1_TUPLE_MAX_ARITY)>
        static
        typename tuple_detail::get_result<N, tuple<BOOST_TR1_TUPLE_TEMPLATE_ARGS> >::type
        get(tuple<BOOST_TR1_TUPLE_TEMPLATE_ARGS>& t)
        { return t.data.BOOST_PP_CAT(m, N); }
    };

#undef N
#endif // defined(BOOST_PP_IS_ITERATING)
