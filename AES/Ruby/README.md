#AES/Ruby
### November 13, 2014
This is the second AES implementation I work on. The first one was PHP. Just as with that one I followed the Federal Information Processing Standards Publication 197 [FIPS 197](http://csrc.nist.gov/publications/fips/fips197/fips-197.pdf) by the National Institute of Standards and Technology to implement this. I will update any findings as I work on it.

[Joan Torres]  
November 13, 2014

###Notes

* Ruby's many core methods are definitely useful when manipulating the various data structures.
* The `.rotate` method was specially useful for the **shift_rows** step.
* Using `.hex` on a hexadecimal string will easily transform it for computations.
* The `.to_s` method on an integer can turn take a parameter which can be 2 for binary and 16 for hexadecimal.
* Using `.rjust(2, '0')` after `to_s(16)` is a simple way to force the string to be of two digits.
* I'm mostly focused on the cipher because the inverse cipher requires more complex galois field calculations on the inverse mix columns steps and I'm not considering using a lookup table right now.
