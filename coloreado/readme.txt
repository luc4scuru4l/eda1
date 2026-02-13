Ejecuté los programas así:

Ejercicio 1:
gcc -g -c coloreado.c -Wall -Wextra -Werror --pedantic --std=c99
gcc -g -o test_coloreado.out  test_coloreado.c coloreado.o -Wall -Wextra -Werror --pedantic --std=c99
valgrind --leak-check=full --show-leak-kinds=all ./test_coloreado.out

Ejercicio 2:
gcc -c tablahash.c
gcc -o ej2.out ejercicio2.c tablahash.o -Wall -Wextra -Werror --pedantic --std=c99
valgrind --leak-check=full --show-leak-kinds=all ./ej2.out