/*
    Copyright (c) 2021 Alethea Katherine Flowers.
    Published under the standard MIT License.
    Full text available at: https://opensource.org/licenses/MIT
*/

/* Tests for src/gem_voice_params.c */

#include "fix16.h"
#include "libwinter_test.h"
#include "wntr_bezier.h"

TEST_CASE_BEGIN(bezier_1d_mostly_linear)
    fix16_t result = wntr_bezier_cubic_1d(F16(0), F16(0.4), F16(0.6), F16(1.0), F16(0.5));
    ASSERT_FIX16_CLOSE(result, F16(0.5), 0.001);

    for (fix16_t i = F16(0); i < F16(1.0); i = fix16_add(i, F16(0.1))) {
        result = wntr_bezier_cubic_1d(F16(0), F16(0.4), F16(0.6), F16(1.0), i);
        ASSERT_FIX16_CLOSE(result, i, 0.02);
    }
TEST_CASE_END

TEST_CASE_BEGIN(bezier_1d_curvy)
    fix16_t result = wntr_bezier_cubic_1d(F16(0), F16(0.7), F16(0.3), F16(1.0), F16(0.5));
    ASSERT_FIX16_CLOSE(result, F16(0.5), 0.001);

    result = wntr_bezier_cubic_1d(F16(0), F16(0.7), F16(0.3), F16(1.0), F16(0.25));
    ASSERT_FIX16_GT(result, 0.3);

    result = wntr_bezier_cubic_1d(F16(0), F16(0.7), F16(0.3), F16(1.0), F16(0.75));
    ASSERT_FIX16_LT(result, 0.7);
TEST_CASE_END

TEST_CASE_BEGIN(bezier_1d_non_normalized)
    fix16_t result = wntr_bezier_cubic_1d(F16(-1.0), F16(-0.3), F16(0.3), F16(1.0), F16(0.5));
    ASSERT_FIX16_CLOSE(result, F16(0), 0.001);

    result = wntr_bezier_cubic_1d(F16(-1.0), F16(-0.3), F16(0.3), F16(1.0), F16(0.25));
    ASSERT_FIX16_GT(result, -0.5);

    result = wntr_bezier_cubic_1d(F16(-1.0), F16(-0.3), F16(0.3), F16(1.0), F16(0.75));
    ASSERT_FIX16_LT(result, 0.5);
TEST_CASE_END

static MunitTest test_suite_tests[] = {
    {.name = "1d, mostly linear", .test = test_bezier_1d_mostly_linear},
    {.name = "1d, curvy", .test = test_bezier_1d_curvy},
    {.name = "1d, non-normalized", .test = test_bezier_1d_non_normalized},
    {.test = NULL},
};

MunitSuite test_bezier_suite = {
    .prefix = "bezier: ",
    .tests = test_suite_tests,
    .iterations = 1,
};
