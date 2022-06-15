#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

struct element
{
    int key;
    struct element* left; 
    struct element* right;
    struct element* parent;
};

struct element* BST_WSTAW(struct element* root, struct element* z);
void drzb_inorder(struct element* x);
void drzb_preorder(struct element* x);
void drzb_postorder(struct element* x);
struct element* BST_SZUKAJ(struct element* x, int k);
struct element* BST_MIN(struct element* x);
struct element* BST_MAX(struct element* x);
struct element* BST_NASTÊPNIK(struct element* x);
struct element* BST_POPRZEDNIK(struct element* x);
struct element* BST_USUN(struct element* root, struct element* usuwany);
struct element* BST_ZWOLNIJ(struct element* root);

int main()
{
    struct element* root = NULL, * nowy = NULL;
    struct element* wynik = NULL, * wynik2 = NULL;
    int d = 0;
    char z;
    while (1)
    {
        wynik = NULL;
        system("CLS");
        printf("Co chcesz zrobic?\n");
        printf("w - wstaw wartosc w drzewo\n");
        printf("i - wyswietl wartosci w drzewie inorder\n");
        printf("r - wyswietl wartosci w drzewie preorder\n");
        printf("o - wyswietl wartosci w drzewie postorder\n");
        printf("s - szukaj \n");
        printf("m - wyszukaj najmniejszy element w drzewie\n");
        printf("x - wyszukaj najwiekszy element w drzewie\n");
        printf("n - znajdz i wyswietl nastepnika\n");
        printf("p - znajdz i wyswietl poprzednika\n");
        printf("u - usun wartosc\n");
        printf("q - Koniec\n");
        fflush(stdin);
        z = getchar();
        
        switch (z)
        {
        case 'w': nowy = (struct element*)calloc(1,sizeof(struct element));
            printf("podaj wartosc do wstawienia\n");
            scanf("%d", &d);
            nowy->key = d;
            nowy->left = NULL;
            nowy->right = NULL;
            nowy->parent = NULL;
            root = BST_WSTAW(root, nowy);
            nowy = NULL;
            break;
        case 'i': system("CLS");
            drzb_inorder(root);
            system("pause");
            break;
        case 'r': system("CLS");
            drzb_preorder(root);
            system("pause");
            break;
        case 'o': system("CLS");
           drzb_postorder(root);
            system("pause");
            break;
        case 's': system("CLS");
            printf("podaj wartosc szukanego elementu: ");
            scanf("%d", &d);
            wynik = BST_SZUKAJ(root, d);
            if (wynik != NULL)printf("podana wartosc zostala znaleziona w drzewie i ma adres %p\n%d", wynik);
            else printf("nie znaleziono podanej wartosci\n");
            system("pause");
            break;
        case 'm': system("CLS");
            printf("Najmniejsza wartosc w drzewie to: %d\n", *(BST_MIN(root)));
            system("pause");
            break;
        case 'x': system("CLS");
            printf("Najwieksza wartosc w drzewie to: %d\n", *(BST_MAX(root)));
            system("pause");
            break;
        case 'n': system("CLS");
            printf("podaj wartosc: ");
            scanf("%d", &d);
            wynik = BST_SZUKAJ(root, d);
            if (wynik == NULL)
            {
                printf("nie znaleziono podanej wartosci\n");
                system("pause");
                break;
            }
            wynik2 = BST_NASTÊPNIK(wynik);
            if (wynik2 != NULL) printf("nastepnik to: %d\n", *wynik2);
            else printf("nastepnik tej wartosci nie istnieje\n");
            system("pause");
            break;
        case 'p': system("CLS");
            printf("podaj wartosc: ");
            scanf("%d", &d);
            wynik = BST_SZUKAJ(root, d);
            if (wynik == NULL)
            {
                printf("nie znaleziono podanej wartosci\n");
                system("pause");
                break;
            }
            wynik2 = BST_POPRZEDNIK(wynik);
            if (wynik2 != NULL) printf("poprzednik to: %d\n", *wynik2);
            else printf("poprzednik tej wartosci nie istnieje\n");
            system("pause");
            break;
        case 'u': system("CLS");
            printf("podaj wartosc do usuniecia: ");
            scanf("%d", &d);
            wynik = BST_SZUKAJ(root, d);
            if (wynik == NULL)
            {
                printf("nie znaleziono podanej wartosci\n");
                system("pause");
                break;
            }
            wynik2 = BST_USUN(root, wynik);
            printf("usunieto element: %d\nzawartosc drzewa po usunieciu\n", *wynik2);
            drzb_inorder(root);
            system("pause");
            break;
        case 'q': BST_ZWOLNIJ(root);
            printf("zwolniono cala pamiec drzewa\n");
            return 0;
        }
    }
}

