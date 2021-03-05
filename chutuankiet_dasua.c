#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
 //HV : Chu Tuan Kiet. ANHTTT c155

char fileName[] = "iris.data";


typedef struct iris{
    float sepal_length;
    float sepal_width;
    float petal_length;
    float petal_width;
    char Class[20];
}IRIS;

typedef struct line {
    char obj[60];
}Line;

int sophantu(char fileName[]);
void pressAnyKey();
void printLine(int n);
void docFile(IRIS *arr, char fileName[]);
void nhap(IRIS *arr, int n);
void ghiFile(IRIS *arr, int n, char fileName[]);
void showList(IRIS *arr, int n);
void ghiFileBin(IRIS *arr, int n, char fileBin[]);
void XoaPhanTu(IRIS *arr, int soluong, int pos);

int main() {
    int key;
    char fileBin[20];
    int soluong = sophantu(fileName);
    IRIS *arr = (IRIS*)malloc(soluong*sizeof(IRIS)); 

    docFile(arr, fileName);
    
    while (1) {
        printf("\n--------------MENU----------------");
        printf("\n1.Them doi tuong moi.");
        printf("\n2.Ghi doi tuong ra File van ban.");
        printf("\n3.Hien thi danh sach.");
        printf("\n4.Ghi File nhi phan. ");
        printf("\n5.Xoa doi tuong trong danh sach.");
        printf("\n6.Hien thi so luong doi tuong. ");
        printf("\n0.Thoat ");
        printf("\n----------------------------------");
        printf("\nNhap tuy chon : ");
        scanf("%d", & key);

        switch (key) {
        case 1: //Them doi tuong
            printf("\n Them mot doi tuong: ");
            ++soluong;
            arr = (IRIS *)realloc(arr, (soluong+1)*sizeof(IRIS));
            nhap(arr, soluong);
            printf("\n Them doi tuong thang cong! ");
            pressAnyKey();
            break;
        case 2: //Ghi doi tuong ra file
            if (soluong > 0) {
                printf("Dang ghi ra file....\n");
                ghiFile(arr, soluong, fileName);
            } else {
                printf("\nDS trong!!!");
            }
            printf("\nGhi file thanh cong! ");
            pressAnyKey();
        case 3: //Hien thi danh sach
            if (soluong > 0) {
                printf("\nHien thi danh sach doi tuong: \n");
                showList(arr, soluong);
            } else {
                printf("\nDanh sach doi tuong trong !!");
            }
            pressAnyKey();
            break;
        case 4: // Ghi file nhi phan
            if (soluong > 0) {
                printf("\nNhap ten file nhi phan (bao gom ca .bin): ");
                scanf("%s", &fileBin);
                printf("\nDang ghi ra file....\n");
                ghiFileBin(arr, soluong, fileBin);
                printf("\nGhi file thanh cong....\n");
            } else {
                printf("\nDS trong!!!");
            }
            pressAnyKey();
            break;
        case 5:
            if(soluong > 0){
                int pos;  
                printf("\nNhap vi tri muon xoa: ");
                scanf("%d", &pos);
                XoaPhanTu(arr, soluong, pos);
                printf("\nHoan tat !! Chon chuc nang 3 de xem lai");
                --soluong;
            }else{
                printf("\nDanh sach trong, khong the xoa !");
            }
            pressAnyKey();
            break;
        case 6: // so luong doi tuong
            printf("\n So luong doi tuong la : %d", soluong);
            pressAnyKey();
            break;
        case 0: //thoat
            printf("\nBan da chon THOAT chuong trinh!! Hen gap lai \n");
            getch();
            return 0;
        default:
            printf("\nKhong co chuc nang nay !");
            pressAnyKey();
            break;
        }
    }

    return 0;
}

void pressAnyKey() {
    printf("\n\nBam phim bat ky de tiep tuc...");
    getch();
    system("cls");
}

void printLine(int n) {
    printf("\n");
    int i;
    for (i = 0; i < n; i++) {
        printf("_");
    }
    printf("\n");
}
int sophantu(char fileName[]){
    FILE *fp = fopen(fileName, "r");
    int n = 0;
    fseek(fp,0,SEEK_SET );
    fscanf(fp,"%d\n",&n);
    fclose(fp);
    return n;
}

