#ifndef USAGE_H
#define USAGE_H

#include <iostream>
#include <array>
#include <format/json.h>
#include "../json_pointer/json_pointer.h"

void
usage ()
{
  format::json j = L"{ \"foo\": [\"bar\", \"baz\"],\
                          \"\": 0,\
                          \"a/b\": 1,\
                          \"c%d\": 2,\
                          \"e^f\": 3,\
                          \"g|h\": 4,\
                          \"i\\j\": 5,\
                          \" \": 7,\
                          \"m~n\": 8 }";

  std::array<format::json_pointer, 13> jp_list = {
      L"",            // the whole document
      L"/foo",        // ["bar", "baz"]
      L"/foo/0",      // "bar"
      L"/",           // 0
      L"/a~1b",       // 1
      L"/c%d",        // 2
      L"/e^f",        // 3
      L"/g|h",        // 4
      L"/i\\j",       // 5
      /* FIXME: L"/k\"l"      // 6 */
      L"/ ",          // 7
      L"/m~0n",       // 8
      L"/notfound",   // empty string
      L"/not/found"   // exception
  };

  for (auto& jp : jp_list)
    {
      try {
        format::value & v =  jp.get (j);
        std::wcout << v.stringify () << std::endl;
      } catch (format::json_pointer_error & e) {
        std::wcerr << e.what () << std::endl;
      }
    }

  /* output:
  {"i\j":5," ":7,"g|h":4,"a/b":1,"":0,"e^f":3,"c%d":2,"m~n":8,"foo":["bar","baz"]}
  ["bar","baz"]
  "bar"
  0
  1
  2
  3
  4
  5
  7
  8

  Key pointing elsewhere than the end of the path must exist. Non-existent key is preceding 'found'
  */
}

#endif // USAGE_H
