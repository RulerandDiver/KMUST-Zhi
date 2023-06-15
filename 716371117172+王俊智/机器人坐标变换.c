#include <stdio.h>
#include <math.h>
#include<stdlib.h>
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
int i;
int op;

// 定义一个坐标向量数组，包含4个元素
typedef float HomogeneousCoordinate[4];

// 定义一个平移向量数组，包含3个元素
typedef float TranslationVector[3];

// 定义一个旋转矩阵数组，包含16个元素
typedef float RotationMatrix[16];

// 零矩阵
void zeroMatrix(RotationMatrix matrix) {
    //将数组的每一个值进行赋值为0
    for (i = 0; i < 16; i++) {
        matrix[i] = 0.0;
    }
}

// 单位矩阵
void identityMatrix(RotationMatrix matrix) {
    zeroMatrix(matrix);
    matrix[0] = matrix[5] = matrix[10] = matrix[15] = 1.0;//将数组相应位置的值赋值为1（单位矩阵的X,Y,Z为1，并且齐次坐标变换中引入的第四列数组为1）
}

// 绕 X 轴旋转
void rotateX(RotationMatrix matrix, float angle) {

    float sinus, cosinus;

    identityMatrix(matrix);//将输入的矩阵初始化为单位矩阵

    sinus = sinf(angle);
    cosinus = cosf(angle);
    //将单位矩阵的对应位置赋值为三角函数以构成旋转数组
    matrix[5] = cosinus;
    matrix[6] = -sinus;
    matrix[9] = sinus;
    matrix[10] = cosinus;
}

// 绕 Y 轴旋转
void rotateY(RotationMatrix matrix, float angle) {
    float sinus = sinf(angle), cosinus = cosf(angle);
    identityMatrix(matrix);//将输入的矩阵初始化为单位矩阵

    //将单位矩阵的对应位置赋值为三角函数以构成旋转矩阵
    matrix[0] = cosinus;
    matrix[2] = sinus;
    matrix[8] = -sinus;
    matrix[10] = cosinus;
}

// 绕 Z 轴旋转
void rotateZ(RotationMatrix matrix, float angle) {
    float sinus = sinf(angle), cosinus = cosf(angle);
    identityMatrix(matrix);//将输入的矩阵初始化为单位矩阵
     //将单位矩阵的对应位置赋值为三角函数以构成旋转数组
    matrix[0] = cosinus;
    matrix[1] = -sinus;
    matrix[4] = sinus;
    matrix[5] = cosinus;

}

// 齐次坐标平移变换
void translate(HomogeneousCoordinate point, TranslationVector transVec)
{
    int k, j;
    //输入时需注意使用空格键或回车键来进行分割不同值的输入
    printf("请输入想要平移的坐标：");
    for (k = 0;k < 4;k++)
    {
        scanf_s("%f", &point[k]);
    }
    printf("请输入想要平移的平移量：");
    for (j = 0;j < 3;j++)
    {
        scanf_s("%f", &transVec[j]);
    }
    for (i = 0; i < 3; i++)
    {
        point[i] += transVec[i] * point[3];
    }
}

