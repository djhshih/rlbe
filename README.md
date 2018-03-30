# Run-length block encoding

Run-length block encoding similar to the PackBits algorithm,

Encoded byte string consists of blocks. Each block has a header byte (n), followed
by data bytes.

If n is in [0, 127], copy next n + 1 bytes verbatim.
If n is in [128, 255], repeat next byte for (n - 128 + 3) times.


## Reference

Michael Dipperstein. "Run Length Encoding Discussion and Implementation" http://michael.dipperstein.com/rle/index.html

