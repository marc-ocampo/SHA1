#include "FileParser.hpp"
#include <fstream>
#include <iostream>

namespace input
{

FileParser::FileParser(const char* input) : _size(0)
{
  _file.clear();
  
  std::ifstream sizeCountingStream(input, std::ifstream::binary);
  sizeCountingStream.seekg(0, std::ios::end);

  _size = static_cast<uint64_t>(sizeCountingStream.tellg());
  sizeCountingStream.close();

  std::ifstream fileStream(input, std::ifstream::in);
  if(!fileStream.eof() && !fileStream.fail())
  {
    _file.resize(_size);
    fileStream.read(&_file[0], _size);
  }
  fileStream.close();
}

} // namespace input
