#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
//#include "solvesudoku.h"

int** createPuzzle();
void printPuzzle(int** puzzle);
bool checkAvailable(int** puzzle, int* row, int* column);
bool checkBox(int** puzzle, int row, int column, int val);
bool solvePuzzle(int** puzzle);
int** copyPuzzle(int** puzzle);
void userChoice(int** userPuzzle, int** tempPuzzle);
void ABOUT();
void RULES();
void Create();
void Generate_Random(int Q);
void Interchange_GroupRows(int n1,int n2);
void Interchange_GroupColumns(int n1,int n2);
void Interchange_Row(int n1,int n2);
void Interchange_Column(int n1,int n2);
void copy_arr();
void Clear_Cell(int lvl);
void display(int arr[9][9]);
int ext=0;
int i,j,a,b,level,lvl;
int arr[9][9];
int arr1[9][9];


int main()
{
    
    /*
    printf("RULES:\n\n");
    printf("1. The objective of Sudoku is to fill a 9x9 grid made of small squares so that each row, each column, and each full 3x3 squares use the numbers 1-9.\n");
    printf("2. While solving the sudoku puzzle you can only use each number one time in the square, column, and row.\n");
    printf("3. You can only insert numbers in the squares that have value \"0\"\n");
    printf("4. If you give up and want to see a solved puzzle please press \"q\" key.\n\n");
    printf("GOOD LUCK!\n");
    */
    //int** puzzle = createPuzzle();
    //

    do
    {
    printf("!!!---WELOME TO THE GAME OF SUDOKU---!!!\n");
    printf("1. WHAT IS SUDOKU ?\n");
    printf("2. RULES TO SOLVE A SUDOKU.\n");
    printf("3. GENERATE A SUDOKU.\n");
    printf("4. SOLVE SUDOKU.\n");
    printf("5. EXIT THE GAME.\n");
    printf("ENTER YOUR CHOICE\n");
    int choice;
    scanf("%d",&choice);
    switch(choice)
    {
    case 1:
        ABOUT();
        break;

    case 2:
        RULES();
        break;

    case 3:

    printf("ENTER THE LEVEL :-\n1. EASY\n2. MEDIUM\n3. HARD\n");
    int lvl;
    scanf("%d",&lvl);
    int** puzzle = createPuzzle();
    int** userPuzzle = copyPuzzle(puzzle);
    int** tempPuzzle = copyPuzzle(puzzle);

    //Create the Sudoku
    

















    // printPuzzle(userPuzzle);
    userChoice(userPuzzle,tempPuzzle);
    // free(puzzle);
    // free(userPuzzle);
    // free(tempPuzzle);
    }
    
    }while(ext==0);
    return 0;
}

// #include <stdio.h>
// #include <stdlib.h>
// #include <stdbool.h>
// #include "solvesudoku.h"

int** createPuzzle()
{
    int i, j;
    int** puzzle;
    Create();
    srand(time(0));

    //Interchange Rows within the group
    Generate_Random(1);

    //Interchange Columns within the group
    Generate_Random(0);

    //Interchange groups of Rows and Columns
    int limit[] = {0, 3 ,6};
    for(i=1; i<=2; i++)
    {
        a = limit[rand() % 3];
        b = limit[rand()%3];
        
        while(a==b)
        {
            a = limit[rand() % 3];
        }

        if(i==1)
            Interchange_GroupRows(a, b);
        else
            Interchange_GroupColumns(a, b);
    }
    copy_arr();
    if(lvl==3)
    {
        level = rand()%6;
        level = level + 20;
    }
    else if(lvl==2)
    {
        level = rand()%6;
        level = level +30;
    }
    else
    {
        level = rand()%6;
        level = level +40;
    }
    Clear_Cell(level);
    display(arr);
    

    puzzle = (int**)malloc(sizeof(int*) * 9);

    for (i = 0; i < 9; i++)
    {
        puzzle[i] = (int*)malloc(sizeof(int) * 9);
        for(j = 0; j < 9; j++)
        {
            puzzle[i][j] = arr[i][j];
        }
    }
    return puzzle;
}


void printPuzzle(int** puzzle){
    int i, j, a;

    printf("\n");
    printf(" 0 | 1  2  3 | 4  5  6 | 7  8  9 | X\n");
    printf(" ---------------------------------\n");
    for (i = 0, a = 1; i < 9; i++, a++){
        for(j = 0; j < 9; j++){
            if (j == 0)
                printf(" %d |", a);
            else if ((j) % 3 == 0)
                printf("|");
            printf(" %d ", puzzle[i][j]);
            if (j == 8)
                printf("|");
        }
        printf("\n");
        if ((i + 1) % 3 == 0)
            printf(" ---------------------------------\n");
    }
    printf(" Y\n");
}

bool checkAvailable(int** puzzle, int* row, int* column){
    int i, j;

    for (i = 0; i < 9; i++){
        for(j = 0; j < 9; j++){
            if (puzzle[i][j] == 0){
                *row = i;
                *column  = j;
                return true;
            }
        }
    }

    return false;
}

