Reports
=======
Collection of binary sequences with low peak sidelobe level.



Requirements
============
The collection must follows the next requirements:
- file format:     XML;
- file encoding:   UTF-8;
- items:
    - ```<codes>```       - root element;
    - ```<code>```        - each sequences with low PSL level is reported in ```<code>``` element, which has attributes:
        - ```id```        - hexadecimal view of sequence (maximum of values which start from a one);
        - ```length```    - length of sequence;
        - ```psl```       - PSL;
    - ```<sequence>```    - character representation of sequence;
    - ```<reference>```   - source of information is reported in ```<reference>``` element, which has attributes;
        - ```article```   - title of a article;
        - ```author```    - author(s) of a article;
        - ```link```      - link.

Example:
```
<?xml version="1.0" encoding="UTF-8"?>
<codes>
<code id="1D" length="5" psl="1">
    <sequence>+++-+</sequence>
    <reference
        article="Group synchronization of binary digital systems"
        author="R.H. Barker"
        link="http://www.researchgate.net/publication/238126880_Group_synchronization_of_binary_digital_systems">
    </reference>
</code>
</codes>
```
