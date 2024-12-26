#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct SinhVien {
    int id;
    char name[100];
    int age;
};

#define MAX 100
struct SinhVien students[MAX];
int studentCount = 0;

void docFile() {
    FILE *file = fopen("students.dat", "rb");
    if (file) {
        studentCount = fread(students, sizeof(struct SinhVien), MAX, file);
        fclose(file);
    }
}

void ghiFile() {
    FILE *file = fopen("students.dat", "wb");
    if (file) {
        fwrite(students, sizeof(struct SinhVien), studentCount, file);
        fclose(file);
    }
}

void inDanhSach() {
    if (studentCount == 0) {
        printf("Danh sach sinh vien rong.\n");
        return;
    }
    for (int i = 0; i < studentCount; i++) {
        printf("ID: %d, Ten: %s, Tuoi: %d\n", students[i].id, students[i].name, students[i].age);
    }
}

void themSinhVien() {
    if (studentCount >= MAX) {
        printf("Danh sach sinh vien da day.\n");
        return;
    }
    struct SinhVien sv;
    printf("Nhap ID: ");
    scanf("%d", &sv.id);
    getchar();
    printf("Nhap Ten: ");
    fgets(sv.name, sizeof(sv.name), stdin);
    sv.name[strcspn(sv.name, "\n")] = '\0';
    printf("Nhap Tuoi: ");
    scanf("%d", &sv.age);
    students[studentCount++] = sv;
    ghiFile();
}

void suaSinhVien() {
    int id;
    printf("Nhap ID sinh vien can sua: ");
    scanf("%d", &id);
    getchar();
    for (int i = 0; i < studentCount; i++) {
        if (students[i].id == id) {
            printf("Nhap Ten moi: ");
            fgets(students[i].name, sizeof(students[i].name), stdin);
            students[i].name[strcspn(students[i].name, "\n")] = '\0';
            printf("Nhap Tuoi moi: ");
            scanf("%d", &students[i].age);
            ghiFile();
            return;
        }
    }
    printf("Khong tim thay sinh vien voi ID nay.\n");
}

void xoaSinhVien() {
    int id;
    printf("Nhap ID sinh vien can xoa: ");
    scanf("%d", &id);
    for (int i = 0; i < studentCount; i++) {
        if (students[i].id == id) {
            for (int j = i; j < studentCount - 1; j++) {
                students[j] = students[j + 1];
            }
            studentCount--;
            ghiFile();
            return;
        }
    }
    printf("Khong tim thay sinh vien voi ID nay.\n");
}

void timKiemSinhVien() {
    char name[100];
    printf("Nhap ten sinh vien can tim: ");
    getchar();
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = '\0';
    for (int i = 0; i < studentCount; i++) {
        if (strcmp(students[i].name, name) == 0) {
            printf("ID: %d, Ten: %s, Tuoi: %d\n", students[i].id, students[i].name, students[i].age);
            return;
        }
    }
    printf("Khong tim thay sinh vien voi ten nay.\n");
}

void sapXepSinhVien() {
    for (int i = 0; i < studentCount - 1; i++) {
        for (int j = i + 1; j < studentCount; j++) {
            if (students[i].id > students[j].id) {
                struct SinhVien temp = students[i];
                students[i] = students[j];
                students[j] = temp;
            }
        }
    }
    ghiFile();
    printf("Danh sach sinh vien da duoc sap xep.\n");
}

int main() {
    docFile();
    int choice;
    do {
        printf("\nMENU\n");
        printf("1. In danh sach sinh vien\n");
        printf("2. Them sinh vien\n");
        printf("3. Sua thong tin sinh vien\n");
        printf("4. Xoa sinh vien\n");
        printf("5. Tim kiem sinh vien\n");
        printf("6. Sap xep danh sach sinh vien\n");
        printf("7. Thoat\n");
        printf("Lua chon cua ban: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                inDanhSach();
                break;
            case 2:
                themSinhVien();
                break;
            case 3:
                suaSinhVien();
                break;
            case 4:
                xoaSinhVien();
                break;
            case 5:
                timKiemSinhVien();
                break;
            case 6:
                sapXepSinhVien();
                break;
            case 7:
                printf("Thoat chuong trinh.\n");
                break;
            default:
                printf("Lua chon khong hop le.\n");
        }
    } while (choice != 7);

    return 0;
}

