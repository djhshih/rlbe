#include <cstdlib>
#include <iostream>

#include "rle/rle.hpp"
#include "rle/rlbe.hpp"

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

template <class Encoder>
int test_encoder(Encoder& encoder, size_t rounds, size_t length) {
		cout << "Test that decode(encode(x)) == x  ";

		for (size_t i = 0; i < rounds; ++i) {
			bytes x;
			random_sequence(length, 3, x);

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

int main(int argc, char* argv[]) {
	srand(time(NULL));

	int rounds = 30;
	int length = 1000;

	int rc = 0;

	{
		cout << "Run-length encoding" << endl;

		for (byte k = 1; k <= 5; ++k) {
			cout << "k = " << (unsigned int) k << endl;
			rle::Encoder<byte> encoder(k);
			rc |= test_encoder(encoder, rounds, length);
		}
	}

	cout << endl;

	{
		cout << "Run-length block encoding" << endl;

		for (byte t = 96; t <= 160; t += 16) {
			cout << "t = " << (unsigned int) t << endl;
			rlbe::Encoder<byte> encoder;
			rc |= test_encoder(encoder, rounds, length);
		}
	}

	return rc;
}

