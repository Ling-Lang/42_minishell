# Structs/Enums

This is a overview of the structs and enums our program uses and what they each do.
<br>
* [Structs](#structs)
    * [t_env](#t_env)
    * [t_token](#t_token)
    * [t_quote](#t_quote)
    * [t_ptable](#t_ptable)
* [Enums](#enums)
    * NULL
<br>

---
## Structs

### t_env

```c
typedef struct s_env
{
    const char *name;
    char *value;
    struct s_env *next;
} t_env;
```

The `t_env` struct is used to store the environment variables. At the start of the program
we initiate it and fill it with the given `envp` variables, after this everything that depends on environment variables uses our t_env struct. We do this to avoid modifying the original environment variables of the user.

*  `const char *name`

    * The name variable is as the name suggests the name of the variable for example: <br>
    `PATH=/usr/bin:/usr/sbin` here the name would be `PATH`.
* `char *value`
    * In the `value` variable we store the contents of the variable using the previous example: <br>
    `PATH=/usr/bin:/usr/sbin` in this case `value` would be `/usr/bin:/usr/sbin`.
* `struct s_env *next`
    * The `next` variable is a pointer to the next env t_env node this effectively make it a linked list.

---

### t_token

```c
typedef struct s_token
{
    int type;
    void *value;
    struct s_token *next;
} t_token;
```
The `t_token` struct represents our Input stream converted to tokens. This makes it easier for the parser to read the input and build our syntax tree out of it. A token consists of 3 elements:

* `int type`
    * In the type variable we simply store the type of the token possible types are:
        * WORD
        * R_TO_FILE (>)
        * R_FROM_FILE (<)
        * GREATER (>>)
        * LESS (<<)
        * PIPE (|)
        * END
    go [here](Lexer.md) for a detailed description what the lexer does and how we assign the tokens.
* `void *value`
    * The `value` variable stores the contents of our given token for example:
    <br> `ls` the type would be WORD and the value would be `ls`.
* `struct s_token *next`
    * Like with the [t_env](#t_env) struct our t_token struct is a linked list which means this is just a pointer to the next token node.

---

### t_quote

```c
typedef struct s_quote
{
    int d_quote;
    int s_quote;
} t_quote;
```
This struct exists to tell wether we have a `d_quote` (\") or a `s_quote` (\') in our input it aids the [lexer](Lexer.md) to identify wether they are unclosed  or not.

---

### t_ptable

```c
typedef struct s_ptable
{
    int state;
    int token;
    int action;
    int n_state;
    int reduce;
}   t_ptable;
```

The `t_ptable` struct represents a entry in our Parsing table at the start of the program we initialize an array of t_ptable to store our Parsing Table. It also helps the [parser](Parser.md) to identify the current state of our program and determine what action should occur next.

* `int state`
    * Here we simply store the current state this ranges from 0-30.
* `int token`
    * This integer represents our [token_type](#t_token) it can also represent a [RULE](#enums).
* `int action`
    * This indicates which action should happen when all conditions are met [more information](#enums).
* `int n_state`
    * This gives us which state follows our current state. This value can also represent a [RULE](#enums) which occures in the case that we reduce.
* `int reduce`
    * The `reduce` variable indicates by how many [tokens](#t_token) we reduce. If we don't reduce the value is `-1`.

---

### t_stack

```c
typedef struct s_stack
{
    void *data;
    int type;
    int state;
    struct s_stack *next;
}   t_stack;
```

The `t_stack` struct is more or less a simplified version of the [t_ptable](#t_ptable) struct with only the most important values and the differene that it is a linked list. In our program it serves as a temporary state between the [t_token](#t_token) and the [t_node](#t_node).
* `void *data`
    * Like in the other structs this stores the contents of our token in it's rawest form.
* `int type`
    * This contains the type of the stack for example it could be a [token type](#t_token) or a [RULE](#t_rule).
* `int state`
    * Here we just store the current state.
* `struct s_stack *next`
    * Like almost every struct we use this is a linked list making this the pointer to the next node.

---

### t_node

```c
typedef struct s_node
{
    int type;
    int reduce;
    void *data;
    struct s_node *l;
    struct s_node *r;
    struct s_node *n;
}   t_node;
```

The `t_node` struct is the "final" struct it is the output of the [parser](Parser.md) and the input for the [interpreter]() and represents our `abstract syntax tree`. It is a special kind of linked list since we use a LR Parser which is the standard AST that bison uses. In here we store the input in.

## Enums
