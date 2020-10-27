#ifndef JSON_POINTER_TEST_H
#define JSON_POINTER_TEST_H

#include "unit_test.h"
#include "../json_pointer/json_pointer.h"

namespace format
{
  /**
  * @brief The json_pointer_test class
  */
  class json_pointer_test : public unit_test
  {
    public:
    class json_pointer_accessor : public json_pointer
    {
      public:
      json_pointer_accessor (const wchar_t * const path)
        : json_pointer (path) {}

      std::size_t
      _parse (const wchar_t * const path)
      { return json_pointer::_parse (path); }
    };
  };

  TEST_F (json_pointer_test, test_parse)
  {
    json_pointer_accessor jp (L"");
    std::size_t c = jp._parse (L"/foo/bar");

    ASSERT_EQ (c, 0);
  }
}

#endif // JSON_POINTER_TEST_H
