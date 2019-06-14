#ifndef CASAMENTO_HPP
#define CASAMENTO_HPP

#include <iostream> // cout, endl
#include <ctype.h>

using std::cout;
using std::cerr;
using std::endl;

#define for_(inicio, fim) for(long i = inicio; i < fim; i++)

#define MAXTAMTEXTO 2000000 // Tamanho maximo de caracteres no texto
#define MAXTAMPADRAO 30 // Tamanho maximo de caracteres do padrao
#define MAXCHAR 256

typedef char TipoTexto[MAXTAMTEXTO];
typedef char TipoPadrao[MAXTAMPADRAO];

bool Boyer_Moore(TipoPadrao);

#endif // CASAMENTO_HPP