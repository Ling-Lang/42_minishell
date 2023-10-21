# Libft
Libft is the 42 implementation of the C standard library and some other functions

## Installation

clone the repo run make and put `libft.a` & `libft.h` into your project folder. 
```bash
git clone https://github.com/Ling-Lang/Libft.git
cd Libft
make
```

## Usage

```c
#include "libft.h"
#include <stdio.h>

int main()
{
    char *str = "Hello World";
    printf("%s is %i long", str, ft_strlen(str));
}
```
output:
```bash
Hello World is 11 long
```


This library also includes my own implementation of Printf
## Contributing

Pull requests are welcome. For major changes, please open an issue first
to discuss what you would like to change.

## License

[MIT](https://choosealicense.com/licenses/mit/)
