import yaml
from geopy.geocoders import Nominatim
from geopy.distance import vincenty

data = yaml.load(file('tsp.yaml'))
geolocator = Nominatim()
geo = [geolocator.geocode(city, timeout=10) for city in data['cities']]

for i,src in enumerate(geo):
    data[i] = [int(vincenty(src.point,dst.point).km) for dst in geo]

with open('tsp.yaml', 'w') as f:
    yaml.dump(data, f)
