#include "FileParser.hpp"
#include <fstream>
#include <iostream>

namespace input
{

FileParser::FileParser(const char* input)
{
  _file.clear();
  setFile(input, calculateFileSize(input));
}

uint64_t FileParser::calculateFileSize(const char* input)
{
  std::ifstream  stream(input, std::ifstream::binary);

  stream.seekg(0, std::ios::end);
  uint64_t size = static_cast<uint64_t>(stream.tellg());
  stream.close();

  return size;
}

void FileParser::setFile(const char* input, const uint64_t size)
{
  std::ifstream stream(input, std::ifstream::in);
  if(!stream.eof() && !stream.fail())
  {
    _file.resize(size);
    stream.read(&_file[0], size);
  }
  stream.close();
}

} // namespace input
