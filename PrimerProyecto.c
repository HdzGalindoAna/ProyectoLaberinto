/*PROYECTO LABERINTO*/
/*AGUILAR SANCHEZ FERNANDO ELFEGO EN COLABORACIÓN DE HERNÁNDEZ GALINDO ANA LAURA*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//VARIABLES GLOBALES
int contador=0, contador1=0;
int a, b; //coordenadas donde (a) son las filas y (b) son las columnas
FILE * laberinto;
int nfilas=0, ncols=0;



//PROTOTIPO DE FUNCIONES
    int contadores(char *archivo[]);
	int resuelveLaberinto(int **matriz, int nfilas, int cols, int a, int b);



//FUNCION PRINCIPAL
int main(int argc, char *argv[]){
        int i, j;

        if (argc <= 1){
            printf("No se pasaron argumentos\n");
            return 0;
        }
       contadores(&argv[1]);

        return 0;
}

//FUNCION QUE LEE EL ARCHIVO
int contadores(char *archivo[]){
    char c;
    char caracter;



    if ((laberinto = fopen(archivo[0], "r")) == NULL){
        printf("Error al intentar abrir el archivo\n");
        return -1;
    }
        // CONTAMOS FILAS Y COLUMNAS
    while (caracter != '\n')      //Mientras no se lea el caracter salto de linea
            {
                caracter = fgetc(laberinto);
                contador=contador+1; //contamos las columnas
            }
    rewind(laberinto);

    while (feof(laberinto) == 0)      //Mientras no se lea el caracter EOF (End Of File)
            {
                c = fgetc(laberinto);
                if(c == '1' || c == '0'){
                    contador1=contador1+1; //contamos el total de caracteres numericos en el archivo
                }
            }

    contador = contador - (contador*0.5); //columnas
    contador1 = contador1/contador; //filas


    fclose(laberinto);

    if ((laberinto = fopen(archivo[0], "r")) == NULL){
        printf("Error al intentar abrir el archivo\n");
        return -1;
    }

        // NUEVAS VARIABLES
    int **matriz, i, j;
    nfilas=contador1;
    ncols=contador;
    char a;

    // MEMORIA DINAMICA
    matriz = (int **)calloc(nfilas, sizeof(int *));
    for (i= 0; i<nfilas; ++i){
        matriz[i] = (int *) calloc(ncols, sizeof(int));
    }

    // ASIGNACION DE VALORES
    for(i=0;i<nfilas;++i)
	{
		for(j=0;j<ncols;++j)
		{
			a = fgetc(laberinto);
			if (a!= EOF)
				fscanf(laberinto, "%d" ,&matriz[i][j]);
		}
	}
	fclose (laberinto);

    // SALIDA POR LA PANTALLA
    /*for (i= 0; i<nfilas; ++i){
        for (j=0; j<ncols; ++j){
            printf("%d ", matriz[i][j]);
        }
        printf("\n");
    }*/

    //RECIBIMOS COORDENADAS INCIALES
    scanf("%d", &a);
    scanf("%d", &b);

    while(matriz[a][b]==1){
        printf("\n Coordenada donde no hay paso, vuelve a introducir las coordeadas");
        printf("\n Introduce la coordenada x para comenzar: ");
        scanf("%d",&a);
        while(a>nfilas){
            printf("\n No existe tal coordenada");
            printf("\n Introduce la coordenada x menor a nfilas para comenzar: ");
            scanf("%d",&a);
        }
            printf("\n Introduce la coordenada y para comenzar: ");
            scanf("%d",&b);
        while(b>ncols){
            printf("\n No existe tal coordenada");
            printf("\n Introduce la coordenada y menor a ncols para comenzar: ");
            scanf("%d",&b);
        }
    }

    // VAMOS A REGRESAR LA MATRIZ OBTENIDA A OTRA FUNCION
    //Vector de punteros
	int *p[nfilas];
	//Puntero a puntero
	int **q;

	//Cada elemento del vector "p" apunta a una fila de la matriz
	for (i=0; i<nfilas;i++)
		p[i]=matriz[i];

	//El puntero "q" apunta al vector "p"
	q=p;

	// INVOCA A LA FUNCIÓN QUE RESUELVE EL LABERINTO
	resuelveLaberinto(q,nfilas, ncols, a, b);

    // LIBERACION DE LA MEMORIA DINAMICA
    for (i= 0; i<nfilas; ++i)
        free(matriz[i]);
    free(matriz);

    return 0;
}

int resuelveLaberinto(int **matriz, int nfilas, int cols, int a, int b){

    FILE *archivo;
    FILE *archivo2;
    int i, j;
    char salto='\n';

                    // ARCHIVO QUE CONTENDRÁ LOS RESULTADOS
        if ((archivo = fopen("CaminosLaberintos.txt", "a")) == NULL){
        printf("Error al intentar abrir el archivo\n");
        return -1;
        }

                    // ARCHIVO QUE GUARDA EL PASO A PASO DE LA SOLUCION
        if ((archivo2 = fopen("PasoApaso.txt", "a")) == NULL){
        printf("Error al intentar abrir el archivo\n");
        return -1;
        }


            fprintf(archivo,"%d ", a); //Primeras coordenadas
            fprintf(archivo,"%d, ", b);

            do{
                while(matriz[a][b]==matriz[a][b+1]){
                        //printf(" Avanza1 \n");
                        matriz[a][b]=8;
                        b=b+1;
                        fprintf(archivo,"%d %d,",a, b);
                }

                while(matriz[a][b]==matriz[a+1][b]){
                        //printf(" Avanza3 \n");
                        matriz[a][b]=8;
                        a=a+1;
                        fprintf(archivo,"%d %d,",a, b);
                }

                while(matriz[a][b]==matriz[a][b-1]){
                        //printf(" Avanza2 \n");
                        matriz[a][b]=8;
                        b=b-1;
                        fprintf(archivo,"%d %d,",a, b);
                }

                while(matriz[a][b]==matriz[a-1][b]){
                        //printf(" Avanza4 \n");
                        matriz[a][b]=8;
                        a=a-1;
                        fprintf(archivo,"%d %d,",a, b);
                }

                while(matriz[a-1][b]!=0 && matriz[a][b-1]!=0 && matriz[a+1][b]!=0 && matriz[a][b+1]!=0){
                        if(matriz[a-1][b]==8){
                            matriz[a][b]=1;
                            a=a-1;
                            matriz[a][b]=0;
                            break;
                        }

                        if(matriz[a][b-1]==8){
                            matriz[a][b]=1;
                            b=b-1;
                            matriz[a][b]=0;
                            break;
                        }

                        if(matriz[a+1][b]==8){
                            matriz[a][b]=1;
                            a=a+1;
                            matriz[a][b]=0;
                            break;
                        }

                        if(matriz[a][b+1]==8){
                            matriz[a][b]=1;
                            b=b+1;
                            matriz[a][b]=0;
                            break;
                        }

                }

            for(i=0;i<nfilas;i++){
                for(j=0;j<ncols;j++){
                    fprintf(archivo2," %d",matriz[i][j]);
            }
            fprintf(archivo2,"%c", salto);
        }
        fprintf(archivo,"%c", salto);
            }while(a<nfilas && a>=0 && b<ncols && b>=0);
                matriz[a][b]=8;
                printf("\n");

    fprintf(archivo,"%c", salto);
    fclose (archivo);
    fclose(archivo2);

        return 0;
    }

