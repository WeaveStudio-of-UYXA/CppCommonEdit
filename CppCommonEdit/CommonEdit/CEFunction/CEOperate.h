/*This file is the CEOperate Library in CommonEdit. 
Most of the functions in this document come from the LazyManV3 written by Ayano Aishi.
The random number function in this document is completed through QT.*/
#pragma once
#include "../CECore/CECore.h"
#ifdef CE_QT_5
#include <QTime>
#else
#include <ctime>
#endif


namespace CE {
    class CEOperate {
    public:
        //��������ָ��ָ��ĵ�ַ
        template <typename T> static void swap(T* p_1, T* p_2)
        {
            T s;
            s = *p_1;
            *p_1 = *p_2;
            *p_2 = s;
        }
        //����ʮ����������λ��
        static unsigned short length(long long n)
        {
            long long d = n;
            unsigned short i = 0;
            if (d == 0) { return 1; }
            while (d != 0)
            {
                d = d / 10;
                i++;
            }
            return i;
        }
        //����ʮ��������d�ĵ�iλ�����޷���0
        static unsigned short digit(long long d, unsigned short i)
        {
            if (i == 1) { return d % 10; }
            int j;
            for (j = 1; j <= i - 1; j++)
            {
                d = d / 10;
            }
            return d % 10;
        }
        //�ж�һ�������Ƿ�����
        static bool isPrime(long long d)
        {
            if (d <= 1) { return false; }
            long long i;
            if (d == 2) { return true; }
            for (i = 2; i * i <= d; i++)
            {
                if (d % i == 0) { return false; }
            }
            return true;
        }
        //���n�����Ӹ���
        static unsigned short getFactorCount(long long n)
        {
            int i, s = 0;
            if (n == 1) { return 1; }
            for (i = 1; i <= n / 2; i++)
            {
                if (n % i == 0)
                    s++;
            }
            return s + 1;
        }
        //�ж�������
        static bool isPerfectNumber(long long n)
        {
            if (n == 1) { return false; }
            long long i, sum = 0;
            for (i = 1; i <= n / 2; i++)
            {
                if (n % i == 0) { sum = sum + i; }
            }
            if (sum == n) { return true; }
            else { return false; }
        }
        //���ӣ�쳲�����������
        static unsigned long long rabbit(unsigned short n) {
            unsigned long long num1 = 1;
            unsigned long long num2 = 1;
            for (int i = 0; i < (n - 1) / 2; i++) {
                num1 += num2;
                num2 += num1;
            }
            if ((n - 2) % 2) { return num1; }
            else { return num2; }
        }
        //ʱ�����ӳ�ʼ������
        static void initSeed() {
#ifndef CE_QT_5
            srand((unsigned)time(NULL));
#else
            qsrand((unsigned)time(NULL));
#endif
        }
        static int randInt(int min, int max)
        {
#ifndef CE_QT_5
            return rand() % (max - min + 1) + min;
#else
            return qrand() % (max - min + 1) + min;
#endif
        }
        //��ʼ�����飨�������飩
        template <typename T>static void initArray(T* Array, int Length, T Min, T Max, bool Unique = false) {
            T Cache[Length];
            bool Repeat = false;
            for (int i = 0; i < Length;) {
#ifndef CE_QT_5
                Cache[i] = rand() % (Max - Min + 1) + Min;
#else
                Cache[i] = qrand() % (Max - Min + 1) + Min;
#endif
                if (Unique) {
                    for (int j = 0; j < i; j++) {
                        if (Cache[i] == Cache[j]) {
                            Repeat = true;
                        }
                    }
                }
                if (!Repeat) {
                    Array* = Cache[i];
                    Array++;
                    i++;
                }
            }
        }
        //����һ��ֵ�������е�����
        //rank(ֵ,��Ԫ�ص�ַ,���鳤��)
        template <typename T>static unsigned int rank(T Num, T* First, int Length) {
            int Rank = 1;
            T* Each = First;
            for (int i = 0; i < Length; i++) {
                if (*Each > Num) { Rank++; }
                Each++;
            }
            return Rank;
        }
        //���ֵ��Сֵ����
        //max/min(��Ԫ�ص�ַ,���鳤��)
        template <typename T>static T maxOf(T* First, int Length)
        {
            T Max = *First;
            T* Each = First;
            for (int i = 0; i < n; i++)
            {
                if (Max < *Each) { Max = *Each; }
                Each++;
            }
            return Max;
        }
        template <typename T>static T minOf(T* First, int Length)
        {
            T Min = *First;
            T* Each = First;
            for (int i = 0; i < n; i++)
            {
                if (Min > *Each) { Min = *Each; }
                Each++;
            }
            return Min;
        }
        //������ͺ���
        template <typename T>static T sumOf(T* First, int Length) {
            T* Each = First;
            T Sum = 0;
            for (int i = 0; i < Length; i++) {
                Sum += *Each;
                Each++;
            }
            return Sum;
        }
    };
}

//We provide you with this macro to quickly set seed of all CE random functions.
//If you do not use the Qt library, the macro uses the native random number seed function.
//All CE functions related to random numbers work like this
#define INIT_RAND_SEED CE::CEOperate::initSeed();
