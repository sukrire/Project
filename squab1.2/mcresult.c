#include <stdio.h>
#include <stdlib.h>
#include "arrays.h"
#include "mcresult.h"

void InitializeResult(struct mcresult *pmcr){
	pmcr->runtime = 0;
	pmcr->fails = malloc(sizeof(long) * 3);
	pmcr->trials = malloc(sizeof(long) * 3);
	pmcr->rates = malloc(sizeof(double) * 3);
	pmcr->bars = malloc(sizeof(double) * 3);
	pmcr->pass = malloc(sizeof(int) * 3);
}

void ResetResults(struct mcresult *pmcr){
	pmcr->runtime = 0;
	FillLongArrayWithConstants(pmcr->trials, 3, 0);
	FillDoubleArrayWithConstants(pmcr->rates, 3, 0);
	FillDoubleArrayWithConstants(pmcr->bars, 3, 0);
	FillLongArrayWithConstants(pmcr->fails, 3, 0);
	FillIntArrayWithConstants(pmcr->pass, 3, 0);
}

void FreeResult(struct mcresult *pmcr){
	free(pmcr->fails);
	free(pmcr->trials);
	free(pmcr->rates);
	free(pmcr->bars);
}

void PrintResult(struct mcresult *pmcr){
	fprintf(stderr, "\tX,Z\t X\t Z\n");
	fprintf(stderr, "Fails\t%ld\t%ld\t%ld\n", (pmcr->fails)[0], (pmcr->fails)[1], (pmcr->fails)[2]);
	fprintf(stderr, "Trials\t%ld\t%ld\t%ld\n", (pmcr->trials)[0], (pmcr->trials)[1], (pmcr->trials)[2]);
	fprintf(stderr, "Rates\t%g\t%g\t%g\n", (pmcr->rates)[0], (pmcr->rates)[1], (pmcr->rates)[2]);
	fprintf(stderr, "Bars\t%g\t%g\t%g\n", (pmcr->bars)[0], (pmcr->bars)[1], (pmcr->bars)[2]);
	fprintf(stderr, "Pass\t%d\t%d\t%d\n", (pmcr->pass)[0], (pmcr->pass)[1], (pmcr->pass)[2]);
}
