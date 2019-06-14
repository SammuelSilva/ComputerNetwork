#include "Casamento.hpp" // TipoTexto, TipoPadrao, MAXTAMPADRAO

#include <iostream> // cout , cin, endl
#include <string.h>
#include <stdio.h> 
using std::cout;
using std::cin;
using std::string;
using std::cerr;

// Boyer Moore com heuristica de ocorrencia 
bool Boyer_Moore(TipoPadrao padrao) {
	long i, j, ocorrencia[MAXTAMPADRAO], max = 0;
	TipoTexto texto;
	long tamanhoTexto;
	long tamanhoPadrao;
	FILE* arquivo;

	if ((arquivo = fopen("texto.txt", "r")) == NULL)
	{
		cerr << "Erro na abertura do arquivo requerido" << endl;
		cerr << "Na linha " << __LINE__ << " do arquivo " << __FILE__ << endl;
	}

	fgets(texto, MAXTAMTEXTO, arquivo);
	tamanhoTexto = strlen(texto);
	tamanhoPadrao = strlen(padrao);

	//processamento
	for (i = 0; i < tamanhoPadrao; i++) {
		ocorrencia[i] = tamanhoPadrao;//iguala cada uma ao tamanho do padrão digitado
	}
	for (i = tamanhoPadrao - 1; i >= 0; i--) {//heuristica de ocorrencias
		for (long j = 0; j < (tamanhoPadrao - 1 - i); j++) {
			if (ocorrencia[i] == tamanhoPadrao) {
				ocorrencia[j] = tamanhoPadrao - 1 - i;
			}
		}
	}
	ocorrencia[tamanhoPadrao - 1] = 1;//ultima posicao iguala a 1
	j = 0;
	//pesquisa
	while (j <= (tamanhoTexto - tamanhoPadrao)) {
		//busca enquanto for igual ao padrão ou i menor que zero
		for (i = tamanhoPadrao - 1; i >= 0 && padrao[i] == texto[i + j]; i--);
		if (i < 0) {//encontrou um casamento de texto
			max++;
			j += tamanhoPadrao;//desloca no tamanho do padrao
		}
		else {
			j += ocorrencia[i];//calcula o deslocamento do texto
		}
	}
	if (max != 0)
		return true;
	return false;

}