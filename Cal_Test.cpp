#include <gmock/gmock.h>
#include "CAL.cpp"

using namespace testing;

class MockCal :public cal {
public:
	MOCK_METHOD(int, getSum, (int a, int b), ());
};

TEST(group, TC1)
{
	cal Cal;

	int ret = Cal.getSum(10, 20);

	EXPECT_EQ(30, ret);
}

TEST(group, TC2)
{
	MockCal mock;

	EXPECT_CALL(mock, getSum(1, 2))
		//.WillRepeatedly(Return(999));
		.WillOnce(Return(1));

	int ret = mock.getSum(1, 2);

	EXPECT_EQ(1, ret);
}