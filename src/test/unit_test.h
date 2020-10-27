#ifndef UNIT_TEST_H
#define UNIT_TEST_H

#include <gtest/gtest.h>
#include <exception>
#include <algorithm>

#define T_PASS  0
#define T_FAIL  1
#define T_SKIP -1

#define EXPECTED 0
#define ACTUAL 1

#ifndef FN
  #define FN __FUNCTION__
#endif

#ifndef CATCH_ERROR_PCHAR
#define CATCH_ERROR_PCHAR\
  catch (const char *error) { errorc++; std::cerr << error << std::endl; }
#endif

#ifndef PRT_IDX
  #define PRT_IDX (void) sprintf (_sz_idx, "%s: index: %u", FN, idx)
#endif

#ifndef PRT_2IDX
  #define PRT_2IDX (void) sprintf (_sz_idx, "%s: 1. index: %u, 2. index: %u", FN, idx, jdx)
#endif

#ifndef ASSERT_IDX
  #define ASSERT_IDX(cond)\
    PRT_IDX;\
    // CPPUNIT_ASSERT_MESSAGE (_sz_idx, (cond))
#endif

#ifndef ASSERT_2IDX
  #define ASSERT_2IDX(cond)\
    PRT_2IDX;\
    // CPPUNIT_ASSERT_MESSAGE (_sz_idx, (cond))
#endif

#ifndef ASSERT_NO_ERROR
  #define ASSERT_NO_ERROR\
    (void) sprintf (_sz_idx, "%s: errorc: %lu", FN, errorc);\
    // CPPUNIT_ASSERT_EQUAL_MESSAGE (_sz_idx, 0, errorc)
#endif

#ifndef ASSERT_ERRORC
  #define ASSERT_ERRORC(__errorc)\
  (void) sprintf (_sz_idx, "%s: errorc: %lu", FN, errorc);\
  // CPPUNIT_ASSERT_MESSAGE (_sz_idx, errorc == __errorc)
#endif

#ifndef ASSERT_EQUAL_IDX
  #define ASSERT_EQUAL_IDX(message, expected, actual)\
  (void) sprintf (_sz_idx, "%s: idx[0] = %lu: %s", FN, this->_idx[0], message);\
  // CPPUNIT_ASSERT_EQUAL_MESSAGE (_sz_idx, expected, actual)
#endif

#ifndef TEST_IT_START
  #define TEST_IT_START\
  \
  for (auto it = test.begin (); it != test.end (); it++, this->_idx[0]++) {\
    try {\
        if ((*it).assert_status == T_SKIP) { continue; }\
        if ((*it).assert_status > T_PASS) { this->_errorc[EXPECTED]++; }
#endif

#ifndef TEST_IT_END
  #define TEST_IT_END\
  \
} catch (std::exception &e) { this->_errorc[ACTUAL]++; std::cerr << e.what () << std::endl; } }\
(void) sprintf (_sz_idx, "%s: errorc: %lu", FN, this->_errorc[ACTUAL]);\
ASSERT_EQ(this->_errorc[EXPECTED], this->_errorc[ACTUAL]);
#endif

namespace format
{
  class unit_test : public ::testing::Test
  {
  protected:
    size_t _errorc[2];
    size_t _idx[5];
    char _sz_idx[300];

    virtual void
    setUp ()
    {
      _errorc[0] = _errorc[1] = _idx[0] = _idx[1] = _idx[2] = _idx[3] = _idx[4] =  0;
    }

    virtual void
    tearDown ()
    {
      _errorc[0] =_errorc[1] = _idx[0] = _idx[1] = _idx[2] = _idx[3] = _idx[4] =  0;
    }

  public:
    unit_test ()
      : _errorc { 0, 0 },
        _idx { 0, 0, 0, 0, 0 }
    {
    }
  };
}

#endif // UNIT_TEST_H
