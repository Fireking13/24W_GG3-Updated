
#### Access Specifiers
- public
- protected
- private

#### Member Variables
- Should have a prefix. I like "m_"
- Should be private or protected

#### Methods
- Constructor
- Setters/Getters
- Private methods are for internal use by the class
- Public methods are for other code using the class
- Protected members are public to subclasses and private to external code

Example class definition: (in your header file)
```c++
class Player
{
public:
	Player(); // Default constructor.
	Player(int x, int y);
	void SetPosition(int x, int y);

private:
	int m_ID;
	int m_PosX;
	int m_PosY;
};
```

Example class method definitions: (in your cpp file)
```c++
Player::Player()
{
	m_Id = 0;
	m_PosX = 0;
	m_PosY = 0;
}

Player::Player(int x, int y)
{
	m_Id = 0;
	m_PosX = x;
	m_PosY = y;
}

void Player::SetPosition(int x, int y)
{
	m_Id = 0;
	m_PosX = x;
	m_PosY = y;
}
```

Example class usage
```c++
int main()
{
	Player player1; // This automatically calls Player::Player()
	Player player2( 10, 35 ); // Calls Player::Player(int x, int y);
}
```
