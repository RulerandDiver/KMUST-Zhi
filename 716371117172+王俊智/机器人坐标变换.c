#include <stdio.h>
#include <math.h>
#include<stdlib.h>
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
int i;
int op;

// ����һ�������������飬����4��Ԫ��
typedef float HomogeneousCoordinate[4];

// ����һ��ƽ���������飬����3��Ԫ��
typedef float TranslationVector[3];

// ����һ����ת�������飬����16��Ԫ��
typedef float RotationMatrix[16];

// �����
void zeroMatrix(RotationMatrix matrix) {
    //�������ÿһ��ֵ���и�ֵΪ0
    for (i = 0; i < 16; i++) {
        matrix[i] = 0.0;
    }
}

// ��λ����
void identityMatrix(RotationMatrix matrix) {
    zeroMatrix(matrix);
    matrix[0] = matrix[5] = matrix[10] = matrix[15] = 1.0;//��������Ӧλ�õ�ֵ��ֵΪ1����λ�����X,Y,ZΪ1�������������任������ĵ���������Ϊ1��
}

// �� X ����ת
void rotateX(RotationMatrix matrix, float angle) {

    float sinus, cosinus;

    identityMatrix(matrix);//������ľ����ʼ��Ϊ��λ����

    sinus = sinf(angle);
    cosinus = cosf(angle);
    //����λ����Ķ�Ӧλ�ø�ֵΪ���Ǻ����Թ�����ת����
    matrix[5] = cosinus;
    matrix[6] = -sinus;
    matrix[9] = sinus;
    matrix[10] = cosinus;
}

// �� Y ����ת
void rotateY(RotationMatrix matrix, float angle) {
    float sinus = sinf(angle), cosinus = cosf(angle);
    identityMatrix(matrix);//������ľ����ʼ��Ϊ��λ����

    //����λ����Ķ�Ӧλ�ø�ֵΪ���Ǻ����Թ�����ת����
    matrix[0] = cosinus;
    matrix[2] = sinus;
    matrix[8] = -sinus;
    matrix[10] = cosinus;
}

// �� Z ����ת
void rotateZ(RotationMatrix matrix, float angle) {
    float sinus = sinf(angle), cosinus = cosf(angle);
    identityMatrix(matrix);//������ľ����ʼ��Ϊ��λ����
     //����λ����Ķ�Ӧλ�ø�ֵΪ���Ǻ����Թ�����ת����
    matrix[0] = cosinus;
    matrix[1] = -sinus;
    matrix[4] = sinus;
    matrix[5] = cosinus;

}

// �������ƽ�Ʊ任
void translate(HomogeneousCoordinate point, TranslationVector transVec)
{
    int k, j;
    //����ʱ��ע��ʹ�ÿո����س��������зָֵͬ������
    printf("��������Ҫƽ�Ƶ����꣺");
    for (k = 0;k < 4;k++)
    {
        scanf_s("%f", &point[k]);
    }
    printf("��������Ҫƽ�Ƶ�ƽ������");
    for (j = 0;j < 3;j++)
    {
        scanf_s("%f", &transVec[j]);
    }
    for (i = 0; i < 3; i++)
    {
        point[i] += transVec[i] * point[3];
    }
}

// ���������ת�任
void transform(HomogeneousCoordinate point, RotationMatrix matrix)
{
  
    HomogeneousCoordinate temp;
    int po;
    int k, i, j;
    float theta = 3.0;
    float angle;
    
    
    printf("������Ҫ������ת������: ");
    for (k = 0;k < 4;k++)
    {
        scanf_s("%f", &point[k]);
    }
    printf("����ת����һ���������ת��<X>--1\t<Y>--2\t<Z>--3\n");

    do
    {
        po = menu_select2();
        switch (po)
        {
        case 1:
            // ��X����ת
            printf("������Ҫ��ת�ĽǶȣ�");
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
            printf("��ת������꣺(%.1f, %.1f, %.1f, %.1f)\n",
                point[0], point[1], point[2], point[3]);
            system("pause");
            break;
        case 2:
            // ��Y����ת
            printf("������Ҫ��ת�ĽǶȣ�");
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
            printf("��ת������꣺(%.1f, %.1f, %.1f , %.1f)\n",
                point[0], point[1], point[2], point[3]);
            system("pause");
            break;
        case 3:
            // ��Z����ת
            printf("������Ҫ��ת�ĽǶȣ�");
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
            printf("��ת������꣺(%.1f, %.1f, %.1f, %.1f)\n",
                point[0], point[1], point[2], point[3]);
            system("pause");
            break;
        case 4:
            // �˳�����
            printf("�˳�����...\n");
            break;
        default:
            printf("��Ч�Ĳ�����\n");
            break;
        }
    } while (po != 4);
}






int menu_select()
{
    char c;
    int n;
    printf("\n****************************����������************************\n");
    printf("\t1. ƽ�Ʊ任\n");
    printf("\t2. ��ת�任\n");
    printf("\t3. �˳�������\n");
    printf("****************************************************************\n");
    printf("\n\t\t\t ����������1-3: ");
    c = getchar();
    if (c == '\n')
    {
        c = getchar();
    }
    n = c - 48;
    while ((n < 1) || (n > 3))
    {
        printf("\n\t\t\tδ����1-3֮�����Ч����,����������:");
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
    printf("\n****************************ѡ����ת�����************************\n");
    printf("\t1. X\n");
    printf("\t2. Y\n");
    printf("\t3. Z\n");
    printf("\t4. �˳�������\n");
    printf("****************************************************************\n");
    printf("\n\t\t\t ����������1-4: ");
    c = getchar();
    if (c == '\n')
    {
        c = getchar();
    }
    n = c - 48;
    while ((n < 1) || (n > 4))
    {
        printf("\n\t\t\tδ����1-4֮�����Ч����,����������:");
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

    // ��ʼ��һ������������x, y, z, w��
    HomogeneousCoordinate point = {0};
    // ��ʼ��һ��ƽ������
    TranslationVector transVec = {0};
    // ��ʼ��һ����ת����
    RotationMatrix matrix = { 0 };




    // �����û�����

    do {
        op = menu_select();
        switch (op) {
        case 1:
            // ���ƽ�Ʊ任
            translate(point, transVec);
            printf("ƽ�ƺ�����꣺(%.1f, %.1f, %.1f, %.1f)\n",
                point[0], point[1], point[2], point[3]);
            system("pause");
            break;
        case 2:
            // �����ת�任
            transform(point, rotationMatrix);
            printf("��ת������꣺(%.1f, %.1f, %.1f , %.1f)\n",
                point[0], point[1], point[2], point[3]);
            system("pause");
            break;
        case 3:
            // �˳�����
            printf("�˳�����...\n");
            system("pause");
            break;
        default:
            printf("��Ч�Ĳ�����\n");
            break;
        }
    } while (op != 3);
    return 0;
}