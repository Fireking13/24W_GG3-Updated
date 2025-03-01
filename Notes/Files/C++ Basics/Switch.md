#break 

```c++
enum class Color
{
	Red,
	Green,
	Blue,
	Purple,
	Magenta,
	Yellow,
};

Color playerColor = Color::Red;

switch( playerColor )
{
case Red:
	cout << "The player is RED!!!";
	break;
case Green:
	cout << "The player is GREEN!!!";
	break;
case Blue:
	cout << "The player is BLUE!!!";
	break;
case Purple:
case Magenta:
	cout << "The player is either PURPLE or MAGENTA!!!";
	break;
default:
	assert( false );
	break;
}
```
