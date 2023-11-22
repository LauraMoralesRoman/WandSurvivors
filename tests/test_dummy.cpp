#include <gtest/gtest.h>

TEST(Dummy, Test_OK) {
	ASSERT_EQ(1, 1);
}

TEST(Dummy, Test_ERR) {
	ASSERT_EQ(1, 2);
}
