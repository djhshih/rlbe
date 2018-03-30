#include <cstdlib>
#include <iostream>
#include <string>

#include "rle/rle.hpp"

using namespace std;


typedef unsigned char byte;
//typedef unsigned int byte;
typedef vector<byte> bytes;

void print_bytes(const bytes&x) {
	for (size_t i = 0; i < x.size(); ++i) {
		cout << (unsigned int) x[i] << ' ';
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

int main(int argc, char* argv[]) {
	srand(time(NULL));

	rle::Encoder<byte> encoder;

	bytes x;
	string_to_bytes("AAAAAAAATTCGATAAAAACGTTTAGATGAGAGTGCGA", x);
	//rle::random_sequence(100, 256, x);

	bytes y;
	encoder.encode(x, y);

	cout << "x = " << endl << "    ";
	print_bytes(x);
	cout << endl;

	cout << "y = " << endl << "    ";
	print_bytes(y);
	cout << endl;

	bytes x2;
	encoder.decode(y, x2);

	string x1s, x2s;
	bytes_to_string(x, x1s);
	cout << x1s << endl;
	bytes_to_string(x2, x2s);
	cout << x2s << endl;
	cout << "equal: " << (x == x2) << endl;

	cout << "|x| = " << x.size() << endl;
	cout << "|y| = " << y.size() << endl;
	cout << "ratio = " << (double) y.size() / x.size() << endl;

	return 0;
}

