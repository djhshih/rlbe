#include <cstdlib>
#include <iostream>
#include <string>

#include "rle/rle.hpp"

using namespace std;


void print_bytes(const rle::bytes&x) {
	for (size_t i = 0; i < x.size(); ++i) {
		cout << (int) x[i] << ' ';
	}
}

int main(int argc, char* argv[]) {
	srand(time(NULL));

	rle::bytes x;

	rle::string_to_bytes("AAAAAAAAAATTCGATAAAAACGTTTAGATGAGAGTGCGA", x);
	//rle::random_sequence(100, 256, x);

	rle::bytes y;
	rle::encode(x, y);

	cout << "x = " << endl << "    ";
	print_bytes(x);
	cout << endl;

	cout << "y = " << endl << "    ";
	print_bytes(y);
	cout << endl;

	rle::bytes x2;
	rle::decode(y, x2);

	string x1s, x2s;
	rle::bytes_to_string(x, x1s);
	cout << x1s << endl;
	rle::bytes_to_string(x2, x2s);
	cout << x2s << endl;
	cout << "equal: " << (x == x2) << endl;

	cout << "|x| = " << x.size() << endl;
	cout << "|y| = " << y.size() << endl;
	cout << "ratio = " << (double) y.size() / x.size() << endl;

	return 0;
}

