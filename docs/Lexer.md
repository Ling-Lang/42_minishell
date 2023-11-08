# Lexer

The Lexer takes the input-string from the readline function and splits the string into multiple tokens. Which then can be passed into the parser. Tokens have the advantage to simplify the input stream and to streamline the parser making it less error prone.
<br>
### Tokens

A token can be multiple things in our case it is defined as either: <br>

* `>` R_TO_FILE | This is used to indicate that we have to move the output into a specific file.
* `<` R_FROM_FILE | This is used to indicate that we have to read the inputs from a file and take that as input for the next command.
* `|` PIPE | This is used when we have to pipe the output from one command into the input to another command.
* `>>` GREATER | We use this when we have to redirect the output from a command into a sepcific file in append mode.
* `<<` LESS | We use this to initiate the heredoc.
* `NULL` END | When the string given is NULL then we give it the END type to indicate that we don't do anything after that.
* Everything else get's the WORD type.
--- 
Example:
We have the following input string "ls -l > file.txt"
<br>ls = WORD
<br>-l = WORD
<br> > = R_TO_FILE
<br> file.txt = WORD

We seperate based on delimiters which are `< > | ' '` < > and | are seperator and delimiter at the same time.
<br> This ensures that int the case we forget to leave a space between them we still recognize it.
Example:
<br>ls -l>test.txt

---
We also check for quotes double and single everything inside a quote will be assigned the WORD token and not seperated 
if the input is `ls -l "> test.txt"` then the > test.txt is seen as one token WORD.
