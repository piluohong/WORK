import matplotlib.pyplot as plt
import numpy as np

data = []

file_names = ['./time_localmap.txt', './time_odom.txt', './time_total.txt']
for file_name in file_names:
    with open(file_name, 'r') as file:
        file_data = [float(line.strip()) for line in file]
        data.append(file_data)

labels = ['Odometry', 'Built_submap', 'Average Total time']

plt.figure(figsize=(6, 6), dpi=150)
plt.grid(True)  # Show grid
plt.boxplot(data,
            medianprops={'color': 'red', 'linewidth': 1.5},
            meanline=True,
            showmeans=True,
            meanprops={'color': 'blue', 'ls': '--', 'linewidth': 1.5},
            flierprops={"marker": "o", "markerfacecolor": "red", "markersize": 4},
            labels=labels)
# plt.yticks(np.arange(0.4, 0.81, 0.1))
plt.show()