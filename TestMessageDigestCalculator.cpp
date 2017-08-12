#include <gtest/gtest.h>
#include <array>
#include <cstring>
#include "MessageDigestCalculator.hpp"

TEST(TestMessageDigestCalculator, CheckMsgDigestWithFixedInput)
{
  // inputMsgDigest generated from 'Hello World' string via SHA-1 online tool
  const char input[] = {'H','e','l','l','o',' ','W','o','r','l','d'};
  const std::array<uint32_t, 5> inputMsgDigest = {0xa4d55a8, 0xd778e502, 0x2fab7019, 0x77c5d840, 0xbbc486d0};

  std::vector<char> inputV(input, input + (sizeof(input) / sizeof(input[0])));
  sha1::MessageDigestCalculator _sha1(inputV);

  const auto messageDigest = _sha1.getMsgDigest();
  EXPECT_TRUE(messageDigest == inputMsgDigest);
}