void docFile(IRIS *arr, char fileName[]) {
    FILE * fp;
    int i = 0;
    fp = fopen(fileName, "r");
    fseek(fp,4,SEEK_SET);
    printf("Chuan bi doc file: ");
    puts(fileName);
    while (fscanf(fp, "%f,%f,%f,%f,%s\n", &((arr+i)->sepal_length), &((arr+i)->sepal_width), &((arr+i)->petal_length), &((arr+i)->petal_width), (arr+i)->Class) != EOF) {
        // printf("%.1f\t%.1f\t%.1f\t%.1f\t%s\n", (arr+i)->sepal_length, (arr+i)->sepal_width, (arr+i)->petal_length, (arr+i)->petal_width, (arr+i)->Class);
        printf("Dang doc ban ghi thu %d \n", i);
        i++;
        system("cls");
    }
    printf("So luong doi tuong co san trong file la: %d \n", i);

    fclose(fp);
}

void nhap(IRIS *arr, int n) {
	printLine(40);
    printf("\n Nhap doi tuong thu %d : ", n);
        int i = n-1;
    //-------------
    printf("\n Nhap sepal_length (float): ");
    scanf("%f", &((arr+i)->sepal_length));
    printf("\n Nhap sepal_width (float): ");
    scanf("%f", &((arr+i)->sepal_width));
    printf("\n Nhap petal_length (float): ");
    scanf("%f", &((arr+i)->petal_length));
    printf("\n Nhap petal_width (float): ");
    scanf("%f", &((arr+i)->petal_width));
    printf("\n Nhap class : ");
    fflush(stdin);
    gets((arr+i)->Class);
    printf("%.1f\t%.1f\t%.1f\t%.1f\t%s\n", (arr+i)->sepal_length, (arr+i)->sepal_width, (arr+i)->petal_length, (arr+i)->petal_width, (arr+i)->Class);
    printLine(40);
}

void ghiFile(IRIS *arr, int n, char fileName[]) {
    FILE * fp;
    fp = fopen(fileName, "w");
    int i;
    fprintf(fp, "%d\n", n);
    for (i = 0; i < n; i++) {
        fprintf(fp, "%.1f,%.1f,%.1f,%.1f,%s\n", (arr+i)->sepal_length, (arr+i)->sepal_width, (arr+i)->petal_length, (arr+i)->petal_width, (arr+i)->Class);
    }
    fclose(fp);
}

void showList(IRIS *arr, int n) {
    printLine(90);
    int i;
    printf("\nsepal_length\tsepal_width\tpetal_length\tpetal_width\tClass\n");
    for (i = 0; i < n; i++) {
        printf("%.1f\t\t%.1f\t\t%.1f\t\t%.1f\t\t%s\n", (arr+i)->sepal_length, (arr+i)->sepal_width, (arr+i)->petal_length, (arr+i)->petal_width, (arr+i)->Class );

    }
    printLine(90);
}

void ghiFileBin(IRIS *arr, int n, char fileBin[]) {
    int i = 0;
    FILE * fp;
    fp = fopen(fileBin, "wb");
    fwrite(&n, sizeof(int), 1, fp);
    for(i = 0; i < n; i++){
        fwrite((arr+i),sizeof(IRIS),1,fp);
    }
    fclose(fp);
}

void XoaPhanTu(IRIS *arr, int soluong, int pos){
    if(pos < 0){
        pos = 0;
        printf("\nVi tri %d < 0....", pos);
        printf("\nDang xoa doi tuong dau....");
    }else if (pos >= soluong){
        pos = soluong - 1;
        printf("\nVi tri %d lon hon so luong doi tuong....", pos);
        printf("\nDang xoa doi tuong cuoi....");

    }
    int i = 0;
    printf("\nDang xoa doi tuong %d", pos);
    for(i = pos ; i < soluong - 1; i++){
        arr[i] = arr[i+1];
    }
}
/// có 200 dòng thui mò ^^