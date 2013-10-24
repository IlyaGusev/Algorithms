#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <sys/stat.h>
#include <cstring>
struct stat stat_buf;
using namespace std;
struct letter
{
    char name;
    int freak;
    letter* left;
    letter* right;
};

struct base_leaf
{
    char name;
    char * code;
};

letter* build_set()
{
    FILE * pFile;
    pFile= fopen ("input.txt", "r");
    stat("input.txt", &stat_buf);
    int i=1;
    char ch;
    letter* alphabet=(letter*)malloc(sizeof(letter));
    int meet;
    int size=1;
    while(fscanf (pFile, "%c", &ch)!=EOF)
    {
        meet=-1;
        for (int i=1; i<size; i++)
            if (ch==alphabet[i].name)
                meet=i;
        if (meet==-1)
        {
            size++;
            alphabet=(letter*)realloc(alphabet,size*sizeof(letter));
            alphabet[size-1].name=ch;
            alphabet[size-1].freak=1;
            alphabet[size-1].left=NULL;
            alphabet[size-1].right=NULL;
        }
        else
            alphabet[meet].freak++;
    }
    alphabet=(letter*)realloc(alphabet,(size+1)*sizeof(letter));
    //Добавление спец. символа
    alphabet[size].name=(char)7;
    alphabet[size].freak=1;
    alphabet[size].left=NULL;
    alphabet[size].right=NULL;
    alphabet[0].freak=size;
    fclose (pFile);
    return alphabet;
}

void swap(letter &a, letter &b)
{
    letter temp=a;
    a=b;
    b=temp;
}
void heapify(letter a[], int rangemax, int i)
{
    int l=2*i;
    int r=2*i+1;
    int smallest=i;
    if (l<=rangemax && a[l].freak<a[i].freak)
        smallest=l;
    if (r<=rangemax && a[r].freak<a[smallest].freak)
        smallest=r;
    if (smallest!=i)
    {
        swap(a[i], a[smallest]);
        heapify(a, rangemax, smallest);
    }
}
void build_min_heap(letter a[], int size)
{
    for (int i=(size)/2; i>=1; i--)
        heapify(a,size,i);
}
letter heap_extract_min(letter a[])
{
    letter min=a[1];
    a[1]=a[a[0].freak];
    a[0].freak--;
    a=(letter*)realloc(a,(a[0].freak+1)*sizeof(letter));
    heapify(a,a[0].freak,1);
    return min;
}
letter *Haffman(letter a[])
{
    int size=a[0].freak;
    for (int i=1; i<=size-1; i++)
    {
        letter* z=(letter*)malloc(sizeof(letter));
        letter* x=(letter*)malloc(sizeof(letter));
        letter* y=(letter*)malloc(sizeof(letter));
        *x=heap_extract_min(a);
        *y=heap_extract_min(a);
        z->left=x;
        z->right=y;
        z->freak=x->freak+y->freak;
        z->name=(char)180;
        a[0].freak++;
        a=(letter*)realloc(a,(a[0].freak+1)*sizeof(letter));
        a[a[0].freak]=(*z);
        free(z);
    }
    return a;
}
void create_letter_base(letter* root, base_leaf base[], char* current_code, int current_code_size)
{
    if (root->left==NULL && root->right==NULL)
    {
        int i=0;
        while(base[i].name!=(char)180)
            i++;
        base[i].name=root->name;
        current_code=(char*)realloc(current_code,(current_code_size+1)*sizeof(char));
        current_code[current_code_size]='\0';
        base[i].code=(char*)malloc((current_code_size+1)*sizeof(char));
        memcpy(base[i].code, current_code, current_code_size+1);
        free(root);
    }
    else
    {
        current_code=(char*)realloc(current_code,(current_code_size+1)*sizeof(char));
        current_code_size++;
        current_code[current_code_size-1]='0';
        create_letter_base(root->left, base, current_code, current_code_size);
        current_code[current_code_size-1]='1';
        create_letter_base(root->right, base, current_code, current_code_size);
        free(root);
    }
}

