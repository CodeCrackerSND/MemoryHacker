MemoryHacker:
MemoryHacker is a tool which can search for values on the target process!
You can use to search/write in the memory of a process.
Can be used for finding information for creating trainers/memory hacking.

First Select a process then do a right mouse click on it and choose "Memory hack",
A new dialog with options will come,
with search type: Full search or Custom search (Customize button),
Customize dialog contains list with Start Address/End Address
in order to perform search only on these ranges.
You can pick up a Module or a memory block.

Type combo specifies the type of variables to search
can be: byte, word, dword, qword, bytes, ASCII string, UNICODE string, float or double.

Base combo specifies the base of "Value to search",
decimal = base 10 and hexadecimal = base 16.

First time you enter "Value to search" and click on "Search" button
in order to find addresses and they will be added to list (Address/Value)

"New value" textbox is used only when you press "Patch" button,
holds the new value to be set!

They are three more options when you right click on list(Address/Value)
"Copy Selected", "Remove Selected" and "Patch Selected".

Read button will read current values of list (Address/Value).

"Remove Not Found" button will read current values of list (Address/Value)
and will remove from list (Address/Value) the ones which
are not equal with "Value to search".

"Patch" button will patch all values of list (Address/Value)
with "New value".

