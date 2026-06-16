import matplotlib.pyplot as plt

# Data
labels = ["Serial", "OpenMP"]
times = [11.7775, 3.8078]

# Create bar chart
plt.bar(labels, times)

plt.title("Heat Diffusion Performance Comparison")
plt.ylabel("Time (seconds)")

# show values فوق الأعمدة
for i, v in enumerate(times):
    plt.text(i, v + 0.2, str(round(v, 2)), ha='center')

plt.show()