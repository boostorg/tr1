/*=============================================================================
    Copyright (c) 2001-2002 Joel de Guzman

    Permission to copy, use, modify, sell and distribute this software
    is granted provided this copyright notice appears in all copies.
    This software is provided "as is" without express or implied
    warranty, and with no claim as to its suitability for any purpose.
==============================================================================*/
#if !defined(BOOST_TR1_TUPLE_HELPERS_HPP)
#define BOOST_TR1_TUPLE_HELPERS_HPP

namespace boost { 
namespace tr1 {
namespace tuple_detail {

    template <typename T>
    struct maybe_string
    {
        typedef typename
            boost::mpl::if_<
                boost::is_array<T>,
                typename boost::mpl::if_<
                    boost::is_convertible<T, char const*>,
                    char const*,
                    typename boost::mpl::if_<
                        boost::is_convertible<T, wchar_t const*>,
                        wchar_t const*,
                        T>::type
                    >::type,
                T
            >::type
        type;
    };

}}} //  namespace boost::tr1::tuple_detail

#endif
