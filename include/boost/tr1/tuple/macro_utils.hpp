/*=============================================================================
    Copyright (c) 2001-2003 Joel de Guzman
    Copyright (c) 2001-2003 Jaakko Järvi

    Permission to copy, use, modify, sell and distribute this software
    is granted provided this copyright notice appears in all copies.
    This software is provided "as is" without express or implied
    warranty, and with no claim as to its suitability for any purpose.
==============================================================================*/
#if !defined(BOOST_TR1_TUPLE_MACRO_UTILS_HPP)
#define BOOST_TR1_TUPLE_MACRO_UTILS_HPP

///////////////////////////////////////////////////////////////////////////////
//
//  Boost PP macro utilities
//
///////////////////////////////////////////////////////////////////////////////

//  BOOST_TR1_TUPLE_TEMPLATE_PARAMS(n) expands to
//
//      typename T0, typename T1, ... template TN

#define BOOST_TR1_TUPLE_TEMPLATE_PARAM(z, n, data)                      \
    typename BOOST_PP_CAT(data, n)
#define BOOST_TR1_TUPLE_TEMPLATE_PARAMS(n)                              \
    BOOST_PP_ENUM(n, BOOST_TR1_TUPLE_TEMPLATE_PARAM, T)

//  BOOST_TR1_TUPLE_TEMPLATE_PARAMS_B(n) expands to
//
//      typename TB0, typename TB1, ... template TBN

#define BOOST_TR1_TUPLE_TEMPLATE_PARAMS_B(n)                            \
    BOOST_PP_ENUM(n, BOOST_TR1_TUPLE_TEMPLATE_PARAM, TB)

//  BOOST_TR1_TUPLE_TEMPLATE_PARAMS_WITH_DEFAULT(n, void_t) expands to
//
//      typename T0 = void_t, typename T1 = void_t, ... template TN = void_t

#define BOOST_TR1_TUPLE_TEMPLATE_PARAM_WITH_DEFAULT(z, n, data)         \
    typename BOOST_PP_CAT(T, n) = data
#define BOOST_TR1_TUPLE_TEMPLATE_PARAMS_WITH_DEFAULT(n, default_)       \
    BOOST_PP_ENUM(n, BOOST_TR1_TUPLE_TEMPLATE_PARAM_WITH_DEFAULT, default_)

//  BOOST_TR1_TUPLE_CALL_TRAITS_PARAMS(n) expands to
//
//      typename boost::call_traits<T0>::param_type _0,
//      typename boost::call_traits<T1>::param_type _1,
//      ...
//      typename boost::call_traits<TN>::param_type _N


// FIXME: Using call traits is different than what is specified in
// the TR. Probably does the same thing, but must be confirmed anyway.

// NO: it is not the same: Function references introduce errors:
// MUST FIX

#define BOOST_TR1_TUPLE_CALL_TRAITS_PARAM(z, n, data)                   \
    typename boost::call_traits<BOOST_PP_CAT(T, n)>             \
        ::param_type BOOST_PP_CAT(_, n)
#define BOOST_TR1_TUPLE_CALL_TRAITS_PARAMS(n)                           \
    BOOST_PP_ENUM(n, BOOST_TR1_TUPLE_CALL_TRAITS_PARAM, _)

//  BOOST_TR1_TUPLE_CALL_TRAITS_PARAMS_WITH_DEFAULT(n) expands to
//
//      typename boost::call_traits<T0>::param_type _0 = T0(),
//      typename boost::call_traits<T1>::param_type _1 = T1(),
//      ...
//      typename boost::call_traits<TN>::param_type _N = TN()

#define BOOST_TR1_TUPLE_CALL_TRAITS_PARAM_WITH_DEFAULT(z, n, data)      \
    typename boost::call_traits<BOOST_PP_CAT(T, n)>             \
        ::param_type BOOST_PP_CAT(_, n) = BOOST_PP_CAT(T, n)()
#define BOOST_TR1_TUPLE_CALL_TRAITS_PARAMS_WITH_DEFAULT(n)              \
    BOOST_PP_ENUM(n, BOOST_TR1_TUPLE_CALL_TRAITS_PARAM_WITH_DEFAULT, _)

//  BOOST_TR1_TUPLE_DEFAULT_INIT_ELEMS(n) expands to
//
//      m1(), m2(), ..., mN()

#define BOOST_TR1_TUPLE_DEFAULT_INIT_ELEM(z, n, data)      \
    BOOST_PP_CAT(m, n)()
#define BOOST_TR1_TUPLE_DEFAULT_INIT_ELEMS(n)              \
    BOOST_PP_ENUM(n, BOOST_TR1_TUPLE_DEFAULT_INIT_ELEM, _)

#endif // defined(BOOST_TR1_TUPLE_MACRO_UTILS_HPP)
