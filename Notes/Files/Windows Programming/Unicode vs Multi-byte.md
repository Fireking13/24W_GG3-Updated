
### String Formats

#### Ascii
- Each letter takes 1 byte
- Values 0-255

#### Unicode
- Each letter takes 2 bytes
- Values 0-65535

#### Multi-byte
- Each letter is a variable size
- If the first byte is 0-127
	- It's a letter
- If the first byte is 128-255
	- Look at the next byte to create a letter
- Some combinations require 3 bytes for a single letter