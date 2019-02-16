#include<stdio.h>
#include<string.h>

int lcs(const char * X, const char * Y)
{
    if (X == NULL || Y == NULL)
        return -1;
    int lenX = strlen(X);
    int lenY = strlen(Y);
    int ** c = new int*[lenX + 1];
    for (int i = 0; i < lenX + 1; i++)
    {
        c[i] = new int[lenY + 1];
    } 
 
    for (int i = 0; i < lenX; i++)
    {
        c[i][lenY] = 0;
    }
    for (int j = 0; j < lenY; j++)
    {
        c[lenX][j] = 0;
    }
    c[lenX][lenY] = 0;

    for (int i = lenX - 1; i >= 0; i--)
    {
        for (int j = lenY -1; j >= 0; j--)
        {
            if (X[i] == Y[j])
                c[i][j] = c[i +1][j + 1] + 1;
	    else
	    {
	        int p = c[i + 1][j];
	        int q = c[i][j + 1];
	        c[i][j] = p > q ? p : q;
	    }
        }
    }
    int ret = c[0][0];
    for (int i = 0; i <= lenX; i++)
        delete[] c[i];
    delete[] c;
    return ret;
}

int main()
{
    const char * X = "BABA";
    const char * Y = "BDCABA";
    int ret = lcs(X, Y);
    if (ret != -1)
        printf("the longest common sequence of %s and %s is %d\n", X, Y, ret);


    return 0;
}




