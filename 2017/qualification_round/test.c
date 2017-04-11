#include<stdio.h>

#define INPUTFILE "input.txt"
//#define INPUTFILE "lazyloading.in"
#define OUTPUTFILE "output.txt"
//#define INPUTFILE "lazy_loading.txt"
//#define OUTPUTFILE "output_final.txt"
//#define INPUTFILE "progress_pie_example_input.txt"
//#define OUTPUTFILE "progress_pie_example_output.txt"
#define MAXCASES 500
#define BUCKETSORTLOW 1
#define BUCKETSORTHIGH 100
#define BUCKETSORTRANGE BUCKETSORTHIGH - BUCKETSORTLOW + 1
#define MAXWEIGHT 50

int numofcases;
int numofitems[MAXCASES], weightarr[100][MAXCASES], sortarr[BUCKETSORTRANGE];
int outputarr[MAXCASES];

static FILE *in;
static FILE *out;

void getinput() {
	int i,j;
	fscanf(in,"%d",&numofcases);

	for(i = 0; i<numofcases; i++) {
		fscanf(in,"%d", &numofitems[i]);
		for(j = 0; j<numofitems[i]; j++) {
			fscanf(in,"%d", &weightarr[j][i]);
		}
	}
}

void printinput() {
	int i,j;
	printf("numofcases - %d\n",numofcases);

	for(i = 0; i<numofcases; i++) {
		printf("numofitems #%d - %d\n", i + 1,  numofitems[i]);
		for(j = 0; j<numofitems[i]; j++) {
			printf("%d ", weightarr[j][i]);
		}
		printf("\n");
	}
}

void bucketsort(int curcase) {
	int i,j,count;
	for(i = 0; i<BUCKETSORTRANGE; i++) { //initialize the sort array
		sortarr[i] = 0; }
	for(i = 0; i<numofitems[curcase]; i++) { //fill the bucket
		sortarr[weightarr[i][curcase] - BUCKETSORTLOW]++; 
	}
	
	for(i = 0,count = 0; i<BUCKETSORTRANGE; i++) { // sort the array
		for(j = 0; j<sortarr[i]; j++) {
			if(sortarr[i] > 0) {
				weightarr[count][curcase] = i + BUCKETSORTLOW;
				count++;
			}
		}
	}
}

void tripnumber(int curcase) {
	int numoftrips = 0, i,count = 0;
	float frac;
	count = numofitems[curcase];

	for(i = numofitems[curcase]; i<0; i++) { // get all the cases sorted
		frac = (float)MAXWEIGHT/(float)weightarr[i][curcase]; //ratio of maxweight by maxweight of array
		count++;
		count += (int)frac; //consumed weights are the new highest in the array times smallest 
		numoftrips++;
		if(count<=0)
			break;
	}
	outputarr[curcase] = numoftrips;

}

void getsolution() {
	int i;

	for(i = 0; i<numofcases; i++) { // get all the cases sorted
		bucketsort(i);
	}

	for (i = 0; i<numofcases; i++) { // fill the solution array
		tripnumber(i);
	}

}

void printsolution() {
	int i;
	for(i = 0; i<numofcases; i++) { // print all the solutions
		printf("Case #%d: %d\n", i+1,outputarr[i]);
		fprintf(out,"Case #%d: %d\n", i+1, outputarr[i]);
	}
}

int main() {
	in = fopen(INPUTFILE, "r");
	out = fopen(OUTPUTFILE, "w");
	getinput();
	printinput();
	getsolution();
	printinput();
	printsolution();
	return 0;
}

