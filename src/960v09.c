/*  Chess960 Position Generator and Lookup v0.9     07/24/2019               #
 #  by Michael Byrne                                                         #
 #                                                                           #
 #  Chess 960 position generator code snippet by:                            #
 #  https://codegolf.stackexchange.com/users/3544/ugoren                     #
 #  Copyrighted by Michael Byrne  No implied warranty provided.              #
*/

/*White's Chess960 starting array can be derived from its number N (0 ... 959) as follows:
 
 a) Divide N by 4, yielding quotient N2 and remainder B1. Place a B​ishop upon the bright square corresponding to B1 (0=b, 1=d, 2=f, 3=h).
 
 b) Divide N2 by 4 again, yielding quotient N3 and remainder B2. Place a second B​ishop upon the dark square corresponding to B2 (0=a, 1=c, 2=e, 3=g).
 
 c) Divide N3 by 6, yielding quotient N4 and remainder Q. Place the Q​ueen according to Q, where 0 is the first free square starting from a, 1 is the second, etc.
 
 d) N4 will be a single digit, 0 ... 9. Place the K​n​ights according to its value by consulting the following table:
 
 Digit     Knight positioning
 0         N   N   -   -   -
 1         N   -   N   -   -
 2         N   -   -   N   -
 3         N   -   -   -   N
 4         -   N   N   -   -
 5         -   N   -   N   -
 6         -   N   -   -   N
 7         -   -   N   N   -
 8         -   -   N   -   N
 9         -   -   -   N   N*/
 

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <ctype.h>
#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

clock_t start, end;
double cpu_time_used;
char*m, l[9], r[9], c;
int i, k, n, rndmcnt, sorto, x, y;
time_t t;
struct tm* tm;
char Date[11];
int g(r) {x=n%r;n/=r;return (r);}  //
int p(s) {(!s*!*m)?*m=c:p(s-!*m++);return (s);}
#define P(s,t); m=r;c=*#t; p(s+0);
#define C960POS 960

//convert string to lowercase
char *strlwr(char *str)
{  unsigned char *p = (unsigned char *)str;
	while (*p) {*p = tolower((unsigned char)*p); p++;}
	return str;}

//convert string to upppercase
char *strupr(char *str)
{  unsigned char *p = (unsigned char *)str;
	while (*p) { *p = toupper((unsigned char)*p); p++;}
	return str;}

 /* Array Shuffle function by Ronald Fisher and Frank Yates - no duplicates!
 #  code snippet from:
 #  https://www.sanfoundry.com/c-program-implement-fisher-yates-algorithm-array-shuffling*/
void shuffle(int *array, int n)
{
	int i, j, tmp;
	for (i = n - 1; i > 0; i--) {
		j = rand() % (i + 1);
		tmp = array[j];
		array[j] = array[i];
		array[i] = tmp;
	}
}

