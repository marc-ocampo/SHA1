#include <gtest/gtest.h>
#include <memory>
#include <fstream>
#include <cstring>

#include "FileParser.hpp"

class TestFileParser : public ::testing::Test
{
protected:
  void SetUp()
  {
    const std::string fileName    = "TestFile.txt";
    _fileContent                  = "Hello World!";

    createFile(fileName);
    _parser   = std::make_unique<input::FileParser>(fileName.c_str());
  }

  std::unique_ptr<input::FileParser> _parser;
  std::string                        _fileContent;

private:
  void createFile(const std::string&);
};

void TestFileParser::createFile(const std::string& name)
{
  std::ofstream file(name.c_str());
  file << _fileContent << std::endl;
  file.close();
}

TEST_F(TestFileParser, CheckFileSize)
{
  EXPECT_EQ(_parser->getFileSize(), sizeof('\0') + _fileContent.length());
}

TEST_F(TestFileParser, CheckFileContent)
{
  auto file = _parser->getFile();
  EXPECT_TRUE(0 == std::memcmp(&file[0], _fileContent.c_str(), _fileContent.length()));
}

int main(int argc, char** argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
