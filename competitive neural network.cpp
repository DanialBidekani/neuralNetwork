// this program implement competitive neural network
// and written by danial bidekani

#include <iostream>
#include <math.h>
#include <limits>
#include <cstdlib>
using namespace std;

void fillMatrix(double**, int, int);
void printMatrix(double**, int, int);
void multiple2matrix(double**, double**, double**, int, int);
int checkAnswerAndAllocateI(double**, double**, int, int);
void transposeInputPattern(double**, double**, int);
void calculateNewWeightMatrix(double**, double**, double, int, int, int);
void assignWeight(double**, int, int);

int main()
{
	int numberOfFeatures;	//number of features
	int numberOfNeurons;	//number of neurons
	double **p;		//property matrix
	register int row;		//counter
	double **answer;		//answer matrix
	double **weight;		//weight matrix
	double **i;
	double alpha = 0.5;		//learning rate
	double **pT;
	int iStar;

		// receive number of features
		cout<<"Enter Number Of Features: \n";
		cin>>numberOfFeatures;

		// assign number of neuron in network
		cout<<"Enter Number Of Neuron You Choose In Network:\n";
		cin>>numberOfNeurons;

		//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*-*-*--------->>>ALLOCATION SPACE FOR ALL MATRIX
		//allocate space for patterns matrix
		p = new double* [numberOfFeatures];
		for(row=0; row<numberOfFeatures; row++)
		{
			p[row] = new double[1];
		}

		// allocate space for weight matrix
		weight = new double* [numberOfNeurons];
		for(row=0; row<numberOfNeurons; row++)
		{
			weight[row] = new double[numberOfFeatures];
		}

		//allocate space for answer matrix
		answer = new double* [numberOfNeurons];
		for(row=0; row<numberOfNeurons; row++)
		{
			answer[row] = new double[1];
		}

		//allocate space for i matrix
		i = new double* [numberOfNeurons];
		for(row=0; row<numberOfNeurons; row++)
		{
			i[row] = new double[1];
		}

		//allocate pattern input inverse

		pT = new double* [1];
		pT[0] = new double[numberOfFeatures];


		//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*-*-*--------->>>END ALLOCATION SPACE FOR ALL MATRIX


		// first assignment for weight matrix
		assignWeight(weight, numberOfNeurons, numberOfFeatures);


		while(true)
		{
		// first assignment for p
		fillMatrix(p, numberOfFeatures, 1);
		cout<<"The Property Input Matrix Is:\n";
		printMatrix(p, numberOfFeatures, 1);

		multiple2matrix(p, weight, answer, numberOfNeurons, numberOfFeatures);
		cout<<"The Answer Matrix Is: \n";
		printMatrix(answer, numberOfNeurons, 1);


		iStar = checkAnswerAndAllocateI(answer, i, numberOfNeurons, 1);
		cout<<"The I Matrix Is:\n";
		printMatrix(i, numberOfNeurons, 1);

		transposeInputPattern(p, pT, numberOfFeatures);

		cout<<"The Winner Neuron Is: "<<iStar<<endl;
		cout<<"- - -"<<endl;

		calculateNewWeightMatrix(weight, pT, alpha, iStar, numberOfNeurons, numberOfFeatures);
		cout<<"The New Weight Matrix Is:\n";
		printMatrix(weight, numberOfNeurons, numberOfFeatures);

		}//end while
}// end main

//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*-*-*--------->>>FILL PATTERN METHOD
void fillMatrix(double **p, int ro, int co)
{
	register int i, j;
	for(i=0; i<ro; i++)
		for(j=0; j<co; j++)
		{
			cout<<"Enter Feature Value "<<i<<endl;
			cin>>p[i][j];
		}
}
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*-*-*--------->>>PRINT MATRIX METHOD
void printMatrix(double **p, int ro, int co)
{
	cout<<"- - -\n";
	register int i, j;
	for(i=0; i<ro; i++)
	{
		for(j=0; j<co; j++)
		{
			cout<<p[i][j]<<"\t";
		}
	cout<<endl;
	}
	cout<<"- - -\n";
}
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*-*-*--------->>>MULTIPLE TWO MATRIX METHOD
void multiple2matrix(double **p, double **w, double **a, int ro, int co)
{
	register int i, j, k;
	for(i=0; i<ro; i++)
	{
		for(j=0; j<co; j++)
		{
			a[i][j] = 0;
			for(k=0; k<co; k++)
			{
				a[i][j] = a[i][j]+ w[i][k]*p[k][0];
			}
		}
	}
}
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*-*-*--------->>>CHECK  ANSWER AND ALLOCATE I MATRIX METHOD
int checkAnswerAndAllocateI(double **a, double **iMatrix, int ro, int co)
{
	register int i;
	int index;
	double max = -1 * numeric_limits<double>::infinity();

	// search to find the biggest element in answer vector
	for(i=0; i<ro; i++)
	{
		if(a[i][0] > max)
		{
			index = i;
			max = a[i][0];
		}
	}


	// assign 1 to bigger element and assign 0 to the others
	for(i=0; i<ro; i++)
	{
		if(i == index)
			iMatrix[i][0] = 1;
		else
			iMatrix[i][0] = 0;
	}

	return index;
}
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*-*-*--------->>>TRANSPOSE THE PATTERN INPUT MATRIX
void transposeInputPattern(double **p, double **pt, int ro)
{
	register int i;

	for(i=0; i<ro; i++)
	{
		pt[0][i] = p[i][0];
	}

}
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*-*-*--------->>> CALCULATE NEW WEIGHT MATRIX
void calculateNewWeightMatrix(double **w, double **pt, double alpha, int iSt, int ro, int co)
{
	register int i;

	for(i=0; i<co; i++)
	{
		w[iSt][i] = (1-alpha) * w[iSt][i];
	}

	for(i=0; i<co; i++)
	{
		w[iSt][i] += alpha * pt[0][i];
	}
}
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*-*-*--------->>> ASSIGN WEIGHT METHOD
void assignWeight(double **w, int ro, int co)
{
	register int i, j;
	for(i=0; i<ro; i++)
		for(j=0; j<co; j++)
		{
			w[i][j] = rand()%10;
		}
}
