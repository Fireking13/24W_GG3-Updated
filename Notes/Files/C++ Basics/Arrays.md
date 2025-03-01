
#### Create Array and Set some values
```c++
int main()
{
	const int c_Size = 8;
	int numbers[c_Size];

	numbers[0] = 5;
	numbers[1] = 10;
}
```

#### Pass Array to Function
```c++
int SumUpArray(int* array, int size)
{
	int sum = 0;
	for( int i=0; i<size; i++ )
	{
		sum += array[i];
	}
	return sum;
}

int main()
{
	const int c_Size = 8;
	int numbers[c_Size];
	numbers[0] = 5;
	numbers[1] = 10;

	int sum = SumUpArray( numbers, c_Size );
}
```

#### Pass Array to Function - Alternate Syntax
```c++
int SumUpArray(int[] array, int size)
{
	int sum = 0;
	for( int i=0; i<size; i++ )
	{
		sum += array[i];
	}
	return sum;
}

int main()
{
	const int c_Size = 8;
	int numbers[c_Size];
	numbers[0] = 5;
	numbers[1] = 10;

	int sum = SumUpArray( numbers, c_Size );
}
```
