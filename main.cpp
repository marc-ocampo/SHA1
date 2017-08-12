#include <iostream>
#include <array>
#include "FileParser.hpp"
#include "MessageDigestCalculator.hpp"

constexpr auto VALID_NUM_ARG = 2;

void printHash(const std::array<uint32_t, sha1::ESizeH>& hash)
{
  std::cout << "SHA1: ";
  for(auto it = hash.begin(); it != hash.end(); ++it)
  {
    std::cout << std::hex << *it;
  }
  std::cout << std::endl;
}

int main(int argc, char** argv)
{
  if(VALID_NUM_ARG != argc)
  {
    std::cout << "ERR: Invalid commandline format. Please use \"./out <test_file>\"" << std::endl;
    return 0;
  }

  input::FileParser parser(argv[1]);
  sha1::MessageDigestCalculator sha1Calc(parser.getFile());
  printHash(sha1Calc.getMsgDigest());
}
