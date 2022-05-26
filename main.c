#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Info{int ID; int quantity; char name[30];};
struct Info Book[100]; ///global struct type
struct Info temp;

void InsertBook() ;
void Scan() ;
void DeleteBook(int BookNum) ;
int SearchID(int x , int BookNum) ;
int SearchName() ;
void DisplaySorted(int length) ;
void DisplayUnsorted(int Number) ;

int main()
{
    int BookNum = 3 ;
    int choice ;
    char again ;
    printf("\n=============================\n") ;
    printf("  LIBRARY MANAGEMENT SYSTEM  ") ;
    printf("\n=============================\n") ;
    do{
        printf("Please insert the operation number: \n") ;
        printf("\n1- Insert a new book.\n2- Delete an exist book by ID.\n3- Search for a book by ID.") ;
        printf("\n4- Search for a book by name\n5- Display all books in alphabetical order.\n6- Display all books.\n") ;
        scanf("%d",&choice) ;
        if(choice == 1){
            InsertBook() ;
            BookNum++ ;
            printf("\n Try another operation ?? (y / Y) for yes.") ;
            scanf("%c",&again) ;
        }
        else if(choice == 2){
            DeleteBook(BookNum) ;
            BookNum-- ;
            printf("\n Try another operation ?? (y / Y) for yes.") ;
            getchar() ;
            scanf("%c",&again) ;
        }
        else if(choice == 3){
            printf("Enter book ID to search for: ") ;
            int x_ID ;
            scanf("%d",&x_ID) ;
            SearchID(x_ID , BookNum) ;
            printf("\n Try another operation ?? (y / Y) for yes.") ;
            getchar() ;
            scanf("%c",&again) ;
        }
        else if(choice == 4){
            SearchName() ;
            printf("\n Try another operation ?? (y / Y) for yes.") ;
            getchar() ;
            scanf("%c",&again) ;
        }
        else if(choice == 5){
            DisplaySorted(BookNum) ;
            printf("\n Try another operation ?? (y / Y) for yes.") ;
            getchar() ;
            scanf("%c",&again) ;
        }
        else if(choice == 6){
            DisplayUnsorted(BookNum) ;
            printf("\n Try another operation ?? (y / Y) for yes.") ;
            getchar() ;
            scanf("%c",&again) ;
        }
        else{
            printf("Error in choice..:(\n") ;
        }
    }while(again == 'y' || again == 'Y') ;
    return 0 ;
}

/// function to scan to struct
void Scan()
{
    int i=0;
    FILE *file=fopen("asem.txt","r");
    if(file==NULL)
    {
        printf("the file don't opened");
        exit(1);
    }
    while(!feof(file))
    {
        fscanf(file,"%d%d%[^\n]",&Book[i].ID,&Book[i].quantity,Book[i].name);
        //printf("%d\t%d\t%s\n",b[i].id,b[i].quantity,b[i].name);
        i++;
    }
    fclose(file);
}

///function to insert book
void InsertBook()
{
    long long id ;
    int quantity ;
    char name[30] ;
    FILE *fptr = fopen("asem.txt","a") ;
    if(fptr == NULL){
        printf("Error\n") ;
        exit(1) ;
    }
    else{
        printf("Please enter book ID, book quantity and book name....\t(SEPARATED BY SPACE)\n") ;
        scanf("%lld %d",&id,&quantity) ;
        getchar() ;
        gets(name) ;
        fprintf(fptr,"\n%lld %d %s",id,quantity,name) ;
        printf("Your book is added successfully \n");
    }
    fclose(fptr) ;
}

/// function to delete book
void DeleteBook(int BookNum)
{
    Scan() ;
    int Book_ID ;
    int i = 0 ;
    printf("Enter the Book ID to  delete:") ;
    scanf("%d",&Book_ID) ;
    FILE *fptr = fopen("asem.txt","w") ;
    while(BookNum){
        if(Book_ID!=Book[i].ID){
            fprintf(fptr,"%d %d",Book[i].ID,Book[i].quantity) ;
            fputs(Book[i].name,fptr) ;
            if(BookNum != 1)
                fprintf(fptr,"\n") ;
            }
        i++ ;
        BookNum-- ;
        }
    printf("Successfully deleted :)..\n") ;
    fclose(fptr) ;
}


/// function to search by ID
int SearchID(int x , int BookNum)
{
    Scan() ;
    if(BookNum < 0){
        printf(" Not found\n") ;
        return -1 ;
    }

    if(Book[BookNum].ID == x){
        printf("Book found successfully :)\n") ;
        printf("Book quantity: %d\tBook name: %s\n",Book[BookNum].quantity,Book[BookNum].name) ;
        return 0 ;
    }
    return SearchID(x , BookNum-1) ;
}

/// function to search by name
int SearchName()
{
    Scan();
    char x[100];
    int lower = 0,upper = 2;
    struct Info temp;
    for(int i=0; i<3; i++)
    {
        for(int j=i+1; j<3; j++)
        {
            if(strcmp(Book[i].name,Book[j].name)>0)
            {
                temp=Book[i];
                Book[i]=Book[j];
                Book[j]=temp;
            }}}
    printf("Enter book's name..\n");
    getchar();
    gets(x);
    while (lower <= upper)
    {
        int mid = (lower + upper)/2;

        if (strcmp(x , Book[mid].name)==0){
            printf("Found\n");
            return 0;}
        else if (strcmp(x , Book[mid].name)>0)
            lower = mid + 1;
        else
            upper = mid - 1;
    }
        printf("Not Found\n");
}

/// function to display sorted
void DisplaySorted(int length)
{
    Scan() ;
    struct Info temp ;
    for(int i = 0 ; i < length ; i++)
        for(int j = i+1 ; j < length ; j++){
            if(strcmp(Book[i].name , Book[j].name)>0){
                temp = Book[i] ;
                Book[i] = Book[j] ;
                Book[j] = temp ;
            }
        }
    printf("%-15s%-25s %s\n","BOOK ID","BOOK QUANTITY","BOOK NAME") ;
    for(int i = 0 ; i < length ; i++)
        printf("%-15d%-25d%s\n",Book[i].ID,Book[i].quantity,Book[i].name) ;
}

/// function to display unordered
void DisplayUnsorted(int Number)
{
    Scan() ;
    printf("%-15s%-25s %s\n","BOOK ID","BOOK QUANTITY","BOOK NAME") ;
    for(int i = 0 ; i < Number ; i++)
        printf("%-15d%-25d%s\n",Book[i].ID,Book[i].quantity,Book[i].name) ;
}
