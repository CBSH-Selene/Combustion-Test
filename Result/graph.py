import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

path = '20220822_33N.csv'
data = pd.read_csv(path)

mass = data['m'] *9.8/1000

maxx = max(mass)
print(maxx)

time = []
t = 0
for i in range(42) :
    time.append(t)
    t+=0.14
    
plt.figure(figsize=(10, 8))
plt.title('t-F graph',fontsize='20')
plt.xlabel('Time(s)', fontsize='15')
plt.ylabel('Force(N)', fontsize='15')
plt.xticks(np.arange(0,7,0.5))
plt.yticks(np.arange(0,35,1))

plt.scatter(time[30],maxx,c='r',marker='x',label='MAX: 32.9N')
plt.plot(time,mass,label='F(N)')
plt.legend(fontsize='15')
plt.show()