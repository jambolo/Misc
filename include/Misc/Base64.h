//
//  base64 encoding and decoding with C++.
//  Version: 1.01.00
//

#ifndef BASE64_H_C0CE2A47_D10E_42C9_A27C_C883944E704A
#define BASE64_H_C0CE2A47_D10E_42C9_A27C_C883944E704A

/*
  This code has been modified from
  its original version. It has been
  formatted to fit my project.

  Original: https://github.com/ReneNyffenegger/cpp-base64
*/

#pragma once

#include <string>

namespace Base64
{
	std::string encode(unsigned char const* , size_t len);
	std::string decode(std::string const& s);
} // namespace Base64

#endif /* BASE64_H_C0CE2A47_D10E_42C9_A27C_C883944E704A */
