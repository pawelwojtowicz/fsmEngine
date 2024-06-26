#pragma once
#include <stdint.h>
#include <string>
/* The MIT License

   Copyright (C) 2012 Zilong Tan (eric.zltan@gmail.com)

   Permission is hereby granted, free of charge, to any person
   obtaining a copy of this software and associated documentation
   files (the "Software"), to deal in the Software without
   restriction, including without limitation the rights to use, copy,
   modify, merge, publish, distribute, sublicense, and/or sell copies
   of the Software, and to permit persons to whom the Software is
   furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be
   included in all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
   EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
   NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
   BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
   ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
   CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
   SOFTWARE.
*/


namespace fsmEngine
{
class CFastHash
{
	CFastHash();
	virtual ~CFastHash();
public:

/**
 * fasthash32 - 32-bit implementation of fasthash
 * @buf:  data buffer
 * @len:  data size
 * @seed: the seed
 */
	static uint32_t CalculateHash32(const void *buf, size_t len, uint32_t seed);
	
	static uint32_t CalculateHash32( const std::string& text, uint32_t seed );

/**
 * fasthash64 - 64-bit implementation of fasthash
 * @buf:  data buffer
 * @len:  data size
 * @seed: the seed
 */
	static uint64_t CalculateHash64(const void *buf, size_t len, uint64_t seed);
	
	static uint64_t CalculateHash64( const std::string& text, uint64_t seed);
};
}