int pow(int n)
{
    int j=1;
    for (int i=0; i<n; i++)
        j*=2;
    return j;
}
char convert_to_char(char* a)
{
    int ch=0;
    for (int i=0; i<=7; i++)
        ch=ch+(((int)a[i]-(int)'0')*pow(i));
    return (char)ch;
}
void shifr(base_leaf* base, int base_size)
{
    FILE* pFileIn;
    pFileIn=fopen("input.txt","r");
    FILE* pFileTemp;
    pFileTemp=fopen("temp.txt","w");
    char ch;
    int i;
    while(fscanf (pFileIn, "%c", &ch)!=EOF)
    {
        for (i=0; i<base_size; i++)
            if (ch==base[i].name)
                break;
        fprintf(pFileTemp, "%s", base[i].code);
    }
    int j=0;
    for (j=0; j<base_size; j++)
        if ((char)7==base[j].name)
            break;
    fprintf(pFileTemp, "%s", base[j].code);
    fclose (pFileIn);
    fclose (pFileTemp);

    pFileTemp=fopen("temp.txt","r");
    FILE* pFileOut;
    pFileOut=fopen("shifr.txt","w");

    i=0;
    char* cur=(char*)malloc(sizeof(char));
    while (fscanf (pFileTemp, "%c", &ch)!=EOF)
    {
        cur=(char*)realloc(cur, (i+2)*sizeof(char));
        cur[i]=ch;
        cur[i+1]='\0';
        i++;
        if (i==8)
        {
            fprintf(pFileOut, "%c", convert_to_char(cur));
            i=0;
            cur=(char*)realloc(cur, 1*sizeof(char));
        }
    }
    if (i!=0)
    {
        cur=(char*)realloc(cur, 9*sizeof(char));
        for (int j=i; j<8; j++)
            cur[j]='0';
        cur[8]='\0';
        fprintf(pFileOut, "%c", convert_to_char(cur));
    }
    free(cur);
    fclose(pFileOut);
    fclose(pFileTemp);
}
char* convert_to_bin(char ch, char* cur)
{
    int n=(int)ch;
    if (n<0) n+=256;
    for (int i=0; i<=7; i++)
    {
        cur[i]=(char)(n%2+48);
        n/=2;
    }
    cur[8]='\0';
    return cur;
}
void deshifr(base_leaf* base, int base_size)
{
    FILE * pFileIn;
    pFileIn= fopen ("shifr.txt", "r");
    FILE * pFileTemp;
    pFileTemp= fopen ("temp.txt", "w");

    char ch;
    char*cur=(char*)malloc(9*sizeof(char));
    while(fscanf (pFileIn, "%c", &ch)!=EOF)
    {
        cur=convert_to_bin(ch, cur);
        fprintf(pFileTemp, "%s", cur);
    }
    fclose(pFileIn);
    fclose(pFileTemp);

    int end;
    for (end=0; end<base_size; end++)
        if ((char)7==base[end].name)
            break;

    pFileTemp= fopen ("temp.txt", "r");
    FILE * pFileOut;
    pFileOut= fopen ("deshifr.txt", "w");
    cur=(char*)realloc(cur,sizeof(char));
    bool con=0;;
    int i=1;
    while(fscanf (pFileTemp, "%c", &ch)!=EOF)
    {
        con=0;
        cur=(char*)realloc(cur, (i+1)*sizeof(char));
        cur[i-1]=ch;
        cur[i]='\0';
        i++;
        int j;
        for (j=0; j<base_size; j++)
            if (strcmp(base[j].code, cur)==0)
            {
                con=1;
                break;
            }
        if (con==1)
        {
            if (j==end)
                break;
            fprintf(pFileOut, "%c", base[j].name);
            i=1;
        }
    }
    free(cur);
    fclose (pFileTemp);
    /*remove("temp.txt");*/
    fclose(pFileOut);
}
int main()
{
    letter* alphabet=build_set();//size is alphabet[0].freak
    build_min_heap(alphabet, alphabet[0].freak);

    int base_size=alphabet[0].freak;
    alphabet=Haffman(alphabet);
    base_leaf* base=(base_leaf*)malloc(base_size*sizeof(base_leaf));
    for (int i=0; i<base_size; i++)
        base[i].name=(char)180;
    char* code=(char*)malloc(sizeof(char));
    alphabet[0]=alphabet[1];
    alphabet=(letter*)realloc(alphabet,sizeof(letter));

    create_letter_base(alphabet, base, code, 0);
    free(code);

    FILE* fout;
    fout=fopen("key.txt", "w");
    for (int i=0; i<base_size; i++)
        fprintf(fout, "%c %s\n", base[i].name,base[i].code);
    fclose(fout);

    /*for (int i=0; i<base_size; i++)
        cout<<base[i].name<<" "<<base[i].code<<endl;*/

    shifr(base, base_size);
    deshifr(base, base_size);
    free(base);
}
