#ifndef JSON_POINTER_ERROR
#define JSON_POINTER_ERROR

#include <cstdlib>
#include <format/json_exception.h>

namespace format
{
  namespace json
  {
    /**
     * @brief The json_pointer_error class
     */
    class json_pointer_error : public json_syntax_error
    {
    public:
      /**
       * @brief json_pointer_error
       * @param what
       */
      json_pointer_error (const char * const what)
       : json_syntax_error (what)
      {}
      /**
       * @brief json_pointer_error
       * @param what
       * @param token
       * @param charc
       */
      json_pointer_error (const char * const what, const wchar_t *token, size_t charc = 0)
       : json_syntax_error (what, token, charc)
      {}
    }; // Class json_pointer_error
  } // Namespace json
} // Namespace format

#endif // JSON_POINTER_ERROR

