#ifndef JSON_POINTER_TEST_H
#define JSON_POINTER_TEST_H

#include "unit_test.h"
#include "../json_pointer/json_pointer.h"

namespace format
{
  namespace test
  {
   /**
    * @brief The json_pointer_test class
    */
    class json_pointer_test : public unit_test {};

    TEST_F (json_pointer_test, path_next)
    {
      struct assert
      {
        const wchar_t *ref_token;
        std::vector<const wchar_t *> key_vec;
        int assert_status;
      };

      std::vector<struct assert > test = {
        { L"", { L"" } , T_PASS },
        { L"/", { L"/" } , T_PASS },
        { L"/foo", { L"foo" } , T_PASS },
        { L"/foo/0", { L"foo", L"0" } , T_PASS },
        { L"/1/0123/foo", { L"1", L"0123", L"foo" } , T_PASS },
      };

      TEST_IT_START

          json_pointer::reference_token rt ((*it).ref_token);

          for (auto exp_it = (*it).key_vec.begin (); exp_it != (*it).key_vec.end (); ++exp_it)
            {
              const wchar_t *act_key = rt.path_next ();
              const wchar_t *exp_key = (*exp_it);

              ASSERT_STREQ (act_key, exp_key);
            }

      TEST_IT_END
    }

    TEST_F (json_pointer_test, parse)
    {
      struct assert
      {
        const wchar_t *ref_token;

        std::size_t count;
        int assert_status;
      };

      std::vector<struct assert> test = {
        { L"", 0, T_PASS },
        { L"/", 1, T_PASS },
        { L"/foo", 1, T_PASS },
        { L"/foo/bar", 2, T_PASS },
        { nullptr, 0, T_FAIL }
      };

      TEST_IT_START

            json_pointer jp(L"");
            std::size_t count = jp._parse ((*it).ref_token);

            ASSERT_EQ (count, (*it).count);
          }
        catch (format::json_pointer_error & pe)
          {
            this->_errorc[ACTUAL]++;
            std::cerr << pe.what () << std::endl;
          }
      }

