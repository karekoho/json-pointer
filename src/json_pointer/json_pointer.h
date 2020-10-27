#ifndef JSON_POINTER_H
#define JSON_POINTER_H

#include "json_pointer_global.h"
#include "json_exception.h"
#include <format/json.h>
#include <wctype.h>

namespace format
{
  /**
   * @brief The json_pointer class
   */
  class JSON_POINTER_EXPORT json_pointer
  {
  public:
    /**
     * @brief json_pointer
     * @param json_pointer
     */
    json_pointer (const wchar_t * const);

    /**
     * @brief get
     * @param json
     * @return
     */
    format::value * get (format::json const &) const;

  protected:
    /**
     * @brief _json_pointer
     */
    std::vector<const wchar_t * const> _json_pointer;

    /**
     * @brief _parse
     * @param json_pointer
     * @return
     */
    std::size_t _parse (const wchar_t * const);

    /**
     * @brief _point
     * @param json
     * @param cursor
     * @param end
     * @return
     */
    format::value * _point (format::json const &, const std::vector<const wchar_t * const>::const_iterator, const std::vector<const wchar_t * const>::const_iterator) const;

    /**
     * @brief The reference_token class
     */
    class reference_token
    {
      /**
       * @brief The _sc enum Structural characters.
       */
      enum _sc
      {
        path_separator  = 47,   // /
      };

      /**
       * @brief __key_len
       */
      std::size_t __key_len;

      /**
       * @brief __key
       */
      wchar_t * __key;

      /**
       * @brief __path_pointer
       */
      const wchar_t * __path_pointer;

    public:
      /**
       * @brief The __esc enum JSON path escape characters
       */
      enum escape
      {
        reverse_solidus   = 47,   // /
        zero              = 48,   // 0
        one               = 49,   // 1
        tilde             = 126   // ~
      };


      /**
       * @brief The __index enum
       */
      enum index
      {
        first       = 48,   // 0
        last        = 57,   // 9
        new_index   = 45    // -
      };

      /**
       * @brief reference_token
       * @param path_pointer
       */
      reference_token (const wchar_t * path_pointer)
        : __key_len (wcslen (path_pointer) + 1),
          __key (nullptr),
          __path_pointer (path_pointer)
      {
      }

      /**
       * @brief destructor
       */
      ~reference_token ()
      {
        delete [] __key;
      }

      /**
       * decode: ~    --> ''
       * decode: ~0   --> ~
       * decode: ~1   --> /
       * decode: ~01  --> ~1
       *
       * @brief decode
       * @param key
       * @param path_pointer
       * @return
       */
      static wchar_t *
      decode (wchar_t *key, const wchar_t **path_pointer)
      {
        const wchar_t *pp = *path_pointer;

        if (*pp != escape::tilde) // Just copy the character
          {
            *key = *pp;
            *path_pointer = pp + 1;

            return key + 1;
          }

        if (*(pp + 1) == escape::zero) // ~0
          {
            if (*(pp + 2) == escape::one)  // ~01
              {
                // Copy ~1 to key
                *key = escape::tilde;
                *(key + 1) = escape::one;

                *path_pointer = pp + 3;

                return key + 2;
              }

            *key = escape::tilde;
            *path_pointer = pp + 2;

            return key + 1;
          }

        if (*(pp + 1) == escape::one) // ~1
          {
            *key = escape::reverse_solidus;
            *path_pointer = pp + 2;

            return key + 1;
          }

        // Unescaped '~'
        throw json_pointer_error ("Character '~' must be escaped");
      }

      /**
       * @brief is_index
       * @param key
       * @return
       */
      static bool
      is_index (const wchar_t *key) noexcept
      {
        bool is_index = false;
        const wchar_t * const begin = key;

        while (*key > 0 && (is_index = ((*key >= index::first && *key <= index::last) || *key == index::new_index)))
          key++;

        return *begin == index::first || *begin == index::new_index
            ? key - begin == 1
            : is_index;
      }

      /**
       * @brief path_next
       * @return
       * @todo Return empty string if json pointer is "/" or "\0"
       */
      const wchar_t *
      path_next ()
      {
        __key = __key == nullptr
            ? new wchar_t[__key_len] ()
              : wmemset (__key, 0, __key_len);

        wchar_t * key_cursor = __key;
        wchar_t * const key_begin = key_cursor;

        if (*__path_pointer == _sc::path_separator)
          {
            if (*(__path_pointer + 1) == 0)
              return L"/";

            __path_pointer++; // Skip leading '/'
          }

        while (*__path_pointer != 0 && *__path_pointer != _sc::path_separator)
          key_cursor = decode (key_cursor, & __path_pointer);

        return key_begin;
      }
    }; // Class refence_token
  };
}

#endif // JSON_POINTER_H
