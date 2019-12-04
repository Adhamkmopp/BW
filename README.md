# Burrows-Wheeler Compression

This is an attempt -in C- at the Burrows Wheeler compression algorithm that utilizes radix sort and MSD-radix sort as its suffix sorting algorithms. The main idea is to refrain from using any sorting libraries or the string library itself, and to make exclusive use of pointers and array indexing to implement both sorting algorithms. The program takes a path to a regular text file as input, and outputs the transformed array, and its associated ordered suffixes after applying both methods.

## Radix Sort:

As a first step, suffix sorting is performed on an input text using radix sort. As a method, it might be more wasteful than others in terms of memory space but it was easier to implement and to think about conceptually as the implementation I had in mind made exclusive use of a single moving pointer to reference different suffixes. This in turn introduced some trivial calculations, but they are also frequent; optimizing these calculations could be worth doing in the future.

As it stands, any text will work as long as it is terminating with a unique character that is not found in anywhere else in the text. The character could be of any value ('$' works for example but so does any unique character). This is most likely due to the fact that radix sort is **stable**, as it relies on count sort on single characters from least to most significant digit; the last character in a string is also the absolute last, and smallest suffix to be sorted, so it will always appear after any previous occurance of that character in any of the previous suffixes, rather than first.

## MSD-Radix Sort:

This is an implementation of the most significant digit (MSD) string sort algorithm adapted from Segwwick's & Wayne's "Algorithms"; a recursive radix sort based on the most significant digit. The algorithm first sorts all suffixes based on the most significant digit, then acts recursively on the next significant digit in subsets of suffixes sharing an identical **previous** significant digit. As the book states, MSD-Radix Sort has a worst case running time linear to the total number of characters, same as the other version of radix sort, it is however significantly more wasteful in terms; every run could potentially require the construction of (n -1)! arrays of size equal to the alphabet of the text (256 for ASCII), which could also have a devastating efffect on running brought on by memory accesses. This is mitigated greatly by replacing count sort with insertion sort for small subarrays. 

The code so far does not have an implementation of insertion sort in place, and it produces the **wrong** overall result. It does however produce a correct ordering based on the first round of sort before recursion, so the sort operation itself is correct. The error is most likely due to imprecise indexing during recursion.
