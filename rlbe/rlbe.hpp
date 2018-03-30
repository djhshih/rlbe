#ifndef _RLBE_HPP_
#define _RLBE_HPP_

/** 
 *  Run-length block encoding.
 **/

#include <vector>
#include <limits>     // numeric_limits


namespace rlbe {

using namespace std;

template<typename T>
class Encoder {

public:

	typedef T symbol;
	typedef vector<T> symbols;

	symbol max_value = numeric_limits<symbol>::max();

private:

	// first value of the head byte that denotes the repeat operation
	symbol t;

public:

	Encoder()
		: t(max_value / 2 + 1)
	{
	}

	Encoder(symbol _t)
		: t(_t)
	{
	}

	void encode(const symbols& x, symbols& y) {
		// unmatched prefix size
		symbol u = 0;

		// matched suffix
		symbol m = 0;

		// starting position
		size_t s = 0;

		// current position
		size_t i = s;

		while (i < x.size()) {

			// look for a same-symbol run
			size_t j = i + 1;
			while (j < x.size() && j - i < t - 1) {
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
					// header symbol n = u - 1: copy n + 1 symbols verbatam
					y.push_back(u - 1);
					y.insert(y.end(), x.begin() + s, x.begin() + i);
				}

				// write matched suffix
				// header symbol n = m + 128 - 3: repeat next symbol for n - 128 + 3 times
				y.push_back(m + t - 3);
				y.push_back(x[i]);

				// move on to next block
				s = i = j;

			} else {

				++i;

				// unmatched length [s, i-1]
				u = i - s;

				// write unmatched prefix if it is too long
				if (u - 1 == t - 1) {
					// header symbol n = u - 1: copy n + 1 symbols verbatam
					y.push_back(u - 1);
					y.insert(y.end(), x.begin() + s, x.begin() + i);

					// move on to next block
					s = i;
				}

			}
		}

		// write unmatched prefix
		if (i > s) {
			// unmatched length [s, i-1]
			u = i - s;
			// header symbol n = u - 1: copy n + 1 symbols verbatam
			y.push_back(u - 1);
			y.insert(y.end(), x.begin() + s, x.begin() + i);
		}
	}

	void decode(const symbols& x, symbols& y) {
		size_t i = 0;
		while (i < x.size()) {
			symbol n = x[i++];
			if (n >= t) {
				// repeat block
				// reverse the header symbol mapping
				n = n - t + 3;
				symbol xi = x[i];
				for (symbol j = 0; j < n; ++j) {
					y.push_back(xi);
				}
				++i;
			} else {
				// verbatim block
				// reverse the header symbol mapping
				n = n + 1;
				y.insert(y.end(), x.begin() + i, x.begin() + i + n);
				i += n;
			}
		}
	}
};


}  // namespace rlbe

#endif
