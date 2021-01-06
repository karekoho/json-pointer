#include "json_pointer.h"

format::json_pointer::json_pointer (const wchar_t * const json_pointer)
{
  (void) _parse (json_pointer);
}

format::json_pointer::~json_pointer ()
{
  for (auto it = _json_pointer.begin (); it != _json_pointer.end (); ) {
    const wchar_t *key = *it;
    it = _json_pointer.erase (it);
    delete [] key;
   }
}

format::value &
format::json_pointer::get (json & json) const
{
  return _point (json, _json_pointer.cbegin ());
}

format::value &
format::json_pointer::get (const wchar_t * const json_text) const
{
  if (json_text == nullptr)
    throw json_pointer_error ("JSON text is null");

  format::json json (json_text);
  return get (json);
}

std::size_t
format::json_pointer::_parse (const wchar_t * const json_pointer)
{
  if (json_pointer == nullptr)
    throw json_pointer_error ("JSON pointer is null");

  reference_token rt (json_pointer);
  const wchar_t * key = nullptr;

  while (*(key = rt.path_next ()) != 0)
    {
      wchar_t *clone = new wchar_t[wcslen (key) + 1]();
      _json_pointer.push_back (wcscpy (clone, key));
    }

  return _json_pointer.size ();
}

format::value &
format::json_pointer::_point (value & v, std::vector<const wchar_t *>::const_iterator cur) const
{
  if (cur == _json_pointer.cend ())
    return v;

  const wchar_t *key = *cur;

  if (v.type () == value::value_t::undefined_t)
      throw json_pointer_error ("Key pointing elsewhere than the end of the path must exist. Non-existent key is preceding ", key);

  if (*key == reference_token::sc::path_separator)
    return v[L""];

  if (v.type () == value::value_t::array_t)
    {
      if (! json_pointer::reference_token::is_index (key))
        throw json_pointer_error ("Invalid array index: ", key);

       if (*key == json_pointer::reference_token::index::new_index)
        return v[v.count ()];
    }

  return _point (v[key], ++cur);
}
