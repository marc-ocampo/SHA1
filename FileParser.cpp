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
  uint64_t       size(0);
  std::ifstream  stream(input, std::ios::binary);
  std::streampos fSize = stream.tellg();

  stream.seekg(0, std::ios::end);
  size = static_cast<uint64_t>(stream.tellg() - fSize);
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
