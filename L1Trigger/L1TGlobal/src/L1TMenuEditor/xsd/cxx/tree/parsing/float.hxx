// file      : xsd/cxx/tree/parsing/float.hxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2010 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef XSD_CXX_TREE_PARSING_FLOAT_HXX
#define XSD_CXX_TREE_PARSING_FLOAT_HXX

#include <limits>
#include <locale>

#include <L1Trigger/L1TGlobal/src/L1TMenuEditor/xsd/cxx/ro-string.hxx>
#include <L1Trigger/L1TGlobal/src/L1TMenuEditor/xsd/cxx/zc-istream.hxx>

#include <L1Trigger/L1TGlobal/src/L1TMenuEditor/xsd/cxx/xml/string.hxx> // xml::transcode

#include <L1Trigger/L1TGlobal/src/L1TMenuEditor/xsd/cxx/tree/text.hxx>  // text_content
#include <L1Trigger/L1TGlobal/src/L1TMenuEditor/xsd/cxx/tree/bits/literals.hxx>

namespace xsd
{
  namespace cxx
  {
    namespace tree
    {
      template <typename C>
      struct traits<float, C, schema_type::other>
      {
        typedef float type;

        static type
        create (const xercesc::DOMElement& e, flags f, container* c);

        static type
        create (const xercesc::DOMAttr& a, flags f, container* c);

        static type
        create (const std::basic_string<C>& s,
                const xercesc::DOMElement*,
                flags,
                container*);
      };

      template <typename C>
      float traits<float, C, schema_type::other>::
      create (const xercesc::DOMElement& e, flags f, container* c)
      {
        return create (text_content<C> (e), 0, f, c);
      }

      template <typename C>
      float traits<float, C, schema_type::other>::
      create (const xercesc::DOMAttr& a, flags f, container* c)
      {
        return create (xml::transcode<C> (a.getValue ()), 0, f, c);
      }

      template <typename C>
      float traits<float, C, schema_type::other>::
      create (const std::basic_string<C>& s,
              const xercesc::DOMElement*,
              flags,
              container*)
      {
        // This type cannot have whitespaces in its values. As result we
        // don't need to waste time collapsing whitespaces. All we need to
        // do is trim the string representation which can be done without
        // copying.
        //
        ro_string<C> tmp (s);
        trim (tmp);

        if (tmp == bits::positive_inf<C> ())
          return std::numeric_limits<float>::infinity ();

        if (tmp == bits::negative_inf<C> ())
          return -std::numeric_limits<float>::infinity ();

        if (tmp == bits::nan<C> ())
          return std::numeric_limits<float>::quiet_NaN ();

        zc_istream<C> is (tmp);
        is.imbue (std::locale::classic ());

        type t;
        is >> t;

        return t;
      }
    }
  }
}

#endif // XSD_CXX_TREE_PARSING_FLOAT_HXX
