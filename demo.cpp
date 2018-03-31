#include <cstdlib>
#include <iostream>
#include <string>

#include "rle/rle.hpp"
#include "rle/rlbe.hpp"

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

int main(int argc, char* argv[]) {
	srand(time(NULL));


	{
		cout << "Run-length encoding" << endl;

		rle::Encoder<byte> encoder;

		bytes x;
		string_to_bytes("AAAAAAAATTCGATAAAAACGTTTAGATGAGAGTGCGA", x);

		bytes y;
		encoder.encode(x, y);

		cout << "x = " << endl << "    ";
		print_bytes(x);
		cout << endl << endl;

		cout << "y = " << endl << "    ";
		print_bytes(y);
		cout << endl << endl;

		bytes x2;
		encoder.decode(y, x2);

		string x1s, x2s;
		bytes_to_string(x, x1s);
		bytes_to_string(x2, x2s);

		cout << "original string: " << x1s << endl;
		cout << "decoded string:  " << x2s << endl;
		cout << "strings are equal: " << (x == x2) << endl;
		cout << endl;

		cout << "|x| = " << x.size() << endl;
		cout << "|y| = " << y.size() << endl;
		cout << "ratio = " << (double) y.size() / x.size() << endl;
	}

	cout << endl;

	{
		cout << "Run-length block encoding" << endl;

		rlbe::Encoder<byte> encoder;

		bytes x;
		string_to_bytes("AAAAAAAATTCGATAAAAACGTTTAGATGAGAGTGCGA", x);

		bytes y;
		encoder.encode(x, y);

		cout << "x = " << endl << "    ";
		print_bytes(x);
		cout << endl << endl;

		cout << "y = " << endl << "    ";
		print_bytes(y);
		cout << endl << endl;

		bytes x2;
		encoder.decode(y, x2);

		string x1s, x2s;
		bytes_to_string(x, x1s);
		bytes_to_string(x2, x2s);

		cout << "original string: " << x1s << endl;
		cout << "decoded string:  " << x2s << endl;
		cout << "strings are equal: " << (x == x2) << endl;
		cout << endl;

		cout << "|x| = " << x.size() << endl;
		cout << "|y| = " << y.size() << endl;
		cout << "ratio = " << (double) y.size() / x.size() << endl;
	}

	return 0;
}

