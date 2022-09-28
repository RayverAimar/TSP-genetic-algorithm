# TSP-genetic-algorithm

The present repository stores a Genetic Algorithm implementation to find out the best path without intersections after a bunch of generations.

First of all, we have to understand every piece of the repository. In the 'src' folder, we got a main.cpp which initialize the whole genome population and how many times the genetic algorithm will be used (known as "generation" per each iteration), this file include a couple of headers (utils.h and genetic.h), these headers contain useful functions about crossover population, elitism, mutation and even euclidean distance (utils.h); in order to get a operational project. 

In the other hand, we've created a dataset folder where we store .csv files about the coordinates of the cities, another one of an adjacency matrix and finally,
the distances between cities, connected with each other (26) which means complexity n^2.

Considering all of the files, we'll be using python (main.py) to illustrate the results using libraries such as networkx, pandas and matplotlib.

### Install libraries 

Install them like this if you haven't before .

```
$ pip install matplotlib
```

### Running the project

After grasping all the files project, we'll compile and execute the C++ file:

```
$ g++ -o main.exe main.cpp
```

We have to run them as normally (by the way, this project doesn't make use of setups):

```
$ ./main.exe
$ ./main.py
```
At our console, we'll get the information such as best path length before and after the process, as well as the best genome, the means improvement and a drastic change of the best fitness value after all the generations. BEAR IN MIND that after executing, in the dataset folder will appear two new .csv files, one of the edges and the other one of the ordered nodes from the best path.

![Console Answer](https://media.discordapp.net/attachments/1024168441462128751/1024168686518538390/Annotation_2022-09-26_225009.png)

Console Answer

On the side of graphic representation (thanks to main.py) you'll get a first window of node's connections, then you'll see a second one showing the best path after the application of the Genetic Algorithm. And finally, you'll have a representation about the best genome and the means through generations.


![First Window, the full graph](https://media.discordapp.net/attachments/1024168441462128751/1024168657124860024/Annotation_2022-09-26_225025.png)

First Window, the full graph.

![Second Window, the Best Path](https://media.discordapp.net/attachments/1024168441462128751/1024168635159289867/Annotation_2022-09-26_225017.png)

Second Window, the Best Path.

![The last Window, the chart](https://media.discordapp.net/attachments/1024168441462128751/1024168586731847730/Annotation_2022-09-26_225031.png)

The last Window, the chart.

---
### Contributors
- Chillitupa Quispihuanca, Alfred Addison
- Muñoz Curi, Rayver Aimar
- Gómez del Carpio, Alexander Sebastian
- Quispe Salcedo, Josep Marko
<a href="https://github.com/RayverAimar/TSP-genetic-algorithm/graphs/contributors">
  <img src="https://contrib.rocks/image?repo=RayverAimar/TSP-genetic-algorithm" />
</a>
