#break
#### For Loop

```c++
for( int i=0; i<size; i++ )
{
	sum += array[i];
}
```

#### While Loop

```c++
while( true )
{
	if( someCondition == true )
	{
		break;
	}
}
```

```c++
int timesToLoop = 5;
while( timesToLoop > 0 )
{
	printf( "We will hit this line %d more times.", timesToLoop - 1 );
	timesToLoop--;
}
```

#### Do/While Loop

```c++
do
{
	// Do stuff.
} while( someCondition == true )
```

#### Range-based Loop

```c++
int total = 0;
std::vector<int> numbers = { 1, 2, 3, 4, 5 }

for( int num : numbers )
{
	total += num;
}
```

#### Iterator-based Loop
```c++
int total = 0;
std::vector<int> numbers = { 1, 2, 3, 4, 5 }

for( std::vector<int>::iterator& it = numbers.begin(); it != numbers.end(); it++ )
{
	total += *it;
}
```
