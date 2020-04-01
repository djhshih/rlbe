# Run-length encoding

## Traditional run-length encoding

Given minimum run-length k, encoded byte string stores the original bytes
mostly unmodified but truncates repeats at run-length k and substitutes
the extra repeated symbols with the additional length.

For example, when k = 2,

    AAAAAATTCGAAAT

is encoded as

    AA4TT0CGAA1T

Notice that it is possible for the run-length to be 0 when the count
of repeated symbols equal k.


## Run-length block encoding

Encoded byte string consists of blocks. Each block has a header byte (n), followed
by data bytes.

If n is in [0, t - 1], copy the next n + 1 bytes verbatim.  
If n is in [t, 255], repeat the next byte for (n - t + 3) times.

For example, when t = 128,

    AAAAAATTCGAAAT

is encoded as

    131A 3TTCG 128A 1T  

where spaces are shown to visually distinguish the blocks. This encoding format
does *not* actually need block delimiters.

Remark: Numbers are stored as raw bytes, so `131` is stored as one `uint8`
value, *not* as three `char` values.


## Reference

Michael Dipperstein. "Run Length Encoding Discussion and Implementation" http://michael.dipperstein.com/rle/index.html

