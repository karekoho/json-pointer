#include "json_pointer.h"

format::json_pointer::json_pointer (const wchar_t * const json_pointer)
{
  (void) _parse (json_pointer);
}

format::value *
format::json_pointer::get (const format::json & json) const
{
  return nullptr;
}

std::size_t
format::json_pointer::_parse (const wchar_t * const json_pointer)
{
  if (json_pointer == nullptr)
    throw json_pointer_error ("JSON pointer is null");

  reference_token rt (json_pointer);
  const wchar_t * key = nullptr;

  while (*(key = rt.path_next ()) != 0)
    _json_pointer.push_back (key);

  return _json_pointer.size ();
}

format::value *
format::json_pointer::_point (const format::json & json,
                              const std::vector<const wchar_t * const>::const_iterator cursor,
                              const std::vector<const wchar_t * const>::const_iterator end) const
{
  return nullptr;
}
