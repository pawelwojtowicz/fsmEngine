#include "CFastHash.h"

namespace fsmEngine
{
// Compression function for Merkle-Damgard construction.
// This function is generated using the framework provided.
#define mix(h) ({					\
			h ^= (h) >> 23;		\
			h *= 0x2127599bf4325c37ULL;	\
			h ^= (h) >> 47; })


uint64_t CFastHash::CalculateHash64(const void *buf, size_t len, uint64_t seed)
{
	const uint64_t    m = 0x880355f21e6d1965ULL;
	const uint64_t *pos = (const uint64_t *)buf;
	const uint64_t *end = pos + (len / 8);
	const unsigned char *pos2;
	uint64_t h = seed ^ (len * m);
	uint64_t v;

	while (pos != end) {
		v  = *pos++;
		h ^= mix(v);
		h *= m;
	}

	pos2 = (const unsigned char*)pos;
	v = 0;

	switch (len & 7) {
	case 7: v ^= (uint64_t)pos2[6] << 48;
	case 6: v ^= (uint64_t)pos2[5] << 40;
	case 5: v ^= (uint64_t)pos2[4] << 32;
	case 4: v ^= (uint64_t)pos2[3] << 24;
	case 3: v ^= (uint64_t)pos2[2] << 16;
	case 2: v ^= (uint64_t)pos2[1] << 8;
	case 1: v ^= (uint64_t)pos2[0];
		h ^= mix(v);
		h *= m;
	}

	return mix(h);
} 

uint32_t CFastHash::CalculateHash32(const void *buf, size_t len, uint32_t seed)
{
	// the following trick converts the 64-bit hashcode to Fermat
	// residue, which shall retain information from both the higher
	// and lower parts of hashcode.
  uint64_t h = CalculateHash64(buf, len, seed);
	return h - (h >> 32);
}

uint64_t CFastHash::CalculateHash64( const std::string& text, uint64_t seed)
{
	return CalculateHash64( text.c_str(), text.length() , seed );
}

uint32_t CFastHash::CalculateHash32( const std::string& text, uint32_t seed)
{
	return CalculateHash32( text.c_str(), text.length() , seed );
}


}
