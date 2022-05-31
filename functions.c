#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
extern char P; 
extern int PayYear; 
extern int py;
extern int SY;
extern float TF;
extern float SL;
extern int NOY;
extern float MOL;
extern float ASalary;
extern float Salary;
extern float Payment;
extern int MS;
extern float intsal;
extern int PayMonth;
extern 	float monthsal;
extern float InterestStudy;
extern float startpoint;
extern float totint;
extern float Placement;
extern int NM;
extern float SalAbvThshld;
extern float InterestPercent;
extern float Monthint;

extern float InitialSalary[73];
extern int csvmonth[360];
extern int csvyear[360];
extern float csvsalary[360];
extern float csvthreshold[360];
extern float csvinterest[360];
extern float csvmonthint[360];
extern float csvpayment[360];
extern float csvbalance[360];

extern FILE*txt;
extern FILE*csv;

/*this functoin creates a range of salaries form 29000 to 100000 in 1000 increments (starts at 29000 becasue that is the aerage starting salary for EEE students at Loughborough university*/
void function1()
{
	for (int i = 1; i < 72; i++)
	{
		InitialSalary[0] = 29000;
		InitialSalary[i] = InitialSalary[i - 1] + 1000;
	}
}

/*this function askes for all the users input and calculates loan for 1 year and what year they will start paying*/
void function2()
{
	//extern int SY;
	printf(" Please enter the year you started in YYYY format: ");
	scanf("%i", &SY);
	printf(" Please entre the number of years you are studying: ");
	scanf("%i", &NOY);
	printf(" Are you doing a placement year? Y for yes N for no: ");
	scanf(" %c", &P);
	SL = TF + MOL;
	PayYear = SY + NOY + 1;
}

