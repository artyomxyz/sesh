#SESH
*sesh* is a copy of a Unix shell - it is a command-line interpreter that provides a traditional user interface for the Unix and Unix-like operating systems.

#COMMANDS
There are implemented such commands, as:
| Command | Keys (No key, if the field is empty) |Description |
|-------|--|------|
cd | |Changes Directory to dirname
cd | _**..**_ |Returns to the previous Directory
cd | _**some_directory**_ |   Changes current Directory to _**some_directory**_, situated in current
cd | _**/some_directory**_ |  Changes current Directory to root _**some directory**_
ls| | Shows the list of files and directories in current directory
ls | _**some_directory**_ |   Show the list of files and directories in _**current_directory/some_directory/**_
ls | _**/some_directory**_ |  Show the list of files and directories in root _**some directory**_
filename| | Opens file with name _**filename**_, situated in current directory
exit| |Quit the sesh
help| |Shows full information about available commands
history| |Shows history of previously inputted commands 

* For user convenience there is a _**navigation through the history**_. 
	You can use _**UP ARROW KEY**_ to iterate through previous commands and _**DOWN ARROW KEY**_  to scroll the history down.
* Also there is one more useful feature - _**autocompleting**_. It helps to type necessary arguments for commands more quick.
	- After typing the command just begin to write a name of file or directory and press _**TAB KEY**_ - and you will see the list of files/directories which have the same beginning as we began to type.
	- If there are several suitable options, you will see a list of these options. You may continue to type from the same place where you pressed _**TAB**_.
	- If there is the only option, then after pressing _**TAB**_ **sesh** will complete the line up of this option and offers to enter.
	- If there is no alternative, then the program offers to type from the same place.
* If you failed in typing, you can just delete incorrect symbols by moving the cursor with _**LEFT ARROW KEY**_ and _**RIGHT ARROW KEY**_ and then by using _**BACKSPACE KEY**_.	

 	

