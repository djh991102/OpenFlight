from mpl_toolkits.basemap import Basemap
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

# Set the plot size for this notebook:
plt.rcParams["figure.figsize"] = 12, 12

# Background map
m = Basemap(llcrnrlon=-179, llcrnrlat=-60, urcrnrlon=179, urcrnrlat=70,  projection='merc')
m.drawmapboundary(fill_color='white', linewidth=0)
m.fillcontinents(color='#f2f2f2', alpha=0.7)
m.drawcoastlines(linewidth=0.1, color="green")

# cities to plot the connection
df = pd.read_csv("Path.csv")

# Plot the connection
num_of_airports = df['airport'].size
lon = df['lon']
lat = df['lat']

for i in range(1, num_of_airports):
    m.drawgreatcircle(float(lon[i-1]), float(lat[i-1]), float(lon[i]), float(lat[i]), linewidth=1, color='skyblue', alpha=0.5);

# Add city names
for i, row in df.iterrows():
    plt.annotate(row.airport, xy=m(float(row.lon)+3, float(row.lat)), verticalalignment='center')

plt.show()
