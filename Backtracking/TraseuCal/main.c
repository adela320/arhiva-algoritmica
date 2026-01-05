#include <stdio.h>


const int dx[] = {-2,-2,-1,-1,1, 1,2, 2};
const int dy[] = {1, -1, 2,-2,2,-2,1,-1};
int b[10][10];
int cnt = 0;
void Bk(int a[10][10], int n, int m, int i, int j, int pas) {
    if (i < 0 || j < 0 || i >= n || j >= m || a[i][j] != 0 || b[i][j] != 0) {
        return;
    }
    if (i == n-1 && j == m-1) {
        cnt++;
    }
    else {
        b[i][j] = pas;
        //printf("%d\n", pas);
        for (int k = 0; k < 8; k++) {
            Bk(a, n, m, i+dx[k], j+dy[k], pas+1);
        }
        b[i][j] = 0;
    }
}

int main(void) {
    int a[10][10];
    int n = 4;
    int m = 5;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j ++) {
            scanf("%d", &a[i][j]);
        }
    }
    Bk(a, n, m, 0,0,0);
    printf("%d\n", cnt);
    return 0;
}