// 齐次坐标旋转变换
void transform(HomogeneousCoordinate point, RotationMatrix matrix)
{
  
    HomogeneousCoordinate temp;
    int po;
    int k, i, j;
    float theta = 3.0;
    float angle;
    
    
    printf("请输入要进行旋转的坐标: ");
    for (k = 0;k < 4;k++)
    {
        scanf_s("%f", &point[k]);
    }
    printf("请旋转绕哪一个轴进行旋转：<X>--1\t<Y>--2\t<Z>--3\n");

    do
    {
        po = menu_select2();
        switch (po)
        {
        case 1:
            // 绕X轴旋转
            printf("请输入要旋转的角度：");
            scanf_s("%f", &theta);
            angle = theta * (M_PI / 180.0f);
            rotateX(matrix, angle);
            for (i = 0; i < 4; i++) {
                temp[i] = point[0] * matrix[i]
                    + point[1] * matrix[i + 4]
                    + point[2] * matrix[i + 8]
                    + point[3] * matrix[i + 12];
            }
            for (i = 0; i < 4; i++)
            {
                point[i] = temp[i];
            }
            printf("旋转后的坐标：(%.1f, %.1f, %.1f, %.1f)\n",
                point[0], point[1], point[2], point[3]);
            system("pause");
            break;
        case 2:
            // 绕Y轴旋转
            printf("请输入要旋转的角度：");
            scanf_s("%f", &theta);
            angle = theta * (M_PI / 180.0f);
            rotateY(matrix, angle);
            for (i = 0; i < 4; i++) {
                temp[i] = 0.0f;
                for (j = 0; j < 4; j++) {
                    temp[i] += point[j] * matrix[4 * i + j];
                }
            }
            for (i = 0; i < 4; i++)
            {
                point[i] = temp[i];
            }
            printf("旋转后的坐标：(%.1f, %.1f, %.1f , %.1f)\n",
                point[0], point[1], point[2], point[3]);
            system("pause");
            break;
        case 3:
            // 绕Z轴旋转
            printf("请输入要旋转的角度：");
            scanf_s("%f", &theta);
            angle = theta * (M_PI / 180.0f);
            rotateZ(matrix, angle);
            for (i = 0; i < 4; i++) {
                temp[i] = point[0] * matrix[i]
                    + point[1] * matrix[i + 4]
                    + point[2] * matrix[i + 8]
                    + point[3] * matrix[i + 12];
            }
            for (i = 0; i < 4; i++)
            {
                point[i] = temp[i];
            }
            printf("旋转后的坐标：(%.1f, %.1f, %.1f, %.1f)\n",
                point[0], point[1], point[2], point[3]);
            system("pause");
            break;
        case 4:
            // 退出程序
            printf("退出程序...\n");
            break;
        default:
            printf("无效的操作！\n");
            break;
        }
    } while (po != 4);
}






int menu_select()
{
    char c;
    int n;
    printf("\n****************************程序主界面************************\n");
    printf("\t1. 平移变换\n");
    printf("\t2. 旋转变换\n");
    printf("\t3. 退出本程序\n");
    printf("****************************************************************\n");
    printf("\n\t\t\t 请输入数字1-3: ");
    c = getchar();
    if (c == '\n')
    {
        c = getchar();
    }
    n = c - 48;
    while ((n < 1) || (n > 3))
    {
        printf("\n\t\t\t未输入1-3之间的有效数字,请重新输入:");
        c = getchar();
        if (c == '\n')
        {
            c = getchar();
        }
        n = c - 48;
    }
    return(n);
}



int menu_select2()
{
    char c;
    int n;
    printf("\n****************************选择旋转轴界面************************\n");
    printf("\t1. X\n");
    printf("\t2. Y\n");
    printf("\t3. Z\n");
    printf("\t4. 退出本程序\n");
    printf("****************************************************************\n");
    printf("\n\t\t\t 请输入数字1-4: ");
    c = getchar();
    if (c == '\n')
    {
        c = getchar();
    }
    n = c - 48;
    while ((n < 1) || (n > 4))
    {
        printf("\n\t\t\t未输入1-4之间的有效数字,请重新输入:");
        c = getchar();
        if (c == '\n')
        {
            c = getchar();
        }
        n = c - 48;
    }
    return(n);
}






int main() {
    RotationMatrix rotationMatrix;
    int op;

    // 初始化一个坐标向量（x, y, z, w）
    HomogeneousCoordinate point = {0};
    // 初始化一个平移向量
    TranslationVector transVec = {0};
    // 初始化一个旋转矩阵
    RotationMatrix matrix = { 0 };




    // 定义用户输入

    do {
        op = menu_select();
        switch (op) {
        case 1:
            // 齐次平移变换
            translate(point, transVec);
            printf("平移后的坐标：(%.1f, %.1f, %.1f, %.1f)\n",
                point[0], point[1], point[2], point[3]);
            system("pause");
            break;
        case 2:
            // 齐次旋转变换
            transform(point, rotationMatrix);
            printf("旋转后的坐标：(%.1f, %.1f, %.1f , %.1f)\n",
                point[0], point[1], point[2], point[3]);
            system("pause");
            break;
        case 3:
            // 退出程序
            printf("退出程序...\n");
            system("pause");
            break;
        default:
            printf("无效的操作！\n");
            break;
        }
    } while (op != 3);
    return 0;
}