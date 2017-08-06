#include "MessageDigestCalculator.hpp"
#include <iostream>

namespace sha1
{

namespace
{
  constexpr uint8_t BIT_MASK_8    = 0xFF;
  constexpr uint32_t INVALID_OUT  = 0xFFFFFFFF;
}

// For debugging purposes only
void print(const std::vector<char>& input)
{
  std::cout << "DBG: ";
  for(auto it = input.begin(); it != input.end(); ++it)
  {
    std::cout << std::hex << (static_cast<uint32_t>(*it)) << " ";
  }
  std::cout << std::endl;
}

MessageDigestCalculator::MessageDigestCalculator(charv_t& input)
{
  appendPaddingTo(input);
  if(!isValidMsgSize(input))
  {
    std::cout << "WRN: Invalid message size!" << std::endl;
    return;
  }
  calculateMsgDigest(input);
}

void MessageDigestCalculator::appendPaddingTo(charv_t& input)
{
  const uint64_t lengthInBits = input.size() * ELengthBitsInByte;
  input.push_back(SHA1_PADDING);
  appendZeroPaddingTo(input);
  appendOrigMsgSizeTo(input, lengthInBits);
}

void MessageDigestCalculator::appendZeroPaddingTo(charv_t& input)
{
  auto msgLength = input.size() + sizeof(SHA1_PADDING);
  auto remainingLength(0u);
  do
  {
    input.push_back(0);
    remainingLength = (msgLength++ * ELengthBitsInByte) % ELengthBitsInMsgBlock;
  }
  while(remainingLength != ELengthBitsInMsgBlock - ELengthBitsInOrigMsg);
}

void MessageDigestCalculator::appendOrigMsgSizeTo(charv_t& input, const uint64_t lengthInBits)
{
  // TODO: Explore memcpy/std::copy here to copy 64-bit len
  // to the end of the input vector for better performance
  for(auto idx = 0u; idx < (ELengthBitsInOrigMsg / ELengthBitsInByte); ++idx)
  {
    const uint8_t entry = lengthInBits >> ((ELengthBitsInByte - 1 - idx) * ELengthBitsInByte);
    input.push_back(entry);
  }
}

bool MessageDigestCalculator::isValidMsgSize(const charv_t& input)
{
  return (0 == (input.size() * ELengthBitsInByte) % ELengthBitsInMsgBlock);
}

void MessageDigestCalculator::calculateMsgDigest(charv_t& input)
{
  const auto len = input.size();

  for(auto idx = 0u; idx < len; idx += ESizeMInBytes)
  {
    arrm_t m;
    std::copy(&input[idx], &input[idx + ESizeMInBytes], m.begin());

    fillW(w, m);
    calculatePartOfMsgDigest(w);
  }
}

void MessageDigestCalculator::fillW(arrw_t& w, const arrm_t& m)
{
  fillWFrom00To15(w, m);
  fillWFrom16To79(w, m);
}

void MessageDigestCalculator::fillWFrom00To15(arrw_t& w, const arrm_t& m)
{
  const uint8_t MULT = sizeof(uint32_t) / sizeof(char);

  for(auto idx = 0u; idx < ESizeWFirstPart; ++idx)
  {
    w[idx] = convertCharToUnsigned(m[idx * MULT]);
    w[idx] = (w[idx] << ELengthBitsInByte) | convertCharToUnsigned(m[(idx * MULT) + 1]);
    w[idx] = (w[idx] << ELengthBitsInByte) | convertCharToUnsigned(m[(idx * MULT) + 2]);
    w[idx] = (w[idx] << ELengthBitsInByte) | convertCharToUnsigned(m[(idx * MULT) + 3]);
  }
}

void MessageDigestCalculator::fillWFrom16To79(arrw_t& w, const arrm_t& m)
{
  for(auto idx = static_cast<uint8_t>(ESizeWFirstPart); idx < ESizeW; ++idx)
  {
    const auto expr = w[idx - 3] ^ w[idx - 8] ^ w[idx-14] ^ w[idx - 16];
    w[idx] = circularLeftShift32(expr, 1);
  }
}

void MessageDigestCalculator::calculatePartOfMsgDigest(const arrw_t& w)
{
  uint32_t  a = _h[0],  // RFC 3174 Section 6.1 Step c
            b = _h[1],
            c = _h[2],
            d = _h[3],
            e = _h[4],
            temp = 0;

  for(auto idx = 0u; idx < ESizeW; ++idx)
  {
    temp = circularLeftShift32(a, 5) + sha1Function(idx, b, c, d) + e + w[idx] + sha1KConstants(idx);

    e = d;
    d = c;
    c = circularLeftShift32(b, 30);
    b = a;
    a = temp;
  }

    _h[0] += a;
    _h[1] += b;
    _h[2] += c;
    _h[3] += d;
    _h[4] += e;
}

uint32_t MessageDigestCalculator::convertCharToUnsigned(const char byte)
{
  return (static_cast<uint32_t>(byte) & BIT_MASK_8);
}

uint32_t MessageDigestCalculator::circularLeftShift32(const uint32_t word, const uint8_t byte)
{
  return ((word << byte) | (word >> (ELengthBitsInWord - byte)));
}


uint32_t MessageDigestCalculator::sha1Function(const uint8_t t,
                                               const uint32_t b,
                                               const uint32_t c,
                                               const uint32_t d)
{
  if((t >= 0) && (t <= 19))
  {
    return ((b & c) | ((~b) & d));
  }
  else if((t >= 20) && (t <= 39))
  {
    return (b ^ c ^ d);
  }
  else if((t >= 40) && (t <= 59))
  {
    return ((b & c) | (b & d) | (c & d));
  }
  else if((t >= 60) && (t <= 79))
  {
    return (b ^ c ^ d);
  }
  else
  {
    std::cout << "ERR: No function available for t(" << std::dec << static_cast<int>(t) << ")." << std::endl;
    return INVALID_OUT;
  }
}

uint32_t MessageDigestCalculator::sha1KConstants(const uint8_t t)
{
  if((t >= 0) && (t <= 19))
  {
    return 0x5A827999;
  }
  else if((t >= 20) && (t <= 39))
  {
    return 0x6ED9EBA1;
  }
  else if((t >= 40) && (t <= 59))
  {
    return 0x8F1BBCDC;
  }
  else if((t >= 60) && (t <= 79))
  {
    return 0xCA62C1D6;
  }
  else
  {
    std::cout << "ERR: No constant available for t(" << std::dec << static_cast<int>(t) << ")." << std::endl;
    return INVALID_OUT;
  }
}

} // namespace sha1
