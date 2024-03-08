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
            showmeans=True,
            meanprops={'color': 'blue', 'ls': '--', 'linewidth': 1.5},
            flierprops={"marker": "o", "markerfacecolor": "red", "markersize": 4},
            labels=labels,showfliers=False)

plt.setp(plt.gca().get_xticklabels(), fontsize=8)
plt.yticks(np.arange(0,50, 5),fontsize=8)
plt.rcParams['font.sans-serif'] = ['Ariel']
plt.title("Time Cost in Mango Orchard Dataset",fontsize=8)
plt.ylabel("Cost Time(ms)",fontsize=8)
plt.savefig('timecost.png', dpi = 600)
plt.show()
print("保存.png")
