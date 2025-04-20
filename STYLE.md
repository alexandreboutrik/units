# Guia de Estilo

Esse guia é baseado no [style do OpenBSD](https://man.openbsd.org/style), com algumas adaptações. Um arquivo .clang-format está em WIP (Work In Progress) para automatizar a aplicação das regras. Fiquem a vontade para abrirem novas Issues sugerindo alterações.

## Comentários

```cp
/*
 * Comentários de UMA linha IMPORTANTES aparecem assim.
 */

/* A maioria dos comentários de uma linha são assim. */

/*
 * Comentários de múltiplas linhas são formatados assim.
 * Mantenha as linhas alinhadas e bem formatadas.
 */
```

## Pré-processamento

```c
/* Includes de rede aparecem em primeiro. */
#include <net/if.h>

/* Linha em branco, seguido por includes do /usr/include. */
#include <stdio.h>
#include <stdlib.h>

/* Linha em branco, seguido por includes locais. */
#include "myheader.h"

/* Constantes em maíusculo */
#define TIMEOUT 5
```

## Funções

```c
/* Funções locais devem ser declaradas como static. */
static char *function(int a, const char *b);
static void  usage(void);

/* Protótipos devem incluir nomes das variáveis. */
static void  print_hello(char *str); // ok
static void  print_hello(char *);    // INCORRETO

/* O tipo de retorno deve ficar antes da declaração da função. */
static int
sum(int a, int b)
{

/*
 * Funções devem retornar 0 em caso de sucesso ou valor diferente de zero
 * para erros. Evite comentários óbvios como "Retorna 0 em caso de sucesso".
 */
exit(0);

/* Não declare funções dentro de funções. */

/*
 * Todas as funções mais importantes devem ter um comentário explicando sua
 * finalidade. O comentário antes da "main" deve descreber o que o programa
 * faz.
 */
int
main(void)
{
```

## Variáveis

```c
/* Prefira o uso de int, char, float e double ao invés do <stdint.h>. */
int8_t c; // EVITE
char c;   // ok


/*
 * Ao declarar variáveis, ordene por tamanho (maior para menor) e depois em
 * ordem alfabética.
 */
int one, two, three;
char four;

/* Não use chamadas de funções para inicializar variáveis. */
int j = 1;  // INCORRETO

int i;
i = 1;      // ok
```

## Enum e Struct

```c
/* Enumerações devem estar em maiúsculo. */
enum enumtype { ONE, TWO, THREE } et;

/* Structs devem ser declaradas no início do arquivo. */

/* Caso utilize typedef em struct, não use o suffixo "_t". */
typedef struct foo
{
  foo *next;
  int  bar;
} foo;

/* Use a macro queue(3) ao invés de implementar listas você mesmo. */
#include <sys/queue.h>
typedef struct foo {
  LIST_ENTRY(foo) link;
  int             bar;
} foo;
LIST_HEAD(, foo) head;
```

## Organização

```c
/* A indentação deve usar ESPAÇOS de 2 caracteres. */

/* Abertura de chaves devem estar em uma nova linha, alinhadas verticalmente. */
while (i < 10) { // INCORRETO
while (i < 10)
{

/* Todo o código deve respeitar o limite de 80 colunas. */

/* Tente manter as funções sempre com menos de 60 linhas. */
```

## Keywords

```c
/* Use um espaço após palavras-chave (if, while, for, return, switch). */
while (i < 10)

/* Não use espaços após castings ou sizeof. */
int i = int (d); // INCORRETO

/* Não use { } para blocos com menos de uma linha. */
for (i = 0; i < 10; i++)
  printf("%d\n", i);

/* As chaves devem ficar na mesma linha do else. */
if (i > 0)
{

} else {

}

/* Compare com 0 ao invés de utilizar !. */
if (function(a, b) == 0) // ok
if (!function(a, b))     // INCORRETO
```

## Operadores

```c
/* Não use espaços após chamadas de funções. */
err = function(a, b)

/* Operadores unários não requerem espaços. */
x = ~y;
z = !flag;

/* Operadores binários requerem espaços. */
a = b + c;
d=e*f;      // INCORRETO

/* Não use espaços após ( ) [ ]. */
if ((err = function(a, b)))
  exit(err);
```