/*this function adds 1 to the year if they are doing a placemnt*/
void function3()
{
	//extern int SY;
	if (P == 'N' || P == 'n')
	{
		py = PayYear;
	}
	else if (P == 'Y' || P == 'y')
	{
		py = PayYear++;
		PayYear = PayYear++;
	}
}
/*there function has the main ccode in it*/
/*the first loop is there so it does the calculations for a range of salaries it also resets all of the values used in the nested loop it also Prints everything to the text and csv files8?
/*the next loop does all the calculations and saves the values in arrays*/
void function4()
{
	for (int i = 0; i < 72; i++)
	{
		ASalary = InitialSalary[i];
		Salary = ASalary / 12.0f; /*monthly salary*/
		Payment = (Salary - (float)MS)* 0.09f; /*Amount they would pay each month*/
		intsal = ASalary;
		PayMonth = 3;
		PayYear = py;
		float SalAbvThshld = 0.0f;
		monthsal = intsal / 12.0f;
		Payment = (monthsal - (float)MS)* 0.09f;
		SalAbvThshld = ((monthsal - (float)MS) * 12) - 4;
		float Monthint = 0.0f;
		InterestStudy = startpoint;
		for (int i = 0; i < NOY; i++)
		{
			;
			InterestStudy = (SL + InterestStudy)*(1.0f + 0.063f);

			totint = InterestStudy;
			if (i == NOY - 1 && P == 'Y')
			{
				InterestStudy = (Placement + InterestStudy)*(1.0f + 0.63f);
				totint = InterestStudy;
				startpoint = InterestStudy;
			}
		}
		for (NM = 0; NM <= 360; NM++)
		{
			csvsalary[NM] = intsal;
			csvthreshold[NM] = SalAbvThshld;
			csvyear[NM] = PayYear;
			csvpayment[NM] = Payment;
			if (PayMonth == 13)
			{
				PayMonth = 1;
				PayYear++;
				intsal = intsal + intsal * 0.04f;
				monthsal = intsal / 12.0f;
				Payment = (monthsal - (float)MS)* 0.09f;
				SalAbvThshld = ((monthsal - (float)MS) * 12) - 4;
			}
			csvmonth[NM] = PayMonth;
			float interest = 0.0f;
			if (intsal < 25000)
			{
				interest = 0.033f;
			}
			else if (intsal > 25000 && intsal < 45000)
			{
				interest = 0.033f + ((intsal - 25000) / 1000)*0.0015f;
				InterestPercent = interest * 100;
				csvinterest[NM] = InterestPercent;
			}
			else if (intsal > 45000)
			{
				interest = 0.063f;
				InterestPercent = interest * 100;
				csvinterest[NM] = InterestPercent;
			}
			float LI = interest / 12; /* Loan interest*/

			if (NM > 360)
			{
				break;
			}
			if (ASalary <= 25000 || intsal <= 25000)
			{
				InterestStudy = InterestStudy + (InterestStudy*LI);


			}
			else
			{
				Monthint = InterestStudy * LI;
				csvmonthint[NM] = Monthint;
				InterestStudy = InterestStudy + Monthint; /*Total loan with interest*/
				totint = totint + Monthint;
				InterestStudy = InterestStudy - Payment;/*Total loan after payment*/
				//fprintf(csv, "%i/%i,", PayMonth, PayYear);
				//fprintf(csv, "%i,", PayMonth);
				//fprintf(csv, "%i,", PayYear);
				//fprintf(csv, "%.2f,", intsal);
				//fprintf(csv, "%.2f,", SalAbvThshld);
				//fprintf(csv, "%.2f,", InterestPercent);
				//fprintf(csv, "%.2f,", Monthint);
				//fprintf(csv, "%.2f,", Payment);
				//fprintf(csv, "%.2f,", InterestStudy);
				//fprintf(csv, "\n");
			}
			PayMonth++;
			csvbalance[NM] = InterestStudy;
			if (InterestStudy < 0)
			{
				InterestStudy = 0;
				break;
			}
		}
		float totpaid = totint - InterestStudy;
		fprintf(txt, "\n Initial salary £%1.2f \n", ASalary);
		fprintf(txt, "\n Final salary £%1.2f \n", intsal);
		fprintf(txt, "\n Total loan £%1.2f \n", SL*NOY);
		fprintf(txt, "\n Last payment date  %1i / %i \n", PayMonth, PayYear);
		fprintf(txt, "\n Closing balance £%1.2f \n", InterestStudy);
		fprintf(txt, "\n Total interest  £%1.2f \n", totint);
		fprintf(txt, "\n Total paid £%1.2f\n", totpaid);
		fprintf(txt, "------------------------------------");

		fprintf(csv, "month-year,");
		for (int i = 1; i < 360; i++)
		{
			fprintf(csv, "%d/%d,", csvmonth[i],csvyear[i]);
			if (csvbalance[i] <= 0)
			{
				csvbalance[i] = 0;
				break;
			}
		}
		fprintf(csv, "\n");
		fprintf(csv, "month,");
		for (int i = 1; i < 360; i++)
		{
			fprintf(csv, "%d,", csvmonth[i]);
			if (csvbalance[i] <= 0)
			{
				csvbalance[i] = 0;
				break;
			}
		}
		fprintf(csv, "\n");
		fprintf(csv, "Year,");
		for (int i = 1; i < 360; i++)
		{
			fprintf(csv, "%d,", csvyear[i]);
			if (csvbalance[i] <= 0)
			{
				csvbalance[i] = 0;
				break;
			}
		}
		fprintf(csv, "\n");
		fprintf(csv, "Salary(£),");
		for (int i = 1; i < 360; i++)
		{
			fprintf(csv, "%.2f,", csvsalary[i]);
			if (csvbalance[i] <= 0)
			{
				csvbalance[i] = 0;
				break;
			}
		}

		fprintf(csv, "\n");
		fprintf(csv, "Above Threshold (£25000),");
		for (int i = 1; i < 360; i++)
		{
			fprintf(csv, "%.2f,", csvthreshold[i]);
			if (csvbalance[i] <= 0)
			{
				csvbalance[i] = 0;
				break;
			}
		}

		fprintf(csv, "\n");
		fprintf(csv, "Interest (%%),");
		for (int i = 1; i < 360; i++)
		{
			fprintf(csv, "%.2f,", csvinterest[i]);
			if (csvbalance[i] <= 0)
			{
				csvbalance[i] = 0;
				break;
			}
		}

		fprintf(csv, "\n");
		fprintf(csv, "Monthly interest (£),");

		for (int i = 1; i < 360; i++)
		{
			fprintf(csv, "%.2f,", csvmonthint[i]);
			if (csvbalance[i] <= 0)
			{
				csvbalance[i] = 0;
				break;
			}
		}

		fprintf(csv, "\n");
		fprintf(csv, "Payment (£),");

		for (int i = 1; i < 360; i++)
		{
				if (csvpayment[i] > csvbalance[i])
			{
				csvpayment[i] = csvbalance[i-1];
			}
			fprintf(csv, "%.2f,", csvpayment[i]);
		
			if (csvbalance[i] <= 0)
			{
				csvbalance[i] = 0;
				break;
			}
		}

		fprintf(csv, "\n");
		fprintf(csv, "Balance (£),");

		for (int i = 1; i < 360; i++)
		{
			fprintf(csv, "%.2f,", csvbalance[i]);
			if(csvbalance[i]<=0)
			{
				csvbalance[i] = 0;
				break;
			}
		}

		fprintf(csv, "\n");
		fprintf(csv, "\n");

	}
	fclose(txt);
	fclose(csv);
}
