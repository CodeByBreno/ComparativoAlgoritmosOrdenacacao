void writeInHTML(char *line, int tag)
{
    char result[250];

    switch (tag)
    {
    case 0:
        sprintf(result, "%s%s%s", "\t\t\t<td>", line, "</td>\n");
        break;
    default: 
        strcpy(result, line);
        break;
    }

    fprintf(htmlFile, result);
}

void createHTML()
{
    fprintf(htmlFile, "<!DOCTYPE html>\n");
    fprintf(htmlFile, "<html>\n");
    fprintf(htmlFile, "\t<head>\n");
    fprintf(htmlFile, "\t\t<title>Algoritmos de Ordenacao</title>\n");
    fprintf(htmlFile, "\t\t<link rel=\"stylesheet\" href=\"styles.css\">\n");
    fprintf(htmlFile, "\t</head>\n");
    fprintf(htmlFile, "\t<body>\n");
    fprintf(htmlFile, "\t\t<header class=\"page_header\">\n");
    fprintf(htmlFile, "\t\t\t<h1>Comparando Algoritmos de Ordenacao</h1>\n");
    fprintf(htmlFile, "\t\t\t<p class=\"students_names\">Feito por: Alan Victor de Souza Pinho, Breno Gabriel de Souza Coelho, Daniel Alencar Penha Carvalho, Mateus Junior de Macedo Cavalcanti, Maic de Oliveira Santos.</p></header>");
}

void buildCaption(){
    writeInHTML("\t<div class=\"legenda\">\n", 50);
    writeInHTML("\t\t<div class=\"legenda_main\"><p><strong>Tempo de Execucao</strong>: Quanto tempo o sistema levou para executar o algoritmo por completo, em media</p>\n", 50);
    writeInHTML("\t\t<p><strong>Quantidade de Instrucoes</strong>: Quantidade de vezes que foram feitas comparacoes (if...) durante a execucao do algoritmo, em media</p>\n", 50);
    writeInHTML("\t\t<p><strong>Desvio Padrao</strong>: Mede o desvio padrao das estatisticas geradas. Lembre que foram feitas diferentes medicoes e o resultado apresentado e a media desses</p></div>", 50);

    writeInHTML("\n\t\t<table class=\"table_legenda\">\n"
                    "\t\t\t<tr class=\"table_legenda_header\">\n"
                    "\t\t\t\t<th>Tamanho do Array</th>\n"
                    "\t\t\t\t<th>Qtd. Repeticoes</th>\n"
                    "\t\t\t</tr>\n"
                    "\t\t\t<tr>\n", 50);


    fprintf(htmlFile, "\t\t\t<td>%d</td>\n", n);
    fprintf(htmlFile, "\t\t\t<td>%d</td>\n", AMOUNT_TESTS);
    writeInHTML("\t\t</tr>\n"
                "\t\t\t</table>\n", 50);
    
    writeInHTML("\t\t</table>\n", 50);
    writeInHTML("\t</div>\n", 50);
}

void buildDataTable(int option){
    writeInHTML("\n\t<table class=\"detailed_table\">\n", 50);

    writeInHTML("\t\t<tr class=\"detailed_table_header\">\n", 50);
    fprintf(htmlFile,"\t\t\t<th class=\"detailed_cycle_cell\">ciclo</th>\n");
    for (int i = 0; i < AMOUNT_FUNCTIONS; i++){
        fprintf(htmlFile,"\t\t\t<th>%s</th>\n", algorithmsNames[i]);
    }
    writeInHTML("\t\t</tr>\n", 50);

    for (int i = 0; i < AMOUNT_TESTS; i++){
        writeInHTML("\t\t<tr class=\"detailed_table_row\">\n", 50);
        fprintf(htmlFile,"\t\t\t<td>%d</td>\n", i);
        for (int j = 0; j < AMOUNT_FUNCTIONS; j++){
            if (option == 0){ fprintf(htmlFile,"\t\t\t<td>%.6f ms</td>\n", times[j][i]); }
            if (option == 1){ fprintf(htmlFile,"\t\t\t<td>%.4E comparacoes</td>\n", forCycles[j][i]); }
        }
        writeInHTML("\t\t</tr>\n", 50);
    }
    writeInHTML("\t</table>\n", 50);
}

void buildDetailedTables(){
    writeInHTML("\t<h2 class=\"detailed_time_title\">Detalhamento dos Tempos de Execução</h2>\n", 50);
    buildDataTable(0); // Tabela de tempos
    writeInHTML("\t<h2 class=\"detailed_time_title\">Detalhamento da Quantidade de Instruções Executadas</h2>\n", 50);
    buildDataTable(1); // Tabela de Número de instruções
}