int main(void)
{
	srand((unsigned) time(&t));
	time(&t);
	tm = localtime(&t);
	strftime(Date, sizeof Date, "%Y.%m.%d", tm);
	printf("\nChess960-LookUp-v0.8\nBy Michael Byrne\nDate: %s\n",Date);
tryagain:
	printf("\n  Enter the non-zero based 960 position number 1 through 960 for that position in PGN format.\n");
	printf("  Enter zero to dislay all Chess960 starting positions in PGN format.\n");
	printf("  Enter a negative number less than -1 for Chess960 positions chosen at random.\n");
	printf("  Any mumber greater than 960 will return all Chess 960 positions in raw FEN format:\n");
	printf("  Enter -1 (minus one) to exit. Output can be redirected to a file: \n");
	printf("  Example: Chess960-LookUp > c960.txt - but learn the commands first.\n\n");
	if (scanf("%d",&n) == 1)
	{
		if (n > C960POS)
		{
		printf("You entered %d, a number greater than 960, all 960 FENs will be displayed in sequence.\n",n);
			printf("Enter 0 (zero) to generate in sequence, any other number will sort the output randomly.\n\n");
		scanf("%d",&sorto);
		printf("\n");
		if (!sorto)
		for (int j=0;j<C960POS;j++)
		{
			n=j;
			g(4)P(x-~x,B) // to set the 1st bishops
			g(4);r[x*2]=c; // to set the 2nd bishop
			g(6)P(x,Q) // to set the queen
			P(n>3?(n-=3)>3?(n-=2)>3?n=3:2:1:0,N) // f() to set the knights
			P(n,N) // f() to set the knights
			P(,R)P(,K)P(,R)  //  to set the rooks and king
			memcpy(l, r, sizeof(l));
			//printf("%d\n", j);//used for testing/debugging
			printf("%s/pppppppp/8/8/8/8/PPPPPPPP/%s w KQkq - 0 1\n", strlwr(l), strupr(r));
			memset(l, 0, sizeof(l));
			memset(r, 0, sizeof(r));
		}
		else
		{
			int fens[C960POS];
			for (int i = 0; i < C960POS; i++)
				fens[i]= i;
			shuffle(fens, C960POS);
			for (k=0;k<C960POS;k++)
			{
				n=fens[k];
				y=n;
				g(4)P(x-~x,B)
				g(4);r[x*2]=c;
				g(6)P(x,Q)
				P(n>3?(n-=3)>3?(n-=2)>3?n=3:2:1:0,N)
				P(n,N)
				P(,R)P(,K)P(,R)
				memcpy(l, r, sizeof(l));
				//printf("%d\n", y);//used for testing/debugging
				printf("%s/pppppppp/8/8/8/8/PPPPPPPP/%s w KQkq - 0 1\n", strlwr(l), strupr(r));
				memset(l, 0, sizeof(l));
				memset(r, 0, sizeof(r));
			}
		}
		goto tryagain;
	}
		if (n == -1) exit(0);
		if (n < -1)
		{
			printf("You entered %d, a negative number, indicating you wish to generate one or more random Chess960 positions.\n",n);
			printf("How many random Chess960 positions do you wish to generate (960 is the maximum which will \n");
			printf("re-shuffle the position order.\n");
			scanf("%d",&rndmcnt);
			printf("You entered %d, Chess960-Lookup will generate %d unique random positions.\n\n",rndmcnt,rndmcnt);
			srand((unsigned) time(&t));
			start = clock();
			int positions[C960POS];
			for (int i = 0; i < C960POS; i++)
			positions[i]= i;
			shuffle(positions, C960POS);
			//printf("\nArray after shuffling is: \n");// used for testing
			for (k=0;k<MIN(C960POS,rndmcnt);k++)
			{
				n=positions[k];
				y=n;
				g(4)P(x-~x,B)
				g(4);r[x*2]=c;
				g(6)P(x,Q)
				P(n>3?(n-=3)>3?(n-=2)>3?n=3:2:1:0,N)
				P(n,N)
				P(,R)P(,K)P(,R)
				memcpy(l, r, sizeof(l));
				//printf("Random Position #%d generated - Chess960 position %d:\n", (k+1), y);//used for testing
				//printf("%d\n", y);// used for testing
				printf("[Event \"?\"]\n");
				printf("[Site \"?\"]\n");
				printf("[Date \"%s\"]\n", Date);
				printf("[Round \"?\"]\n");
				printf("[White \"?\"]\n");
				printf("[Black \"?\"]\n");
				printf("[Result \"*\"]\n");
				printf("[FEN \"%s/pppppppp/8/8/8/8/PPPPPPPP/%s w KQkq - 0 1\"] \n", strlwr(l),strupr(r));
				printf("[Setup \"1\"]\n");
				printf("[Variant \"Chess960\"]\n");
				printf("[StartPosition \"%d\"]\n",y);
				printf("*\n\n");
				
				memset(l, 0, sizeof(l));
				memset(r, 0, sizeof(r));
			}
			end = clock();
			cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
			printf("\nCPU time taken to generate %d random Chess960 positions was: %f seconds.\n\n",k,((float)cpu_time_used/1));
			goto tryagain;
		}
		if(n)
		{
			//printf("You entered %d.\n",n); //used for testinng
			n=n-1;
			y=n;
			g(4)P(x-~x,B)
			g(4);r[x*2]=c;
			g(6)P(x,Q)
			P(n>3?(n-=3)>3?(n-=2)>3?n=3:2:1:0,N)
			P(n,N)
			P(,R)P(,K)P(,R)
			memcpy(l, r, sizeof(l));
			printf("[Event \"?\"]\n");
			printf("[Site \"?\"]\n");
			printf("[Date \"%s\"]\n", Date);
			printf("[Round \"?\"]\n");
			printf("[White \"?\"]\n");
			printf("[Black \"?\"]\n");
			printf("[Result \"*\"]\n");
			printf("[FEN \"%s/pppppppp/8/8/8/8/PPPPPPPP/%s w KQkq - 0 1\"] \n", strlwr(l), strupr(r));
			printf("[Setup \"1\"]\n");
			printf("[Variant \"Chess960\"]\n");
			printf("[StartPosition \"%d\"]\n\n",y);
			printf("*\n\n");
			memset(l, 0, sizeof(l));
			memset(r, 0, sizeof(r));
			goto tryagain;
		}
	}
	printf("You entered %d, all 960 positions will be generated in PGN format.\n\n",n);
	for (int j=0;j<C960POS;j++)
	{
		n=j;
		g(4)P(x-~x,B)
		g(4);r[x*2]=c;
		g(6)P(x,Q)
		P(n>3?(n-=3)>3?(n-=2)>3?n=3:2:1:0,N)
		P(n,N)
		P(,R)P(,K)P(,R)
		memcpy(l, r, sizeof(l));
		//printf("%d\n", j);//used for testing
		printf("[Event \"?\"]\n");
		printf("[Site \"?\"]\n");
		printf("[Date \"%s\"]\n", Date);
		printf("[Round \"?\"]\n");
		printf("[White \"?\"]\n");
		printf("[Black \"?\"]\n");
		printf("[Result \"*\"]\n");
		printf("[FEN \"%s/pppppppp/8/8/8/8/PPPPPPPP/%s w KQkq - 0 1\"] \n", strlwr(l), strupr(r));
		printf("[Setup \"1\"]\n");
		printf("[StartPosition \"%d\"]\n\n",j);
		printf("*\n\n");
		memset(l, 0, sizeof(l));
		memset(r, 0, sizeof(r));
	}
}

