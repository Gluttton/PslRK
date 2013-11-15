CodeManager
===========
Tool for everyday tasks.



System requirements
===================



Features
========
The CodeManager already has CLI user interface which allows:
- convert hex view of sequence into string view (based on symbols '+' and '-') and vice versa;
- calculate Minimum Peak Sidelobe Level (MSL) of sequence;
- get view of sequence which is required for adding to the [Collection](https://github.com/Gluttton/PslRK/tree/master/Reports);
- calculate [Autocorrelation Function (ACF)](http://en.wikipedia.org/wiki/Autocorrelation);
- manipulate whith the Collection of sequences.



Usage
=====
Example of session which consists of the following steps:
- open the Collection of sequences;
- input sequence in arbitrary view;
- convert view of sequnce which is required;
- calculate and print MSL;
- add sequence in the Collection;
- save and close the Collection.

```
> open base base.xml
> push code 038FE23225492
> show codes
038FE23225492
> to string 50
> show codes
----+++---+++++++---+---++--+---+--+-+-+--+--+--+-
> show msl
4
> show id
----+++---+++++++---+---++--+---+--+-+-+--+--+--+- - 3c701dcddab6d
> add base
Input code: > 3c701dcddab6d
Sequence: ++++---+++-------+++-+++--++-+++-++-+-+-++-++-++-+
ID:       3c701dcddab6d
Length:   50
Max PSL:  4
Input reference article: > Binary Sequences with Minimum Peak Sidelobe Level up to Length 68
Input reference author: > Leukhin A.N., Potehin E.N.
Input reference link: > http://arxiv.org/pdf/1212.4930.pdf
> save base
> close base
> quit
```
