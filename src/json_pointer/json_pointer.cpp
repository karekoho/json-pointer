#include "json_pointer.h"

format::json_pointer::json_pointer (const wchar_t * const json_pointer)
{
}

format::value *
format::json_pointer::get (const format::json & json) const
{
  return nullptr;
}

std::size_t
format::json_pointer::_parse (const wchar_t * const)
{
  return 0;
}

format::value *
format::json_pointer::_point (const format::json & json,
                              const std::vector<const wchar_t * const>::const_iterator cursor,
                              const std::vector<const wchar_t * const>::const_iterator end) const
{
  return nullptr;
}
