#include <stdio.h>
#include <stdlib.h>
#define VERDADERO 1
#define FALSO 0

struct Nodo{
    int info;
    struct Nodo *sig;//se crea la estructura de los nodos con los campos siguiente y anterior.
    struct Nodo *ant;
};
typedef struct Nodo tNodo;
typedef tNodo *Lista;//se renombra como lista.

typedef int BOOL;

Lista CreaNodo(int x)
{
    Lista aux;

    aux = (Lista)malloc(sizeof(tNodo));//se pide espacio en la memoria.
    if (aux != NULL)
    {
        aux->info = x;
        aux->sig = NULL; //se cre al nodo con el campo con la informacion y los punteros a ant y sig apuntan a null.
        aux->ant = NULL;
    }
    else
    {
        system("cls");
        printf("\n no hay memoria suficiente.");//mensaje que sale si no se encontro espacio.
        exit(1);
    }
    return aux;
}

Lista InsertaOrdenado(Lista L, int x)
{
    Lista pNodo,aux,aux2;

    pNodo = CreaNodo(x);
    if(L == NULL){
        L = pNodo; // si la lista esta vacia quda con el primer nodo.
    }
    else{
        if(x < L->info){
            pNodo->sig = L; // se ingresa en nodo cuando es menor al primer valor de la lista.
            L = pNodo;
        }
        else{
             aux = L;
             while(aux != NULL)
             {
                if(aux->info < x && aux->sig->info > x) // si el valor del nodo es menor al del nodo anterior y mayor del nodo siguiente queda al medio de ambos.
                {
                   pNodo->ant = aux;
                   pNodo->sig = aux->sig;
                   aux->sig->ant = pNodo;
                   aux->sig = pNodo;

                }
                else
                   aux = aux->sig;

            }
            aux2 = L;
            while(aux2->sig != NULL){ // inserta al final de la lista.
                aux2 = aux2->sig;
            }
            aux2->sig = pNodo;
            pNodo->ant = aux2;

           }
        }

    return L;
}

Lista Elimina(Lista L,int x)
{
    Lista aux1, aux2;
    if(L->info == x){ // elimina el nodo del principio.
       aux1 = L;
       L = L->sig;
       aux1->sig = NULL;
       free(aux1);;
    }
    else{
       aux1 = L;
       while(aux1->info != x){ //se coloca un auxiliar en el nodo deonde se encontro el valor que se quiere eliminar.
           aux1 = aux1->sig;
        }
       aux2 = L;
       while(aux2->sig != aux1){ //se coloca un segundo auxiliar antes del primer auxiliar.
           aux2 = aux2->sig;
        }
       aux2->sig = aux1->sig;
       aux1->sig = NULL;
       free(aux1); // se elimina el nodo.
       aux2 = NULL;

    return L;
   }
}

BOOL BuscaElemento(Lista L,int x)
{
    Lista aux;

    aux = L;
    while(aux != NULL){
        if(aux->info == x){ // se busca en la lista el valor deseado.
            return VERDADERO; // se encontro.
        }
        else
            aux = aux->sig;
    }
    return FALSO; // no se encontro.

}

int Posicion(Lista L, int x)
{
    Lista aux;
    int pos;

    if(BuscaElemento(L,x)){ // primero se busca si existe el valor en la lista.
        aux = L;
        pos = 1;
        while(aux->info != x){ //se recorre la lista hasta que se encuentra el valor.
            aux = aux->sig;
            pos++;
        }
        return pos; // se regresa el numero de posiciones recorridas.
    }
    else
        return -1; // no se encontro el valor.
}

void Imprime(Lista P)
{
    Lista aux;

    aux = P;
    printf("\nP: ");
    while(aux != NULL)
    {
        printf("%d > ", aux->info);// se muestra por pantalla los valores de lalista.
        aux = aux->sig;
    }

}
int main()
{
    Lista L;
    L = NULL;
    int x;
    char str[50];
    char *archivo;
    int i = 2;
    archivo = &str[i];
    char comando;
    FILE *arch;

   printf("TDA Listas Ordenadas> ");
   gets(str);
   comando = str[0];

   switch(comando){
       case 'I': // opcion para abrir el archivo y guardar los valores en la lista.
           arch = fopen(archivo,"r");
           if(arch == NULL){
            printf("\nno se encuentra el archivo."); // mensaje de si no se encuentra el archivo.
            exit(1);
           }
           while(archivo != EOF){
           fscanf(arch,"%d",&x);
           InsertaOrdenado(L,x);
           }
           fclose(arch);
           system("PAUSE");
           break;

       case 'L': // opcion para mostrar por pantalla la lista.
           Imprime(L);
           system("\nPAUSE");
           break;

       case 'E': // opcion para eliminar un valor de la lista.
           Elimina(L,x);
           break;

       case 'B':// opcion buscar un elemento en la lista e indicar su posicion.
           Posicion(L,x);
           break;
   }

  return 0;
}
