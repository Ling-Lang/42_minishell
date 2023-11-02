# Parser

The Parser takes the token structure generated by the Lexer and processes them into more usable Types like simple commands or pipe sequences. It operates upon a simplified version of the [bash shell grammar](https://pubs.opengroup.org/onlinepubs/009695399/utilities/xcu_chap02.html#tag_02_10). We create a Verbose output file using bison and the gramm.y which is used to make the parsing table.