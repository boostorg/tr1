/*=============================================================================
    Copyright (c) 1999-2003 Jaakko Järvi
    Copyright (c) 2001-2003 Joel de Guzman

    Permission to copy, use, modify, sell and distribute this software
    is granted provided this copyright notice appears in all copies.
    This software is provided "as is" without express or implied
    warranty, and with no claim as to its suitability for any purpose.
==============================================================================*/
#if !defined(BOOST_TR1_TUPLE_TUPLE_IDENTITY_IPP)
#define BOOST_TR1_TUPLE_TUPLE_IDENTITY_IPP

///////////////////////////////////////////////////////////////////////////////
//
//  tuple_identity
//
//      Given a list of types T0..TN, where each element can either be void_t
//      or an arbitrary type, the objective is to create a unique type based
//      on the number of non-void_t template parameters passed in.
//
//      The simplest scheme is to actually count the number of template
//      parameters from T0 until we get a void_t. However, this not so
//      compile-time efficient. The scheme presented simply creates a type
//      where all non-void_t template parameters are converted to struct
//      non_void_t. For example:
//
//          tuple_identity<int, char, double, void_t, void_t>::type
//
//      is:
//
//          boost::mpl::vector5<
//              non_void_t, non_void_t, non_void_t, void_t, void_t>
//
///////////////////////////////////////////////////////////////////////////////
#define BOOST_TR1_TUPLE_IDENTITY_PARAM(z, n, data)  \
    typename id_type<BOOST_PP_CAT(T, n)>::type

    namespace tuple_detail
    {
        struct non_void_t {};

        template <typename T>
        struct id_type
        { typedef non_void_t type; };

        template <>
        struct id_type<void_t>
        { typedef void_t type; };

        template <BOOST_TR1_TUPLE_TEMPLATE_PARAMS_MAX>
        struct tuple_identity
        {
            typedef BOOST_PP_CAT(boost::mpl::vector, BOOST_TR1_TUPLE_MAX_ARITY)<
                BOOST_PP_ENUM(
                    BOOST_TR1_TUPLE_MAX_ARITY, BOOST_TR1_TUPLE_IDENTITY_PARAM, _)> type;
        };
    }

#undef BOOST_TR1_TUPLE_IDENTITY_PARAM

#if defined(BOOST_MSVC) && (BOOST_MSVC <= 1200)
#define BOOST_TR1_TUPLE_ID    \
    tuple_detail::tuple_identity<BOOST_TR1_TUPLE_TEMPLATE_ARGS>::type
#else
#define BOOST_TR1_TUPLE_ID    \
    typename tuple_detail::tuple_identity<BOOST_TR1_TUPLE_TEMPLATE_ARGS>::type
#endif

#endif // defined(BOOST_TR1_TUPLE_TUPLE_IDENTITY_IPP)
