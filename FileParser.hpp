#pragma once

#include <string>
#include <vector>

namespace input
{

class FileParser
{
using charv_t = std::vector<char>;

public:
  FileParser() = delete;
  FileParser(const FileParser&) = delete;
  FileParser& operator=(const FileParser&) = delete;

  FileParser(const char*);
  uint64_t getFileSize() { return _size; }
  charv_t& getFile() { return _file; }
private:
  void setFile(const char*);

  charv_t  _file;

  // stored instead of calculating from _file to save in processing time
  uint64_t _size;
};

} // namespace input
