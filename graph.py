import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns
import numpy as np

# Load and filter data
df = pd.read_csv('algorithm_metrics.csv')
quick_sort_data = df[
    (df['Algorithm'] != 'HeapSort') &
    (df['Algorithm'] != 'InsertionSort') &
    (df['Algorithm'] != 'QuickSortŚrodek') &
    (df['Algorithm'] != 'QuickSortPierwszy') &
    (df['Algorithm'] != 'QuickSortOstatni') &
    # (df['Algorithm'] != 'QuickSortLosowy') &
    (df['Algorithm'] != 'QuickSortDouble') &
    (df['Algorithm'] != 'ShellSortSedgewicka') &
    (df['Algorithm'] != 'ShellSortIncerpiego-Sedgewicka') &
    (df['Data_Type'] == 'G')
].sort_values('Size')

# Create plot
plt.figure(figsize=(14, 8))
sns.set_style("whitegrid")
palette = sns.color_palette("husl", n_colors=len(quick_sort_data['Algorithm'].unique()))

# Calculate positions and offsets
sizes = quick_sort_data['Size'].unique()
n_algorithms = len(quick_sort_data['Algorithm'].unique())
width = 1  # Width of each "box" group

for idx, (algo_name, algo_data) in enumerate(quick_sort_data.groupby('Algorithm')):
    # Base x positions (0, 1, 2, ... for sizes)
    x_pos = np.arange(len(sizes))
    
    # Convert time values to milliseconds
    avg_ms = algo_data['Avg'] * 1000
    std_dev_ms = algo_data['Std_Dev'] * 1000
    min_ms = algo_data['Min'] * 1000
    max_ms = algo_data['Max'] * 1000
    
    # Box dimensions in milliseconds
    box_top = avg_ms + std_dev_ms
    box_bottom = avg_ms - std_dev_ms
    
    # Plot bars (std-dev boxes)
    plt.bar(x_pos, height=box_top - box_bottom, width=.25,
            bottom=box_bottom, color=palette[idx], alpha=0.6, label=algo_name)
    
    # Whiskers (min/max)
    plt.vlines(x_pos, min_ms, max_ms, colors=palette[idx], linewidths=2, alpha=0.8)
    
    # Median line (average)
    plt.hlines(avg_ms, x_pos - .1, x_pos + .1, colors='white', linewidths=2)
    
    # Dashed line connecting averages
    plt.plot(x_pos, avg_ms, color=palette[idx], linewidth=2, alpha=0.8, linestyle='--')


# Configure axes and labels
plt.xticks(np.arange(len(sizes)), sizes, fontsize=18)
plt.yticks(fontsize=18)
plt.xlabel('Rozmiar Tablic', fontsize=20)
plt.ylabel('Czas (millisekundy)', fontsize=20)
plt.legend(
    title='Algorytmy',
    title_fontsize='20',  # Legend title size
    fontsize='18',        # Legend item text size
    bbox_to_anchor=(0.5, -0.1),
    loc='upper center',
    ncol=4,
    frameon=True
)
plt.subplots_adjust(bottom=0.25)
plt.tight_layout()
plt.subplots_adjust(
    left=0.043,     # Space from left edge of window to plot
    right=0.992,    # Space from right edge of window to plot
    bottom=0.192,   # Space from bottom edge (adjust if legend is cut off)
    top=0.986       # Space from top edge
)
plt.show()
