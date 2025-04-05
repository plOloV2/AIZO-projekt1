import pandas as pd
import glob
import numpy as np
import csv

# --- Data Loading and Processing ---
files = glob.glob('data/Results_*.csv')
files.sort(key=lambda x: int(x.split('_')[1].split('.')[0]))

# Read and clean data
dataframes = []
for file in files:
    df = pd.read_csv(file)
    df.columns = df.columns.str.strip()  # Remove whitespace from column names
    dataframes.append(df)

combined_df = pd.concat(dataframes, ignore_index=True)

# --- Create Structured Data ---
sizes = np.sort(combined_df['data_size'].unique())

results = {
    'sizes': sizes,
    'algorithms': {}
}

algorithms = combined_df['name'].unique()
data_types = ['N', 'G', 'D', '33', '67']

for algorithm in algorithms:
    alg_data = combined_df[combined_df['name'] == algorithm].sort_values('data_size')
    
    algorithm_dict = {}
    for dtype in data_types:
        metrics_array = np.array([
            alg_data[f'{dtype}_avg'],
            alg_data[f'{dtype}_std_dev'],
            alg_data[f'{dtype}_min'],
            alg_data[f'{dtype}_max']
        ])
        algorithm_dict[dtype] = metrics_array
    
    results['algorithms'][algorithm] = algorithm_dict

# --- Save to CSV ---
csv_rows = []
headers = ['Algorithm', 'Data_Type', 'Size', 'Avg', 'Std_Dev', 'Min', 'Max']
csv_rows.append(headers)

for algo_name, algo_data in results['algorithms'].items():
    for dtype, metrics_array in algo_data.items():
        for size_idx, size in enumerate(results['sizes']):
            csv_rows.append([
                algo_name,
                dtype,
                size,
                f"{metrics_array[0, size_idx]:.9f}",  # Avg
                f"{metrics_array[1, size_idx]:.9f}",  # Std
                f"{metrics_array[2, size_idx]:.9f}",  # Min
                f"{metrics_array[3, size_idx]:.9f}"   # Max
            ])

with open('data/algorithm_metrics.csv', 'w', newline='') as f:
    writer = csv.writer(f)
    writer.writerows(csv_rows)

print("Data saved to data/algorithm_metrics.csv")
