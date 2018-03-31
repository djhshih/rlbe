#ifndef _RLE_HPP_
#define _RLE_HPP_

/** 
 *  Run-length block encoding.
 **/

#include <vector>
#include <limits>     // numeric_limits
#include <iostream>


namespace rle {

using namespace std;

// T must be unsigned type.
template<typename T>
class Encoder {

public:

	typedef T symbol;
	typedef vector<T> symbols;

	symbol max_value = numeric_limits<symbol>::max();

private:

	// minimum number of repeats to start encoding run length
	symbol k;

public:

	Encoder()
		: k(2)
	{
	}

	Encoder(symbol _k)
		: k(_k)
	{
	}

	void encode(const symbols& x, symbols& y) {
		// current position
		size_t i = 0;

		while (i < x.size()) {
			y.push_back(x[i]);

			// look for repeated symbols
			size_t j = i + 1;
			while (j < x.size() && j - i < max_value) {
				if (x[i] != x[j]) {
					break;
				}
				++j;
			}

			// matched length [i, j-1]
			symbol m = j - i;

			if (m >= k) {
				// write escape code
				for (symbol l = 1; l < k; ++l) {
					y.push_back(x[i]);
				}
				// write run length
				y.push_back(m - k);
				// skip over run
				i = j;
			} else {
				++i;
			}
		}
	}

	void decode(const symbols& x, symbols& y) {
		// current position
		size_t i = 0;
		// whether we have started matching
		bool matching = false;
		// m starts at 1 because we start counting at the second symbol in the run
		symbol m = 1;
		// previous symbol
		symbol b;

		while (i < x.size()) {
			y.push_back(x[i]);

			if (matching && x[i] == b) {
				++m;
			} else {
				// reset counter due to mismatch
				m = 1;
				b = x[i];
				// previous symbol is set
				matching = true;
			}

			if (m >= k) {
				// next symbol is run length
				symbol n = x[i+1];
				// expand the compressed repeat run
				for (symbol j = 0; j < n; ++j) {
					y.push_back(b);
				}
				// reset matching status
				m = 1;
				matching = false;
				// go to next symbol
				i += 2;
			} else {
				++i;
			}
		}
	}
};


}  // namespace rlbe

#endif
