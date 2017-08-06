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
  uint64_t getFileSize() { return _file.size(); }
  charv_t& getFile() { return _file; }
private:
  uint64_t calculateFileSize(const char*);
  void     setFile(const char*, const uint64_t);

  charv_t  _file;
};

} // namespace input
