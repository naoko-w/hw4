#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void matrix_initialize(int x[][50]){
    int i, j;
    for(i = 0; i < 50; i++){
        for(j = 0; j < 50; j++){
            x[i][j] = 100;
        }
    }
}

void list_initialize(int x[]){
    int i;
    for(i = 0; i < 50; i++){
        x[i] = 0;
    }
}

void display(FILE *myFile){
    char string[10];
    int n;
    while(fscanf(myFile, "%d %s", &n, string) != EOF){
        printf("%s  ",string);
    }
    printf("\n\n");
}

int enqueue(int i, int matrix[][50], int matrix_copy[][50], int queue[], int flag[], int l){
    int j;
    for(j = 0; matrix[i][j] != 100; j++){
        if(flag[matrix[i][j]] == 0){
            queue[l] = matrix[i][j];
            matrix_copy[i][j] = -1;
            flag[matrix[i][j]] = flag[i] + 1;
            l++;
        }
    }
    queue[l] = -1;
    return l - 1;
}

int getfirst(int queue[]){
    if(queue[1] != -1){
        return queue[1];
    }
    else{
        printf("NotFound\n");
        return -1;
    }
}

int judge(int x, int y){
    int z;
    if(x == y) z = 1;
    return z;
}

void dequeue(int queue[], int j){
    int i;
    for(i = 2; i <= j; i++){
        queue[i - 1] = queue[i];
    }
    queue[i] = -1;
}

void root(int matrix[][50], int matrix_copy[][50], int flag[], int id){
    int i, j;
    if(flag[id] == 0) return;
    for(i = 0; i < 50; i++){
        for(j = 0; j < 50; j++){
            if(matrix[i][j] == id && matrix_copy[i][j] == -1 && flag[id] == flag[i] + 1){
                printf("%d <- %d, ",id, i);
                return root(matrix, matrix_copy, flag, i);
            }
        }
    }
}


int main(){
    char fileName_link[] = "links.txt", fileName_name[] = "nicknames.txt", yourNickname[10], target[10], IDname[10];
    int matrix[50][50], matrix_copy[50][50], flag[50], queue[50], a, b, IDnum, yourIDnum, targetIDnum, i, j, temp = 0, length = 1, head, start, goal = 0;
    
    
    matrix_initialize(matrix); //matrixを初期化
    list_initialize(flag); //flagを初期化
    

    FILE *myFile;
    myFile = fopen (fileName_link, "r");
    i = 0;
    while(fscanf(myFile, "%d %d", &a, &b) != EOF){
        if(temp != a) i = 0;
        matrix[a][i] = b; //隣接リストを作成
        matrix_copy[a][i] = b;
        temp = a;
        i++;
    }

    myFile = fopen (fileName_name, "r");
    display(myFile); //ニックネームを一覧表示
    
    printf("Your nickname is ??? : ");
    scanf("%s", yourNickname);
    printf("Target is ???        : ");
    scanf("%s",target);

    myFile = fopen (fileName_name, "r");
    while(fscanf(myFile, "%d %s", &IDnum, IDname) != EOF){
        if(strcmp(IDname, yourNickname) == 0) yourIDnum = IDnum; //ニックネーム(from)をIDナンバーに変換
        else if(strcmp(IDname, target) == 0) targetIDnum = IDnum; //ニックネーム(to)をIDナンバーに変換
        else continue;
    }
    fclose(myFile);

    start = yourIDnum;
    
    while(1){
        length = enqueue(start, matrix, matrix_copy, queue, flag, length); //キューに子ノードを追加
        head = getfirst(queue); //キューの先頭を取り出す
        goal = judge(head, targetIDnum); //取り出したものが探索対象かどうか

        if(goal == 1){
            printf("\nFrom '%s' to '%s' : %d\n", yourNickname, target, flag[targetIDnum]);
            printf("PATH : ");
            flag[yourIDnum] = 0;
            root(matrix, matrix_copy, flag, targetIDnum);
            break;
        }
        else{
            dequeue(queue, length);
            start = head;
            continue;
        }
    }
    printf("\n");
    return 0;
} 