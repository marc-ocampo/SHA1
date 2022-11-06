#include <iostream>
#include <array>
#include "FileParser.hpp"
#include "MessageDigestCalculator.hpp"

constexpr auto VALID_NUM_ARG = 2;

void printHash(const std::array<uint32_t, sha1::ESizeH>& hash)
{
  for(auto it = hash.begin(); it != hash.end(); ++it)
  {
    std::cout << std::hex << *it;
  }
}

int main(int argc, char** argv)
{
  if(VALID_NUM_ARG != argc)
  {
    std::cout << "ERR: Invalid commandline format. Please use \"./out <test_file>\"" << std::endl;
    return 1;
  }

  input::FileParser parser(argv[1]);
  sha1::MessageDigestCalculator sha1Calc(parser.getFile());

  // aligns to bash sha1sum output
  printHash(sha1Calc.getMsgDigest());
  std::cout << argv[1] << std::endl;

  return 0;
}
