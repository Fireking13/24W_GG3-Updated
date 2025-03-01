
#### Usage

Can be used as a sanity check to see if values passed as parameters are valid

```c++
#include <assert.h>

void Inventory::DropItem(int itemNumber)
{
	assert( itemNumber < m_NumberOfItemsHeld );

	// Code to drop item.
}
```