struct element* BST_WSTAW(struct element* root, struct element* z)
{
    struct element* y = NULL;
    struct element* x = root;
    while (x != NULL)
    {
        y = x;
        if (x->key < z->key) x = x->right;
        else x = x->left;
    }
    z->parent = y;
    if (y == NULL) root = z;
    else
        if (y->key < z->key) y->right = z;
        else y->left = z;
    return root;
}

void drzb_inorder(struct element* x)
{
    if (x != NULL)
    {
        drzb_inorder(x->left);
        printf("Wartosci w drzewie: %d\n", x->key);
        drzb_inorder(x->right);
    }
}

void drzb_preorder(struct element* x)
{
    if (x != NULL)
    {
        printf("Wartosci w drzewie: %d\n", x->key);
        drzb_preorder(x->left);
        drzb_preorder(x->right);

    }
}

void drzb_postorder(struct element* x)
{
    if (x != NULL)
    {
        drzb_postorder(x->left);
        drzb_postorder(x->right);
        printf("Wartosci w drzewie: %d\n", x->key);
    }
}

struct element* BST_SZUKAJ(struct element* x, int zm)
{
    if (x == NULL || zm == x->key) return x;
    if (zm < x->key) return BST_SZUKAJ(x->left, zm);
    else return BST_SZUKAJ(x->right, zm);
}

struct element* BST_MIN(struct element* x)
{
    while (x->left != NULL) x = x->left;
    return x;
}

struct element* BST_MAX(struct element* x)
{
    while (x->right != NULL) x = x->right;
    return x;
}

struct element* BST_NASTÊPNIK(struct element* x)
{
    struct element* y = x;

    if (x->right != NULL) return BST_MIN(x->right);
    y = x->parent;
    while (y != NULL && (x == y->right))
    {
        x = y;
        y = y->parent;
    }
    return y;
}

struct element* BST_POPRZEDNIK(struct element* x)
{
    struct element* y = x;
    if (x->left != NULL) return BST_MAX(x->left);
    y = x->parent;
    while(y != NULL && (x ==y->left))
    {
        x = y;
        y = y->parent;
    }
    return y;
}

struct element* BST_USUN(struct element* root, struct element* z)
{
    struct element* y = NULL;
    struct element* x = NULL;
    int w;

    if (z->left == NULL || z->right == NULL) y = z;
    else y = BST_NASTÊPNIK(z);
    if (y->left != NULL) x = y->left;
    else x = y->right;
    if (x != NULL) x->parent = y->parent; 
    if (y->parent == NULL) root = x; 
    else
        if (y == y->parent->left) y->parent->left = x;
        else y->parent->right = x; 
    if (y != z) 
    {
        w = y->key;
        y->key = z->key;
        z->key = w;
    }
    void free(void* z);
    return y;
}

struct element* BST_ZWOLNIJ(struct element* root)
{
    if (root != NULL)
    {
        BST_ZWOLNIJ(root->left);
        BST_ZWOLNIJ(root->right);
        void free(void* root);
    }
}