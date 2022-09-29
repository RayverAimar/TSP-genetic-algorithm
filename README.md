<div align="center">

# TSP Genetic Algorithm

The present repository stores a Genetic Algorithm implementation to find out the best path without intersections after a bunch of generations.

</div>

First of all, we have to understand every piece of the repository. In the [/src](https://github.com/RayverAimar/TSP-genetic-algorithm/tree/master/src "/src") folder, we got a [main.cpp](https://github.com/RayverAimar/TSP-genetic-algorithm/blob/master/src/main.cpp "main.cpp") which initialize the whole genome population and how many times the genetic algorithm will be used (known as "generation" per each iteration), this file include a couple of headers ([utils.h](https://github.com/RayverAimar/TSP-genetic-algorithm/blob/master/src/include/utils.h "utils.h") and [genetic.h](https://github.com/RayverAimar/TSP-genetic-algorithm/blob/master/src/include/genetic.h "genetic.h")), these headers contain useful functions about crossover population, elitism, mutation and even euclidean distance ([utils.h](https://github.com/RayverAimar/TSP-genetic-algorithm/blob/master/src/include/utils.h "utils.h")); in order to get a operational project. 

In the other hand, we've created a dataset folder where we store .csv files about the coordinates of the cities, another one of an adjacency matrix and finally,
the distances between cities, connected with each other (26) which means complexity $n^{\mathrm{2}}$.

Considering all of the files, we'll be using python [main.py](https://github.com/RayverAimar/TSP-genetic-algorithm/blob/master/src/main.py "main.py") to illustrate the results using libraries such as networkx, pandas and matplotlib.

### Install libraries 

Install them like this if you haven't before .

```
$ pip install matplotlib
$ pip install networkx
$ pip install pandas
```

### Running the project

After grasping all the files project, we'll compile and execute the C++ file:

```
$ g++ -o main.exe main.cpp
```

We have to run it as normally (by the way, this project doesn't make use of setups):

```
$ ./main.exe
```
At our console, we'll get the information such as best path length before and after the process, as well as the best genome, the means improvement and a drastic change of the best fitness value after all the generations. **BEAR IN MIND** that after executing, in the dataset folder will appear two new .csv files, one of the edges and the other one of the ordered nodes from the best path.

![Console Answer](https://i.ibb.co/RHCB1rV/execution-logs.png)

Console Answer

After that we'll run [main.py](https://github.com/RayverAimar/TSP-genetic-algorithm/blob/master/src/main.py "main.py") to get the charts:

### Running the project
```
$ ./main.py

```

On the side of graphic representation (thanks to [main.py](https://github.com/RayverAimar/TSP-genetic-algorithm/blob/master/src/main.py "main.py")) you'll get a first window of node's connections, then you'll see a second one showing the best path after the application of the Genetic Algorithm. And finally, you'll have a representation about the best genome and the means through generations.

1. First Window, the full graph.
2. Second Window, the Best Path.
3. The last Window, the chart.

![TSPGenetic Algorithm demo](https://i.ibb.co/nLBR1Bz/TSPGenetic-Algorithm-demo.gif)

---
### Contributors
- Chillitupa Quispihuanca, Alfred Addison
- Muñoz Curi, Rayver Aimar
- Gómez del Carpio, Alexander Sebastian
- Quispe Salcedo, Josep Marko

<a href="https://github.com/RayverAimar/TSP-genetic-algorithm/graphs/contributors">
  <img src="https://contrib.rocks/image?repo=RayverAimar/TSP-genetic-algorithm" />
</a>
