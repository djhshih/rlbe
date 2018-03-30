#ifndef _RLE_HPP_
#define _RLE_HPP_

#include <string>
#include <vector>
#include <cstdlib>    // rand

#include <algorithm>  // copy
#include <iterator>   // back_inserter


namespace rle {

using namespace std;

typedef unsigned char byte;
typedef vector<byte> bytes;

void encode(const bytes& x, bytes& y) {
	// unmatched prefix size
	byte u = 0;

	// matched suffix
	byte m = 0;

	// starting position
	size_t s = 0;

	// current position
	size_t i = s;

	while (i < x.size()) {

		// look for a same-symbol run
		size_t j = i + 1;
		while (j < x.size() && j - i < 128 - 1) {
			if (x[i] != x[j]) {
				break;
			}
			++j;
		}

		// matched length [i, j-1]
		m = j - i;

		// m < 2 does not achieve compression
		if (m >= 3) {

			// write unmatched prefix
			if (i > s) {
				// unmatched length [s, i-1]
				u = i - s;
				// header byte n = u - 1: copy n + 1 bytes verbatam
				y.push_back(u - 1);
				y.insert(y.end(), x.begin() + s, x.begin() + i);
			}

			// write matched suffix
			// header byte n = m + 128 - 3: repeat next byte for n - 128 + 3 times
			y.push_back(m + 128 - 3);
			y.push_back(x[i]);

			// move on to next segment
			s = i = j;
		} else {
			++i;
		}
	}

	// write unmatched prefix
	if (i > s) {
		// unmatched length [s, i-1]
		u = i - s;
		// header byte n = u - 1: copy n + 1 symbols verbatam
		y.push_back(u - 1);
		y.insert(y.end(), x.begin() + s, x.begin() + i);
	}
}

void decode(const bytes& x, bytes& y) {
	size_t i = 0;
	while (i < x.size()) {
		byte b = x[i++];
		if (b >= 128) {
			// repeat block
			// reverse the header byte mapping
			byte n = b - 128 + 3;
			byte xi = x[i];
			for (byte j = 0; j < n; ++j) {
				y.push_back(xi);
			}
			++i;
		} else {
			// verbatim block
			// reverse the header byte mapping
			byte n = b + 1;
			y.insert(y.end(), x.begin() + i, x.begin() + i + n);
			i += n;
		}
	}
}

void bytes_to_string(const bytes& x, string& y) {
	copy(x.begin(), x.end(), back_inserter(y));
}

void string_to_bytes(const string&x, bytes& y) {
	copy(x.begin(), x.end(), back_inserter(y));
}

void random_sequence(size_t n, size_t k, bytes& y) {
	for (size_t i = 0; i < n; ++i) {
		y.push_back( rand() % k );
	}
}

}  // namespace rle

#endif
