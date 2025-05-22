#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
// Dinh nghia cau truc sinh vien dung DSLK don
// Ap dung: Cau truc, DSLK don, Con tro
typedef struct sinhvien{
	long long MSSV;
	char HoTen[50];
	float DiemTK;
	char Lop[50];
	struct sinhvien *next;
} SV;

// Ham themSinhVien: Them sinh vien moi vao dau danh sach
// Ap dung: Cau truc, Con tro, DSLK don, Ham
void themSinhVien(SV** head) {
    SV *sv = (SV*)malloc(sizeof(SV));
    if (sv == NULL) {
        printf("Khong du bo nho de them sinh vien.\n");
        return;
    }
    printf("Nhap MSSV: ");
    scanf("%lld", &sv->MSSV); getchar();
    printf("Nhap ho ten: ");
    fgets(sv->HoTen, sizeof(sv->HoTen), stdin);
    printf("Nhap diem tong ket: ");
    scanf("%f", &sv->DiemTK); getchar();
    printf("Nhap lop: ");
    fgets(sv->Lop, sizeof(sv->Lop), stdin);
    sv->next = *head;
    *head = sv;
}

// Ham xuatDSSV: Xuat thong tin sinh vien ra man hinh va file (neu co ten file)
// Ap dung: Ham, Ghi file, Con tro
void xuatDSSV(SV* head, const char* tenFile) {
    FILE *f = NULL;
    if (tenFile != NULL) f = fopen(tenFile, "w");
    int stt = 1;
    printf("\n%-5s\t%-15s\t%-30s\t%-10s\t%-10s\n", "STT", "MSSV", "Ho ten", "Diem", "Lop");
    if (f) fprintf(f, "%-5s\t%-15s\t%-30s\t%-10s\t%-10s\n", "STT", "MSSV", "Ho ten", "Diem", "Lop");
    while (head) {
        printf("%-5d\t%-15lld\t%-30s\t%-10.2f\t%-10s\n", stt, head->MSSV, head->HoTen, head->DiemTK, head->Lop);
        if (f) fprintf(f, "%-5d\t%-15lld\t%-30s\t%-10.2f\t%-10s\n", stt, head->MSSV, head->HoTen, head->DiemTK, head->Lop);
        head = head->next;
        stt++;
    }
    if (f) fclose(f);
    if (tenFile != NULL) printf("Danh sach da duoc ghi vao file %s\n", tenFile);
}

// Ham sxDSSVTheoDiem: Sap xep giam dan theo diem TK bang cach doi du lieu
// Ap dung: Sap xep, DSLK don, Con tro
void sxDSSVTheoDiem(SV** head) {
    for (SV* i = *head; i != NULL; i = i->next) {
        for (SV* j = i->next; j != NULL; j = j->next) {
            if (i->DiemTK < j->DiemTK) {
                long long tempMSSV = i->MSSV;
                i->MSSV = j->MSSV;
                j->MSSV = tempMSSV;
                float tempDiem = i->DiemTK;
                i->DiemTK = j->DiemTK;
                j->DiemTK = tempDiem;
                char tempHoTen[50], tempLop[50];
                strcpy(tempHoTen, i->HoTen);
                strcpy(i->HoTen, j->HoTen);
                strcpy(j->HoTen, tempHoTen);
                strcpy(tempLop, i->Lop);
                strcpy(i->Lop, j->Lop);
                strcpy(j->Lop, tempLop);
            }
        }
    }
}

// Ham sxDSSVTheoMSSV: Sap xep tang dan theo MSSV bang cach doi du lieu
// Ap dung: Sap xep, DSLK don, Con tro
void sxDSSVTheoMSSV(SV** head) {
    for (SV* i = *head; i != NULL; i = i->next) {
        for (SV* j = i->next; j != NULL; j = j->next) {
            if (i->MSSV > j->MSSV) {
                long long tempMSSV = i->MSSV;
                i->MSSV = j->MSSV;
                j->MSSV = tempMSSV;
                float tempDiem = i->DiemTK;
                i->DiemTK = j->DiemTK;
                j->DiemTK = tempDiem;
                char tempHoTen[50], tempLop[50];
                strcpy(tempHoTen, i->HoTen);
                strcpy(i->HoTen, j->HoTen);
                strcpy(j->HoTen, tempHoTen);
                strcpy(tempLop, i->Lop);
                strcpy(i->Lop, j->Lop);
                strcpy(j->Lop, tempLop);
            }
        }
    }
}

