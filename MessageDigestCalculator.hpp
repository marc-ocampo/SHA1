#pragma once

#include <cstdint>
#include <vector>
#include <array>

namespace sha1
{

constexpr char SHA1_PADDING             = 0x80; // SHA1 message padding
constexpr auto NUM_WORDS_IN_MSG_DIGEST  = 5;

enum
{
  ELengthBitsInByte     = 8,
  ELengthBitsInWord     = 32,
  ELengthBitsInOrigMsg  = 64, // see RFC 3174 Section 4
  ELengthBitsInMsgBlock = 512 // see RFC 3174
};

enum
{
  ESizeH                = 5,  // RFC 3174 Section 6.1
  ESizeWFirstPart       = 16,
  ESizeMInBytes         = 64,
  ESizeW                = 80
};

class MessageDigestCalculator
{

using charv_t = std::vector<char>;
using arrh_t  = std::array<uint32_t, ESizeH>;
using arrw_t  = std::array<uint32_t, ESizeW>;
using arrm_t  = std::array<char, ESizeMInBytes>;

public:
  MessageDigestCalculator() = delete;
  MessageDigestCalculator(const MessageDigestCalculator&) = delete;
  MessageDigestCalculator& operator= (const MessageDigestCalculator&) = delete;

  MessageDigestCalculator(charv_t&);
  arrh_t getMsgDigest() { return _h; }
private:
  void appendPaddingTo(charv_t&);
  void appendZeroPaddingTo(charv_t&);
  void appendOrigMsgSizeTo(charv_t&, const uint64_t);
  bool isValidMsgSize(const charv_t&);

  void calculateMsgDigest(charv_t&);
  void calculatePartOfMsgDigest(const arrw_t&);
  void fillW(arrw_t&, const arrm_t&);
  void fillWFrom00To15(arrw_t&, const arrm_t&);
  void fillWFrom16To79(arrw_t&, const arrm_t&);

  uint32_t convertCharToUnsigned(const char);
  uint32_t circularLeftShift32(const uint32_t, const uint8_t);
  uint32_t sha1Function(const uint8_t, const uint32_t, const uint32_t, const uint32_t);
  uint32_t sha1KConstants(const uint8_t);

  arrh_t _h =
  {{
    0x67452301,
    0xEFCDAB89,
    0x98BADCFE,
    0x10325476,
    0xC3D2E1F0
  }};

  arrw_t  w = {};
};

} // namespace sha1
