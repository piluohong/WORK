import matplotlib.pyplot as plt
import numpy as np

# 文件路径
file_path = './traj.txt'


# 读取文件中的第2列和第3列数据
data = np.loadtxt(file_path, usecols=(1, 2))

# 提取第2列和第3列
column_2 = data[:, 0]
column_3 = data[:, 1]

plt.plot(column_2,column_3,color='r')

background_image_path = './mango.png'
background_image = plt.imread(background_image_path)
plt.imshow(background_image, extent=[min(column_2), max(column_2), min(column_3), max(column_3)])

# 添加标签和标题
plt.xlabel('Second Column')
plt.ylabel('Third Column')
plt.title('Scatter Plot of Second and Third Columns')

# 显示图形
plt.show()