      ASSERT_EQ (_errorc[ACTUAL], _errorc[EXPECTED]);
    }

    TEST_F (json_pointer_test, decode)
    {
      struct assert
      {
        const wchar_t *endoced;
        const wchar_t *dedoced;
        int assert_status;
      };

      std::vector<struct assert > test = {
        { L"012", L"012", T_PASS },
        { L"~0", L"~", T_PASS },
        { L"~1", L"/", T_PASS },
        { L"~01", L"~1", T_PASS },
        { L"~012", L"~12", T_PASS },
        { L"~", L"~", T_FAIL },   // NOTE: throwing exception leak 8 bytes
        { L"~2", L"~2", T_FAIL }  // NOTE: throwing exception leak 12 bytes
      };

      const wchar_t * key_begin = nullptr;

      TEST_IT_START

        const wchar_t *encoded = (*it).endoced;

        wchar_t *key_cursor = new wchar_t[wcslen (encoded) + 1] ();
        /* const wchar_t * const */ key_begin = key_cursor;

        while (*encoded != 0)
          key_cursor = json_pointer::reference_token::decode (key_cursor, & encoded);

        ASSERT_STREQ (key_begin, (*it).dedoced);

        delete [] key_begin; // FIXME: not freed when json_pointer_error thrown

        }
      catch (format::json_pointer_error & pe)
        {
          this->_errorc[ACTUAL]++; std::cerr << pe.what () << std::endl;
          delete [] key_begin;
        }
      }

      ASSERT_EQ (_errorc[ACTUAL], _errorc[EXPECTED]);
    }

    TEST_F (json_pointer_test, is_index)
    {
      struct assert
      {
        const wchar_t *key;
        bool is_index;
        int assert_status;
      };

      std::vector<struct assert > test = {
        { L"-", true, T_PASS },
        { L"0", true, T_PASS },
        { L"1", true, T_PASS },
        { L"123", true, T_PASS },
        { L"", false, T_PASS },
        { L"01", false, T_PASS },
        { L"a", false, T_PASS },
        { L"1a", false, T_PASS },
      };

      TEST_IT_START

        bool is_index = json_pointer::reference_token::is_index ((*it).key);
        ASSERT_EQ ((*it).is_index, is_index);

      TEST_IT_END
    }

    TEST_F (json_pointer_test, point)
    {
      format::json j (  L"{ \"foo\": [\"bar\", \"baz\", {}, []],\
                        \"\": 0,\
                        \"a/b\": 1,\
                        \"c%d\": 2,\
                        \"e^f\": 3,\
                        \"g|h\": 4,\
                        \"i\\j\": 5,\
                        \" \": 7,\
                        \"m~n\": 8 }" );

      // FIXME: \"k\"l\": 6 parse error

      struct assert
      {
        const wchar_t *ref_token;
        value::value_t type;
        long num_val;
        int assert_status;
      };

      std::vector<struct assert > test = {
        { L"", value::value_t::object_t, 0, T_PASS },
        { L"/foo", value::value_t::array_t, 0, T_PASS },
        { L"/foo/1", value::value_t::string_t, 0, T_PASS },
        { L"/foo/2/bar", value::value_t::undefined_t, 0, T_PASS },
        { L"/foo/3/0", value::value_t::undefined_t, 0, T_PASS },
        { L"/foo/4", value::value_t::undefined_t, 0, T_PASS },
        { L"/", value::value_t::number_t, 0, T_PASS },
        { L"a~1b", value::value_t::number_t, 1, T_PASS },
        { L"c%d", value::value_t::number_t, 2, T_PASS },
        { L"g|h", value::value_t::number_t, 4, T_PASS },
        { L"i\\j", value::value_t::number_t, 5, T_PASS },
        { L"/ ", value::value_t::number_t, 7, T_PASS },
        { L"m~0n", value::value_t::number_t, 8, T_PASS },
        { L"/not", value::value_t::undefined_t, 0, T_PASS },
        { L"/not/found", value::value_t::undefined_t, 0, T_FAIL },
        { L"/foo/foo", value::value_t::undefined_t, 0, T_FAIL },
        { L"/foo/3/bar", value::value_t::undefined_t, 0, T_FAIL },
      };

      TEST_IT_START

          json_pointer jp ((*it).ref_token);
          format::value & v = jp._point (j, jp._json_pointer.cbegin ());

          ASSERT_EQ ((*it).type, v.type ());

          if (v.type () == value::number_t)
            {
              format::number & n = static_cast<format::number &> (v);
              ASSERT_EQ ( (*it).num_val, static_cast<long> (n.get ()));
            }

      TEST_IT_END
    }

    TEST_F (json_pointer_test, get)
    {
      format::json j (  L"{ \"foo\": [\"bar\", \"baz\"],\
                        \"\": 0,\
                        \"a/b\": 1,\
                        \"c%d\": 2,\
                        \"e^f\": 3,\
                        \"g|h\": 4,\
                        \"i\\j\": 5,\
                        \" \": 7,\
                        \"m~n\": 8 }" );

      // FIXME: \"k\"l\": 6 parse error

      struct assert
      {
        const wchar_t *ref_token;
        value::value_t type;
        long num_val;
        int assert_status;
      };

      std::vector<struct assert > test = {
        { L"", value::value_t::object_t, 0, T_PASS },
//        { L"/foo", value::value_t::array_t, 0, T_PASS },
//        { L"/foo/1", value::value_t::string_t, 0, T_PASS },
//        { L"/", value::value_t::number_t, 0, T_PASS },
//        { L"a~1b", value::value_t::number_t, 1, T_PASS },
//        { L"c%d", value::value_t::number_t, 2, T_PASS },
//        { L"g|h", value::value_t::number_t, 4, T_PASS },
//        { L"i\\j", value::value_t::number_t, 5, T_PASS },
//        { L"/ ", value::value_t::number_t, 7, T_PASS },
//        { L"m~0n", value::value_t::number_t, 8, T_PASS },
//        { L"/not", value::value_t::undefined_t, 0, T_PASS },
        { nullptr, value::value_t::undefined_t, 0, T_FAIL },
//        { L"/not/found", value::value_t::undefined_t, 0, T_FAIL },
//        { L"/foo/foo", value::value_t::string_t, 0, T_FAIL },
      };

      TEST_IT_START

          json_pointer jp ((*it).ref_token);
          format::value & v = jp.get (j);

          ASSERT_EQ ((*it).type, v.type ());

          if (v.type () == value::number_t)
            {
              format::number & n = static_cast<format::number &> (v);
              ASSERT_EQ ( (*it).num_val, static_cast<long> (n.get ()));
            }

      TEST_IT_END
    }
  } // namespace test
} //  namespace format

#endif // JSON_POINTER_TEST_H
