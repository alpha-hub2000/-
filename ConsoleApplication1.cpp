// ConsoleApplication1.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include<math.h>
#include<stdlib.h>
#define pi 3.1415926
using namespace std;
int main()
{
    int choice;
    int condition;
    double H;//BL数组最后一个元素表示BL的弧度制
    double X;
    double Y ;
    double Z;
    double B[4] = {0};
    double L[4];
    double p = 180*3600/pi;
    cout << "大地坐标转换为大地空间直角直角坐标请输入1" << endl << "大地空间直角坐标转化为大地坐标请输入2：" << endl;
    cin >> choice;
    if (choice == 1)
    {
        
        cout << "请输入大地坐标L。如72° 32′ 45″输入形式为 72 32 45:" << endl;
        for (int i = 0; i < 3; i++)
            cin >> L[i];
        cout << "请输入大地坐标B。如72° 32′ 45″输入形式为 72 32 45:" << endl;
        for (int i = 0; i < 3; i++)
            cin >> B[i];
        cout << "请输入大地高H:" << endl;
        cin >> H;
        B[3] = (B[0] * 60 * 60 + B[1] * 60 + B[2]) / p;
        L[3] = (L[0] * 60 * 60 + L[1] * 60 + L[2]) / p;
        //cout << B[3] << endl << L[3];
        cout << "使用克拉索夫斯基椭球请输入1,IUGG 1975椭球请输入2，CGCS 2000椭球请输入3" << endl;
        cin >> condition;
        double a, e=0, N=0, W=0; //定义椭球参数
        if (condition == 1)
        {

            a = 6378245;
            e = 0.00669342162297;
            W = sqrt(1 - e *sin(B[3])*sin(B[3]));
            N = a / W;
        }
        else if (condition == 2)
        {
            a = 6378140;
            e = 0.00669438499959;
            W = sqrt(1 - e * sin(B[3]) * sin(B[3]));
            N = a / W;
        }
        else if (condition == 3)
        {
            a = 6378137;
            e = 0.00669438002290;
            W = sqrt(1 - e * sin(B[3]) * sin(B[3]));
            N = a / W;
        }

        X = (N + H) * cos(B[3]) * cos(L[3]);
        Y = (N + H) * cos(B[3]) * sin(L[3]);
        Z = (N * (1 - e) + H) * sin(B[3]);
        cout << "大地空间直角坐标为：" << endl;
        cout.setf(ios::fixed, ios::floatfield);
        cout << "X=" << X <<endl<< "Y=" << Y <<endl<< "Z=" << Z << endl;
    }
    else if (choice == 2)
    {
        cout << "请输入大地空间直角坐标X、Y、Z：" << endl;
        cin >> X >> Y >> Z;
        L[3] = atan2(Y, X);
        cout << "使用克拉索夫斯基椭球请输入1,IUGG 1975椭球请输入2，CGCS 2000椭球请输入3：" << endl;
        cin >> condition;
        double a=0, e = 0, N = 0, W; //定义椭球参数

        //选用椭球类型
        if (condition == 1)
        {

            a = 6378245;
            e = 0.00669342162297;
            
        }
        else if (condition == 2)
        {
            a = 6378140;
            e = 0.00669438499959;
            //W = sqrt(1 - e * sin(B[3]) * sin(B[3]));
            //N = a / W;
        }
        else if (condition == 3)
        {
            a = 6378137;
            e = 0.00669438002290;
            //W = sqrt(1 - e * sin(B[3]) * sin(B[3]));
            //N = a / W;
        }
        B[3] =atan(Z / sqrt(X * X + Y * Y));
        B[2] = atan((1 / sqrt(X * X + Y * Y)) * (Z + (a*e*tan(B[3]))/sqrt(1+tan(B[3])*tan(B[3])-e* tan(B[3]) * tan(B[3]))));
        while (abs(B[3]-B[2])>5E-10)
        {
            B[3] = B[2];
            B[2] = atan((1 / sqrt(X * X + Y * Y)) * (Z + (a * e * tan(B[3])) / sqrt(1 + tan(B[3]) * tan(B[3]) - e * tan(B[3]) * tan(B[3]))));
        }
        B[3] = B[2];
        W = sqrt(1 - e * sin(B[3]) * sin(B[3]));
        N = a / W;
        H = sqrt(X*X + Y *Y)/cos(B[3])-N;
        //将弧度制转化为角度制
        L[0] = int(L[3] * 180 / pi);
        L[1] = int((L[3] * 180 / pi - int(L[3] * 180 / pi)) * 60);
        L[2] = ((L[3] * 180 / pi - int(L[3] * 180 / pi)) * 60 - int((L[3] * 180 / pi - int(L[3] * 180 / pi)) * 60)) * 60;
        cout << "L=" << L[0] << "°" << L[1] << "′" << L[2] << "″" << endl;
        B[0] = int(B[3] * 180 / pi);
        B[1] = int((B[3] * 180 / pi - int(B[3] * 180 / pi)) * 60);
        B[2] = ((B[3] * 180 / pi - int(B[3] * 180 / pi)) * 60 - int((B[3] * 180 / pi - int(B[3] * 180 / pi)) * 60)) * 60;
        cout << "B=" << B[0] << "°" << B[1] << "′" << B[2] << "″" << endl;
        cout << "H=" << H << endl;
    }
    else
    {
        cout << "输入错误，请重新开始" << endl;
    }

    return 0;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