// Ham daXuatLop: Kiem tra 1 lop da duoc xuat chua
// Ap dung: Mang, Ham
int daXuatLop(char daXuat[][50], int dem, char* lop) {
    for (int i = 0; i < dem; i++) {
        if (strcmp(daXuat[i], lop) == 0) return 1;
    }
    return 0;
}

// Ham xuatTheoLop: Xuat danh sach theo tung lop, tranh trung lap lop
// Ap dung: Ham, Mang, Ghi file, Con tro
void xuatTheoLop(SV *head, const char *tenFile) {
    char daXuat[100][50];
    int dem = 0;
    FILE *f = NULL;
    if (tenFile != NULL) f = fopen(tenFile, "w");
    for (SV *i = head; i != NULL; i = i->next) {
        if (!daXuatLop(daXuat, dem, i->Lop)) {
            printf("\nDanh sach sinh vien lop %s: \n", i->Lop);
            printf("%-5s %-15s %-30s %-10s %-10s\n", "STT", "MSSV", "Ho ten", "Diem", "Lop");
            if (f) fprintf(f, "\n===== Lop %s =====\n", i->Lop);
            if (f) fprintf(f, "%-5s %-15s %-30s %-10s %-10s\n", "STT", "MSSV", "Ho ten", "Diem", "Lop");
            int stt = 1;
            for (SV *j = head; j != NULL; j = j->next) {
                if (strcmp(i->Lop, j->Lop) == 0) {
                    printf("%-5d %-15lld %-30s %-10.2f %-10s\n", stt, j->MSSV, j->HoTen, j->DiemTK, j->Lop);
                    if (f) fprintf(f, "%-5d %-15lld %-30s %-10.2f %-10s\n", stt, j->MSSV, j->HoTen, j->DiemTK, j->Lop);
                    stt++;
                }
            }
            strcpy(daXuat[dem++], i->Lop);
        }
    }
    if (f) {
        fclose(f);
        printf("Danh sach theo lop da duoc ghi vao file %s\n", tenFile);
    }
}

// Ham File_Dau: Ghi danh sach SV dat (DiemTK >= 5) vao file
// Ap dung: Ghi file, Ham
void File_Dau(SV* head, const char *filename) {
    sxDSSVTheoDiem(&head);
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Khong the mo tep %s\n", filename);
        return;
    }
    int count = 0, stt = 1;
    while (head) {
        if (head->DiemTK >= 5.0) {
            printf("%-5d %-15lld %-30s %-10.2f\n", stt, head->MSSV, head->HoTen, head->DiemTK);
            fprintf(file, "%-5d %-15lld %-30s %-10.2f\n", stt, head->MSSV, head->HoTen, head->DiemTK);
            count++; stt++;
        }
        head = head->next;
    }
    if (count == 0) {
        fprintf(file, "Khong co sinh vien nao dau.\n");
    }
    fclose(file);
    printf("Co %d sinh vien dau. Da in danh sach vao tep %s\n", count, filename);
}

// Ham File_HocLai: Ghi danh sach SV rot (DiemTK < 5) vao file
// Ap dung: Ghi file, Ham
void File_HocLai(SV* head, const char *filename) {
    sxDSSVTheoDiem(&head);
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Khong the mo tep %s\n", filename);
        return;
    }
    int count = 0, stt = 1;
    while (head) {
        if (head->DiemTK < 5.0) {
            printf("%-5d %-15lld %-30s %-10.2f\n", stt, head->MSSV, head->HoTen, head->DiemTK);
            fprintf(file, "%-5d %-15lld %-30s %-10.2f\n", stt, head->MSSV, head->HoTen, head->DiemTK);
            count++; stt++;
        }
        head = head->next;
    }
    if (count == 0) {
        fprintf(file, "Khong co sinh vien nao hoc lai.\n");
    }
    fclose(file);
    printf("Co %d sinh vien hoc lai. Da in danh sach vao tep %s\n", count, filename);
}

// Ham timSV: Tim sinh vien theo MSSV
// Ap dung: Ham, DSLK don
void timSV(SV*head){
	long long n;
	printf("Vui long nhap vao ma so sinh vien ban can tim : ");
	scanf("%lld",&n);
	while(head){
		if(head->MSSV==n){
			printf("Sinh vien ban can tim la :\n");
			printf("MSSV : %lld\ nHo ten : %s\n Diem TK : %.2f\n Lop : %s\n",head->MSSV,head->HoTen,head->DiemTK,head->Lop);
			return;
		}
		head=head->next;
	}
	printf("Khong tim thay\n");
}

