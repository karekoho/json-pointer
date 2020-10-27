#ifndef JSON_EXCEPTION
#define JSON_EXCEPTION

#include <exception>
#include <cstdlib>
#include <alloca.h>
#include <string>
#include <cwchar>

namespace format
{
  /**
   * @brief The JSON_Error class
   */
  class json_error : public std::exception
  {
    public:
    /**
     * @brief JSON_Error
     * @param what
     */
    json_error (const char * const what)
      : exception (),
        _what (what)
    {
    }

    /**
     * @brief what
     * @return
     */
    virtual const char *
    what () const noexcept override
    { return _what.c_str (); }

  protected:

    /**
     * @brief _what
     */
    std::string _what;
  };

  /**
   * @brief The JSON_Syntax_Error class
   */
  class json_syntax_error : public json_error
  {
  public:
    /**
     * @brief Syntax_Error
     * @param what
     */
    json_syntax_error (const char * const what)
      : json_error (what)
    {}

    /**
     * @see http://www.cplusplus.com/reference/cstdlib/wcstombs/
     * @brief Syntax_Error
     * @param what
     * @param token
     */
    json_syntax_error (const char * const what, const wchar_t *token, size_t charc = 0)
      : json_error (what)
    {
      _add_token (token, charc);
    }

  protected:    
    /**
     * @brief _add_token
     * @param token
     * @param charc
     * @return
     */
    size_t _add_token (const wchar_t *token, size_t offset);
  };

  /**
   * @brief The JSON_Out_Of_Range class
   */
  class json_out_of_range : public json_error
  {
  public:
    /**
     * @brief Syntax_Error
     * @param what
     */
    json_out_of_range (const char * const what)
      : json_error (what)
    {}
  };

  /**
   * @brief The json_conversion_error class
   */
  class json_conversion_error : public json_error
  {
    public:
    /**
     * @brief json_conversion_error
     * @param what
     */
    json_conversion_error (const char * const what)
      : json_error (what)
    {}
  };

  /**
   * @brief The json_pointer_error class
   */
  class json_pointer_error : public json_syntax_error
  {
  public:
    json_pointer_error (const char * const what)
     : json_syntax_error (what)
    {}

    json_pointer_error (const char * const what, const wchar_t *token, size_t charc = 0)
     : json_syntax_error (what, token, charc)
    {}
  };
} // Namespace format

#endif // JSON_EXCEPTION

