/*=============================================================================
    Copyright (c) 1999-2003 Jeremiah Willcock
    Copyright (c) 1999-2003 Jaakko Järvi
    Copyright (c) 2001-2003 Joel de Guzman

    Permission to copy, use, modify, sell and distribute this software
    is granted provided this copyright notice appears in all copies.
    This software is provided "as is" without express or implied
    warranty, and with no claim as to its suitability for any purpose.
==============================================================================*/


#ifndef BOOST_TR1_TUPLE_MANIP_HPP
#define BOOST_TR1_TUPLE_MANIP_HPP

#ifndef BOOST_TR1_TUPLE_TUPLEIO_HPP
#error "Must include "tupleio.hpp" for this library"
#endif

#include <iostream>
#include <string>

// Tuple I/O manipulators

// Based partially on Matt Austern's article at 
// http://www.cuj.com/experts/1902/austern.htm?topic=experts
// and Langer's and Kreft's book: Standard C++ IOStreams and Locales



namespace boost {
  namespace tr1 {
    namespace tuple_detail {

      // The type of string that is stored can vary (wchar streams etc.)
      // The pword mechanism need to be able to allocate/clone/etc. 
      // objecst of some fixed type. Hence this virtual construction 
      // wrapper.
      struct any_string {
	virtual any_string* clone() = 0;
      };
      
      template <class Str> 
      class string_holder : public any_string {
	Str s;
      public:
	string_holder(const Str& s_) : s(s_) {}

	Str get() const { return s; }

	virtual string_holder* clone() { return new string_holder(s); }
      };

      void string_manip_callback(std::ios_base::event ev,
				 std::ios_base& b,
				 int n)
      {
	any_string*  p = (any_string*) b.pword(n);
	if (ev == std::ios_base::erase_event) {
	  // maybe the delete should be wrapped in a try_catch as well?
	  delete p;
	  b.pword(n) = 0;
	}
	else if (ev == std::ios_base::copyfmt_event && p != 0)
	  try {
	    b.pword(n) = p->clone(); 
	  } 
	  catch(std::bad_alloc&) { 
	
	    // Standard prohibits this callback function from
	    // thwrowing exceptions. Bad_alloc could occur, so it must
	    // be supressed.  We cannot directly set the stream state
	    // into bad, as the we only have access to ios_base, not
	    // the stream :( One way to indicate that error has
	    // occurred is to set the corresponding iword slot into
	    // some error value and examine that after cpyfmt
	    // call. That is not specified in the tr1 though and we
	    // just suppress the exception for now. It is a hack :(
	  }
      }

      template <class Tag>
      struct string_ios_manip_helper {
	static int index() {
	  static int index_ = std::ios_base::xalloc();
	  return index_;
	}
      };
      
      template <class Tag, class Stream>
      class string_ios_manip {
		
	int index; Stream& stream;
	
	typedef std::basic_string<typename Stream::char_type,
				  typename Stream::traits_type> stringT;
	
      public:
	string_ios_manip(Stream& str_): stream(str_) {
	  index = string_ios_manip_helper<Tag>::index();
	}
	
	void set(const stringT& s) {
	  int registered = stream.iword(index);
	  // avoid registering the callback twice
	  if (!registered) {
	    stream.iword(index) = 1;
	    stream.register_callback(&string_manip_callback, index); 
	  }
	  any_string* p = (any_string*)(stream.pword(index));
	  if (p) delete p;
	  stream.pword(index) = (void*)(new string_holder<stringT>(s));
	}
	
	stringT get(const stringT& default_) const {
	  any_string* a = (any_string*)stream.pword(index);
	  if (a) {
	    return (static_cast<string_holder<stringT>* >(a))->get();
	  }
	  else {
	    return default_;
	  }
	}
      };
    } // tuple_detail

#define STD_TUPLE_DEFINE_MANIPULATOR(name) \
  namespace tuple_detail { \
    struct name##_tag; \
 \
    template <class CharT, class Traits = std::char_traits<CharT> > \
    struct name##_type { \
      typedef std::basic_string<CharT,Traits> stringT; \
      stringT data; \
      name##_type(const stringT& d): data(d) {} \
    }; \
 \
    template <class Stream, class CharT, class Traits> \
    Stream& \
    operator>> \
	(Stream& s, \
	 const name##_type<CharT,Traits>& m) { \
      string_ios_manip<name##_tag, Stream>(s). \
	set(m.data); \
      return s; \
    } \
 \
    template <class Stream, class CharT, class Traits> \
    Stream& \
    operator<< \
	(Stream& s, \
	 const name##_type<CharT,Traits>& m) { \
      string_ios_manip<name##_tag, Stream>(s). \
	set(m.data); \
      return s; \
    } \
  } \
  \
  template <class CharT, class Traits> \
  tuple_detail::name##_type<CharT,Traits> \
  name(const std::basic_string<CharT,Traits>& s) { \
    return tuple_detail::name##_type<CharT,Traits>(s); \
  } \
 \
  template <class CharT> \
  tuple_detail::name##_type<CharT> \
  name(const CharT c[]) { \
    return tuple_detail::name##_type<CharT>(std::basic_string<CharT>(c)); \
  } \
 \
  template <class CharT> \
  tuple_detail::name##_type<CharT> \
  name(CharT c) { \
    return tuple_detail::name##_type<CharT>(std::basic_string<CharT>(1,c)); \
  }

  STD_TUPLE_DEFINE_MANIPULATOR(tuple_open)
  STD_TUPLE_DEFINE_MANIPULATOR(tuple_close)
  STD_TUPLE_DEFINE_MANIPULATOR(tuple_delimiter)

#undef STD_TUPLE_DEFINE_MANIPULATOR

  } // namespace tr1
} // namespace boost

#endif // BOOST_TR1_TUPLE_MANIP_HPP