// Ham xoaSinhVien: Xoa sinh vien theo MSSV
// Ap dung: 4. Ham, 3. DSLK don
void xoaSinhVien(SV** head) {
    long long MSSV;
    printf("Nhap MSSV sinh vien can xoa: ");
    scanf("%lld", &MSSV);
    SV *temp = *head, *prev = NULL;
    if (temp != NULL && temp->MSSV == MSSV) {
        *head = temp->next;
        free(temp);
        printf("Sinh vien da duoc xoa.\n");
        return;
    }
    while (temp != NULL && temp->MSSV != MSSV) {
        prev = temp;
        temp = temp->next;
    }
    if (temp == NULL) {
        printf("Khong tim thay sinh vien\n");
        return;
    }
    prev->next = temp->next;
    free(temp);
    printf("Sinh vien da duoc xoa\n");
}

// Ham giaiPhongBoNho: Giai phong toan bo danh sach lien ket
// Ap dung: Ham, DSLK don
void giaiPhongBoNho(SV *head){
	while(head){
		SV* the = head;
		head = head->next;
		free(the);
	}
}

// Ham xuatDanhSach: xuat danh sach sinh vien ra man hinh 
void xuatDanhSach(SV *head) {
    if (head == NULL) {
        printf("Danh sach rong\n");
        return;
    }
    printf("\n%-5s%-15s%-30s%-10s%-10s\n", "STT", "MSSV", "Ho ten", "Diem", "Lop");
    int stt = 1;
    while (head) {
        printf("%-5d%-15lld%-30s%-10.2f%-10s\n", stt, head->MSSV, head->HoTen, head->DiemTK, head->Lop);
        head = head->next;
        stt++;
    }
}

// Ly thuyet duoc ap dung trong ham main: bien, con tro, ham, dieu kien, vong lap, cau truc, xau ky tu, toan tu, tap tin
int main() {
    bool t = true;
    int x;
    SV *head = NULL;
    printf("Nhap so luong sinh vien: ");
    scanf("%d", &x);
    getchar();
    while (x > 100 || x <= 0) {
        printf("So luong khong hop le. Moi nhap lai: ");
        scanf("%d", &x);
    }
    if(x==1) {
		printf("Nhap thong tin cua sinh vien: \n");
		themSinhVien(&head);
	} else {
		for(int i=0; i<x; i++) {
			printf("Nhap thong tin cua sinh vien thu %d: \n",i+1);
			themSinhVien(&head);
		}
	}
    xuatDanhSach(head);
    int luaChon;
    luaChon = 9;
    char tenFile[100];
    while (t) {
        if (luaChon == 9) {
            printf("\n1. Xuat theo MSSV tang dan\n");
            printf("2. Xuat theo diem TK giam dan\n");
            printf("3. Xuat theo lop\n");
            printf("4. Tim sinh vien theo MSSV\n");
            printf("5. Xuat danh sach sinh vien dat va hoc lai\n");
            printf("6. Them sinh vien\n");
            printf("7. Xoa sinh vien\n");
            printf("8. Hien lai danh sach sinh vien\n");
            printf("9. Hien lai bang chuc nang\n");
            printf("10. Thoat\n");
        }
        printf("Chon: ");
        scanf("%d", &luaChon); getchar();
        switch (luaChon) {
            case 1:
                sxDSSVTheoMSSV(&head);
                xuatDSSV(head, "DSSV_MSSV.txt");
                break;
            case 2:
                sxDSSVTheoDiem(&head);
                xuatDSSV(head, "DSSV_Diem.txt");
                break;
            case 3:
                sxDSSVTheoMSSV(&head);
                xuatTheoLop(head, "DSSV_Lop.txt");
                break;
            case 4:
                timSV(head);
                break;
            case 5:
                File_Dau(head, "Dat.txt");
                File_HocLai(head, "Khongdat.txt");
                break;
            case 6:
                themSinhVien(&head);
                break;
            case 7:
                xoaSinhVien(&head);
                break;
            case 8:
            	xuatDanhSach(head);
            case 9:
                break;
            case 10:
                t = false;
                break;
            default:
                printf("Lua chon khong hop le.\n");
        }
    }
    giaiPhongBoNho(head);
    return 0;
}
