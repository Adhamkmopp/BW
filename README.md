# Burrows-Wheeler Compression

This is an attempt -in C- at the Burrows Wheeler compression algorithm that utilizes radix sort as its suffix sorting algorithm. The main idea is to refrain from using any sorting libraries or the string library itself, and to make exclusive use of pointers and array indexing to implement a new sorting algorithm.

## Radix sort:

As a first step, suffix sorting is performed on an input text using radix sort. As a method, it might be more wasteful than others in terms of memory space but it was easier to implement and to think about conceptually as the implementation I had in mind made exclusive use of a single moving pointer to reference different suffixes. This in turn introduced some trivial calculations, but they are also frequent; optimizing these calculations could be worth doing in the future.

As it stands, any text will work as long as it is terminating with a unique character that is not found in anywhere else in the text. The character could be of any value ('$' works for example but so does any unique character). This is most likely due to the fact that radix sort is **stable**, as it relies on count sort on single characters from least to most significant digit; the last character in a string is also the absolute last, and smallest suffix to be sorted, so it will always appear after any previous occurance of that character in any of the previous suffixes, rather than first.
