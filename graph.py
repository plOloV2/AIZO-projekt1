import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns
import numpy as np

# Load and filter data
df = pd.read_csv('algorithm_metrics.csv')
quick_sort_data = df[
    (
        (df['Algorithm'].str.startswith('QuickSort') & 
        (df['Algorithm'] != 'QuickSortRandom')
    ) | 
    (df['Algorithm'] == 'HeapSort')  # Include HeapSort
) & 
    (df['Data_Type'] == 'N') & 
    (df['Size'].between(45000, 75000))
].sort_values('Size')

# Create plot
plt.figure(figsize=(14, 8))
sns.set_style("whitegrid")
palette = sns.color_palette("husl", n_colors=len(quick_sort_data['Algorithm'].unique()))

# Calculate positions and offsets
sizes = quick_sort_data['Size'].unique()
n_algorithms = len(quick_sort_data['Algorithm'].unique())
width = 0.6  # Width of each "box" group

for idx, (algo_name, algo_data) in enumerate(quick_sort_data.groupby('Algorithm')):
    # Calculate x positions with offset
    x_base = np.arange(len(sizes))
    x_pos = x_base + (idx - n_algorithms/2 + 0.5) * (width/n_algorithms)
    
    # Box dimensions
    box_top = algo_data['Avg'] + algo_data['Std_Dev']
    box_bottom = algo_data['Avg'] - algo_data['Std_Dev']
    
    # Plot elements
    plt.bar(x_pos, height=box_top - box_bottom, width=width/n_algorithms*0.8,
            bottom=box_bottom, color=palette[idx], alpha=0.6, label=algo_name)
    
    # Whiskers (min/max)
    plt.vlines(x_pos, algo_data['Min'], algo_data['Max'], 
              colors=palette[idx], linewidths=1, alpha=0.8)
    
    # Median line (using average)
    plt.hlines(algo_data['Avg'], x_pos - width/(n_algorithms*3), 
              x_pos + width/(n_algorithms*3), colors='white', linewidths=2)

# Configure axes
plt.xticks(np.arange(len(sizes)), sizes)
plt.title('QuickSort Variants Performance (Random array)', 
         fontsize=14, pad=20)
plt.xlabel('Array Size', fontsize=12)
plt.ylabel('Time (seconds)', fontsize=12)
plt.legend(
    title='Algorithm',
    bbox_to_anchor=(0.5, -0.2),  # Adjust these values for positioning
    loc='upper center',
    ncol=4,  # Number of columns in the legend
    frameon=True
)
plt.subplots_adjust(bottom=0.25)  # Adjust this value based on your legend height
plt.tight_layout()
plt.show()
