/*=============================================================================
    Copyright (c) 1999-2003 Jaakko Järvi
    Copyright (c) 2001-2003 Joel de Guzman

    Permission to copy, use, modify, sell and distribute this software
    is granted provided this copyright notice appears in all copies.
    This software is provided "as is" without express or implied
    warranty, and with no claim as to its suitability for any purpose.
==============================================================================*/
#if !defined(BOOST_PP_IS_ITERATING)
#if !defined(BOOST_TR1_TUPLE_GENERATOR_IPP)
#define BOOST_TR1_TUPLE_GENERATOR_IPP

#include <boost/preprocessor/iterate.hpp>

///////////////////////////////////////////////////////////////////////////////
//
//      The following Boost::PP code generate expansions for:
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
//      where N runs from 1 to BOOST_TR1_TUPLE_MAX_ARITY and as_tuple_element
//      is a metafunction that converts a ref(T) to a reference to T, a
//      cref(T) to a const reference to T, T[N] to T(&type)[N], and of course
//      a T left unconverted as-is to a T.
//
///////////////////////////////////////////////////////////////////////////////
    namespace tuple_detail
    {

    #if !defined BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

    //  I do not know why Borland chokes on the MPL code below in the #else
    //  branch. Oh my, Borland! Anyway, there's no way with MPL to convert an
    //  array to a pointer so probably, PTS is still the way to go to allow
    //  constant literals arguments to make_tuple, e.g. make_tuple("Hello").

        template <typename T>
        struct as_tuple_element
        { typedef T type; };

        template <typename T>
        struct as_tuple_element<boost::reference_wrapper<T> >
        { typedef T& type; };

    #if !defined(__MWERKS__) || (__MWERKS__ > 0x2407)
        template <typename T>
        struct as_tuple_element<boost::reference_wrapper<T> const>
        { typedef T& type; };
    #endif
        template <typename T, int N>
        struct as_tuple_element<T[N]>
        { typedef const T(&type)[N]; };

        template <typename T, int N>
        struct as_tuple_element<volatile T[N]>
        { typedef const volatile T(&type)[N]; };

        template <typename T, int N>
        struct as_tuple_element<const volatile T[N]>
        { typedef const volatile T(&type)[N]; };
    #else

        //  The Non-PTS version cannot accept arrays since there is no way to
        //  get the element type of an array T[N]. However, we shall provide
        //  the most common case where the array is a char[N] or wchar_t[N].
        //  Doing so will allow literal string argument types.

        template <typename T>
        struct as_tuple_element
        {
            typedef typename boost::mpl::if_<
                boost::is_reference_wrapper<T>,
                typename boost::add_reference<
                    typename boost::unwrap_reference<T>::type
                >::type,
                typename maybe_string<T>::type
            >::type type;
        };

    #endif
    }

#if defined(BOOST_MSVC) && (BOOST_MSVC <= 1200)
#define BOOST_TR1_TUPLE_TYPENAME
#else
#define BOOST_TR1_TUPLE_TYPENAME typename
#endif

#define BOOST_TR1_TUPLE_AS_TUPLE_ELEMENT(z, n, data)        \
    BOOST_TR1_TUPLE_TYPENAME tuple_detail::as_tuple_element<        \
        BOOST_PP_CAT(T, n)>::type

#define BOOST_TR1_TUPLE_REFERENCE_TYPE(z, n, data)          \
    BOOST_PP_CAT(T, n)&

#define BOOST_TR1_TUPLE_REFERENCE_ARG(z, n, data)           \
    BOOST_PP_CAT(T, n)& BOOST_PP_CAT(_, n)

#define BOOST_TR1_TUPLE_CONST_REFERENCE_ARG(z, n, data)     \
    BOOST_PP_CAT(T, n) const& BOOST_PP_CAT(_, n)

#define BOOST_PP_ITERATION_PARAMS_1                 \
    (3, (1, BOOST_TR1_TUPLE_MAX_ARITY,               \
    "boost/tr1/tuple/tuple_generator.ipp"))
#include BOOST_PP_ITERATE()

#undef BOOST_TR1_TUPLE_TYPENAME
#undef BOOST_TR1_TUPLE_AS_TUPLE_ELEMENT
#undef BOOST_TR1_TUPLE_REFERENCE_TYPE
#undef BOOST_TR1_TUPLE_REFERENCE_ARG
#undef BOOST_TR1_TUPLE_CONST_REFERENCE_ARG
#endif // defined(BOOST_TR1_TUPLE_GENERATOR_IPP)

///////////////////////////////////////////////////////////////////////////////
//
//  Preprocessor vertical repetition code
//
///////////////////////////////////////////////////////////////////////////////
#else // defined(BOOST_PP_IS_ITERATING)

#define N BOOST_PP_ITERATION()

    template <BOOST_TR1_TUPLE_TEMPLATE_PARAMS(N)>
    inline tuple<BOOST_PP_ENUM(N, BOOST_TR1_TUPLE_AS_TUPLE_ELEMENT, _)>
    make_tuple(BOOST_PP_ENUM(N, BOOST_TR1_TUPLE_CONST_REFERENCE_ARG, _))
    {
        return tuple<BOOST_PP_ENUM(N, BOOST_TR1_TUPLE_AS_TUPLE_ELEMENT, _)>
            (BOOST_PP_ENUM_PARAMS(N, _));
    }

    template <BOOST_TR1_TUPLE_TEMPLATE_PARAMS(N)>
    inline tuple<BOOST_PP_ENUM(N, BOOST_TR1_TUPLE_REFERENCE_TYPE, _)>
    tie(BOOST_PP_ENUM(N, BOOST_TR1_TUPLE_REFERENCE_ARG, _))
    {
        return tuple<BOOST_PP_ENUM(N, BOOST_TR1_TUPLE_REFERENCE_TYPE, _)>
            (BOOST_PP_ENUM_PARAMS(N, _));
    }

#undef N
#endif // defined(BOOST_PP_IS_ITERATING)
