//Василевский И.А. гр.150702
//Компоненты файла f – целые двухзначные числа.Получить файл g, образованный из f включением только чисел больше K.

#include <stdio.h>
#include <math.h>

int getMinNumber();
void writeBiggerNumbers(FILE* sourceFile, FILE* newFile, int minNumber);

int main()
{
    FILE* sourceFile, * newFile;
    int minNumber;

    fopen_s(&sourceFile, "sourceFile.txt", "r");
    fopen_s(&newFile, "newFile.txt", "w");

    if (sourceFile == NULL || newFile == NULL)
        printf("Files could not be opened\n");
    else
    {
        minNumber = getMinNumber();
        writeBiggerNumbers(sourceFile, newFile, minNumber);
        fclose(sourceFile);
        fclose(newFile);
    }
}

int getMinNumber()
{
    int minNumber;
    printf("Enter the minimum two-digit number: ");
    scanf_s("%d", &minNumber);
    return minNumber;
}

void writeBiggerNumbers(FILE* sourceFile, FILE* newFile, int minNumber)
{
    char currentCharNumber[3];
    int currentNumber = 0;
    do
    {
        fgets(currentCharNumber, 3, sourceFile);

        for (int i = 0; currentCharNumber[i] != '\0'; i++)
            currentNumber += ((int)currentCharNumber[i] - 48) * pow(10, 1 - i);

        if (currentNumber > minNumber)
            fprintf(newFile, "%s", currentCharNumber);

        currentNumber = 0;
    } while (!feof(sourceFile));
}