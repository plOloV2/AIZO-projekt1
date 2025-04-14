int** creat_dataINT(int ammount);                           //used befor sorting to generate arrays of int


double** creat_dataDOUBLE(int ammount);                     //used befor sorting to generate arrays of double


int sort_results(void **data, int size, int config, void (*f)(void *, int, int), double *results_array, int start_pos);


double** final_result(double **results, int size, int num_of_sets);                                                 //function to calculate end results


int print_results_to_file(double **result, int num_algorithms, const char *filename_pref, int n, int ammount);      //function to save end results to file
