#pragma once

#include <cstdint>
#include <string>
#include <string_view>
#include <vector>

#include <Windows.h>
#include <wincrypt.h>

// Look @ CRYPT_XXX_ALGORITHM constants to see what can be passed as the algorithm.
std::vector<uint8_t> hashData(std::string_view algorithm, const uint8_t* data, size_t length);
std::vector<uint8_t> hashString(std::string_view algorithm, std::string_view str);

std::vector<uint8_t> genRandomBuffer(size_t length);

// Encrypt/decrypt arbitrary data with a password. The cipher key is generated by
// hasing the password with SHA256 so arbitrary-length passwords work. The data is
// then encrypted using AES-GCM where the nonce is authenticated. The resulting buffer 
// formatted like this:
//      GCM nonce + GCM tag + ciphertext
//
// The decrypt functions will only work with data formatted like this.
std::vector<uint8_t> encryptData(std::string_view password, const uint8_t* data, size_t length);
std::vector<uint8_t> encryptData(std::string_view password, const std::vector<uint8_t>& data);
std::vector<uint8_t> encryptString(std::string_view password, std::string_view str);
std::vector<uint8_t> decryptData(std::string_view password, const uint8_t* data, size_t length);
std::vector<uint8_t> decryptData(std::string_view password, const std::vector<uint8_t>& data);

// Use CRYPT_STRING_ constants for encoding.
std::string stringEncode(int encoding, const uint8_t* data, size_t length);
std::string stringEncode(int encoding, const std::vector<uint8_t>& data);