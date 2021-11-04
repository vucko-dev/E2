//http://www.cprogrammingnotes.com/question/dynamic-queue.html
#include <stdio.h>
#include <stdlib.h>

typedef struct element{
    int broj;
    struct element * sledeci;
}Element;

typedef struct red{
    Element * glava;
    Element * rep;
}Red;

void IspisiRed();
void UbaciRed(Red *r, int noviBroj);
int UzmiPrvi(Red * r);

void UcitajRed(Red * r);
int SumaCifara(int broj);
int ProizvodCifara(int broj);

int main()
{
    Red r;
    r.glava = NULL;
    r.rep = NULL;

    UcitajRed(&r);
    //IspisiRed(r);

    int brojUzetih = 0;
    int broj;
    while(r.glava != NULL){
       broj = UzmiPrvi(&r);
       brojUzetih++;

       if(broj < 10){
            break;
       }

       if(broj % 2 == 0){
            int suma = SumaCifara(broj);
            UbaciRed(&r, suma);
       }
       else{
            int proizvod = ProizvodCifara(broj);
            UbaciRed(&r, proizvod);
       }
    }

    printf("Perica je uzeo %d puta broj iz reda.\n", brojUzetih);

    return 0;
}
int SumaCifara(int broj){
    int suma = 0;

    while (broj > 0) {
         int cifra = broj % 10;

         suma += cifra;

         broj = broj / 10;
    }

    return suma;
}
int ProizvodCifara(int broj){
    int proizvod = 1;

    while (broj > 0) {
         int cifra = broj % 10;

         proizvod *= cifra;

         broj /= 10;
    }

    return proizvod;
}

void UcitajRed(Red *red){
	FILE* ulaz = fopen("brojevi.txt", "r");
	if(ulaz == NULL){
		printf("Greska pri otvaranju fajla.\n");
		exit(1);
	}

    int i,n, broj;
    fscanf(ulaz, "%d", &n);

	for(i = 0; i < n; i++){
       fscanf(ulaz, "%d", &broj);
       UbaciRed(red, broj);
	}

	fclose(ulaz);
}



void IspisiRed(Red r)
{
    Element *tekuci = r.glava;
    printf("\n****Red****\n");
    while (tekuci != NULL)
    {
        printf("%d ", tekuci->broj);
        tekuci = tekuci->sledeci;
    }
    printf("\n----------\n");
}

void UbaciRed(Red *r, int noviBroj)
{
    Element * noviElement = malloc(sizeof(Element));
    noviElement->broj = noviBroj;
    noviElement->sledeci = NULL;

    if (r->rep == NULL)
    {
        r->glava = noviElement;
        r->rep = noviElement;
    }
    else
    {
        r->rep->sledeci = noviElement;
        r->rep = noviElement;
    }
}

int UzmiPrvi(Red * r)
{
    int prvi;
    if (r->glava == NULL)
    {
        prvi = -1;
    }
    else
    {
        prvi = r->glava->broj;

        if(r->rep == r->glava){
            r->rep = NULL;
        }

        Element *tekuci;
        tekuci = r->glava;
        r->glava = r->glava->sledeci;
        free(tekuci);
    }

    return prvi;
}
