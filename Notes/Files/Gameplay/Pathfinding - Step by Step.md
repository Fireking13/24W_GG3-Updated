
# Step by Step example of Dijkstra's Algorithm

#### Step 1

- Give all nodes a cost of infinite
- Give the start node a cost of 0
	- i.e. Change orange: ∞ → 0

![Pathfinding-Step1](../Images/Pathfinding-Step1.png)

#### Step 2

- Pick the node with the lowest G
	- In this case: Orange

![Pathfinding-Step2](../Images/Pathfinding-Step2.png)

#### Step 3

- Calculate the neighbour G scores
	- Yellow: ∞ → 8
	- Red:    ∞ → 4
- Make neighbours point back to the active node

![Pathfinding-Step3](../Images/Pathfinding-Step3.png)

#### Step 4

- Pick the node with the lowest G
	- In this case: Red

![Pathfinding-Step4](../Images/Pathfinding-Step4.png)

#### Step 5

- Calculate the neighbour G scores
	- Yellow: 8 → 7  
	- Blue:   ∞ → 10
- Notice the arrow from yellow is now pointing to red
- Also notice we overwrite the score in yellow because the new 'G' score is lower
	- i.e. we found a better path to yellow

![Pathfinding-Step5](../Images/Pathfinding-Step5.png)

#### Step 6

- Pick the node with the lowest G
	- In this case: Yellow

![Pathfinding-Step6](../Images/Pathfinding-Step6.png)

#### Step 7

- Calculate the neighbour G scores
	- Blue:  10 → 8
	- Notice the arrow from blue is now pointing to yellow

![Pathfinding-Step7](../Images/Pathfinding-Step7.png)

#### Step 8

- Pick the node with the lowest G
	- In this case: Blue
- Since Blue is the target, we're done
- Follow the arrows back home.
- Blue → Yellow → Red → Orange

![Pathfinding-Step8](../Images/Pathfinding-Step8.png)

