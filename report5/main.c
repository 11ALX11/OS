#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>

int main() {
    int j, fd, strArrCount, strArr2Count;
    size_t sizeRead;
    char input[255], string[255];
    char stringArray[1000][255];
    int stringArraySize[1000];
    char stringArray2[1000][255];
    int stringArray2Size[1000];

    sizeRead = 1; j = 0; strArrCount = 0;
    while (sizeRead > 0) {
        //Считываем данные из стандартного потока ввода
        sizeRead = read(0, input, 255);

        for (int i = 0; i < sizeRead; i++) {
            string[j] = input[i];
            j++;

            if (string[j-1] == '\n') {
                //Первая - цифра
                if (string[0] >= 48 && string[0] <= 57) {
                    //Замена X на Y
                    for (int k = 0; k < j; k++) {
                        if (string[k] == 'X') {
                            string[k] = 'Y';
                        }
                    }

                    strcpy(stringArray[strArrCount], string);
                    stringArraySize[strArrCount++] = j;
                    if (strArrCount > 1000) strArrCount = 1000;
                }

                j=0;
            }
        }
    }

    (void)umask(0);
    if((fd = open("text2", O_RDONLY | O_CREAT, 0666)) < 0){
        printf("Can\'t open file\n");
        return(-1);
    }

    sizeRead = 1; j = 0; strArr2Count = 0;
    while (sizeRead > 0) {
        //Считываем данные из файла
        sizeRead = read(fd, input, 255);
        if (sizeRead < 0) {
            printf("Error reading file.\n");
            return -1;
        }

        for (int i = 0; i < sizeRead; i++) {
            string[j] = input[i];
            j++;

            if (string[j-1] == '\n') {
                strcpy(stringArray2[strArr2Count], string);
                stringArray2Size[strArr2Count++] = j;
                if (strArr2Count > 1000) strArr2Count = 1000;

                j=0;
            }
        }
    }

    if(close(fd) < 0){
        printf("Can\'t close file\n");
    }

    int i = 0;
        j = 0;
    while (i < strArrCount || j < strArr2Count) {
        //Вывод на экран
        if (i < strArrCount) write(1, stringArray[i], stringArraySize[i]);
        if (j < strArr2Count) write(1, stringArray2[i], stringArray2Size[i]);
        i++; j++;
    }

    return 0;
}
