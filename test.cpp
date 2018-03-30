#include <cstdlib>
#include <iostream>

#include "rlbe/rlbe.hpp"

using namespace std;


typedef unsigned char byte;
typedef vector<byte> bytes;

void random_sequence(size_t n, size_t k, bytes& y) {
	for (size_t i = 0; i < n; ++i) {
		y.push_back( rand() % k );
	}
}

void print_bytes(const bytes&x) {
	for (size_t i = 0; i < x.size(); ++i) {
		cout << (unsigned int) x[i] << ' ';
	}
}

int main(int argc, char* argv[]) {
	srand(time(NULL));

	rlbe::Encoder<byte> encoder;

	size_t n = 30;

	cout << "test that decode(encode(x)) == x  ";

	for (size_t i = 0; i < n; ++i) {
		bytes x;
		random_sequence(1000, 3, x);

		bytes y;
		encoder.encode(x, y);

		bytes x2;
		encoder.decode(y, x2);

		if (x == x2) {
			cout << '.';
		} else {
			cout << " failed" << endl;

			cout << "original: " << endl << "  ";
			print_bytes(x);
			cout << endl;

			cout << "encoded: " << endl << "  ";
			print_bytes(y);
			cout << endl;

			cout << "decoded: " << endl << "  ";
			print_bytes(x2);
			cout << endl;

			return 1;
		}
	}

	cout << " success" << endl;

	return 0;
}

