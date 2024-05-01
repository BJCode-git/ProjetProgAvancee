#include <iostream>

#define ASSERT_TRUE(condition) \
    if (!(condition)) { \
        std::cerr << "Test failed in file " << __FILE__ \
                  << " at line " << __LINE__ << ": " \
                  << "Expected: " #condition " to be true." << std::endl; \
        return false; \
    }

#define ASSERT_FALSE(condition) \
    if ((condition)) { \
        std::cerr << "Test failed in file " << __FILE__ \
                  << " at line " << __LINE__ << ": " \
                  << "Expected: " #condition " to be false." << std::endl; \
        return false; \
    }

#define ASSERT_EQUAL(expected, actual) \
    if ((expected) != (actual)) { \
        std::cerr << "Test failed in file " << __FILE__ \
                  << " at line " << __LINE__ << ": " \
                  << "Expected: " << (expected) << ", Actual: " << (actual) << std::endl; \
        return false; \
    }

#define ASSERT_NOT_EQUAL(not_expected, actual) \
    if ((not_expected) == (actual)) { \
        std::cerr << "Test failed in file " << __FILE__ \
                  << " at line " << __LINE__ << ": " \
                  << "Expected not equal to: " << (not_expected) << ", Actual: " << (actual) << std::endl; \
        return false; \
    }