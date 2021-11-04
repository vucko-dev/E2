#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_IME 20+1
#define MAX_OZNAKA 10+1

typedef struct student_st {
    char ime[MAX_IME];
    char prezime[MAX_IME];
	unsigned int poeni_1;
	unsigned int poeni_2;
	char predmet[MAX_OZNAKA];

    struct student_st *left;
    struct student_st *right;
} STUDENT;

void init_tree(STUDENT **root) {
    *root = NULL;
}

void add_to_tree(STUDENT *new_st, STUDENT **root) {
    if(*root == NULL)
        *root = new_st;
	
	else if (new_st->poeni_1 + new_st->poeni_2 >= 
			 (*root)->poeni_1 + (*root)->poeni_2  ) 
		add_to_tree(new_st, &((*root)->left));
	else add_to_tree(new_st, &((*root)->right));
}

STUDENT *create_new_item(char ime[], char prezime[], 
	unsigned int poeni_1, unsigned int poeni_2, char predmet[]) {
		
    STUDENT *new_st = (STUDENT *)malloc(sizeof(STUDENT));
    if (new_st == NULL) {
        printf("Not enough RAM!\n");
        exit(21);
    }

    strcpy(new_st->ime, ime);
    strcpy(new_st->prezime, prezime);
    new_st->poeni_1 = poeni_1;
    new_st->poeni_2 = poeni_2;
    strcpy(new_st->predmet, predmet);

    new_st->left = NULL;
    new_st->right = NULL;

    return new_st;
}

void read_tree_from(FILE *in, STUDENT **root) {
    char ime[MAX_IME];
    char prezime[MAX_IME];
	unsigned int poeni_1;
	unsigned int poeni_2;
	char predmet[MAX_OZNAKA];

    while(fscanf(in, "%s %s %d %d %s", ime, prezime, &poeni_1, &poeni_2, predmet) != EOF) {
        STUDENT *new_st = create_new_item(ime, prezime, poeni_1, poeni_2, predmet);
        add_to_tree(new_st, root);
    }
}

void save_item_to(FILE *out, STUDENT *x) {
    fprintf(out, "%-20s %-20s %d %d %d\n", 
		x->ime, x->prezime, x->poeni_1, x->poeni_2, x->poeni_1 + x->poeni_2);
}

void save_tree_to(FILE *out, STUDENT *root) {
    if(root != NULL) {
        save_tree_to(out, root->left);
        save_item_to(out, root);
        save_tree_to(out, root->right);
    }
}

void destroy_tree(STUDENT **root) {
    if(*root != NULL) {
        destroy_tree(&((*root)->left));
        destroy_tree(&((*root)->right));
        free(*root);
        *root = NULL;
    }
}

FILE *safe_fopen(char *filename, char *mode, int error_code) {
    FILE *fp = fopen(filename, mode);
    if (fp == NULL) {
        printf("Can't open '%s'!\n", filename);
        exit(error_code);
    }
    return fp;
}

void ispisi_najbolje_ucenike(STUDENT *x, unsigned int poeni){
	if (x == NULL)
		return;
	else if(x->poeni_1 + x->poeni_2 == poeni){
		printf("\n%-20s %-20s %d %d\n", 
			x->ime, x->prezime, x->poeni_1, x->poeni_2);
	}
	ispisi_najbolje_ucenike(x->right, poeni);
	ispisi_najbolje_ucenike(x->left, poeni);
}

unsigned int najbolji_poeni(STUDENT *root) {
    if (root == NULL)
		return 0;
	int poeni = root->poeni_1 + root->poeni_2;  
    int najbolji_levo = najbolji_poeni(root->left);  
    int najbolji_desno = najbolji_poeni(root->right);  
	
    if (najbolji_levo > poeni)  
		poeni = najbolji_levo;  
    if (najbolji_desno > poeni)  
		poeni = najbolji_desno;  
    return poeni;
}

void swap(STUDENT* &S1, STUDENT* &S2){
	STUDENT *temp = S1;
	*S1 = *S2;
	*S2 = *temp;
}

STUDENT* leftmost(STUDENT* root){
	if(root == NULL)
		return root;
	STUDENT* current = root;  

	while (current->left != NULL)  
		current = current->left;  
 
	return current;  
};

STUDENT* rightmost(STUDENT* root){
	if(root == NULL)
		return root;
	STUDENT* current = root;  

	while (current->right != NULL)  
		current = current->right;

	return current;  
};

void deleteNode(STUDENT *&root, char ime[], char prezime[]){
    if(root != NULL){
        if(!strcmp(root->ime, ime) && !strcmp(root->prezime, prezime)){
            if(root->left == NULL && root->right == NULL){
                free(root);
                root = NULL;
                return;
            }
			
            if(root->right != NULL){
                STUDENT* temp;
                temp = rightmost(root->right);
                swap(root, temp);
                deleteNode(root->right, temp->ime, temp->prezime);
                return;
            }
           
            if(root->left != NULL){
                STUDENT* temp;
                temp = leftmost(root->left);
                swap(root, temp);
                deleteNode(root->left, temp->ime, temp->prezime);
                return;
            }
        }
        deleteNode(root->left, ime, prezime);
        deleteNode(root->right, ime, prezime);
    }
}

void obrisi_ispod_50(STUDENT *&root, char predmet[], unsigned int min_poeni){
    if(root != NULL){
        if(!strcmp(root->predmet, predmet)){
            if(root->poeni_1 + root->poeni_2 < min_poeni)
				deleteNode(root, root->ime, root->prezime);
        }
        obrisi_ispod_50(root->left, predmet, min_poeni);
        obrisi_ispod_50(root->right, predmet, min_poeni);
    }
}

int main(int arg_num, char *args[]) {
    //if (arg_num == 3) {
    //    printf("USAGE: %s IN_FILENAME OUT_FILENAME\n", args[0]);
    //    exit(11);
    //}

    char *in_filename = args[1];
    char *out_filename = args[2];
	unsigned int min_poeni = atoi(args[3]);

    FILE *in   = safe_fopen(in_filename,        (char*)"r", 1);
    FILE *out1 = safe_fopen(out_filename,       (char*)"w", 2);
    FILE *out  = safe_fopen((char*)"izlaz.txt", (char*)"w", 3);
	
    STUDENT *root;
    init_tree(&root);

    read_tree_from(in, &root);
    save_tree_to(out, root);
	
	unsigned int najbolji = najbolji_poeni(root);
	ispisi_najbolje_ucenike(root, najbolji);
	
	obrisi_ispod_50(root, out_filename, min_poeni / 2);
    save_tree_to(out1, root);
	
    destroy_tree(&root);

    fclose(in);
    fclose(out);
	fclose(out1);

    return 0;
}