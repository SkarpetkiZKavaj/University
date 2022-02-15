//Василевский И.А. гр.150702
//Удалите из текстового файла одинаковые строки. Если в файле нет одинаковых строк, вывести на экран соответствующее сообщение.
//Вывести на экран первоначальный файл и преобразованный. В программе используйте подпрограммы.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void printFile(FILE* file);
int deleteIdenticalStrings(FILE* sourceFile, FILE* newFile, char* (*getStr)(FILE*), void (*nextStr)());
char* getNextSting(FILE* file);
void goToNextString(FILE* file);

int main()
{
    FILE* sourceFile, *newFile;
    int uniqueStrings;

    fopen_s(&sourceFile, "sourceFile.txt", "r+");
    fopen_s(&newFile, "newFile.txt", "w+");

    if (sourceFile == NULL || newFile == NULL)
        printf("Files could not be opened\n");
    else
    {
        printFile(sourceFile);

        uniqueStrings = deleteIdenticalStrings(sourceFile, newFile, getNextSting, goToNextString);

        if (uniqueStrings)
        {
            printf("File doesn't contain seriate strings\n");
            fclose(newFile);
            fclose(sourceFile);
            remove("newFile.txt");
        }
        else
        {
            rewind(newFile);
            printFile(newFile);
            fclose(sourceFile);
            fclose(newFile);
            remove("sourceFile.txt");
            rename("newFile.txt", "sourceFile.txt");
        }
    }

    return 0;
}

void printFile(FILE* file)
{
    do
    {
        printf("%c", fgetc(file));
    } while (!feof(file));
    printf("\n\n");
}

int deleteIdenticalStrings(FILE* sourceFile, FILE* newFile, char* (*getStr)(FILE*), void (*nextStr)())
{
    char* currentString;
    char* nextString;
    int stringIsSeriate = 0, uniqueStrings = 1, numberOfString = 0;

    rewind(sourceFile);
    while (!feof(sourceFile))
    {
        numberOfString++;
        nextStr(sourceFile);
    }

    rewind(sourceFile);
    for (int i = 0; i < numberOfString; i++)
    {
        currentString = getStr(sourceFile);
        rewind(sourceFile);

        for (int j = 0; !feof(sourceFile) && !stringIsSeriate; j++)
        {
            nextString = getStr(sourceFile);
            if (i != j)
            {
                stringIsSeriate = !strcmp(currentString, nextString);

                if (uniqueStrings)
                    uniqueStrings = !stringIsSeriate;
            }
            free(nextString);
        }

        if (!stringIsSeriate)
        {
            fputs(currentString, newFile);
            fputc('\n', newFile);
        }
        else
            stringIsSeriate = 0;

        free(currentString);
        rewind(sourceFile);

        for (int j = 0; j < i + 1; j++)
            nextStr(sourceFile);
    }

    return uniqueStrings;
}

char* getNextSting(FILE* file)
{
    char* nextString = (char*)calloc(1, 1);
    char symbol = fgetc(file);
    int size = 1;

    while (symbol != '\n' && !feof(file))
    {
        nextString = (char*)realloc(nextString, ++size);
        nextString[size - 2] = symbol;
        symbol = fgetc(file);
    }

    nextString[size - 1] = '\0';

    return nextString;
}

void goToNextString(FILE* file)
{
    char symbol = fgetc(file);

    while (symbol != '\n' && !feof(file))
        symbol = fgetc(file);

}