
#### Structure
Windows messages come in 3 parts
- a message type
	- For example WM_KEYDOWN, WM_RESIZE, WM_PAINT
- 2 parameters
	- wParam and lParam
	- These have different meaning for every message type
		- Make sure you search the docs for each type you want to use

#### WM_KEYDOWN
- wParam: is the keyCode for the key pressed
	- A is 65, B is 66, etc.
	- VK_ defines can be used for special keys
		- e.g. VK_ESCAPE, VK_LEFT, VK_RIGHT
- lParam has some other info packed into the bits
	- bit 30 is the previous state of the key
	- Useful to know if the key was just pressed or was held since the last message for that key
