#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char ten[100];          
    int so_trang;           
    char loai[20];          
    struct Node *cha;       // node cha
    struct Node *con;       // node con
    struct Node *ke_tiep;   // lien ket
} Node;

// Tao node
Node* tao_node(const char *ten, int so_trang, const char *loai, Node *cha) {
    Node *node = (Node*)malloc(sizeof(Node));
    strcpy(node->ten, ten);
    node->so_trang = so_trang;
    strcpy(node->loai, loai);
    node->cha = cha;
    node->con = NULL;
    node->ke_tiep = NULL;
    return node;
}

// Dem cay
int dem_chuong(Node *root) {
    if (!root) return 0;
    int dem = 0;
    if (strcmp(root->loai, "chapter") == 0) {
        dem++;
    }
    Node *child = root->con;
    while (child) {
        dem += dem_chuong(child);
        child = child->ke_tiep;
    }
    return dem;
}

// tong so trang 
int tinh_tong_trang(Node *node) {
    if (!node) return 0;
    int tong = node->so_trang;
    Node *child = node->con;
    while (child) {
        tong += tinh_tong_trang(child);
        child = child->ke_tiep;
    }
    return tong;
}

// chuong max
void tim_chuong_dai_nhat(Node *root, Node **chuong_dai_nhat, int *max_trang) {
    if (!root) return;

    if (strcmp(root->loai, "chapter") == 0) {
        int tong_trang = tinh_tong_trang(root);
        if (tong_trang > *max_trang) {
            *max_trang = tong_trang;
            *chuong_dai_nhat = root;
        }
    }

    Node *child = root->con;
    while (child) {
        tim_chuong_dai_nhat(child, chuong_dai_nhat, max_trang);
        child = child->ke_tiep;
    }
}

// so trang node cha
void cap_nhat_trang(Node *node, int thay_doi) {
    while (node) {
        node->so_trang += thay_doi;
        node = node->cha;
    }
}

// Tim va xoa
int tim_va_xoa(Node *root, const char *ten_muc) {
    if (!root) return 0;

    Node *prev = NULL, *child = root->con;

    while (child) {
        if (strcmp(child->ten, ten_muc) == 0) {
            int tong_trang = tinh_tong_trang(child);
            if (prev) {
                prev->ke_tiep = child->ke_tiep;
            } else {
                root->con = child->ke_tiep;
            }
            cap_nhat_trang(root, -tong_trang);
            free(child);
            return 1;
        }
        prev = child;
        child = child->ke_tiep;
    }

    child = root->con;
    while (child) {
        if (tim_va_xoa(child, ten_muc)) {
            return 1;
        }
        child = child->ke_tiep;
    }
    return 0;
}

int main() {
    Node *root = tao_node("Sách học lập trình", 0, "book", NULL);
    Node *chuong1 = tao_node("Chương 1: Cơ bản", 20, "chapter", root);
    Node *chuong2 = tao_node("Chương 2: Nâng cao", 30, "chapter", root);
    root->con = chuong1;
    chuong1->ke_tiep = chuong2;

    Node *section1 = tao_node("Section 1.1", 10, "section", chuong1);
    chuong1->con = section1;
    Node *subsection1 = tao_node("Subsection 1.1.1", 5, "subsection", section1);
    section1->con = subsection1;

    // Nhap so chuong
    printf("Số chương: %d\n", dem_chuong(root));

    // Tim chuong dai nhat
    Node *chuong_dai_nhat = NULL;
    int max_trang = 0;
    tim_chuong_dai_nhat(root, &chuong_dai_nhat, &max_trang);
    if (chuong_dai_nhat) {
        printf("Chương dài nhất: %s với %d trang\n", chuong_dai_nhat->ten, max_trang);
    }

    // Xoa mot muc
    if (tim_va_xoa(root, "Section 1.1")) {
        printf("Đã xóa mục Section 1.1\n");
    } else {
        printf("Không tìm thấy mục cần xóa\n");
    }

    // Tong so trang sau khi xoa
    printf("Số trang sau khi xóa: %d\n", tinh_tong_trang(root));

    return 0;
}
