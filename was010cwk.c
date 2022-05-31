/********************************************/
/*               Gentian Hila               */
/*                  B727617             a   */
/*         Programming Coursework           */
/********************************************/
/*bibliography*/
/*Interest rate: https://www.slc.co.uk/students-and-customers/loan-repayment/interest-rates.aspx*/
/*Student loan repayment formula: http://www.studentloanrepayment.co.uk/portal/page?_pageid=93,6678490&_dad=portal&_schema=PORTAL*/
/*Annual salary increase https://www.ons.gov.uk/economy/grossdomesticproductgdp/timeseries/kgq2/qna*/
/* average starting salary for EEE at Loughborough https://www.lboro.ac.uk/study/undergraduate/courses/a-z/electronic-and-electrical-engineering-beng/*/


#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "functions.h"


char P=NULL; /*palcement year?*/
int PayYear=0; /*yaer they start paying*/
int py=0; /*reset PayYear in loop*/
int SY=0; /*start year*/
float SL=0.0; /*loan for 1 year*/
int NOY=0; /*nummber of years studying*/
float TF = 9250.00;/*tuition fees*/
float MOL = 8700.00;/*maintenance loan*/
float InterestStudy = 0.0;/*amount owed after finishing university*/
float ASalary = 0.0; /*annual salary*/
float Salary=0.0; /*monthly salary*/
float Payment=0.0; /*amount paid monthly */
int MS = 25000 / 12; /*monthly threshold salary*/
float intsal = 0.0; /*annual salary with 4% increase*/
int PayMonth = 3; /*month they start paying*/
float monthsal=0.0; /*monthly salary with annual 4% increase*/
float startpoint = 0.0; /*reset InterestStudy*/
float totint = 0.0; /*total interest*/
float Placement = 1850.00; /*placement cost*/
int NM = 0; /*counter for payment loop*/
float SalAbvThshld = 0.0f; /*salary above threshold*/
float InterestPercent = 0.0f; /*interest based on salary*/


float InitialSalary[73];
int csvmonth[360];
int csvyear[360];
float csvsalary[360];
float csvthreshold[360];
float csvinterest[360];
float csvmonthint[360];
float csvpayment[360];
float csvbalance[360];

FILE* txt;
FILE* csv;
void main()
{

	txt = fopen("loancalc.txt", "w");
	txt = fopen("loancalc.txt", "a");
	csv = fopen("loancalc.csv", "w");
	csv = fopen("loancalc.csv", "a");

	function1();

	function2();

	function3();

	function4();
	
	fclose(txt);
	fclose(csv);
	printf("\n Pleaase open the txt and csv files\n");
	scanf("%*s");

}