bool checkBox(int** puzzle, int row, int column, int val){
    int i, j;
    int squareRow, squareColumn;

    //CHECK VERTICAL
    for(i = 0; i < 9; i++){
        if (puzzle[i][column] == val)
            return false;
    }

    //CHECK HORIZONTAL
    for(j = 0; j < 9; j++){
        if (puzzle[row][j] == val)
            return false;
    }

    //CHECK SQUARE
    squareRow = row - row % 3;
    squareColumn = column - column % 3;

    for(i = 0; i < 3; i++){
        for(j = 0; j < 3; j++){
            if(puzzle[squareRow + i][squareColumn + j] == val)
                return false;
        }
    }

    return true;
}

bool solvePuzzle(int** puzzle){
    int i, j, val;

    if(!checkAvailable(puzzle, &i, &j))
        return true;

    for(val = 1; val < 10; val++){
        if(checkBox(puzzle, i, j, val)){
            puzzle[i][j] = val;
            if(solvePuzzle(puzzle))
                return true;
            else
                puzzle[i][j] = 0;
        }
    }
    return false;
}

int** copyPuzzle(int** puzzle){
    int i, j;
    int** newPuzzle;

    newPuzzle = (int**)malloc(sizeof(int*) * 9);
    for (i = 0; i < 9; i++){
        newPuzzle[i] = (int*)malloc(sizeof(int) * 9);
        for(j = 0; j < 9; j++){
            newPuzzle[i][j] = puzzle[i][j];
        }
    }
    return newPuzzle;
}

void userChoice(int** userPuzzle, int** tempPuzzle){
    int i, j;
    int positionX, positionY, userVal;
    char c;

    while(1){
    if(!checkAvailable(userPuzzle, &i, &j)){
        printf("\nGood Job You Solved the Puzzle!!!\n");
        return;
    }

    while(1){
        printf("\nPress Enter to continue. Press \"q\" to Quit.\n");
        c = getchar();
        if((c == 'q') || (c == 'Q')){
            getchar();
            solvePuzzle(userPuzzle);
            printf("\nSOLVED PUZZLE:\n");
            printPuzzle(userPuzzle);
            return;
        }
        else if((c != '\n') && (c != 'q'))
            getchar();
        else
            break;
    }


    printf("\nplease Enter Coordinate for the square you want to insert the value to in the following format \"X Y\":\n");
    scanf("%d %d",&positionX, &positionY);
    while(1){
        if ((positionX > 9) || (positionX < 1) || (positionY > 9) || (positionY < 1) || (userPuzzle[positionY - 1][positionX - 1] != 0)){
            printf("\nyou can't insert value to this Coordinate, please pick a new Coordinate\n");
            scanf("%d %d",&positionX, &positionY);
        }
        else {
            positionX -= 1;
            positionY -= 1;
            break;
        }
    }


    printf("\nPlease insert value from 1 to 9\n");
    scanf("%d", &userVal);
    while(1){
        if((userVal > 9) || (userVal < 1)){
            printf("\nplease insert valid value:\n");
            scanf("%d", &userVal);
        }
        else break;
    }

    if(checkBox(userPuzzle, positionY, positionX, userVal))
        userPuzzle[positionY][positionX] = userVal;
    else
        printf("\nincorrect value for the X = %d Y = %d coordinate, please try again\n",positionX + 1, positionY + 1);

    for (i = 0; i < 9; i++){
        for(j = 0; j < 9; j++){
            tempPuzzle[i][j] = userPuzzle[i][j];
        }
    }

    if(!solvePuzzle(tempPuzzle)){
        printf("\nincorrect value for the X = %d Y = %d coordinate, please try again\n",positionX + 1, positionY + 1);
        userPuzzle[positionY][positionX] = 0;
    }
    getchar();
    printPuzzle(userPuzzle);
    }


    return;
}

void ABOUT()
{
    printf("\nThe history of Sudoku puzzles likely has it roots in the mathematical concept of Latin Squares.\nLeonhard Euler, a Swiss mathematician, in the 1780's developed the idea of arranging numbers in such a way that any number or symbol would occur only once in each row or column. Latin Squares is used in statistical analysis.\n");
    printf("Sudoku rules add the restraint that each region may only have the numbers (or symbols) occurring but once. Howard Garns, an architect from Indianapolis, is credited with creating this rule when he developed the puzzle we know as Sudoku.\n");
    printf("Dell Magazines published the puzzle under the name of Number Place for over 25 years. It is a staple of Dell Magazines to this day. You can find Number Place in Dell Collector's Series.\n");
    printf("Presently Dell Magazines publishes several Sudoku puzzle books with such titles as Dell Original Sudoku, Dell Extreme Sudoku, and Dell Maximum Sudoku to name a few.\n");
    printf("Sudoku is definitely an American invention, but the name isn't. Introduced into Japan by Nikoli under the name of 'Suuji wa dokushin ni kagiru' roughly translating to mean the numbers must be unmarried or single. Thankfully the name has been shortened to Sudoku.\n");
    printf("The history of Sudoku continues to expand. Wayne Gould, a retired Hong Kong judge, author of Su Doku The Official Utterly Addictive Number-Placing Puzzle, first encountered the puzzle in a Tokyo book store.\n");
    printf("He began to create his own puzzles and was soon addicted like the rest of us. He introduced his puzzles to The Times, a British newspaper, as Su Doku. His puzzles first appeared there on November 12, 2004.\n");
    printf("As they say, the rest is history. The puzzle has crossed the pond back to the United States from England. It now appears in many major newspapers across the USA. It's popularity is gaining daily.\n");
    printf("Today you will find not only Sudoku puzzle books, but Sudoku hand held games, Sudoku board games and a growing list of merchandise.\n\n\n");
}

