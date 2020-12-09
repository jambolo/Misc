/*
   This code has been modified from
   its original version. It has been
   formatted to fit my project.

   Original: https://github.com/ReneNyffenegger/cpp-base64
 */

#include "Misc/Base64.h"

#include "gtest/gtest.h"

using namespace Base64;

const std::string rest0_original  = "abc";
const std::string rest0_reference = "YWJj";
const std::string rest1_original  = "abcd";
const std::string rest1_reference = "YWJjZA==";
const std::string rest2_original  = "abcde";
const std::string rest2_reference = "YWJjZGU=";

TEST(Base64Test, Encode)
{
    // Test all possibilites of fill bytes (none, one =, two ==)
    // References calculated with: https://www.base64encode.org/

    std::string rest0_encoded = encode(reinterpret_cast<const unsigned char *>(rest0_original.c_str()),
                                       rest0_original.length());

    EXPECT_EQ(rest0_encoded, rest0_reference);

    std::string rest1_encoded = encode(reinterpret_cast<const unsigned char *>(rest1_original.c_str()),
                                       rest1_original.length());

    EXPECT_EQ(rest1_encoded, rest1_reference);

    std::string rest2_encoded = encode(reinterpret_cast<const unsigned char *>(rest2_original.c_str()),
                                       rest2_original.length());

    EXPECT_EQ(rest2_encoded, rest2_reference);
}

TEST(Base64Test, Decode)
{
    // Test all possibilites of fill bytes (none, one =, two ==)
    // References calculated with: https://www.base64encode.org/

    std::string rest0_decoded = decode(rest0_reference);

    EXPECT_EQ(rest0_decoded, rest0_original);

    std::string rest1_decoded = decode(rest1_reference);

    EXPECT_EQ(rest1_decoded, rest1_original);

    std::string rest2_decoded = decode(rest2_reference);

    EXPECT_EQ(rest2_decoded, rest2_original);
}
