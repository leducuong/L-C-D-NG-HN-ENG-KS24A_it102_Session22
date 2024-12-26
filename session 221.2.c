#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Account {
    char username[50];
    char password[50];
};

#define MAX 100
struct Account accounts[MAX];
int accountCount = 0;

void docFile() {
    FILE *file = fopen("accounts.dat", "rb");
    if (file) {
        accountCount = fread(accounts, sizeof(struct Account), MAX, file);
        fclose(file);
    }
}

void ghiFile() {
    FILE *file = fopen("accounts.dat", "wb");
    if (file) {
        fwrite(accounts, sizeof(struct Account), accountCount, file);
        fclose(file);
    }
}

int dangNhap() {
    char username[50], password[50];
    printf("Nhap tai khoan: ");
    scanf("%s", username);
    printf("Nhap mat khau: ");
    scanf("%s", password);

    for (int i = 0; i < accountCount; i++) {
        if (strcmp(accounts[i].username, username) == 0 && strcmp(accounts[i].password, password) == 0) {
            printf("Dang nhap thanh cong!\n");
            return 1;
        }
    }
    printf("Dang nhap that bai. Tai khoan hoac mat khau sai.\n");
    return 0;
}

void dangKy() {
    if (accountCount >= MAX) {
        printf("Danh sach tai khoan da day.\n");
        return;
    }
    struct Account newAccount;
    printf("Nhap tai khoan moi: ");
    scanf("%s", newAccount.username);
    printf("Nhap mat khau moi: ");
    scanf("%s", newAccount.password);

    for (int i = 0; i < accountCount; i++) {
        if (strcmp(accounts[i].username, newAccount.username) == 0) {
            printf("Tai khoan da ton tai.\n");
            return;
        }
    }

    accounts[accountCount++] = newAccount;
    ghiFile();
    printf("Dang ky tai khoan thanh cong.\n");
}

int main() {
    docFile();
    int choice;
    do {
        printf("\nMENU\n");
        printf("1. Dang nhap\n");
        printf("2. Dang ky\n");
        printf("3. Thoat\n");
        printf("Lua chon cua ban: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                dangNhap();
                break;
            case 2:
                dangKy();
                break;
            case 3:
                printf("Thoat chuong trinh.\n");
                break;
            default:
                printf("Lua chon khong hop le.\n");
        }
    } while (choice != 3);

    return 0;
}