void RULES()
{
    printf("\nRULE 1 :\nThere are 9 rows in a traditional Sudoku puzzle.\nEvery row must contain the numbers 1, 2, 3, 4, 5, 6, 7, 8, and 9. \nThere may not be any duplicate numbers in any row. \nIn other words, there can not be any rows that are identical.\n");
    printf("RULE 2 :\nThere are 9 columns in a traditional Sudoku puzzle.\nLike the Sudoku rule for rows, every column must also contain the numbers 1, 2, 3, 4, 5, 6, 7, 8, and 9. \nAgain, there may not be any duplicate numbers in any column. Each column will be unique as a result.\n");
    printf("RULE 3 :\nA region is a 3x3 box like the one shown to the left. There are 9 regions in a traditional Sudoku puzzle.\nLike the Sudoku requirements for rows and columns, every region must also contain the numbers 1, 2, 3, 4, 5, 6, 7, 8, and 9.\nDuplicate numbers are not permitted in any region.\nEach region will differ from the other regions.\n\n\n");
}

void Create()
    {
    int A=1; int B=1;
    int i, j;
    for(i=0 ; i<9 ; i++)
    {
        A = B;
        for(j=0 ; j<9 ; j++)
        {
            if(A<=9)
            {
                arr[i][j]=A;
                A++;
            }
            else
            {
                A=1;
                arr[i][j]=A;
                A++;
            }
        }
        B = B + 3;
        if(B>9)
            B = B%9 + 1;
    }
    }

void Generate_Random(int Q)
    {
    int i,j;
    int lower=0, upper=2;
    int num1, num2 ; //To store random numbers
    for(i=1; i<=3; i++)  //Loop is used to generate three sets of number
    {
        num1 = (rand() % (upper - lower + 1)) + lower;
        do
        {
            num2 = (rand() % (upper - lower + 1)) + lower;
        }while(num1==num2); //To ensure both the numbers aren't equal

        lower = lower + 3;
        upper = upper + 3;

        if(Q == 1)
            Interchange_Row(num1, num2);
        else
            Interchange_Column(num1, num2);
    }
    }

void Interchange_GroupRows(int n1,int n2)
    {
    int i,j;
   int temp;
   for(i=1; i<=3; i++)
   {
      for(j=0; j<9; j++)
      {
         temp=arr[n1][j];
         arr[n1][j]=arr[n2][j];
         arr[n2][j]=temp;
      }
      n1++;
      n2++;
   }
    }

    //Function to Interchange two group of Columns
void Interchange_GroupColumns(int n1,int n2)
    {
    int i,j;
   int temp;
   for(i=1; i<=3; i++)
   {
      for(j=0; j<9; j++)
      {
         temp=arr[j][n1];
         arr[j][n1]=arr[j][n2];
         arr[j][n2]=temp;
      }
      n1++;
      n2++;
   }
    }

void Interchange_Row(int n1,int n2)
    {
   int i;
   int temp; //n1 and n2 are two rows that we are selecting to interchange.
   for(i=0;i<9;i++)
   {
      temp=arr[n1][i];
      arr[n1][i]=arr[n2][i];
      arr[n2][i]=temp;
    }
    }

    //Function to interchange columns within the same group
    void Interchange_Column(int n1,int n2)
    {
    int temp; int i;
    for(i=0; i<9; i++)
    {
      temp=arr[i][n1];
      arr[i][n1]=arr[i][n2];
      arr[i][n2]=temp;
    }
    }

void copy_arr()
{
    int i,j;
    for(i=0;i<9;i++)
    {
        for(j=0;j<9;j++)
        {
            arr1[i][j]=arr[i][j];
        }
    }
}

void Clear_Cell(int lvl)
    {
        int x,y;
    while(lvl>0)
    {
        int cell_number = rand() % 82;
        int i = cell_number / 9;
        int j = cell_number % 9;

        if(j!=0)
            j = j-1;

        if(arr[i][j]!=0)
        {
                arr[i][j]=0;
                lvl--;
        }
    }
    }

void display(int arr[9][9])
    {
    int i,j;
    for(i=0;i<9;i++)
    {
        printf("-------------------------------------\n");
        for(j=0;j<9;j++)
        {
            if(j==8)
                printf("| %d |",arr[i][j]);
            else
                printf("| %d ",arr[i][j]);
        }
        printf("\n");
        if(i==8)
            printf("---------------------------------------\n\n");
    }
    }