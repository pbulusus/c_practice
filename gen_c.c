/*
Author : Praveen Bulusu
*/
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdio.h>
#include <ctype.h>
#include <limits.h>
//
#include "get_int.c"

typedef enum {false, true} bool;
///

// Declarations
int htoi(char s[]);
int get_leff(const char sub[]);
int any(char s1[], const char s2[]);
int bin_search(int array[], int arr_len, int value);
int bitcount (void* x);
int bitcount2(void* x);
void printbits(void* x);
bool search_str_wld_crds(const char str[], const char sub[]);
void get_num_in_words(int num, char out_string[]);
void squeeze2(char s1[], const char s2[]);
void expand(const char s1[], char s2[]);
void reverse(char s[], int s_len);
void itoa2(int n, char s[]);
void itob(int n, char s[], unsigned b);
void num2xlcol(unsigned col_num, char s[]);
unsigned setbits(unsigned x, int p, int n, unsigned y);
unsigned invert(unsigned x, int p, int n);
unsigned rightrot(unsigned x, int n);
unsigned raise(unsigned x, int n);
unsigned xlcol2num(char s[]);
// vectors
float  dot(const float vec1[], const float vec2[], unsigned len);
float norm(const float vec1[], unsigned len);
void cross(const float vec1[3], const float vec2[3], float out_vec[3]);
short check_tolerance(float f);
void  bool_vector(const float vec1[], const float vec2[], float rel_vec[], unsigned len, float fac1, float fac2);
float tria_to_circ(const float x[3], const float y[3],const float z[3], float ctr[3], char circle_type);
int strrindex(char string[], char pattern[]);
void reverse_rec(char s[], int left, int right);
// End Declarations

