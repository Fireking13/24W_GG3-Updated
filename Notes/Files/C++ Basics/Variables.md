
# What are Variables?

Variables are used to store data.

# Types

The following examples define a local variable and give them an initial values.

**integers** - These are whole numbers

```c++
int numberOfCoconuts = 46;
```

**float** / **double** - Fractional numbers

```c++
float timeRemaining = 4.712512f;
double moreAccurateTimeRemaining = 4.7125119191841;
```

**boolean** - true / false values

```c++
bool isOpen = true;
```

**char** - letter from a-z, A-Z, 0-9, or some other limited set of characters

```c++
char firstInitial = 'T'; // Use single quotes.
```

**[std](std.md)::string** - a consecutive block of chars

```c++
std::string name = "George"; // Use double quotes.
```

# Assignment

Variables can start with a value and that value can be changed with the **assignment operator**

```c++
int count = 0;      // count is 0.

count = 5;          // count is 5.

count = count + 3;  // count is 8.
```

# Copying Data

```c++
float litresOfGasAdded = 7.8f;

float litresOfGasPaidFor = litresOfGasAdded; // Both floats have a value of 7.8.
```

# Getting user input

```c++
int age;

cout << "Input your Age: ";
cin >> age;
```

# Doing Math with Variables

```c++
float saving = 145.75f;

float moneySpent;
cout >> "How much did you spend on groceries: ";
cin << moneySpent;

savings = savings - moneySpent;
```
