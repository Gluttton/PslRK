Reports
=======
Collection of binary sequences with low peak sidelobe level.



Requirements
============
Collection must follows the next requirements:
 - file format:     XML;
 - file encoding:   UTF-8;
 - endline format:  not specified;
 - items:
     - <lowpslcodes>;
     - <code>;
     - <value>;
     - <reference>;
     - <author>;
     - <article>;
     - <link>.

Example:
```
<?xml version="1.0" encoding="UTF-8"?>
<lowpslcodes>
<code id="17" length="5" maxpsl="1" mlslrate="0.200">
    <value>+-+++</value>
    <value>+++-+</value>
    <value>-+---</value>
    <value>---+-</value>
    <reference>
        <author>R.H. Barker</author>
        <article>Group synchronization of binary digital systems</article>
        <link>http://www.researchgate.net/publication/238126880_Group_synchronization_of_binary_digital_systems</link>
    </reference>
</code>
</lowpslcodes>
```