typedef struct a
{
    double x;
    struct a* y;
}A;
// main
int main(int argc, char* argv[])
{
    clock_t start, end;
    start = clock();
    printf("----------------------\n");
    /*
    char a[] = "abc\\**de\\f";
    char b[] = "a*b*c\\\\*\\*\\*d**e\\f";
    printf("%d\n", search_str_wld_crds(a,b));
    char c[] = "abcdef";
    char d[] = "abcd?f";
    char d[] = "a*b*c\\\\*\\*\\*d\\?e\\f?h";
    char c[] = "abc\\***d?e\\fgh";
    char d[] = "a*b*c\\\\*\\*\\*d\\?e\\f?";
    printf("%d\n", search_str_wld_crds(c,d));
    //
    char num_in_words[125];
    int num = UINT_MIN;
    get_num_in_words(num, num_in_words);
    int num = 1751776789;
    get_num_in_words(num, num_in_words);
    printf("--%s--", num_in_words);
    */
//    //
//    char s1[1000];
//    char s2[1000];
//    unsigned x = 0, y, counter = 0;
//    while (x++ < UINT_MAX)
//    {
//         num2xlcol(x, s1);
//         y = xlcol2num(s1);
//         if (x != y)
//         {
//             ++counter;
//             printf("NOT MATCHING %u : %s : %u", x, s1, y);
//             if (counter == 10)
  //         }
//    }
//    printf("All Values are Matching\n");
//    //.
    // circumscribed circle code
    // float x[3] = {-100.2, 200.3, 600.5};
    // float y[3] = {500.7, -800.9, 500.4};
    // float z[3] = {700.9, 400.5, -300.4};
    // float x[3] = {1.0, 0.0, 0.0};
    // float y[3] = {0.0, 1.0, 0.0};
    // float z[3] = {-1.0, 0.0, 0.0};
    // float ctr[3], radius;
    // radius = tria_to_circ(x, y, z, ctr, 'c');
    // printf("Radius is : %3.18f\nCo-ordinates %3.18f, %3.18f, %3.18f \n", radius, ctr[0], ctr[1], ctr[2]);
    //
    char s[] = "abcdefghijbvef";
    char p[] = "";
    int ind = strrindex(s, p);
    printf("Index : %d\n", ind);
    //
    // char s_rec[] = "abcd";
    // printf("%s\n", s_rec); 
    // reverse_rec(s_rec, 0, strlen(s_rec)-1);
    // printf("%s\n", s_rec); 
    end_main:
        printf("\n----------------------\n");
        end = clock();
        double cpu_time_seconds = ((double) (end - start)) / CLOCKS_PER_SEC;
        printf("%s %3.18f %s\n", "Finished processing in :", cpu_time_seconds, "Seconds");
        return 0;
}
//
/*
Exercise 2-6. Write a function setbits(x, p, n, y) that returns x with the n bits that 
begin at position p set tothe rightmost n bits of y, leaving the other bits unchanged. 
*/
unsigned setbits(unsigned x, int p, int n, unsigned y)
{
    unsigned mask = ~(~0 << n);
    int shift = (p + 1 - n);
    return (x & ~(mask << shift)) | ((y & mask) << shift);
}
//
///////////////////////////////////////////////////////////////////////////////////////////
/*
Exercise 2-7. Write a function invert(x, p, n) that return x with the n bits that begin at
position p inverted (i.e., 1 changed into 0 and vice versa), leaving the others unchanged.
*/
unsigned invert(unsigned x, int p, int n)
{
    unsigned mask = ~(~0 << n) << (p + 1 - n);
    return (x & ~mask) | (~x & mask);
}
///////////////////////////////////////////////////////////////////////////////////////////
/*
Exercise 2-8. Write a function rightrot(x, n) that returns the value of the integer x
 rotated to the right by n bit positions.
*/
unsigned rightrot(unsigned x, int n)
{
    return ((x & ~(~0 << n)) << (8 * sizeof(unsigned) - n)) | (x >> n);
}
//
bool contains(const char str[], char c)
{
    int i;
    for (i = 0; str[i]; ++i)
        if (str[i] == c)
            return true;
    return false;
}
//
int any (char s1[], const char s2[])
{
    int i, j;
    for (i = 0; s1[i]; ++i)
        for(j = 0; s2[j]; ++j)
            if (s1[i] == s2[j])
                return i;
    return -1;
}
//
/* bitcount function in K&R */
/* bitcount : count number of 1 bits in x*/
int bitcount(void* x)
{
    int b;
    unsigned x_u = * ( unsigned* ) x;
    for (b = 0; x_u; x_u >>= 1)
        if (x_u & 01)
            b++;
    return b;
}
//
/* Exercise 2-9 bitcount function using x &= (x-1)*/
int bitcount2(void* x)
{
    int b;
    unsigned x_u = * ( unsigned* ) x;
    for (b = 0; x_u; x_u &= (x_u - 1))
        ++b;
    return b;
}
//
void printbits(void* x)
{
    unsigned mask = ~(~0u >> 1);
    unsigned x_u = * (unsigned* ) x;
    char bitchar[2] = "01";
    do
        putchar(bitchar[(x_u & mask) != 0u]);
    while (mask >>= 1);
    putchar('\n'); 
}
//
void squeeze2(char s1[], const char s2[])
{
    bool brk_flg;
    int i, j, k;
    for (i = k = 0; s1[i]; ++i)
    {
        brk_flg = false;
        for (j = 0; s2[j]; ++j)
        {
            if (s1[i] == s2[j])
            {
                brk_flg = true;
                break;
            }
        }
        if (!brk_flg)
            s1[k++] = s1[i];
    }
    s1[k] = '\0';
}
//
int htoi(char s[])
{
    if (! (s[0] == '0' && (s[1] == 'x' || s[1] == 'X')))
    {
        printf("%s\n", "Invalid input to htoi (char str[])");
        return -1;
    }
    int i = 2;
    int num = 0;
    char c;
    while(1)
    {
        c = s[i];
        if ( c >= '0' && c <= '9')
            c -= '0';
        else if (c >= 'A' && c <= 'F')
            c -= 'A' - 10;
        else if (c >= 'a' && c <= 'f')
            c -= 'a' - 10;
        else
            return num;
        num = 16 * num + c;
        ++i;
    }
}
//
// search string with wild cards
int get_leff (const char sub[])
{
    int i;
    int counter = 0;
    for (i = 0; sub[i]; ++i)
        if ((sub[i] == '*') || (sub[i] == '\\' && sub[i + 1] == '?'))
            ++counter;
    return i - counter;
}
bool search_str_wld_crds (const char str[], const char sub[])
{
    int l_str = strlen (str);
    int l_eff = get_leff (sub);

    if (l_eff == 0)
        return true;
    else if (l_eff > l_str)
        return false;
    
    int i, j, j_strt, nc, nc_strt;
    i = j_strt = nc_strt = 0;

    while (i + l_eff - nc_strt <= l_str)
    {
        nc = nc_strt;
        j = j_strt;
        while (sub[j] != '\0')
        {
            if ( sub[j] == '\\' && (sub[j + 1] == '*' || sub[j + 1] == '?') )
                ++j;
            else if (sub[j] == '*')
            {
                j_strt = ++j;
                nc_strt = nc;
                break;
            }
            else if (sub[j] == '?')
            {
                ++i;
                ++j;
                ++nc;
                continue;
            }
            if (sub[j++] != str[i++])
                break;
            ++nc;
        }
        if (nc == l_eff)
            return true;
    }
    return false;
}
//
// just a modified version of strcat, using start inex.
int add_str(char* str, const char* add, int start_i)
{
    int add_i;
    for (add_i = 0; (str[start_i] = add[add_i]); ++add_i, ++start_i)
        ;    
    return start_i;
}
///////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////// Get Num in Words ////////////////////////////////////////////
/*
    void get_num_in_words(int num, char* out_string) :
    Gets number, num, in words into out_string.
    eg. 1999 --> One Thousand Nine Hundred Ninety Nine.
    Make sure char array out_string is allocated atleast 121 Bytes.
    Works for Negative and Postitive Integers for upto type int limits.
*/
void get_num_in_words(int num, char* out_string)
{
    int start_i = 0;
    unsigned num_u;
    if (num == 0)
    {
        start_i = add_str(out_string, "Zero", start_i);
        return;
    }
    else if (num < 0)
    {
        start_i = add_str(out_string, "Negative ", start_i);
        num_u = num * -1;
    }
    else
        num_u = num;

    const char* ones_place[20] = { "", "One", "Two", "Three", "Four",
                                   "Five", "Six", "Seven", "Eight",
                                   "Nine", "Ten", "Eleven", "Twelve",
                                   "Thirteen", "Fourteen", "Fifteen",
                                   "Sixteen", "Seventeen", "Eighteen",
                                   "Nineteen"};
    const char* twos_place[10] = { "", "", "Twenty", "Thirty", "Forty",
                                   "Fifty", "Sixty", "Seventy", "Eighty",
                                   "Ninety"};
    const char* places[4]      = { " BILLION", " MILLION", " THOUSAND", ""};
    int divisors[4]            = {1000000000, 1000000, 1000, 1};
    const char hundred[]       = " Hundred";
    const char space[]         = " ";
    int places_counter         = 0;
    unsigned remainder100, remainder10, num100, num10, quot;

    while (num_u > 0)
    {
        quot = num_u / divisors[places_counter];
        num_u %= divisors[places_counter];
        if (quot)
        {
            remainder100 = quot % 100;
            num100       = (quot - remainder100) / 100;
            if (num100)
            {
                start_i = add_str(out_string, ones_place[num100], start_i);
                start_i = add_str(out_string, hundred, start_i);
                if (remainder100)
                    start_i = add_str(out_string, space, start_i);
            }
            if (remainder100)
            {
                if (remainder100 < 20)
                    start_i = add_str(out_string, ones_place[remainder100], start_i);
                else
                {
                    remainder10 = remainder100 % 10;
                    num10       = (remainder100 - remainder10) / 10;
                    start_i     = add_str(out_string, twos_place[num10], start_i);
                    if (remainder10)
                    {
                        start_i = add_str(out_string, space, start_i);
                        start_i = add_str(out_string, ones_place[remainder10], start_i);
                    }
                }
            }
            start_i = add_str(out_string, places[places_counter], start_i);
            if (num_u)
                start_i = add_str(out_string, space, start_i);
        }
        ++places_counter;
    }
}
//////////////////////////End Get Num in Words ////////////////////////////////////////////
int bin_search (int array[], int arr_len, int value)
{
    int start_indx = 0;
    int end_indx = arr_len - 1;
    int mid_indx;
    while (start_indx <= end_indx)
    {
        mid_indx = (start_indx + end_indx) / 2;
        if (array[mid_indx] == value)
            return mid_indx;
        else if (array[mid_indx] > value)
            end_indx = --mid_indx;
        else
            start_indx = ++mid_indx;
    }
    return -1; // not found
}
//
void expand (const char s1[], char s2[])
{
    int i, j, counter = 0;
    for (i = 0; s1[i]; ++i)
    {
        if (s1[i] == '-' && i  && s1[i + 1] && isalnum(s1[i - 1]) && isalnum(s1[i + i]))
            for (j = 1 + s1[i - 1]; j < s1[i + 1]; ++j)
                s2[counter++] = j;
        else
            s2[counter++] = s1[i];
    }
    s2[counter] = '\0';
}
//
void itoa2 (int n, char s[])
{
    int i;
    unsigned n_u;
    n_u = (n < 0) ? -1 * n : n;
    i = 0;
    do
        s[i++] =n_u % 10 + '0';
    while (n_u /= 10);
    if (n < 0)
        s[i++] = '-';
    s[i] = '\0';
    reverse(s, i);
}
//
void reverse(char s[], int s_len)
{
    int i;
    int i_lim = s_len / 2;
    char temp;
    for (i = 0; i < i_lim; ++i)
    {
        temp = s[--s_len];
        s[s_len] = s[i];
        s[i] = temp;
    }
}
//
unsigned raise(unsigned x, int n)
{
    unsigned power = 1;
    for (; n > 0; --n)
        power *= x;
    return power;
}
//
void itob(int n, char s[], unsigned b)
{
    if (b < 2 || b > 36)
        exit(1);
    int i = 0;
    unsigned n_u;
    char numbers[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    if (n < 0)
        n_u = -1 * n;
    else
        n_u = n;
    
    do
        s[i++] = numbers[n_u % b];
    while (n_u /= b);
    
    if (n < 0)
        s[i++] = '-';
    s[i] = '\0';
}
//
void num2xlcol (unsigned col_num, char s[])
{
    if (col_num == 0)
        return;
    int i = 0;
    do
        s[i++] = 65 + --col_num % 26;
    while (col_num /= 26);
    s[i] = '\0';
    reverse(s, i);
}
//
unsigned xlcol2num(char s[])
{
    unsigned num = 0u;
    char c;
    while (1)
    {
        c = *(s++);
        if (c > 64 && c < 91)
            c -= 64;
        else if (c > 96 && c < 123)
            c-= 96;
        else
            return num;
        num = 26 * num + c;
    }
}
//
// vectors
float  dot(const float vec1[], const float vec2[], unsigned len)
{
    int i;
    float dot_sum = 0.0;
    for (i = 0; i < len; ++i)
        dot_sum += vec1[i] * vec2[i];
    return dot_sum;
}
float norm(const float vec1[], unsigned len)
{
    return sqrt(dot(vec1, vec1, len));
}
void cross(const float vec1[3], const float vec2[3], float out_vec[3])
{
    out_vec[0] = vec1[1] * vec2[2] - vec1[2] * vec2[1];
    out_vec[1] = vec1[2] * vec2[0] - vec1[0] * vec2[2]; 
    out_vec[2] = vec1[0] * vec2[1] - vec1[1] * vec2[0]; 
}
void  bool_vector(const float vec1[], const float vec2[], float rel_vec[], unsigned len, float fac1, float fac2)
{
    int i;
    for (i = 0; i < len; ++i)
        rel_vec[i] = fac1 * vec1[i] + fac2 * vec2[i];
}
//
short check_tolerance(float f)
{
    if (f > -1E-6 && f < 1E-6)
        return 1;
    return 0;
}
void print_vector(float v[], unsigned len)
{
    unsigned i;
    for (i = 0; i < len; ++i)
        printf ("%3.18f ", v[i]);
    printf("\n");
}
float get_q(const float v[3], const float w[3], const float l[3])
{
    float tmp = (v[0] * w[1] - v[1] * w[0]);
    if (check_tolerance(tmp))
        return (v[2] * l[0] - v[0] * l[2]) / (v[0] * w[2] - v[2] * w[0]);
    else
        return (v[1] * l[0] - v[0] * l[1]) / tmp;
}
// circumscribed circle
float tria_to_circ(const float x[3], const float y[3],const float z[3], float ctr[3], char circle_type)
{
    float a[3], b[3], u[3];
    bool_vector(x, y, a, 3, -1.0, 1.0);
    bool_vector(x, z, b, 3, -1.0, 1.0);
    cross(a, b, u);
    // check
    if (check_tolerance(norm(u, 3)))
    {
        printf("ERROR : Points are collinear or coincident.\n");
        return 0.0;
    }
    // end checks
    float c[3], v[3], w[3], q, radius = 0.0;
    bool_vector(y, z, c, 3, -1.0, 1.0);

    if (circle_type == 'c') // circumsscribed
    { 
        cross(a, u, v);
        cross(b, u, w);
        q = get_q(v, w, c);
        bool_vector(b, w, ctr, 3, 0.5, 0.5 * q);
        radius = norm(ctr, 3);
        bool_vector(ctr, x, ctr, 3, 1.0, 1.0);
    }
    else if (circle_type == 'i') // inscribed
    {
        float anormc = 1.0 / norm(a, 3);
        bool_vector(a, b, v, 3,  anormc, 1.0 / norm(b, 3));
        bool_vector(a, c, w, 3, -anormc, 1.0 / norm(c, 3));
        q = get_q(v, w, a);
        bool_vector(w, a, ctr, 3, q, -q * dot(w, a, 3) * anormc * anormc);
        radius = norm(ctr, 3);
        bool_vector(y, w, ctr, 3, 1.0, 1.0);
    }
    else
    {
        printf("ERROR : Unknown circle type argument %c to fucntion tria_to_circ.\n", circle_type);
        return 0.0;
    }
    return radius;
}
//
// K & R exercise 4-1
int strrindex(char string[], char pattern[])
{
    int index = -1;
    int si = 0;
    int pi = 0;
    while (1)
    {
        for ( ; pattern[pi] != '\0' && string[si] != '\0' && (pattern[pi] == string[si]); ++pi, ++si)
            ;
        if (pattern[pi] == '\0')
            index = si - pi;
        if (string[si] == '\0')
            return index;
        si -= --pi;
        pi = 0;
    }
    // return index;
}
void reverse_rec(char s[], int left, int right)
{
    if (left < right)
    {
        char tmp = s[right];
        s[right] = s[left];
        s[left]  = tmp;
        reverse_rec(s, ++left, --right);
    }
}
///
