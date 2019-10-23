#include <stdio.h>
#include <cs50.h>

string check_cc_type(void);
long check_cc_num(void);

long cc;
int num=0;
string type="";
int typecheck=1;

int main(void)
{
        type = check_cc_type();

        if (typecheck == 1)
        {
            num = check_cc_num();
            if (num%10 == 0)
            {
                printf("%s\n",type);
            }
            else
            {
                printf("INVALID1\n");
            }
        }
        else
        {
            printf("INVALID2\n");
        }

}

string check_cc_type(void)
{
    cc = get_long("Number: ");
    int ax  = cc/10000000000000; //convert AMEX to 2 digits from 15
    int mc  = cc/100000000000000; // convert MASTERCARD to 2 digits from 16
    int vs1 = cc/1000000000000; // convert VISA to 1 digit from 13
    int vs2 = cc/1000000000000000; // convert VISA to 1 digit from 16

    if (ax == 34 || ax == 37)
    {
        type = "AMEX";
    }

    else if (mc == 51 || mc == 52 || mc == 53 || mc == 54 || mc == 55)
    {
        type = "MASTERCARD";
    }
    else if (vs1 == 4 || vs2 == 4)
    {
        type = "VISA";
    }
    else
    {
        typecheck = 0;
    }
    return type;
}

long check_cc_num(void)
{
    for (long x=100; x<cc*100; x*=100)
    {
        int e=0;
        int c = (cc%x)/(x/10); //get digits starting from second to last
        int d = c * 2;

        if(d>9) //separate double digits
        {
            e = d%10;
            d /= 10;
        }

        int f = (cc%(x/10))/(x/100); //get digits starting from last
        num = num + d + e + f;
    }
    return num;
}