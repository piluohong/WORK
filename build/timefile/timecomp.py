import matplotlib.pyplot as plt
import numpy as np

data = []

file_names = ['../t_odom.txt', '../t_submap.txt', '../t_total.txt']
for file_name in file_names:
    with open(file_name, 'r') as file:
        file_data = [float(line.strip()) for line in file]
        data.append(file_data)

labels = ['Odometry', 'Built_submap', 'Total']

plt.figure(figsize=(4,3), dpi=150)
plt.grid(True)  # Show grid
plt.boxplot(data,
            medianprops={'color': 'red', 'linewidth': 1.5},
            meanline=True,
            showmeans=False,
            meanprops={'color': 'blue', 'ls': '--', 'linewidth': 1.5},
            flierprops={"marker": "o", "markerfacecolor": "red", "markersize": 4},
            labels=labels,showfliers=False)
# plt.yticks(np.arange(0.4, 0.81, 0.1))
plt.rcParams['font.sans-serif'] = ['Times New Roman']
plt.title("Time Cost in Mixture Scene Dataset")
plt.ylabel("Cost Time(ms)")
plt.savefig('timecost.png', dpi = 600)
plt.show()
