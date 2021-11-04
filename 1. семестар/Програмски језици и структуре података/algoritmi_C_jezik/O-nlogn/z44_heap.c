//z44.c Heap sort (sa acs.uns sajta praktikum, bez ikakvih dodatnih funkcija i rekurzija)
    #include <stdio.h>

    int main()
    {
        int heap[10], brEl, i, j, c, root, temp;

        printf("\n Broj elemenata:");
        scanf("%d", &brEl);
        printf("\n Elementi niza: \n");

        for (i = 0; i < brEl; i++)
           scanf("%d", &heap[i]);

        for (i = 1; i < brEl; i++)
        {
            c = i;
            do
            {
                root = (c - 1) / 2;
                printf("\nroot=%d C=%d i=%d",root,c,i);
                if (heap[root] < heap[c])//Medjusobni odnos novog i njegovog nadredjenog
                {
                    temp = heap[root];
                    heap[root] = heap[c];
                    heap[c] = temp;
                }
                c = root;
            } while (c != 0);
        }
        printf("\nHeap: ");
        for (i = 0; i < brEl; i++)
            printf("%d\t ", heap[i]);

        for (j = brEl - 1; j >= 0; j--)
        {
            temp = heap[0];
            heap[0] = heap[j] ;
            heap[j] = temp;
            root = 0;

            do
            {
                c = 2 * root + 1;
                if ((heap[c] < heap[c + 1]) && c < j-1)
                    c++;
                if (heap[root]<heap[c] && c<j)
                {
                    temp = heap[root];
                    heap[root] = heap[c];
                    heap[c] = temp;
                }
                root = c;
            } while (c < j);
        }
        printf("\n Sortiran niz: : ");
        for (i = 0; i < brEl; i++)
           printf("\t %d", heap[i]);

  return 0;
    }
